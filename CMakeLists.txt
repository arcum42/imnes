cmake_minimum_required(VERSION 3.28)

project(imnes CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)

include_directories(ext/imgui
    ext/imgui/backends
    ext/imgui_hex_editor)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
    PUBLIC
        ext/imgui/imgui.cpp
        ext/imgui/imgui_draw.cpp
        ext/imgui/imgui_tables.cpp
        ext/imgui/imgui_widgets.cpp
        ext/imgui/imgui_demo.cpp
        ext/imgui/backends/imgui_impl_sdl3.cpp
        ext/imgui/backends/imgui_impl_sdlrenderer3.cpp

        ext/imgui_hex_editor/imgui_hex.cpp

        src/cpu.cppm
        src/main.cpp
    PUBLIC
        FILE_SET CXX_MODULES FILES 
            src/imgui_wrap.cppm 
            src/imgui_sdl3_wrap.cppm
            src/cpu.cppm
            src/bus.cppm
            src/log.cppm
    )

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
