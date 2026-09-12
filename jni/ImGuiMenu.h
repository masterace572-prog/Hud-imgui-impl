#pragma once

#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <android/native_window.h>
#include <android/input.h>
#include <android/configuration.h>
#include <dlfcn.h>
#include <unistd.h>

#include "Helper/include.h"
#include "Helper/definition.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "imgui/backends/imgui_impl_android.h"

#include <shadowhook.h>
#include "Includes/json.hpp"
#include <map>
#include <string>

// External globals from main.cpp
extern nlohmann::json items_data;
extern std::map<int, bool> Items;

// Global ImGui state
extern bool g_ImGuiInitialized;
extern EGLDisplay g_EglDisplay;
extern EGLSurface g_EglSurface;
extern EGLContext g_EglContext;
extern bool g_MenuOpen;

// Original function pointers
extern EGLBoolean (*orig_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface);
extern __int64 (*orig_renderer)(__int64 *ConfigAttrib, int a2);
extern int32_t (*orig_onInputEvent)(struct android_app* app, AInputEvent* event);
extern int (*orig_AInputQueue_getEvent)(AInputQueue* queue, AInputEvent** outEvent);

// Hook functions
EGLBoolean hook_eglSwapBuffers(EGLDisplay dpy, EGLSurface surface);
__int64 hook_renderer(__int64 *ConfigAttrib, int a2);
int32_t hook_onInputEvent(struct android_app* app, AInputEvent* event);
int hook_AInputQueue_getEvent(AInputQueue* queue, AInputEvent** outEvent);

// Core
bool InitImGui(EGLDisplay dpy, EGLSurface surface, ANativeWindow* window);
void RenderImGui();
void DrawMenu();
void ShutdownImGui();
void InstallImGuiHooks();
void InstallRendererHook(uintptr_t rendererAddr);
void InstallInputHooks();
