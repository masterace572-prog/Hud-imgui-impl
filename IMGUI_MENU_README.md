# ImGui Menu Only - EGL Implementation

This implements ImGui **only for menu** (toggles), keeping your existing ESP logic untouched:
- ESP still uses `DrawHUD()` / `RenderESPPRIVATE()` 
- Memory still uses `DrawMemory()`
- Menu only enables/disables features like ESP Line, Name, Health, Box, etc.

## What was added

### 1. `jni/ImGuiMenu.h` + `jni/ImGuiMenu.cpp`
Core ImGui EGL integration:

- `hook_renderer(__int64 *ConfigAttrib, int a2)` - **your requested hook** using EGL data from ConfigAttrib:
  ```cpp
  EGLDisplay dpy = reinterpret_cast<EGLDisplay>(*(uintptr_t *) (*ConfigAttrib + 96LL));
  EGLSurface surface = reinterpret_cast<EGLSurface>(*(uintptr_t *) (*ConfigAttrib + 120LL));
  eglQuerySurface(dpy, surface, EGL_WIDTH, &glWidth);
  eglQuerySurface(dpy, surface, EGL_HEIGHT, &glHeight);
  screenWidth = ANativeWindow_getWidth(g_App->window);
  screenHeight = ANativeWindow_getHeight(g_App->window);
  density = AConfiguration_getDensity(g_App->config);
  ```
  This updates `glWidth/glHeight/screenWidth/screenHeight/density` and init ImGui after original call.

- `hook_eglSwapBuffers` - main render hook where ImGui menu is drawn:
  - Lazy init ImGui on first valid EGL context
  - Calls `RenderImGui()` which does:
    ```cpp
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(glWidth, glHeight);
    ImGui::NewFrame();
    DrawMenu();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData();
    ```

- `hook_onInputEvent` - forwards touch to ImGui, blocks game input when menu wants capture:
  ```cpp
  ImGui_ImplAndroid_HandleInputEvent(event);
  if (g_MenuOpen && io.WantCaptureMouse) return 1;
  ```

- `DrawMenu()` - tabbed UI:
  - **ESP**: Line, Box, Skeleton, Health, Name, Distance, Counter, Target, Vehicle, LootBox, Throwable
  - **Aimbot**: Aimbot Enable, BulletTrack Enable, VisCheck, IgnoreKnock, IgnoreBot, Range, FOV, Recoil
  - **Memory**: Wide View, Small/NoRecoil, Hit Effect, Show Damage, Skin
  - **Items**: Enable All / Disable All + per-item checkboxes from `items_data`
  - **Settings**: Screen info, Close Menu

### 2. `jni/Android.mk` updated
Added ImGui sources:
```makefile
LOCAL_SRC_FILES := main.cpp \
        ImGuiMenu.cpp \
        imgui/imgui.cpp \
        imgui/imgui_draw.cpp \
        imgui/imgui_widgets.cpp \
        imgui/imgui_tables.cpp \
        imgui/backends/imgui_impl_opengl3.cpp \
        imgui/backends/imgui_impl_android.cpp \
        ...
```

### 3. `jni/main.cpp` updated
- `#include "ImGuiMenu.h"`
- In `RunGame()` after getting `libUE4Base` and `g_App`:
  ```cpp
  InstallImGuiHooks(); // hooks eglSwapBuffers via Dobby
  // Optional renderer hook if you know offset:
  // InstallRendererHook(Cheat::libUE4Base + 0xYOUR_OFFSET);
  ```

### 4. `jni/Helper/definition.h` & `Login.h` made `inline`
To allow inclusion in multiple translation units (main.cpp + ImGuiMenu.cpp) without linker duplicate errors, globals changed to `inline` (C++17).

## How to hook your renderer function

You posted:
```cpp
__int64 __fastcall(*orig_renderer)(__int64 *ConfigAttrib, int a2);
__int64 __fastcall hook_renderer(__int64 *ConfigAttrib, int a2) {
  if (!g_App || !g_App->window || !g_App->config) return orig_renderer(ConfigAttrib,a2);
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
    }
   if (screenHeight <= 0 || screenWidth <= 0) return orig_renderer(ConfigAttrib, a2);
return orig_renderer(ConfigAttrib,a2);
}
```

Now `ImGuiMenu.cpp` contains the same logic **plus ImGui init**:

```cpp
__int64 hook_renderer(__int64 *ConfigAttrib, int a2) {
    if (!g_App ...) return orig_renderer...
    if (*(_DWORD*)(*(_QWORD*)ConfigAttrib + 272) != a2) {
        EGLDisplay dpy = ...
        EGLSurface surface = ...
        eglQuerySurface(dpy, surface, EGL_WIDTH, &glWidth);
        ...
        g_EglDisplay = dpy;
        g_EglSurface = surface;
    }
    if (screenHeight <=0 ...) return orig_renderer...
    __int64 ret = orig_renderer(ConfigAttrib,a2);
    if (!g_ImGuiInitialized) {
        EGLDisplay dpy = ...
        EGLSurface surface = ...
        EGLContext ctx = eglGetCurrentContext();
        if (dpy != EGL_NO_DISPLAY && surface != EGL_NO_SURFACE && ctx != EGL_NO_CONTEXT) {
            InitImGui(dpy, surface, g_App->window);
        }
    }
    return ret;
}
```

To install:
```cpp
// In RunGame after libUE4Base known:
uintptr_t rendererOffset = 0x1234567; // <-- YOUR OFFSET HERE
InstallRendererHook(Cheat::libUE4Base + rendererOffset);
```

If you don't know offset, **eglSwapBuffers hook alone is enough** for menu to appear. The renderer hook is optional but gives you more accurate width/height from game struct.

## Menu visibility
- `g_MenuOpen` bool controls visibility
- Floating "Menu" button when closed
- Full window when open, draggable, with close button
- Input blocked when touching menu (via `WantCaptureMouse`)

## No ESP/Memory touched
- `DrawHUD()` still does all ESP drawing using `Cheat::Esp::*` bools
- `DrawMemory()` still does memory hacks using `Cheat::Memory::*`
- Menu only toggles those bools, doesn't replace rendering

## Build
Uses existing `Android.mk`, just added ImGui files. Build with ndk-build as before:
```
/data/user/0/com.idragoncheats.studiopro/no_backup/ndksupport-1710240003/android-ndk-aide/ndk-build -j14
```
Or via Android Studio.

## Tested flow
1. Game starts, `RunGame` thread gets `libUE4Base` and `g_App`
2. `InstallImGuiHooks()` hooks `eglSwapBuffers`
3. First `eglSwapBuffers` call -> `InitImGui()` creates context, style scaled by density
4. Next frames -> `RenderImGui()` draws menu
5. Touch -> `hook_onInputEvent` -> ImGui handles, menu interactive
6. Checkboxes toggle `Cheat::Esp::Line` etc, which `DrawHUD` reads

Enjoy!
