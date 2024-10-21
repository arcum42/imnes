module;

#include <SDL3/SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

export module imgui_sdl3_wrap;

// Seperating some of the convenience functions here because they are specific to using sdl 3 as a backend.

namespace ImGui_Wrap
{
    export void Init(SDL_Window *window, SDL_Renderer *renderer)
    {
        // Setup Platform/Renderer backends
        ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
        ImGui_ImplSDLRenderer3_Init(renderer);
    }

    export void Shutdown()
    {
        ImGui_ImplSDLRenderer3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
    }

    export void NewFrame()
    {
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
    }

    export void Render(SDL_Renderer *renderer)
    {
        ImGui::Render();
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
    }
}