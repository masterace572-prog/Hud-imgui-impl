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
__int64 (*orig_renderer)(__int64 *ConfigAttrib, int a2) = nullptr;
int32_t (*orig_onInputEvent)(struct android_app* app, AInputEvent* event) = nullptr;
int (*orig_AInputQueue_getEvent)(AInputQueue* queue, AInputEvent** outEvent) = nullptr;

static bool g_InputHookInstalled = false;
static bool g_EglHookInstalled = false;
static int g_MenuTab = 0; // 0=ESP, 1=Aim, 2=Memory, 3=Items, 4=Settings

// Style setup - similar to your IMGUI example but keeping HUD ESP
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
    colors[ImGuiCol_ChildBg] = ImVec4(0.09f, 0.20f, 0.35f, 0.00f); // transparent like example
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

    // Scale based on density like your example does: density / 20, density / 14 etc
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
    io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
    io.IniFilename = nullptr;

    SetupImGuiStyle();

    // Init backends - note example uses ImGui_ImplAndroid_Init() without window, but our backend needs window
    bool androidInit = ImGui_ImplAndroid_Init(window);
    LOGI("ImGui_ImplAndroid_Init ret=%d", androidInit);
    bool glInit300 = ImGui_ImplOpenGL3_Init("#version 300 es");
    LOGI("ImGui_ImplOpenGL3_Init #300 es ret=%d", glInit300);
    if (!glInit300) {
        LOGI("ImGui_ImplOpenGL3_Init #300 es failed, trying #100");
        bool glInit100 = ImGui_ImplOpenGL3_Init("#version 100");
        LOGI("ImGui_ImplOpenGL3_Init #100 ret=%d", glInit100);
    }

    // Optional: load custom font like example does with PIRO_data
    // io.Fonts->AddFontFromMemoryTTF((void*)PIRO_data, PIRO_size, 20.0f, NULL, io.Fonts->GetGlyphRangesDefault());
    // For now use default + density scaled size
    ImFontConfig cfg;
    cfg.SizePixels = density > 0 ? (density / 20.0f) : 20.0f;
    // io.Fonts->AddFontDefault(&cfg); // default already added

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

// Input hook - like your IMGUI example: passes screen_scale
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

// Low-level input queue hook using your offset 0xD494B60 (AInputQueue_GetEvent)
// Signature: int AInputQueue_getEvent(AInputQueue* queue, AInputEvent** outEvent)
int hook_AInputQueue_getEvent(AInputQueue* queue, AInputEvent** outEvent) {
    int result = -1;
    if (orig_AInputQueue_getEvent) {
        result = orig_AInputQueue_getEvent(queue, outEvent);
    }
    if (result >= 0 && outEvent && *outEvent && g_ImGuiInitialized) {
        // Forward to ImGui with scale like example
        float sx = 1.0f, sy = 1.0f;
        if (glWidth > 0 && screenWidth > 0) sx = (float)screenWidth / (float)glWidth;
        if (glHeight > 0 && screenHeight > 0) sy = (float)screenHeight / (float)glHeight;
        ImVec2 scale = ImVec2(sx, sy);
        ImGui_ImplAndroid_HandleInputEvent(*outEvent, scale);
        // If menu open and ImGui wants capture, we could consume? 
        // But AInputQueue_getEvent is expected to return event, so we don't block here
        // Blocking is done in onInputEvent hook
    }
    return result;
}

