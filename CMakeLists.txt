# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(Encrypt VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES WIN32
            src/main.cpp
            src/GUI.cpp
            include/imgui/misc/cpp/imgui_stdlib.cpp
            include/imgui/imgui.cpp
            include/imgui/imgui_draw.cpp
            include/imgui/imgui_widgets.cpp
            include/imgui/imgui_tables.cpp
            include/imgui/backends/imgui_impl_glfw.cpp
            include/imgui/backends/imgui_impl_opengl3.cpp
            include/tiny-AES-c/aes.c
            include/glad/src/glad.c)

if(WIN32)
    set(LINK_LIBRARIES  glfw3
                        # Replace this line with the proper path to your OpenGL32.Lib file on Windows
                        "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22621.0/um/x64/OpenGL32.Lib"
                        nfd
                        )
elseif(UNIX)
    set(LINK_LIBRARIES  glfw #You may need to substitute this with "glfw3"
                        nfd
                        )
endif()

include_directories( include/glew-2.1.0/include
                     include/
                     include/glfw-3.4/include
                     include/imgui
                     include/imgui/backends
                     include/glad/include)

add_subdirectory(include/nativefiledialog-extended)

link_directories(   include/glew-2.1.0/lib/Release/x64
                    include/glfw-3.4/build/src/Debug
                    lib)

# Add the executable
add_executable(Encrypt ${SOURCES})

target_link_libraries(Encrypt ${LINK_LIBRARIES})
