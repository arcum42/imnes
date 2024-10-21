#include <SDL3/SDL.h>

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include <imgui_hex.h>

#include <cstdio>
#include <format>
#include <string>

import cpu;
import imgui_wrap;
import imgui_sdl3_wrap;
import log;

int main(int argc, char *argv[])
{
    // Initialize SDL subsystems
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    cpu::init();

    // Create a window with title "Hello World"
    SDL_Window *win = SDL_CreateWindow("imNes", 1280, 720, 0);
    if (!win)
    {
        printf("Failed to create window: %s\n", SDL_GetError());
        return 1;
    }

    // Setup SDL rendering context for ImGui
    int screenW, screenH;
    SDL_GetWindowSize(win, &screenW, &screenH);

    // Create a renderer
    SDL_Renderer *rend = SDL_CreateRenderer(win, NULL);
    if (!rend)
    {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        return 1;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_Wrap::Init(win, rend);

    // Update the screen
    SDL_UpdateWindowSurface(win);

    log::writeln("Hello, World!");
    log::writeln("Text.");

    // Begin ImGui main loop
    bool quit = false;
    bool demo = true;
    while (!quit)
    {
        // Process events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // Handle SDL events
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT)
                quit = true;

            if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event.window.windowID == SDL_GetWindowID(win))
                quit = true;
        }

        // Start the Dear ImGui frame
        ImGui_Wrap::NewFrame();

        // Just for testing.
        bool show_demo_window = true;
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // Create context for ImGui widgets
        static float globalCount = 0.0f;
        ImGui::Begin("Hello World");
        ImGui::Text("This is some useful text.");
        ImGui::SliderFloat("My Slider", &globalCount, 0.0f, 10.0f);
        if (ImGui::Button("Quit"))
        {
            quit = true;
        }
        ImGui::End();

        ImGui::Begin("Stats");
        if (ImGui::CollapsingHeader("Registers"))
        {
            ImGui_Wrap::BulletText(std::format("PC: {}", cpu::reg.PC));
            ImGui_Wrap::BulletText(std::format("AC: {}", cpu::reg.AC));
            ImGui_Wrap::BulletText(std::format("X: {}", cpu::reg.X));
            ImGui_Wrap::BulletText(std::format("Y: {}", cpu::reg.Y));
            ImGui_Wrap::BulletText(std::format("SR: {}", cpu::reg.SR));
            ImGui_Wrap::BulletText(std::format("SP: {}", cpu::reg.SP));
        }
        if (ImGui::CollapsingHeader("Flags"))
        {
            ImGui_Wrap::BulletText(std::format("Negative: {}", cpu::flag.N));
            ImGui_Wrap::BulletText(std::format("Overflow: {}", cpu::flag.V));
            ImGui_Wrap::BulletText(std::format("(Unused): {}", cpu::flag.Unused));
            ImGui_Wrap::BulletText(std::format("Break: {}", cpu::flag.B));
            ImGui_Wrap::BulletText(std::format("Decimal: {}", cpu::flag.D));
            ImGui_Wrap::BulletText(std::format("Interrupt: {}", cpu::flag.I));
            ImGui_Wrap::BulletText(std::format("Zero: {}", cpu::flag.Z));
            ImGui_Wrap::BulletText(std::format("Carry: {}", cpu::flag.C));
        }
        ImGui::End();

        log::draw();
        // Clear the window with a grey fill
        SDL_SetRenderDrawColor(rend, 128, 128, 128, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(rend);

        // Rendering
        ImGui_Wrap::Render(rend);
        SDL_RenderPresent(rend);

        SDL_UpdateWindowSurface(win);

        // Wait for a key press before exiting
        SDL_Delay(1000 / 60);
    }

    // Cleanup
    ImGui_Wrap::Shutdown();

    // Quit SDL subsystems
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
