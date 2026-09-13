#include "ImGuiMenu.h"
#include "Includes/Logger.h"
#include "Dobby/dobby.h"

// Globals
bool g_ImGuiInitialized = false;
EGLDisplay g_EglDisplay = EGL_NO_DISPLAY;
EGLSurface g_EglSurface = EGL_NO_SURFACE;
EGLContext g_EglContext = EGL_NO_CONTEXT;
bool g_MenuOpen = true;

EGLBoolean (*orig_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface) = nullptr;
EGLBoolean (*orig_eglSwapBuffers_Real)(EGLDisplay dpy, EGLSurface surface) = nullptr;
EGLBoolean (*orig_eglSwapBuffers_Offset)(EGLDisplay dpy, EGLSurface surface) = nullptr;
__int64 (*orig_renderer)(__int64 *ConfigAttrib, int a2) = nullptr;
int32_t (*orig_onInputEvent)(struct android_app* app, AInputEvent* event) = nullptr;
int (*orig_AInputQueue_getEvent)(AInputQueue* queue, AInputEvent** outEvent) = nullptr;

static bool g_InputHookInstalled = false;
static bool g_EglHookInstalled = false;
static bool g_EglRealHookInstalled = false;
static int g_MenuTab = 0; // 0=ESP, 1=Aim, 2=Memory, 3=Items, 4=Settings

// Reentrancy guard to avoid double RenderImGui when wrapper calls real eglSwapBuffers
static thread_local int g_SwapDepth = 0;
static thread_local bool g_InEglSwap = false;

// Style setup
static void SetupImGuiStyle() {
    ImGuiStyle &style = ImGui::GetStyle();
    ImGui::StyleColorsDark();

    style.WindowPadding = ImVec2(7, 7);
    style.WindowRounding = 8.0f;
    style.FramePadding = ImVec2(4, 4);
    style.FrameRounding = 5.5f;
    style.FrameBorderSize = 1.0f;
    style.WindowBorderSize = 0.0f;
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    style.GrabRounding = 6.0f;
    style.ScrollbarRounding = 6.0f;

    ImVec4* colors = style.Colors;
    colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.12f, 0.94f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.09f, 0.20f, 0.35f, 0.00f);
    colors[ImGuiCol_Border] = ImVec4(0.39f, 0.39f, 0.39f, 0.78f);
    colors[ImGuiCol_Header] = ImVec4(0.20f, 0.25f, 0.40f, 0.55f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.35f, 0.55f, 0.80f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.30f, 0.50f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.20f, 0.30f, 0.50f, 0.60f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.30f, 0.40f, 0.65f, 0.80f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.25f, 0.35f, 0.60f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.40f, 0.70f, 1.00f, 1.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.20f, 0.22f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.30f, 0.30f, 0.35f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.25f, 0.35f, 0.55f, 1.00f);

    float scale = 1.0f;
    if (density > 0) {
        scale = density / 160.0f;
        if (scale < 1.0f) scale = 1.0f;
        if (scale > 3.5f) scale = 3.5f;
        scale *= 0.65f;
    } else {
        if (glHeight > 0) {
            scale = glHeight / 1080.0f;
            if (scale < 1.0f) scale = 1.0f;
            if (scale > 2.5f) scale = 2.5f;
        }
    }
    style.ScaleAllSizes(scale);
    ImGuiIO &io = ImGui::GetIO();
    io.FontGlobalScale = scale * 0.9f;
}

bool InitImGui(EGLDisplay dpy, EGLSurface surface, ANativeWindow* window) {
    if (g_ImGuiInitialized) return true;
    if (dpy == EGL_NO_DISPLAY || surface == EGL_NO_SURFACE) return false;
    EGLContext ctx = eglGetCurrentContext();
    if (ctx == EGL_NO_CONTEXT) return false;
    if (!window) return false;

    g_EglDisplay = dpy;
    g_EglSurface = surface;
    g_EglContext = ctx;

    LOGI("ImGui Menu Init: dpy=%p surface=%p ctx=%p window=%p w=%d h=%d density=%.0f", dpy, surface, ctx, window, glWidth, glHeight, density);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.DisplaySize = ImVec2((float)glWidth, (float)glHeight);
    io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
    io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
    io.IniFilename = nullptr;

    SetupImGuiStyle();

    bool androidInit = ImGui_ImplAndroid_Init(window);
    LOGI("ImGui_ImplAndroid_Init ret=%d", androidInit);
    // Force #version 100 for max compatibility, fallback to 300 es
    bool glInit100 = ImGui_ImplOpenGL3_Init("#version 100");
    LOGI("ImGui_ImplOpenGL3_Init #100 ret=%d", glInit100);
    if (!glInit100) {
        bool glInit300 = ImGui_ImplOpenGL3_Init("#version 300 es");
        LOGI("ImGui_ImplOpenGL3_Init #300 es ret=%d", glInit300);
    }

    g_ImGuiInitialized = true;

    if (!g_InputHookInstalled && g_App) {
        orig_onInputEvent = g_App->onInputEvent;
        g_App->onInputEvent = hook_onInputEvent;
        g_InputHookInstalled = true;
        LOGI("ImGui input hook installed with scale handling");
    }

    LOGI("ImGui Menu Initialized - ESP still via DrawHUD");
    return true;
}