// Menu only - no ESP draw via ImGui drawlist, ESP stays in DrawHUD
void DrawMenu() {
    static int drawCount = 0;
    drawCount++;
    if (drawCount < 10 || drawCount % 100 == 0) {
        LOGI("[ImGui] DrawMenu count %d tab=%d open=%d", drawCount, g_MenuTab, g_MenuOpen);
    }

    // Test if ImGui background drawlist works at all
    ImDrawList* bg = ImGui::GetBackgroundDrawList();
    if (bg) {
        bg->AddRectFilled(ImVec2(100, 100), ImVec2(400, 400), IM_COL32(255, 0, 0, 200));
        bg->AddText(ImVec2(110, 110), IM_COL32(255, 255, 255, 255), "SANKE TEST");
    }

    if (!g_MenuOpen) {
        ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(120, 50), ImGuiCond_Always);
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;
        ImGui::Begin("##ToggleMenu", nullptr, flags);
        if (ImGui::Button("Menu", ImVec2(100, 35))) {
            g_MenuOpen = true;
        }
        ImGui::End();
        return;
    }

    ImGuiIO &io = ImGui::GetIO();
    float menuW = glWidth * 0.42f;
    float menuH = glHeight * 0.52f;
    if (menuW < 500) menuW = 500;
    if (menuW > 850) menuW = 850;
    if (menuH < 400) menuH = 400;
    if (menuH > 900) menuH = 900;

    // Force visible position for debugging
    ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(menuW, menuH), ImGuiCond_Always);
    char titleBuf[128];
    // Like example: FPS in title
    sprintf(titleBuf, "SANKE MENU ~ HUD ESP ~ %.1f FPS", io.Framerate);

    ImGuiWindowFlags mainFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiConfigFlags_NoMouseCursorChange;

    if (ImGui::Begin(titleBuf, &g_MenuOpen, mainFlags)) {

        // Left panel like your IMGUI example
        ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.6f);
        ImGui::PushStyleColor(ImGuiCol_Border, ImColor(100, 100, 100, 200).Value);
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImColor(9, 36, 89, 0).Value);
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0.0f);
        ImGui::BeginChild("left", ImVec2(170, 0), true);
        ImGui::PopStyleVar(2);
        ImGui::PopStyleColor(2);

        // Buttons like example: Player ESP, Bullet Track, Extra Features
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

        // Right panel
        ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.6f);
        ImGui::PushStyleColor(ImGuiCol_Border, ImColor(100, 100, 100, 200).Value);
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImColor(9, 36, 89, 0).Value);
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0.0f);
        ImGui::BeginChild("mainchild", ImVec2(0, 0), true);
        ImGui::PopStyleVar(2);
        ImGui::PopStyleColor(2);

        if (g_MenuTab == 0) { // Player ESP - toggles for DrawHUD
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
        } else if (g_MenuTab == 1) { // Aimbot
            ImGui::Text("Aimbot - Uses DrawMemory aim");
            ImGui::Separator();
            ImGui::Checkbox("Aimbot Enable", &Cheat::Aimbot::Enable);

            ImGui::Separator();
            ImGui::Text("Aim Mode");
            bool isFOV = Cheat::FOV::Enable;
            bool is180 = !Cheat::FOV::Enable;
            if (ImGui::RadioButton("FOV", isFOV)) {
                Cheat::FOV::Enable = true;
            }
            ImGui::SameLine();
            if (ImGui::RadioButton("180°", is180)) {
                Cheat::FOV::Enable = false;
            }

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
        } else if (g_MenuTab == 2) { // Bullet Track
            ImGui::Text("Bullet Track - Magic Bullet");
            ImGui::Separator();
            ImGui::Checkbox("Bullet Track", &Cheat::BulletTrack::Enable);

            ImGui::Separator();
            ImGui::Text("Aim Mode");
            bool isFOV = Cheat::FOV::Enable;
            bool is180 = !Cheat::FOV::Enable;
            if (ImGui::RadioButton("FOV", isFOV)) {
                Cheat::FOV::Enable = true;
            }
            ImGui::SameLine();
            if (ImGui::RadioButton("180°", is180)) {
                Cheat::FOV::Enable = false;
            }

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
        } else if (g_MenuTab == 3) { // Memory
            ImGui::Text("Memory Features");
            ImGui::Separator();
            ImGui::Checkbox("Wide View", &Cheat::Memory::Wide);
            ImGui::Checkbox("Small Crosshair / No Recoil", &Cheat::Memory::Small);
            ImGui::Checkbox("Hit Effect", &Cheat::Memory::Hit);
            ImGui::Checkbox("Show Damage", &Cheat::Memory::ShowDamage);
            ImGui::Checkbox("Skin Hack", &Cheat::Memory::Skin);
        } else if (g_MenuTab == 4) { // Items
            ImGui::Text("Item ESP - Toggles for DrawHUD item loop");
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
        } else if (g_MenuTab == 5) { // Settings
            ImGui::Text("Info");
            ImGui::Separator();
            ImGui::Text("Screen: %d x %d", glWidth, glHeight);
            ImGui::Text("Window: %d x %d", screenWidth, screenHeight);
            ImGui::Text("Density: %.0f", density);
            ImGui::Text("Menu: ImGui only, ESP via HUD");
            ImGui::Separator();
            ImGui::Text("Your example used ImGui drawlist for ESP");
            ImGui::Text("This version keeps DrawHUD for ESP");
            ImGui::Text("Menu toggles same bools");
        }

        ImGui::EndChild();
    }
    ImGui::End();
}

