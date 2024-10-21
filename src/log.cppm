module;

#include <cstdint>
#include <iostream>
#include <string>
#include <imgui.h>

export module log;

import imgui_wrap;

namespace log
{
    std::string the_log;

    export void draw()
    {
        ImGui::Begin("Log");
        ImGui_Wrap::Text(the_log);
        ImGui::End();
    }

    export void write(const std::string text)
    {
        the_log += text;
    }

    export void writeln(const std::string text)
    {
        the_log += text + "\n";
    }

    export void clear()
    {
        the_log = "";
    }

}