void ShutdownImGui() {
    if (!g_ImGuiInitialized) return;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplAndroid_Shutdown();
    ImGui::DestroyContext();
    g_ImGuiInitialized = false;
    g_EglDisplay = EGL_NO_DISPLAY;
    g_EglSurface = EGL_NO_SURFACE;
    g_EglContext = EGL_NO_CONTEXT;
}

int32_t hook_onInputEvent(struct android_app* app, AInputEvent* event) {
    if (g_ImGuiInitialized && event) {
        float sx = 1.0f, sy = 1.0f;
        if (glWidth > 0 && screenWidth > 0) sx = (float)screenWidth / (float)glWidth;
        if (glHeight > 0 && screenHeight > 0) sy = (float)screenHeight / (float)glHeight;
        ImVec2 scale = ImVec2(sx, sy);
        bool handled = ImGui_ImplAndroid_HandleInputEvent(event, scale);
        ImGuiIO &io = ImGui::GetIO();
        if (g_MenuOpen && handled && io.WantCaptureMouse) {
            return 1;
        }
    }
    if (orig_onInputEvent) {
        return orig_onInputEvent(app, event);
    }
    return 0;
}

int hook_AInputQueue_getEvent(AInputQueue* queue, AInputEvent** outEvent) {
    int result = -1;
    if (orig_AInputQueue_getEvent) {
        result = orig_AInputQueue_getEvent(queue, outEvent);
    }
    if (result >= 0 && outEvent && *outEvent && g_ImGuiInitialized) {
        float sx = 1.0f, sy = 1.0f;
        if (glWidth > 0 && screenWidth > 0) sx = (float)screenWidth / (float)glWidth;
        if (glHeight > 0 && screenHeight > 0) sy = (float)screenHeight / (float)glHeight;
        ImVec2 scale = ImVec2(sx, sy);
        ImGui_ImplAndroid_HandleInputEvent(*outEvent, scale);
    }
    return result;
}

