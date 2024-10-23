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

bool quit = false;
bool demo = true;

SDL_Window *main_window;
SDL_Renderer *main_renderer;

void draw_content()
{
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
}

bool init_sdl()
{
    // Initialize SDL subsystems
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return false;
    }

    // Create a window.
    main_window = SDL_CreateWindow("imNes", 1280, 720, 0);
    if (!main_window)
    {
        printf("Failed to create window: %s\n", SDL_GetError());
        return false;
    }

    // Create a renderer
    main_renderer = SDL_CreateRenderer(main_window, NULL);
    if (!main_renderer)
    {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

void init_imgui()
{
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
    ImGui_Wrap::Init(main_window, main_renderer);
}

int main(int argc, char *argv[])
{
    if (!init_sdl())
        return 1;

    init_imgui();

    cpu::init();

    // Update the screen
    SDL_UpdateWindowSurface(main_window);

    log::writeln("Hello, World!");
    log::writeln("Text.");

    // Begin ImGui main loop
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

            if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event.window.windowID == SDL_GetWindowID(main_window))
                quit = true;
        }

        // Start the Dear ImGui frame
        ImGui_Wrap::NewFrame();

        draw_content();

        // Clear the window with a grey fill
        SDL_SetRenderDrawColor(main_renderer, 128, 128, 128, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(main_renderer);

        // Rendering
        ImGui_Wrap::Render(main_renderer);
        SDL_RenderPresent(main_renderer);

        SDL_UpdateWindowSurface(main_window);

        // Wait for a key press before exiting
        SDL_Delay(1000 / 60);
    }

    // Cleanup
    ImGui_Wrap::Shutdown();

    // Quit SDL subsystems
    SDL_DestroyRenderer(main_renderer);
    SDL_DestroyWindow(main_window);
    SDL_Quit();

    return 0;
}
