module;

#include <imgui.h>
#include <format>
#include <string>
#include <vector>

export module imgui_wrap;

// ImGui does not use standard C++ features like strings, and makes you futz around with char* and such.
// Just wrapping some of those functions here for convenience.

// I may add other convenience functions as well.

// A fair number of these will probably not actually be used, but here in case I want to use them.

// (And yes, I was feeling irritable on implementing, then decided to stay with the naming scheme.)

namespace ImGui_Wrap
{
    export void Begin(const std::string fucking_string, bool *p_open = NULL, ImGuiWindowFlags flags = 0)
    {
        ImGui::Begin((const char *)fucking_string.c_str(), p_open, flags);
    }

    // Just for consistancy.
    export void End()
    {
        ImGui::End();
    }

    export bool CollapsingHeader(const std::string fucking_string, ImGuiTreeNodeFlags flags = 0)
    {
        return ImGui::CollapsingHeader((const char *)fucking_string.c_str(), flags);
    }

    export void Text(const std::string fucking_string)
    {
        ImGui::Text("%s", (const char *)fucking_string.c_str());
    }

    export void BulletText(const std::string fucking_string)
    {
        ImGui::BulletText("%s", (const char *)fucking_string.c_str());
    }

    export void BulletsText(const std::vector<std::string> fucking_strings)
    {
        for (auto str : fucking_strings)
        {
            BulletText(str);
        }
    }
}