void DrawMenu() {
    static int drawCount = 0;
    drawCount++;
    if (drawCount < 10 || drawCount % 100 == 0) {
        LOGI("[ImGui] DrawMenu count %d tab=%d open=%d", drawCount, g_MenuTab, g_MenuOpen);
    }

    // Red rect test - use ForegroundDrawList to be on top, and also Background
    if (drawCount <= 20) {
        ImDrawList* fg = ImGui::GetForegroundDrawList();
        if (fg) {
            fg->AddRectFilled(ImVec2(0, 0), ImVec2(800, 800), IM_COL32(255, 0, 0, 255));
            fg->AddText(ImVec2(20, 20), IM_COL32(255, 255, 255, 255), "SANKE TEST - FOREGROUND RED 800x800");
        }
        ImDrawList* bg = ImGui::GetBackgroundDrawList();
        if (bg) {
            bg->AddRectFilled(ImVec2(100, 100), ImVec2(600, 600), IM_COL32(0, 255, 0, 200));
            bg->AddText(ImVec2(110, 110), IM_COL32(255, 255, 255, 255), "SANKE TEST - BACKGROUND GREEN 500x500");
        }
    }

    if (!g_MenuOpen) {
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(200, 80), ImGuiCond_Always);
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_AlwaysAutoResize;
        ImGui::Begin("##ToggleMenu", nullptr, flags);
        ImGui::Text("MENU HIDDEN");
        if (ImGui::Button("Show Menu", ImVec2(180, 50))) {
            g_MenuOpen = true;
        }
        ImGui::End();
        return;
    }

    ImGuiIO &io = ImGui::GetIO();
    // Force visible position 0,0 for debugging
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
    char titleBuf[128];
    sprintf(titleBuf, "SANKE MENU DEBUG FPS %.1f - SHOULD BE VISIBLE AT 0,0", io.Framerate);
    ImGuiWindowFlags mainFlags = ImGuiWindowFlags_NoScrollbar;

    if (ImGui::Begin(titleBuf, &g_MenuOpen, mainFlags)) {
        ImGui::Text("IF YOU SEE THIS, MENU WORKS! w=%d h=%d", glWidth, glHeight);
        ImGui::Text("Density %.0f", density);
        ImGui::Separator();
        if (ImGui::Button("Close Menu", ImVec2(200, 50))) g_MenuOpen = false;
        ImGui::SameLine();
        if (ImGui::Button("Test Button", ImVec2(200, 50))) {
            LOGI("[ImGui] Test button clicked");
        }
        ImGui::Separator();

        ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.6f);
        ImGui::PushStyleColor(ImGuiCol_Border, ImColor(100, 100, 100, 200).Value);
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImColor(9, 36, 89, 0).Value);
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0.0f);
        ImGui::BeginChild("left", ImVec2(170, 0), true);
        ImGui::PopStyleVar(2);
        ImGui::PopStyleColor(2);

        if (ImGui::Button("Player ESP", ImVec2(150, 40))) g_MenuTab = 0;
        if (ImGui::Button("Aimbot", ImVec2(150, 40))) g_MenuTab = 1;
        if (ImGui::Button("Bullet Track", ImVec2(150, 40))) g_MenuTab = 2;
        if (ImGui::Button("Memory", ImVec2(150, 40))) g_MenuTab = 3;
        if (ImGui::Button("Items", ImVec2(150, 40))) g_MenuTab = 4;
        if (ImGui::Button("Settings", ImVec2(150, 40))) g_MenuTab = 5;

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        if (ImGui::Button("Close Menu", ImVec2(150, 30))) g_MenuOpen = false;

        ImGui::EndChild();
        ImGui::SameLine();

        ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.6f);
        ImGui::PushStyleColor(ImGuiCol_Border, ImColor(100, 100, 100, 200).Value);
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImColor(9, 36, 89, 0).Value);
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0.0f);
        ImGui::BeginChild("mainchild", ImVec2(0, 0), true);
        ImGui::PopStyleVar(2);
        ImGui::PopStyleColor(2);

        if (g_MenuTab == 0) {
            ImGui::Text("ESP - Uses DrawHUD (not ImGui drawlist)");
            ImGui::Separator();
            ImGui::Checkbox("Line", &Cheat::Esp::Line);
            ImGui::Checkbox("Box", &Cheat::Esp::Box);
            ImGui::Checkbox("Skeleton", &Cheat::Esp::Skeleton);
            ImGui::Checkbox("Health", &Cheat::Esp::Health);
            ImGui::Checkbox("Name", &Cheat::Esp::Name);
            ImGui::Checkbox("Distance", &Cheat::Esp::Distance);
            ImGui::Checkbox("Counter", &Cheat::Esp::Counter);
            ImGui::Checkbox("Target Line", &Cheat::Esp::Target);
            ImGui::Checkbox("Vehicle Name", &Cheat::Esp::Vehicle::Name);
            ImGui::Checkbox("LootBox", &Cheat::Esp::LootBox);
            ImGui::Checkbox("Throwable (Nade)", &Cheat::Esp::Throwable);
            ImGui::Separator();
            ImGui::Text("FOV Circle (HUD)");
            ImGui::Checkbox("Show FOV Circle", &Cheat::FOV::ShowCircle);
            ImGui::ColorEdit4("Circle Color", (float*)&Cheat::FOV::CircleColor);
        } else if (g_MenuTab == 1) {
            ImGui::Text("Aimbot - Uses DrawMemory aim");
            ImGui::Separator();
            ImGui::Checkbox("Aimbot Enable", &Cheat::Aimbot::Enable);
            ImGui::Separator();
            ImGui::Text("Aim Mode");
            bool isFOV = Cheat::FOV::Enable;
            bool is180 = !Cheat::FOV::Enable;
            if (ImGui::RadioButton("FOV", isFOV)) Cheat::FOV::Enable = true;
            ImGui::SameLine();
            if (ImGui::RadioButton("180°", is180)) Cheat::FOV::Enable = false;
            if (Cheat::FOV::Enable) {
                if (ImGui::SliderFloat("FOV Radius", &Cheat::FOV::Radius, 50.0f, 1000.0f, "%.0f")) {
                    Cheat::Aimbot::Radius = Cheat::FOV::Radius;
                    Cheat::Aimbot::Fov = Cheat::FOV::Radius;
                    Cheat::BulletTrack::Radius = Cheat::FOV::Radius;
                    Cheat::BulletTrack::Fov = Cheat::FOV::Radius;
                }
            }
            ImGui::SliderFloat("Recoil", &Cheat::Aimbot::Recoil, 0.0f, 5.0f, "%.2f");
            ImGui::SliderFloat("RecoilSet", &Cheat::Aimbot::RecoilSet, 0.0f, 5.0f, "%.2f");
            ImGui::SliderFloat("Range", &Cheat::Aimbot::Range, 0.0f, 1000.0f, "%.0f");
            ImGui::Separator();
            ImGui::Text("Shared Target Checks");
            bool vis = Cheat::Aimbot::VisCheck;
            if (ImGui::Checkbox("VisCheck (Shared)", &vis)) {
                Cheat::Aimbot::VisCheck = vis;
                Cheat::BulletTrack::VisCheck = vis;
            }
            bool knock = Cheat::Aimbot::IgnoreKnock;
            if (ImGui::Checkbox("Ignore Knock (Shared)", &knock)) {
                Cheat::Aimbot::IgnoreKnock = knock;
                Cheat::BulletTrack::IgnoreKnock = knock;
            }
            bool bot = Cheat::Aimbot::IgnoreBot;
            if (ImGui::Checkbox("Ignore Bot (Shared)", &bot)) {
                Cheat::Aimbot::IgnoreBot = bot;
                Cheat::BulletTrack::iGnoreBot = bot;
            }
            ImGui::Separator();
            ImGui::Text("FOV Circle");
            ImGui::Checkbox("Show Circle", &Cheat::FOV::ShowCircle);
            ImGui::ColorEdit4("Circle Color", (float*)&Cheat::FOV::CircleColor);
        } else if (g_MenuTab == 2) {
            ImGui::Text("Bullet Track - Magic Bullet");
            ImGui::Separator();
            ImGui::Checkbox("Bullet Track", &Cheat::BulletTrack::Enable);
            ImGui::Separator();
            ImGui::Text("Aim Mode");
            bool isFOV = Cheat::FOV::Enable;
            bool is180 = !Cheat::FOV::Enable;
            if (ImGui::RadioButton("FOV", isFOV)) Cheat::FOV::Enable = true;
            ImGui::SameLine();
            if (ImGui::RadioButton("180°", is180)) Cheat::FOV::Enable = false;
            if (Cheat::FOV::Enable) {
                if (ImGui::SliderFloat("FOV Radius", &Cheat::FOV::Radius, 50.0f, 1000.0f, "%.0f")) {
                    Cheat::Aimbot::Radius = Cheat::FOV::Radius;
                    Cheat::Aimbot::Fov = Cheat::FOV::Radius;
                    Cheat::BulletTrack::Radius = Cheat::FOV::Radius;
                    Cheat::BulletTrack::Fov = Cheat::FOV::Radius;
                }
            }
            ImGui::SliderFloat("Range", &Cheat::BulletTrack::Range, 0.0f, 600.0f, "%.0f");
            ImGui::Separator();
            ImGui::Text("Hit Target (Head / Body)");
            int hitTarget = Cheat::BulletTrack::HitTarget;
            if (ImGui::RadioButton("Head", hitTarget == 0)) {
                Cheat::BulletTrack::HitTarget = 0;
                Cheat::BulletTrack::HitWhere = false;
            }
            ImGui::SameLine();
            if (ImGui::RadioButton("Body", hitTarget == 1)) {
                Cheat::BulletTrack::HitTarget = 1;
                Cheat::BulletTrack::HitWhere = true;
            }
            ImGui::Separator();
            ImGui::Text("Adjust Accuracy - 3 Modes");
            int acc = Cheat::BulletTrack::AccuracyMode;
            if (ImGui::RadioButton("1 Bullet / 3 (skip 2)", acc == 0)) {
                Cheat::BulletTrack::AccuracyMode = 0;
                Cheat::BulletTrack::HitChance = false;
                Cheat::BulletTrack::SBullet = false;
            }
            if (ImGui::RadioButton("2 Bullets / 3 (skip 1)", acc == 1)) {
                Cheat::BulletTrack::AccuracyMode = 1;
                Cheat::BulletTrack::HitChance = false;
                Cheat::BulletTrack::SBullet = true;
            }
            if (ImGui::RadioButton("Full Track - Every Bullet", acc == 2)) {
                Cheat::BulletTrack::AccuracyMode = 2;
                Cheat::BulletTrack::HitChance = true;
                Cheat::BulletTrack::SBullet = true;
            }
            ImGui::Separator();
            ImGui::Text("Shared Target Checks");
            bool vis = Cheat::BulletTrack::VisCheck;
            if (ImGui::Checkbox("Visibility Check (Shared)", &vis)) {
                Cheat::BulletTrack::VisCheck = vis;
                Cheat::Aimbot::VisCheck = vis;
            }
            bool knock = Cheat::BulletTrack::IgnoreKnock;
            if (ImGui::Checkbox("Ignore Knocked (Shared)", &knock)) {
                Cheat::BulletTrack::IgnoreKnock = knock;
                Cheat::Aimbot::IgnoreKnock = knock;
            }
            bool bot = Cheat::BulletTrack::iGnoreBot;
            if (ImGui::Checkbox("Ignore Bot (Shared)", &bot)) {
                Cheat::BulletTrack::iGnoreBot = bot;
                Cheat::Aimbot::IgnoreBot = bot;
            }
            ImGui::Separator();
            ImGui::Text("FOV Circle");
            ImGui::Checkbox("Show Circle", &Cheat::FOV::ShowCircle);
            ImGui::ColorEdit4("Circle Color", (float*)&Cheat::FOV::CircleColor);
        } else if (g_MenuTab == 3) {
            ImGui::Text("Memory Features - Wide/FPS removed");
            ImGui::Separator();
            ImGui::Checkbox("Small Crosshair / No Recoil", &Cheat::Memory::Small);
            ImGui::Checkbox("Hit Effect", &Cheat::Memory::Hit);
            ImGui::Checkbox("Show Damage", &Cheat::Memory::ShowDamage);
            ImGui::Text("Wide/FPS functions removed as requested");
        } else if (g_MenuTab == 4) {
            ImGui::Text("Item ESP");
            ImGui::Separator();
            if (ImGui::Button("Enable All")) {
                for (auto &p : Items) p.second = true;
            }
            ImGui::SameLine();
            if (ImGui::Button("Disable All")) {
                for (auto &p : Items) p.second = false;
            }
            ImGui::Separator();
            ImGui::BeginChild("##ItemList", ImVec2(0, 0), true);
            int idx = 0;
            for (auto &cat : items_data) {
                std::string catName = cat["CategoryName"].is_string() ? cat["CategoryName"].get<std::string>() : "Category";
                if (ImGui::CollapsingHeader(catName.c_str())) {
                    for (auto &it : cat["Items"]) {
                        int id = it["itemId"].get<int>();
                        std::string name = it["itemName"].get<std::string>();
                        bool enabled = Items[id];
                        std::string label = name + "##" + std::to_string(id) + "_" + std::to_string(idx++);
                        if (ImGui::Checkbox(label.c_str(), &enabled)) {
                            Items[id] = enabled;
                        }
                    }
                }
            }
            ImGui::EndChild();
        } else if (g_MenuTab == 5) {
            ImGui::Text("Info");
            ImGui::Separator();
            ImGui::Text("Screen: %d x %d", glWidth, glHeight);
            ImGui::Text("Window: %d x %d", screenWidth, screenHeight);
            ImGui::Text("Density: %.0f", density);
            ImGui::Text("Menu: ImGui only, ESP via HUD");
            ImGui::Text("Hooks: ShadowHook-only offsets");
            ImGui::Text("ReceiveDrawHUD 0xafc6044, eglSwapBuffers 0xD495D50");
            ImGui::Text("AInputQueue 0xD494B60, ShootBulletInner 0x6ff841c");
        }

        ImGui::EndChild();
    }
    ImGui::End();
}

