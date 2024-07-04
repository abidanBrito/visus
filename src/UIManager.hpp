#pragma once

#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM <glbinding/gl/gl.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include <string>

class UIManager
{
public:
    UIManager();
    static void initialize(GLFWwindow* hwnd);
    static void startFrame();
    static void endFrame();
    static void render();
    static void font(const std::string& path, const float pixelSize = 18);
};
