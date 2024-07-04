#include "UIManager.hpp"

#include <deque>
#include <array>
#include <iomanip>
#include <sstream>

// IMPORTANT(abi): Dear ImGui defines flags for captured input. These get updated
// by `ImGui::NewFrame()` or `ImGui::EndFrame()`/`ImGui::Render()`.
//	- WantCaptureMouse
//	- WantCaptureKeyboard

constexpr size_t FPS_SAMPLE_COUNT = 50;

UIManager::UIManager()
{
    ImGui::CreateContext();
}

void UIManager::initialize(GLFWwindow* hwnd)
{
    ImGui_ImplGlfw_InitForOpenGL(hwnd, true);
    ImGui_ImplOpenGL3_Init();
}

void UIManager::startFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();
}

void UIManager::endFrame()
{
    static std::deque<float> fpsSamples;

    fpsSamples.push_back(ImGui::GetIO().Framerate);
    if (fpsSamples.size() > FPS_SAMPLE_COUNT)
    {
        fpsSamples.pop_front();
    }

    std::array<float, FPS_SAMPLE_COUNT> fpsSamplesBuffer;
    std::copy(fpsSamples.begin(), fpsSamples.end(), fpsSamplesBuffer.begin());

    // Fixed-point and precision
    std::stringstream fpsStream;
    fpsStream << std::fixed << std::setprecision(2) << ImGui::GetIO().Framerate;
    std::string fps = fpsStream.str() + " fps";

    // Framerate plot
    ImGui::SameLine(ImGui::GetWindowWidth() - 370.f);
    ImGui::PlotLines(fps.c_str(), fpsSamplesBuffer.data(),
                     static_cast<int>(fpsSamplesBuffer.size()), 0, nullptr, 0.f, 350.f,
                     ImVec2(128.f, 0.f));

    render();
}

void UIManager::render()
{
    ImGui::Render();

    ImDrawData* drawData = ImGui::GetDrawData();
    ImGui_ImplOpenGL3_RenderDrawData(drawData);
}

void UIManager::font(const std::string& path, const float pixelSize)
{
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF(path.c_str(), pixelSize);
}
