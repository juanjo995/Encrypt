#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"

#include "FileDialog.h"
#include "AES.h"

struct GUI {

    std::string path;
    std::string password;
    std::string message;
    
    bool sureToEncrypt;

    void init();
    void draw();
};