void RenderImGui() {
    if (!g_ImGuiInitialized) return;
    if (g_EglDisplay == EGL_NO_DISPLAY) return;
    if (glWidth <= 0 || glHeight <= 0) return;

    // Debug log every 300 frames
    static int frameCount = 0;
    frameCount++;
    if (frameCount < 10 || frameCount % 100 == 0) {
        LOGI("[ImGui] RenderImGui frame %d g_MenuOpen=%d w=%d h=%d", frameCount, g_MenuOpen, glWidth, glHeight);
    }

    // Ensure GL state is clean for ImGui
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_STENCIL_TEST);
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(glWidth, glHeight);
    ImGui::NewFrame();

    // NOTE: We do NOT call DrawESP with ImGui drawlist here
    // Your example did: DrawESP(ImGui::GetBackgroundDrawList());
    // We keep HUD ESP: DrawHUD is called via ProcessEvent hook, not here
    // Only menu:
    DrawMenu();

    ImGui::Render();
    ImGuiIO &io = ImGui::GetIO();
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Check GL error
    GLenum err = glGetError();
    if (err != GL_NO_ERROR && frameCount % 100 == 0) {
        LOGI("[ImGui] GL error after RenderDrawData: 0x%x", err);
    }
}

EGLBoolean hook_eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
    // Same as your example: query surface, get g_App window size, density
    eglQuerySurface(dpy, surface, EGL_WIDTH, &glWidth);
    eglQuerySurface(dpy, surface, EGL_HEIGHT, &glHeight);

    if (glWidth <= 0 || glHeight <= 0) {
        if (orig_eglSwapBuffers) return orig_eglSwapBuffers(dpy, surface);
        return EGL_FALSE;
    }

    if (!g_App) {
        if (orig_eglSwapBuffers) return orig_eglSwapBuffers(dpy, surface);
        return EGL_FALSE;
    }

    // Ensure input hook installed (in case g_App was null earlier)
    if (!g_InputHookInstalled) InstallInputHooks();

    screenWidth = ANativeWindow_getWidth(g_App->window);
    screenHeight = ANativeWindow_getHeight(g_App->window);
    density = AConfiguration_getDensity(g_App->config);

    static int swapCount = 0;
    swapCount++;
    if (swapCount < 10 || swapCount % 200 == 0) {
        LOGI("[ImGui] eglSwapBuffers called count=%d dpy=%p surf=%p w=%d h=%d init=%d", swapCount, dpy, surface, glWidth, glHeight, g_ImGuiInitialized);
    }

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
        RenderImGui();
    }

    if (orig_eglSwapBuffers) {
        return orig_eglSwapBuffers(dpy, surface);
    }
    return EGL_FALSE;
}

