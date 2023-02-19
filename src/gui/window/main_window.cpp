#include "gui/window/main_window.hpp"

void MainAppWindow()
{
    ImGui::Begin("Main Window", NULL, (ImGuiWindowFlags_NoCollapse ));
    ImGui::Text("Hello, world!");
    ImGui::End();
}