void RenderImGui() {
    if (!g_ImGuiInitialized) return;
    if (g_EglDisplay == EGL_NO_DISPLAY) return;
    if (glWidth <= 0 || glHeight <= 0) return;

    static int frameCount = 0;
    frameCount++;
    if (frameCount < 20 || frameCount % 50 == 0) {
        LOGI("[ImGui] RenderImGui frame %d g_MenuOpen=%d w=%d h=%d dpy=%p surf=%p", frameCount, g_MenuOpen, glWidth, glHeight, g_EglDisplay, g_EglSurface);
    }

    ImGuiIO &io = ImGui::GetIO();
    io.DisplaySize = ImVec2((float)glWidth, (float)glHeight);
    io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);

    // Make sure context is current
    if (g_EglDisplay != EGL_NO_DISPLAY && g_EglSurface != EGL_NO_SURFACE && g_EglContext != EGL_NO_CONTEXT) {
        eglMakeCurrent(g_EglDisplay, g_EglSurface, g_EglSurface, g_EglContext);
    }

    while (glGetError() != GL_NO_ERROR) {}

    // Backup GL state that might clip ImGui
    GLboolean scissorEnabled = glIsEnabled(GL_SCISSOR_TEST);
    GLboolean depthEnabled = glIsEnabled(GL_DEPTH_TEST);
    GLboolean stencilEnabled = glIsEnabled(GL_STENCIL_TEST);
    GLboolean cullEnabled = glIsEnabled(GL_CULL_FACE);
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    if (scissorEnabled) glDisable(GL_SCISSOR_TEST);
    if (depthEnabled) glDisable(GL_DEPTH_TEST);
    if (stencilEnabled) glDisable(GL_STENCIL_TEST);
    if (cullEnabled) glDisable(GL_CULL_FACE);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(glWidth, glHeight);
    ImGui::NewFrame();

    DrawMenu();

    ImGui::Render();
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    GLboolean blendWasEnabled = glIsEnabled(GL_BLEND);
    if (!blendWasEnabled) glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_SCISSOR_TEST);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    if (!blendWasEnabled) glDisable(GL_BLEND);

    // Restore
    if (scissorEnabled) glEnable(GL_SCISSOR_TEST);
    if (depthEnabled) glEnable(GL_DEPTH_TEST);
    if (stencilEnabled) glEnable(GL_STENCIL_TEST);
    if (cullEnabled) glEnable(GL_CULL_FACE);
    glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        LOGI("[ImGui] GL error after RenderDrawData: 0x%x frame=%d", err, frameCount);
    }
}