// Your requested renderer hook - ConfigAttrib offsets 96,120,272
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
    // ShadowHook only
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
    // Hook via libUE4Base + offsets provided: eglSwapBuffers 0xD495D50, AInputQueue_GetEvent 0xD494B60
    // ShadowHook only for primary hooks, but also try GOT overwrite for EGL
    if (Cheat::libUE4Base != 0) {
        if (!g_EglHookInstalled) {
            uintptr_t eglAddr = Cheat::libUE4Base + Cheat::eglSwapBuffers_Offset;
            LOGI("[ImGui] Hooking eglSwapBuffers via base+0x%llx @ %p via ShadowHook", (unsigned long long)Cheat::eglSwapBuffers_Offset, (void*)eglAddr);
            void* stub = shadowhook_hook_func_addr((void*)eglAddr, (void*)hook_eglSwapBuffers, (void**)&orig_eglSwapBuffers);
            if (stub) {
                g_EglHookInstalled = true;
                LOGI("[ImGui] eglSwapBuffers hooked via offset ShadowHook stub=%p", stub);
            } else {
                int err = shadowhook_get_errno();
                LOGI("[ImGui] eglSwapBuffers offset ShadowHook failed err=%d (%s), trying Dobby", err, shadowhook_to_errmsg(err));
                int dobbyRet = DobbyHook((void*)eglAddr, (void*)hook_eglSwapBuffers, (void**)&orig_eglSwapBuffers);
                if (dobbyRet == 0) {
                    g_EglHookInstalled = true;
                    LOGI("[ImGui] eglSwapBuffers hooked via offset Dobby");
                } else {
                    LOGI("[ImGui] eglSwapBuffers offset Dobby failed ret=%d, trying GOT overwrite", dobbyRet);
                    // Try GOT overwrite: if this offset is a pointer to eglSwapBuffers, replace it
                    void** gotPtr = (void**)eglAddr;
                    if (Tools::IsPtrValid((void*)gotPtr)) {
                        void* orig = *gotPtr;
                        LOGI("[ImGui] GOT eglSwapBuffers ptr @ %p currently %p", gotPtr, orig);
                        if (orig && Tools::IsPtrValid(orig)) {
                            uintptr_t page = (uintptr_t)gotPtr & ~0xFFFULL;
                            if (mprotect((void*)page, 0x2000, PROT_READ | PROT_WRITE | PROT_EXEC) == 0) {
                                orig_eglSwapBuffers = (EGLBoolean (*)(EGLDisplay, EGLSurface))orig;
                                *gotPtr = (void*)hook_eglSwapBuffers;
                                g_EglHookInstalled = true;
                                LOGI("[ImGui] eglSwapBuffers hooked via GOT overwrite @ %p orig %p", gotPtr, orig);
                            } else {
                                LOGI("[ImGui] mprotect GOT eglSwapBuffers failed errno=%d", errno);
                            }
                        } else {
                            LOGI("[ImGui] GOT eglSwapBuffers orig invalid, not overwriting");
                        }
                    }
                }
            }
        }
        // Hook AInputQueue_getEvent
        uintptr_t inputAddr = Cheat::libUE4Base + Cheat::AInputQueue_GetEvent_Offset;
        if (!orig_AInputQueue_getEvent) {
            LOGI("[ImGui] Hooking AInputQueue_getEvent via base+0x%llx @ %p via ShadowHook", (unsigned long long)Cheat::AInputQueue_GetEvent_Offset, (void*)inputAddr);
            void* stub = shadowhook_hook_func_addr((void*)inputAddr, (void*)hook_AInputQueue_getEvent, (void**)&orig_AInputQueue_getEvent);
            if (stub) LOGI("[ImGui] AInputQueue_getEvent hooked via offset ShadowHook");
            else {
                int err = shadowhook_get_errno();
                LOGI("[ImGui] AInputQueue_getEvent ShadowHook failed err=%d (%s), trying Dobby", err, shadowhook_to_errmsg(err));
                int dobbyRet = DobbyHook((void*)inputAddr, (void*)hook_AInputQueue_getEvent, (void**)&orig_AInputQueue_getEvent);
                if (dobbyRet == 0) {
                    LOGI("[ImGui] AInputQueue_getEvent hooked via Dobby");
                } else {
                    LOGI("[ImGui] AInputQueue_getEvent Dobby failed ret=%d, trying GOT", dobbyRet);
                    void** gotPtr = (void**)inputAddr;
                    if (Tools::IsPtrValid((void*)gotPtr)) {
                        void* orig = *gotPtr;
                        LOGI("[ImGui] GOT AInputQueue_getEvent ptr @ %p currently %p", gotPtr, orig);
                        if (orig && Tools::IsPtrValid(orig)) {
                            uintptr_t page = (uintptr_t)gotPtr & ~0xFFFULL;
                            if (mprotect((void*)page, 0x2000, PROT_READ | PROT_WRITE | PROT_EXEC) == 0) {
                                orig_AInputQueue_getEvent = (int (*)(AInputQueue*, AInputEvent**))orig;
                                *gotPtr = (void*)hook_AInputQueue_getEvent;
                                LOGI("[ImGui] AInputQueue_getEvent hooked via GOT overwrite");
                            }
                        }
                    }
                }
            }
        }
    }

    // Always try to hook real eglSwapBuffers in libEGL.so as well, because game may call it directly
    // This ensures we catch per-frame swaps even if offset hook only catches wrapper init
    // Try ShadowHook first, then Dobby as fallback as user requested
    {
        const char* eglLibs[] = { "libEGL.so", "libGLESv2.so", "libGLESv3.so", nullptr };
        for (int i = 0; eglLibs[i] != nullptr; ++i) {
            void* lib = dlopen(eglLibs[i], RTLD_NOW);
            if (!lib) continue;
            void* sym = dlsym(lib, "eglSwapBuffers");
            if (sym) {
                // Check if already hooked (same as orig)
                if (orig_eglSwapBuffers && sym == (void*)orig_eglSwapBuffers) {
                    LOGI("[ImGui] eglSwapBuffers in %s already hooked (same addr %p)", eglLibs[i], sym);
                    continue;
                }
                LOGI("[ImGui] Also hooking eglSwapBuffers in %s @ %p", eglLibs[i], sym);
                void* stub = shadowhook_hook_func_addr(sym, (void*)hook_eglSwapBuffers, (void**)&orig_eglSwapBuffers);
                if (stub) {
                    LOGI("[ImGui] eglSwapBuffers hooked in %s via ShadowHook stub=%p", eglLibs[i], stub);
                    g_EglHookInstalled = true;
                } else {
                    int err = shadowhook_get_errno();
                    LOGI("[ImGui] eglSwapBuffers ShadowHook in %s failed err=%d (%s), trying Dobby", eglLibs[i], err, shadowhook_to_errmsg(err));
                    int dobbyRet = DobbyHook(sym, (void*)hook_eglSwapBuffers, (void**)&orig_eglSwapBuffers);
                    if (dobbyRet == 0) {
                        LOGI("[ImGui] eglSwapBuffers hooked in %s via Dobby", eglLibs[i]);
                        g_EglHookInstalled = true;
                    } else {
                        LOGI("[ImGui] eglSwapBuffers Dobby hook in %s failed ret=%d", eglLibs[i], dobbyRet);
                    }
                }
            }
        }
    }

    // Fallback to dlsym if offset hook not done - also via ShadowHook
    if (!g_EglHookInstalled) {
        const char* eglLibs[] = { "libEGL.so", "libGLESv2.so", "libGLESv3.so", "libUE4.so", nullptr };
        for (int i = 0; eglLibs[i] != nullptr; ++i) {
            void* lib = dlopen(eglLibs[i], RTLD_NOW);
            if (!lib) {
                LOGI("[ImGui] dlopen %s failed", eglLibs[i]);
                continue;
            }
            void* sym = dlsym(lib, "eglSwapBuffers");
            if (sym) {
                LOGI("[ImGui] Found eglSwapBuffers in %s @ %p, trying hook via ShadowHook", eglLibs[i], sym);
                void* stub = shadowhook_hook_func_addr(sym, (void*)hook_eglSwapBuffers, (void**)&orig_eglSwapBuffers);
                if (stub) {
                    g_EglHookInstalled = true;
                    LOGI("[ImGui] eglSwapBuffers hooked via dlsym %s %p ShadowHook stub=%p", eglLibs[i], sym, stub);
                    break;
                } else {
                    int err = shadowhook_get_errno();
                    LOGI("[ImGui] eglSwapBuffers dlsym hook failed in %s err=%d (%s)", eglLibs[i], err, shadowhook_to_errmsg(err));
                }
            } else {
                LOGI("[ImGui] dlsym eglSwapBuffers not found in %s", eglLibs[i]);
            }
            // also try eglSwapBuffers with symbol name via shadowhook_hook_sym_name as last resort
            if (!g_EglHookInstalled) {
                void* stub = shadowhook_hook_sym_name(eglLibs[i], "eglSwapBuffers", (void*)hook_eglSwapBuffers, (void**)&orig_eglSwapBuffers);
                if (stub) {
                    g_EglHookInstalled = true;
                    LOGI("[ImGui] eglSwapBuffers hooked via sym_name %s ShadowHook", eglLibs[i]);
                    break;
                } else {
                    int err = shadowhook_get_errno();
                    LOGI("[ImGui] eglSwapBuffers sym_name hook failed in %s err=%d (%s)", eglLibs[i], err, shadowhook_to_errmsg(err));
                }
            }
        }
        if (!g_EglHookInstalled) {
            LOGI("[ImGui] All eglSwapBuffers fallback hooks failed, ImGui will not render!");
        }
    }

    InstallInputHooks();
}
