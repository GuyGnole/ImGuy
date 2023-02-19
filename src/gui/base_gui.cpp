#include "gui/base_gui.hpp"
#include <thread>


ImGuy_GUI::ImGuy_GUI(std::string title, uint32_t width, uint32_t height)
{
    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
    }

    // Setup SDL OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    // Setup SDL window
    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, window_flags);

    // Setup OpenGL
    glcontext = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, glcontext);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    // Setup ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplSDL2_InitForOpenGL(window, glcontext);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Setup GUI
    gui_handler = GUI_Handler();

    gui_handler.SetMainWindowState(true);
    gui_handler.SetDemoWindowState(false);

    gui_handler.SetDebugLogWindowState(false);
    gui_handler.SetMetricsWindowState(false);
    gui_handler.SetAboutWindowState(false);

    // Run the GUI
    run();
}


ImGuy_GUI::~ImGuy_GUI()
{
    // Cleanup ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    // Cleanup SDL
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void ImGuy_GUI::run()
{
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    bool running = true;

    // Polling loop
    while (running)
    {
        // Poll events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // Handle events
            ImGui_ImplSDL2_ProcessEvent(&event);

            // Handle quit events
            if (event.type == SDL_QUIT)
                running = false;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                running = false;
        }

        // Render the GUI
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();

        // Draw the GUI
        ShowMainMenuBar();
        gui_handler.ShowWindow();
        ImGui::Render();

        SDL_GL_MakeCurrent(window, glcontext);

        glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }
}

void ImGuy_GUI::ShowMainMenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        ShowFileMenu();
        ShowEditMenu();
        ShowViewMenu();
        ShowHelpMenu();

        ImGui::EndMainMenuBar();
    }
}

void ImGuy_GUI::ShowFileMenu()
{
    if (ImGui::BeginMenu("File"))
    {
        if (ImGui::MenuItem("New", "Ctrl+N"))
        {

        }
        if (ImGui::MenuItem("Open", "Ctrl+O"))
        {
            
        }
        ImGui::Separator();
        if (ImGui::MenuItem("Save", "Ctrl+S"))
        {
            
        }
        if (ImGui::MenuItem("Save As", "Ctrl+Shift+S"))
        {
            
        }
        ImGui::Separator();
        if (ImGui::MenuItem("Exit", "Alt+F4"))
        {
            // Close the window
            SDL_Event event;
            event.type = SDL_QUIT;
            SDL_PushEvent(&event);
        }
        ImGui::EndMenu();
    }
}

void ImGuy_GUI::ShowEditMenu()
{
    if (ImGui::BeginMenu("Edit"))
    {
        if (ImGui::MenuItem("Undo", "Ctrl+Z"))
        {
            
        }
        if (ImGui::MenuItem("Redo", "Ctrl+Y"))
        {
            
        }
        ImGui::Separator();
        if (ImGui::MenuItem("Cut", "Ctrl+X"))
        {
            
        }
        if (ImGui::MenuItem("Copy", "Ctrl+C"))
        {
            
        }
        if (ImGui::MenuItem("Paste", "Ctrl+V"))
        {
            
        }
        ImGui::EndMenu();
    }
}

void ImGuy_GUI::ShowViewMenu()
{
    if (ImGui::BeginMenu("View"))
    {
        if (ImGui::MenuItem("Main Window", NULL, &private_window_flags.show_main_window))
        {
            gui_handler.SetMainWindowState(private_window_flags.show_main_window);
        }
        if (ImGui::MenuItem("Demo Window", NULL, &private_window_flags.show_demo_window))
        {
            gui_handler.SetDemoWindowState(private_window_flags.show_demo_window);
        }
        ImGui::Separator();
        if (ImGui::MenuItem("Log Window", NULL, &private_window_flags.show_app_debug_log))
        {
            gui_handler.SetDebugLogWindowState(private_window_flags.show_app_debug_log);
        }
        if (ImGui::MenuItem("Metrics Window", NULL, &private_window_flags.show_app_metrics))
        {
            gui_handler.SetMetricsWindowState(private_window_flags.show_app_metrics);
        }
        ImGui::Separator();
        if (ImGui::MenuItem("Settings Window", NULL, &private_window_flags.show_app_settings))
        {

        }
        ImGui::EndMenu();
    }
}

void ImGuy_GUI::ShowHelpMenu()
{
    if (ImGui::BeginMenu("Help"))
    {
        if (ImGui::MenuItem("About Window", NULL, &private_window_flags.show_app_about))
        {
            gui_handler.SetAboutWindowState(private_window_flags.show_app_about);
        }
        ImGui::EndMenu();
    }
}