// Core logic shared by both hooks - returns true if should call orig after
static int g_SwapCount = 0;
static bool CommonEglSwapPre(EGLDisplay dpy, EGLSurface surface, bool afterOrig) {
    eglQuerySurface(dpy, surface, EGL_WIDTH, &glWidth);
    eglQuerySurface(dpy, surface, EGL_HEIGHT, &glHeight);

    if (glWidth <= 0 || glHeight <= 0) return false;
    if (!g_App) return false;

    if (!g_InputHookInstalled) InstallInputHooks();

    if (g_App->window) {
        screenWidth = ANativeWindow_getWidth(g_App->window);
        screenHeight = ANativeWindow_getHeight(g_App->window);
    }
    if (g_App->config) {
        density = AConfiguration_getDensity(g_App->config);
    }

    if (!afterOrig) {
        g_SwapCount++;
        LOGI("[ImGui] eglSwapBuffers count=%d dpy=%p surf=%p w=%d h=%d init=%d depth=%d afterOrig=%d", g_SwapCount, dpy, surface, glWidth, glHeight, g_ImGuiInitialized, g_SwapDepth, afterOrig);
        if (!g_ImGuiInitialized) {
            EGLContext ctx = eglGetCurrentContext();
            if (ctx != EGL_NO_CONTEXT && g_App->window) {
                InitImGui(dpy, surface, g_App->window);
            }
        } else {
            if (dpy != g_EglDisplay || surface != g_EglSurface) {
                g_EglDisplay = dpy;
                g_EglSurface = surface;
                g_EglContext = eglGetCurrentContext();
            }
            // Render BEFORE swap - standard ImGui hook pattern
            if (g_SwapDepth <= 1) {
                RenderImGui();
            }
        }
    } else {
        // After orig - only for first frame init case, ensure we rendered at least once
        if (g_ImGuiInitialized && g_SwapCount == 1) {
            // First frame was init only, no render before - render now for next buffer
            // But to avoid double render corruption, we already rendered in afterOrig previously, now we skip
            // Actually we want to ensure first frame also shows menu, so render again if needed
            // We'll not render here to avoid double render after swap which caused hang
        }
    }
    return true;
}

