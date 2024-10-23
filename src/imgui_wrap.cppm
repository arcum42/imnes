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

namespace ImGui_Wrap
{
    export void Begin(const std::string str, bool *p_open = NULL, ImGuiWindowFlags flags = 0)
    {
        ImGui::Begin((const char *)str.c_str(), p_open, flags);
    }

    // Just for consistancy.
    export void End()
    {
        ImGui::End();
    }

    export bool CollapsingHeader(const std::string str, ImGuiTreeNodeFlags flags = 0)
    {
        return ImGui::CollapsingHeader((const char *)str.c_str(), flags);
    }

    export void Text(const std::string str)
    {
        ImGui::Text("%s", (const char *)str.c_str());
    }

    export void BulletText(const std::string str)
    {
        ImGui::BulletText("%s", (const char *)str.c_str());
    }

    export void BulletsText(const std::vector<std::string> strs)
    {
        for (auto str : strs)
        {
            BulletText(str);
        }
    }
}