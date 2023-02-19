#include "gui/gui_handler.hpp"

GUI_Handler::GUI_Handler()
{
    show_main_window = true;
    show_demo_window = false;
}

GUI_Handler::~GUI_Handler()
{
}

void GUI_Handler::ShowWindow()
{
    if (show_main_window)
    {
        MainAppWindow();
    }
    if (show_demo_window)
    {
        ImGui::ShowDemoWindow(&show_demo_window);
    }

    if (show_debug_log_window)
    {
        ImGui::ShowDebugLogWindow(&show_debug_log_window);
    }
    if (show_metrics_window)
    {
        ImGui::ShowMetricsWindow(&show_metrics_window);
    }
    if (show_settings_window)
    {
        
    }
    if (show_about_window)
    {
        ImGui::ShowAboutWindow(&show_about_window);
    }
}

void GUI_Handler::SetMainWindowState(bool state)
{
    show_main_window = state;
}

void GUI_Handler::SetDemoWindowState(bool state)
{
    show_demo_window = state;
}

void GUI_Handler::SetDebugLogWindowState(bool state)
{
    show_debug_log_window = state;
}

void GUI_Handler::SetMetricsWindowState(bool state)
{
    show_metrics_window = state;
}

void GUI_Handler::SetSettingsWindowState(bool state)
{
    show_settings_window = state;
}

void GUI_Handler::SetAboutWindowState(bool state)
{
    show_about_window = state;
}