EGLBoolean hook_eglSwapBuffers_Offset(EGLDisplay dpy, EGLSurface surface) {
    g_SwapDepth++;
    g_InEglSwap = true;
    if (g_SwapDepth > 1) {
        LOGI("[ImGui] offset hook reentrant depth=%d, calling orig directly", g_SwapDepth);
        EGLBoolean res = EGL_FALSE;
        if (orig_eglSwapBuffers_Offset) res = orig_eglSwapBuffers_Offset(dpy, surface);
        else if (orig_eglSwapBuffers) res = orig_eglSwapBuffers(dpy, surface);
        g_SwapDepth--;
        if (g_SwapDepth == 0) g_InEglSwap = false;
        return res;
    }
    // Before orig - init + render
    CommonEglSwapPre(dpy, surface, false);
    EGLBoolean res = EGL_FALSE;
    if (orig_eglSwapBuffers_Offset) res = orig_eglSwapBuffers_Offset(dpy, surface);
    else if (orig_eglSwapBuffers) res = orig_eglSwapBuffers(dpy, surface);
    // After orig - no render to avoid hang, just log
    // CommonEglSwapPre(dpy, surface, true);
    g_SwapDepth--;
    if (g_SwapDepth == 0) g_InEglSwap = false;
    if (g_SwapCount < 20) LOGI("[ImGui] offset hook after orig res=%d count=%d depth=%d", res, g_SwapCount, g_SwapDepth);
    return res;
}

EGLBoolean hook_eglSwapBuffers_Real(EGLDisplay dpy, EGLSurface surface) {
    g_SwapDepth++;
    g_InEglSwap = true;
    if (g_SwapDepth > 1) {
        LOGI("[ImGui] real hook reentrant depth=%d, calling orig directly", g_SwapDepth);
        EGLBoolean res = EGL_FALSE;
        if (orig_eglSwapBuffers_Real) res = orig_eglSwapBuffers_Real(dpy, surface);
        else if (orig_eglSwapBuffers) res = orig_eglSwapBuffers(dpy, surface);
        g_SwapDepth--;
        if (g_SwapDepth == 0) g_InEglSwap = false;
        return res;
    }
    CommonEglSwapPre(dpy, surface, false);
    EGLBoolean res = EGL_FALSE;
    if (orig_eglSwapBuffers_Real) res = orig_eglSwapBuffers_Real(dpy, surface);
    else if (orig_eglSwapBuffers) res = orig_eglSwapBuffers(dpy, surface);
    g_SwapDepth--;
    if (g_SwapDepth == 0) g_InEglSwap = false;
    if (g_SwapCount < 20) LOGI("[ImGui] real hook after orig res=%d count=%d depth=%d", res, g_SwapCount, g_SwapDepth);
    return res;
}

EGLBoolean hook_eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
    // Generic fallback - calls offset version logic
    return hook_eglSwapBuffers_Offset(dpy, surface);
}

