#include "ImGuiMenu.h"
#include "Includes/Logger.h"

// Globals
bool g_ImGuiInitialized = false;
EGLDisplay g_EglDisplay = EGL_NO_DISPLAY;
EGLSurface g_EglSurface = EGL_NO_SURFACE;
EGLContext g_EglContext = EGL_NO_CONTEXT;
bool g_MenuOpen = true;

EGLBoolean (*orig_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface) = nullptr;
__int64 (*orig_renderer)(__int64 *ConfigAttrib, int a2) = nullptr;
int32_t (*orig_onInputEvent)(struct android_app* app, AInputEvent* event) = nullptr;

static bool g_InputHookInstalled = false;

// Forward for menu tabs
static int g_MenuTab = 0; // 0=ESP, 1=Aim, 2=Memory, 3=Items

// Helper to init ImGui style for mobile
static void SetupImGuiStyle() {
    ImGuiStyle &style = ImGui::GetStyle();
    style.WindowRounding = 8.0f;
    style.FrameRounding = 6.0f;
    style.GrabRounding = 6.0f;
    style.ScrollbarRounding = 6.0f;
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);

    // Dark theme with custom accent
    ImGui::StyleColorsDark();
    ImVec4* colors = style.Colors;
    colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.12f, 0.94f);
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

    // Scale for mobile density - if density available use it
    float scale = 1.0f;
    if (density > 0) {
        // density is DPI, e.g. 320, 480 etc. Base 160
        scale = density / 160.0f;
        // clamp
        if (scale < 1.0f) scale = 1.0f;
        if (scale > 3.5f) scale = 3.5f;
        // Slightly reduce to keep UI usable
        scale *= 0.65f;
    } else {
        // fallback based on screen height
        if (glHeight > 0) {
            scale = glHeight / 1080.0f;
            if (scale < 1.0f) scale = 1.0f;
            if (scale > 2.5f) scale = 2.5f;
        }
    }
    style.ScaleAllSizes(scale);
    // Font scale
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

    LOGI("ImGui Init: dpy=%p surface=%p ctx=%p window=%p w=%d h=%d", dpy, surface, ctx, window, glWidth, glHeight);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.DisplaySize = ImVec2((float)glWidth, (float)glHeight);
    // Enable touch / mouse
    io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
    // For mobile, we want keyboard to not block
    io.IniFilename = nullptr; // don't save ini to disk

    SetupImGuiStyle();

    // Init backends
    if (!ImGui_ImplAndroid_Init(window)) {
        LOGI("ImGui_ImplAndroid_Init failed");
    }
    // Use GLES 3.0 shader
    if (!ImGui_ImplOpenGL3_Init("#version 300 es")) {
        LOGI("ImGui_ImplOpenGL3_Init failed");
        // Try fallback
        ImGui_ImplOpenGL3_Init("#version 100");
    }

    g_ImGuiInitialized = true;

    // Hook input if not yet
    if (!g_InputHookInstalled && g_App) {
        orig_onInputEvent = g_App->onInputEvent;
        g_App->onInputEvent = hook_onInputEvent;
        g_InputHookInstalled = true;
        LOGI("ImGui input hook installed");
    }

    LOGI("ImGui Initialized successfully");
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

// Input hook - forward to ImGui and optionally block game input when menu open
int32_t hook_onInputEvent(struct android_app* app, AInputEvent* event) {
    if (g_ImGuiInitialized && event) {
        // Let ImGui handle it
        bool handled = ImGui_ImplAndroid_HandleInputEvent(event);
        ImGuiIO &io = ImGui::GetIO();
        if (g_MenuOpen && handled && io.WantCaptureMouse) {
            // If menu is open and ImGui wants mouse, consume event to prevent game from handling it
            // Check if touch is inside menu window area - we let ImGui decide via WantCapture
            return 1;
        }
    }
    if (orig_onInputEvent) {
        return orig_onInputEvent(app, event);
    }
    return 0;
}

