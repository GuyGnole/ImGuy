#ifndef GUI_HPP
#define GUI_HPP

#include "global_header.hpp"

#include <stdio.h>
#include <string>

#include <SDL.h>
#include <SDL_opengl.h>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

#include "gui/gui_handler.hpp"


class ImGuy_GUI
{
public:
    ImGuy_GUI(std::string title, uint32_t width, uint32_t height);
    ~ImGuy_GUI();
private:
    void run();

    SDL_Window* window;
    SDL_GLContext glcontext;

    GUI_Handler gui_handler;

    void ShowMainMenuBar();
    
    void ShowFileMenu();
    void ShowEditMenu();
    void ShowViewMenu();
    void ShowHelpMenu();

protected:
    typedef struct
    {
        bool show_main_window;
        bool show_demo_window;

        bool show_app_settings;

        bool show_app_metrics;
        bool show_app_debug_log;
        bool show_app_about;
    } GUI_WindowFlags;
    GUI_WindowFlags private_window_flags = { 
        true, 
        false, 
        false, 
        false, 
        false, 
        false };
};



#endif // GUI_HPP