__int64 hook_renderer(__int64 *ConfigAttrib, int a2) {
    if (!g_App || !g_App->window || !g_App->config) {
        if (orig_renderer) return orig_renderer(ConfigAttrib, a2);
        return 0;
    }

    if ( *(_DWORD *)(*(_QWORD *)ConfigAttrib + 272LL) != a2 ) {
        EGLDisplay dpy = reinterpret_cast<EGLDisplay>(*(uintptr_t *) (*ConfigAttrib + 96LL));
        EGLSurface surface = reinterpret_cast<EGLSurface>(*(uintptr_t *) (*ConfigAttrib + 120LL));

        eglQuerySurface(dpy, surface, EGL_WIDTH, &glWidth);
        eglQuerySurface(dpy, surface, EGL_HEIGHT, &glHeight);

        screenWidth = ANativeWindow_getWidth(g_App->window);
        screenHeight = ANativeWindow_getHeight(g_App->window);
        density = AConfiguration_getDensity(g_App->config);

        int v4 = glHeight;
        if (glHeight > a2) v4 = a2;
        if (glWidth > a2) v4 = glWidth;
        *(_DWORD *)(*(_QWORD *)ConfigAttrib + 272LL) = v4;

        g_EglDisplay = dpy;
        g_EglSurface = surface;
    }

    if (screenHeight <= 0 || screenWidth <= 0) {
        if (orig_renderer) return orig_renderer(ConfigAttrib, a2);
        return 0;
    }

    __int64 ret = 0;
    if (orig_renderer) ret = orig_renderer(ConfigAttrib, a2);

    if (!g_ImGuiInitialized) {
        EGLDisplay dpy = reinterpret_cast<EGLDisplay>(*(uintptr_t *) (*ConfigAttrib + 96LL));
        EGLSurface surface = reinterpret_cast<EGLSurface>(*(uintptr_t *) (*ConfigAttrib + 120LL));
        EGLContext ctx = eglGetCurrentContext();
        if (dpy != EGL_NO_DISPLAY && surface != EGL_NO_SURFACE && ctx != EGL_NO_CONTEXT) {
            InitImGui(dpy, surface, g_App->window);
        }
    }

    return ret;
}

void InstallRendererHook(uintptr_t rendererAddr) {
    if (rendererAddr == 0) return;
    if (orig_renderer != nullptr) return;
    void* stub = shadowhook_hook_func_addr((void*)rendererAddr, (void*)hook_renderer, (void**)&orig_renderer);
    if (stub) LOGI("Renderer hook installed at %p via ShadowHook", (void*)rendererAddr);
    else LOGI("Renderer hook failed at %p via ShadowHook err=%d", (void*)rendererAddr, shadowhook_get_errno());
}

void InstallInputHooks() {
    if (g_App && !g_InputHookInstalled) {
        if (g_App->onInputEvent) orig_onInputEvent = g_App->onInputEvent;
        g_App->onInputEvent = hook_onInputEvent;
        g_InputHookInstalled = true;
        LOGI("[ImGui] Installed onInputEvent hook orig %p", orig_onInputEvent);
    }
}

