#include "GUI.h"

void GUI::init() {
    sureToEncrypt = false;
}

void GUI::draw() {
    ImGui::Begin("Encrypt");
    ImGui::Text("Path:");
    ImGui::SameLine();
    ImGui::InputText("##path", &path);
    ImGui::SameLine();
    if(ImGui::Button("...")) {
        path = openFileDialog();
    }
    ImGui::Text("Password:");
    ImGui::SameLine();
    ImGui::InputText("##password", &password, ImGuiInputTextFlags_Password);
    
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    
    if(ImGui::Button("Encrypt")) {
        sureToEncrypt = true;
    }
    if(sureToEncrypt) {
        ImGui::Begin("Are you sure?");
        if(ImGui::Button("Yes")) {
            if(path != "" && password != "") {
                encrypt(path, message, password);
            }
            sureToEncrypt = false;
        }
        ImGui::SameLine();
        if(ImGui::Button("No")) {
            sureToEncrypt = false;
        }
        ImGui::End();
    }
    ImGui::SameLine();
    if(ImGui::Button("Decrypt")) {
        if(path != "" && password != "")
            message = decrypt(path, password);
    }
    
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::InputTextMultiline("##message", &message, ImGui::GetContentRegionAvail());

    ImGui::End();
}