void DrawMenu() {
    if (!g_MenuOpen) {
        // Small floating button to open menu
        ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(120, 50), ImGuiCond_FirstUseEver);
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;
        ImGui::Begin("##ToggleMenu", nullptr, flags);
        if (ImGui::Button("Menu", ImVec2(100, 35))) {
            g_MenuOpen = true;
        }
        ImGui::End();
        return;
    }

    // Main menu window
    float menuW = glWidth * 0.55f;
    float menuH = glHeight * 0.70f;
    if (menuW < 500) menuW = 500;
    if (menuW > 800) menuW = 800;
    if (menuH < 400) menuH = 400;
    if (menuH > 900) menuH = 900;

    ImGui::SetNextWindowPos(ImVec2(glWidth * 0.5f - menuW * 0.5f, glHeight * 0.5f - menuH * 0.5f), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(menuW, menuH), ImGuiCond_FirstUseEver);
    ImGuiWindowFlags mainFlags = ImGuiWindowFlags_NoCollapse;

    ImGui::Begin("SANKE CHEAT MENU", &g_MenuOpen, mainFlags);

    // Tab bar
    if (ImGui::BeginTabBar("##Tabs")) {
        if (ImGui::BeginTabItem("ESP")) {
            g_MenuTab = 0;
            ImGui::Spacing();
            ImGui::Columns(2, nullptr, false);
            // Left column
            ImGui::Checkbox("Line", &Cheat::Esp::Line);
            ImGui::Checkbox("Box", &Cheat::Esp::Box);
            ImGui::Checkbox("Skeleton", &Cheat::Esp::Skeleton);
            ImGui::Checkbox("Health", &Cheat::Esp::Health);
            ImGui::Checkbox("Name", &Cheat::Esp::Name);
            ImGui::Checkbox("Distance", &Cheat::Esp::Distance);
            ImGui::NextColumn();
            ImGui::Checkbox("Counter", &Cheat::Esp::Counter);
            ImGui::Checkbox("Target Line", &Cheat::Esp::Target);
            ImGui::Checkbox("Vehicle", &Cheat::Esp::Vehicle::Name);
            ImGui::Checkbox("LootBox", &Cheat::Esp::LootBox);
            ImGui::Checkbox("Grenade", &Cheat::Esp::Throwable);
            ImGui::Columns(1);
            ImGui::Separator();
            ImGui::Text("ESP keeps using DrawHUD, this menu only toggles");
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Aimbot")) {
            g_MenuTab = 1;
            ImGui::Spacing();
            ImGui::Checkbox("Aimbot Enable", &Cheat::Aimbot::Enable);
            ImGui::Checkbox("BulletTrack Enable", &Cheat::BulletTrack::Enable);
            ImGui::Checkbox("VisCheck", &Cheat::BulletTrack::VisCheck);
            ImGui::Checkbox("Ignore Knock", &Cheat::BulletTrack::IgnoreKnock);
            ImGui::Checkbox("Ignore Bot", &Cheat::BulletTrack::iGnoreBot);
            ImGui::SliderFloat("BulletTrack Range", &Cheat::BulletTrack::Range, 50.0f, 600.0f, "%.0f");
            ImGui::SliderFloat("BulletTrack FOV", &Cheat::BulletTrack::Fov, 10.0f, 1000.0f, "%.0f");
            ImGui::Separator();
            ImGui::SliderFloat("Recoil Comp", &Cheat::Aimbot::Recoil, 0.0f, 5.0f, "%.2f");
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Memory")) {
            g_MenuTab = 2;
            ImGui::Spacing();
            ImGui::Checkbox("Wide View", &Cheat::Memory::Wide);
            ImGui::Checkbox("Small Crosshair / No Recoil", &Cheat::Memory::Small);
            ImGui::Checkbox("Hit Effect", &Cheat::Memory::Hit);
            ImGui::Checkbox("Show Damage", &Cheat::Memory::ShowDamage);
            ImGui::Checkbox("Skin Hack", &Cheat::Memory::Skin);
            ImGui::Separator();
            ImGui::Text("Memory features from DrawMemory");
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Items")) {
            g_MenuTab = 3;
            ImGui::Spacing();
            if (ImGui::Button("Enable All Items")) {
                for (auto &pair : Items) {
                    pair.second = true;
                }
            }
            ImGui::SameLine();
            if (ImGui::Button("Disable All Items")) {
                for (auto &pair : Items) {
                    pair.second = false;
                }
            }
            ImGui::Separator();
            ImGui::BeginChild("##ItemList", ImVec2(0, 0), true);
            // Show items if items_data parsed
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
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Settings")) {
            ImGui::Spacing();
            ImGui::Text("Screen: %d x %d", glWidth, glHeight);
            ImGui::Text("Window: %d x %d", screenWidth, screenHeight);
            ImGui::Text("Density: %.0f", density);
            ImGui::Separator();
            if (ImGui::Button("Close Menu")) {
                g_MenuOpen = false;
            }
            ImGui::SameLine();
            if (ImGui::Button("Exit Cheat (Danger)")) {
                // just close menu, not exit
                g_MenuOpen = false;
            }
            ImGui::Separator();
            ImGui::Text("Menu uses EGL hook + ImGui");
            ImGui::Text("ESP still uses DrawHUD");
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }

    ImGui::End();
}