void InstallImGuiHooks() {
    // Hook libUE4 offsets as GOT pointer overwrite - not as function hook
    // Because 0xD495D50 and 0xD494B60 are likely GOT entries pointing to real eglSwapBuffers / AInputQueue_getEvent
    // Hooking them as function (shadowhook_hook_func_addr) corrupts data and causes splash hang
    if (Cheat::libUE4Base != 0) {
        if (!g_EglHookInstalled) {
            uintptr_t eglAddr = Cheat::libUE4Base + Cheat::eglSwapBuffers_Offset;
            void** gotPtr = (void**)eglAddr;
            LOGI("[ImGui] Trying GOT overwrite for eglSwapBuffers at %p", gotPtr);
            if (Tools::IsPtrValid((void*)gotPtr)) {
                void* origPtr = *gotPtr;
                LOGI("[ImGui] GOT eglSwapBuffers current ptr %p", origPtr);
                if (origPtr && Tools::IsPtrValid(origPtr)) {
                    uintptr_t page = (uintptr_t)gotPtr & ~0xFFFULL;
                    if (mprotect((void*)page, 0x2000, PROT_READ | PROT_WRITE | PROT_EXEC) == 0) {
                        orig_eglSwapBuffers_Offset = (EGLBoolean (*)(EGLDisplay, EGLSurface))origPtr;
                        orig_eglSwapBuffers = orig_eglSwapBuffers_Offset;
                        *gotPtr = (void*)hook_eglSwapBuffers_Offset;
                        g_EglHookInstalled = true;
                        LOGI("[ImGui] eglSwapBuffers hooked via GOT overwrite @ %p orig %p -> hook %p", gotPtr, origPtr, hook_eglSwapBuffers_Offset);
                    } else {
                        LOGI("[ImGui] mprotect failed for eglSwapBuffers GOT errno=%d", errno);
                    }
                }
            }
            // Fallback to function hook if GOT method failed
            if (!g_EglHookInstalled) {
                LOGI("[ImGui] GOT overwrite failed, trying function hook at %p", (void*)eglAddr);
                void* stub = shadowhook_hook_func_addr((void*)eglAddr, (void*)hook_eglSwapBuffers_Offset, (void**)&orig_eglSwapBuffers_Offset);
                if (stub) {
                    g_EglHookInstalled = true;
                    orig_eglSwapBuffers = orig_eglSwapBuffers_Offset;
                    LOGI("[ImGui] eglSwapBuffers offset hooked via function hook stub=%p orig=%p", stub, orig_eglSwapBuffers_Offset);
                } else {
                    int err = shadowhook_get_errno();
                    LOGI("[ImGui] eglSwapBuffers offset function hook failed err=%d (%s)", err, shadowhook_to_errmsg(err));
                }
            }
        }
        uintptr_t inputAddr = Cheat::libUE4Base + Cheat::AInputQueue_GetEvent_Offset;
        void** inputGot = (void**)inputAddr;
        if (!orig_AInputQueue_getEvent) {
            LOGI("[ImGui] Trying GOT overwrite for AInputQueue_getEvent at %p", inputGot);
            if (Tools::IsPtrValid((void*)inputGot)) {
                void* origPtr = *inputGot;
                LOGI("[ImGui] GOT AInputQueue_getEvent current ptr %p", origPtr);
                if (origPtr && Tools::IsPtrValid(origPtr)) {
                    uintptr_t page = (uintptr_t)inputGot & ~0xFFFULL;
                    if (mprotect((void*)page, 0x2000, PROT_READ | PROT_WRITE | PROT_EXEC) == 0) {
                        orig_AInputQueue_getEvent = (int (*)(AInputQueue*, AInputEvent**))origPtr;
                        *inputGot = (void*)hook_AInputQueue_getEvent;
                        LOGI("[ImGui] AInputQueue_getEvent hooked via GOT overwrite");
                    }
                }
            }
            if (!orig_AInputQueue_getEvent) {
                void* stub = shadowhook_hook_func_addr((void*)inputAddr, (void*)hook_AInputQueue_getEvent, (void**)&orig_AInputQueue_getEvent);
                if (stub) LOGI("[ImGui] AInputQueue_getEvent hooked via function hook");
                else LOGI("[ImGui] AInputQueue_getEvent hook failed err=%d", shadowhook_get_errno());
            }
        }
    }

    // Hook real eglSwapBuffers in libEGL.so - critical for per-frame rendering
    const char* eglLibs[] = { "libEGL.so", "libGLESv2.so", "libGLESv3.so", nullptr };
    for (int i = 0; eglLibs[i] != nullptr; ++i) {
        void* lib = dlopen(eglLibs[i], RTLD_NOW);
        if (!lib) {
            LOGI("[ImGui] dlopen %s failed", eglLibs[i]);
            continue;
        }
        void* sym = dlsym(lib, "eglSwapBuffers");
        if (!sym) {
            LOGI("[ImGui] dlsym eglSwapBuffers not found in %s", eglLibs[i]);
            continue;
        }
        if (Cheat::libUE4Base != 0) {
            uintptr_t offsetAddr = Cheat::libUE4Base + Cheat::eglSwapBuffers_Offset;
            if (sym == (void*)offsetAddr) {
                LOGI("[ImGui] Skipping libEGL hook for %s - same as offset addr", eglLibs[i]);
                continue;
            }
        }
        if (orig_eglSwapBuffers_Real && sym == (void*)orig_eglSwapBuffers_Real) {
            LOGI("[ImGui] real eglSwapBuffers in %s already hooked", eglLibs[i]);
            continue;
        }
        LOGI("[ImGui] Hooking real eglSwapBuffers in %s @ %p via ShadowHook", eglLibs[i], sym);
        void* stub = shadowhook_hook_func_addr(sym, (void*)hook_eglSwapBuffers_Real, (void**)&orig_eglSwapBuffers_Real);
        if (stub) {
            g_EglRealHookInstalled = true;
            LOGI("[ImGui] real eglSwapBuffers hooked in %s via ShadowHook stub=%p orig=%p", eglLibs[i], stub, orig_eglSwapBuffers_Real);
            if (!g_EglHookInstalled) {
                orig_eglSwapBuffers = orig_eglSwapBuffers_Real;
                g_EglHookInstalled = true;
            }
        } else {
            int err = shadowhook_get_errno();
            LOGI("[ImGui] real eglSwapBuffers ShadowHook in %s failed err=%d (%s)", eglLibs[i], err, shadowhook_to_errmsg(err));
        }
    }

    if (!g_EglHookInstalled) {
        LOGI("[ImGui] All eglSwapBuffers hooks failed, ImGui will not render!");
    } else {
        LOGI("[ImGui] eglSwapBuffers hook installed: offset=%d real=%d", g_EglHookInstalled, g_EglRealHookInstalled);
    }

    InstallInputHooks();
}
