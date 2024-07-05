#pragma once

#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM <glbinding/gl/gl.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include <string>

namespace visus
{
    namespace ui
    {
        void initialize(GLFWwindow* hwnd);
        void startFrame();
        void endFrame();
        void render();
        void font(const std::string& path, const float pixelSize = 18);
    } // namespace ui

} // namespace visus