void RenderImGui() {
    if (!g_ImGuiInitialized) return;
    if (g_EglDisplay == EGL_NO_DISPLAY) return;

    // Ensure we have correct display size
    if (glWidth <= 0 || glHeight <= 0) return;

    // Backup GL state is handled by ImGui_ImplOpenGL3

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(glWidth, glHeight);
    ImGui::NewFrame();

    DrawMenu();

    ImGui::Render();
    // Get display size for viewport
    ImGuiIO &io = ImGui::GetIO();
    // Make sure viewport is correct
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

// eglSwapBuffers hook - main render point
EGLBoolean hook_eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
    // Lazy init if not initialized
    if (!g_ImGuiInitialized) {
        if (dpy != EGL_NO_DISPLAY && surface != EGL_NO_SURFACE && g_App && g_App->window) {
            EGLContext ctx = eglGetCurrentContext();
            if (ctx != EGL_NO_CONTEXT) {
                // Only init if we have valid width/height
                if (glWidth > 0 && glHeight > 0) {
                    InitImGui(dpy, surface, g_App->window);
                } else {
                    // Try query surface size here as fallback
                    EGLint w, h;
                    if (eglQuerySurface(dpy, surface, EGL_WIDTH, &w) && eglQuerySurface(dpy, surface, EGL_HEIGHT, &h)) {
                        glWidth = w;
                        glHeight = h;
                        if (w > 0 && h > 0) {
                            InitImGui(dpy, surface, g_App->window);
                        }
                    }
                }
            }
        }
    } else {
        // Update display/surface if changed
        if (dpy != g_EglDisplay || surface != g_EglSurface) {
            g_EglDisplay = dpy;
            g_EglSurface = surface;
            g_EglContext = eglGetCurrentContext();
        }
        // Render menu
        RenderImGui();
    }

    // Call original
    if (orig_eglSwapBuffers) {
        return orig_eglSwapBuffers(dpy, surface);
    }
    return EGL_FALSE;
}

// Your requested renderer hook - using the EGL data from ConfigAttrib
// This keeps your original logic and adds ImGui init
__int64 hook_renderer(__int64 *ConfigAttrib, int a2) {
    if (!g_App || !g_App->window || !g_App->config) {
        if (orig_renderer) return orig_renderer(ConfigAttrib, a2);
        return 0;
    }

    // Your original size logic
    if ( *(_DWORD *)(*(_QWORD *)ConfigAttrib + 272LL) != a2 ) {
        EGLDisplay dpy = reinterpret_cast<EGLDisplay>(*(uintptr_t *) (*ConfigAttrib + 96LL));
        EGLSurface surface = reinterpret_cast<EGLSurface>(*(uintptr_t *) (*ConfigAttrib + 120LL));

        eglQuerySurface(dpy, surface, EGL_WIDTH, &glWidth);
        eglQuerySurface(dpy, surface, EGL_HEIGHT, &glHeight);

        screenWidth = ANativeWindow_getWidth(g_App->window);
        screenHeight = ANativeWindow_getHeight(g_App->window);
        density = AConfiguration_getDensity(g_App->config);

        int v4;
        v4 = glHeight;
        if ( glHeight > a2 )
            v4 = a2;
        if ( glWidth > a2 )
            v4 = glWidth;
        *(_DWORD *)(*(_QWORD *)ConfigAttrib + 272LL) = v4;

        // Also store for ImGui
        g_EglDisplay = dpy;
        g_EglSurface = surface;
    }

    if (screenHeight <= 0 || screenWidth <= 0) {
        if (orig_renderer) return orig_renderer(ConfigAttrib, a2);
        return 0;
    }

    // Call original renderer first - this makes GL context current
    __int64 ret = 0;
    if (orig_renderer) {
        ret = orig_renderer(ConfigAttrib, a2);
    }

    // After original, try to init ImGui if not yet
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
    if (orig_renderer != nullptr) return; // already hooked
    // Use And64InlineHook or Dobby - try Dobby first
    int res = DobbyHook((void*)rendererAddr, (void*)hook_renderer, (void**)&orig_renderer);
    if (res == 0) {
        LOGI("Renderer hook installed at %p", (void*)rendererAddr);
    } else {
        LOGI("Renderer hook failed at %p res=%d", (void*)rendererAddr, res);
    }
}

void InstallImGuiHooks() {
    // Hook eglSwapBuffers
    void* libEGL = dlopen("libEGL.so", RTLD_NOW);
    if (!libEGL) libEGL = dlopen("libGLESv2.so", RTLD_NOW);
    if (libEGL) {
        void* sym = dlsym(libEGL, "eglSwapBuffers");
        if (sym) {
            if (!orig_eglSwapBuffers) {
                DobbyHook(sym, (void*)hook_eglSwapBuffers, (void**)&orig_eglSwapBuffers);
                LOGI("eglSwapBuffers hooked at %p", sym);
            }
        } else {
            LOGI("dlsym eglSwapBuffers failed");
        }
    } else {
        LOGI("dlopen libEGL failed");
    }

    // Optional: try to auto find renderer offset if libUE4Base is known
    // The renderer function you provided is usually at some offset in libUE4.so
    // User can call InstallRendererHook manually with known offset
    // Example: InstallRendererHook(Cheat::libUE4Base + 0x...);
    // We will attempt to install if Cheat::libUE4Base is already set and we know common offsets
    if (Cheat::libUE4Base != 0) {
        // You can add your renderer offset here if you know it
        // For PUBG 3.3/3.4 common offsets are around 0x... This is placeholder - user should set
        // uintptr_t possibleOffsets[] = {0x...};
        // For now we don't auto hook, user can provide offset via config or we leave eglSwapBuffers as main render hook
    }
}
