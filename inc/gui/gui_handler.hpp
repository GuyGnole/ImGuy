#ifndef GUI_HANDLER_HPP
#define GUI_HANDLER_HPP

#include "global_header.hpp"
#include "imgui.h"

#include "gui/window/main_window.hpp"

class GUI_Handler
{
public:
    GUI_Handler();
    ~GUI_Handler();

    void ShowWindow();

    void SetMainWindowState(bool state);
    void SetDemoWindowState(bool state);

    void SetDebugLogWindowState(bool state);
    void SetMetricsWindowState(bool state);
    void SetSettingsWindowState(bool state);

    void SetAboutWindowState(bool state);
private:
    bool show_main_window;
    bool show_demo_window;
    bool show_debug_log_window;
    bool show_metrics_window;
    bool show_settings_window;
    bool show_about_window;
};

#endif // GUI_HANDLER_HPP