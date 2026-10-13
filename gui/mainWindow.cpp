#include "mainWindow.h"
#include "../data/data.h"

static std::string message = "Hello";

void render(ImVec2 windowSize) {

    ImGui::SetNextWindowSize(windowSize);
    ImGui::SetNextWindowPos(ImVec2(0, 0));

    if (ImGui::Begin("mainWindow", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar)) {

        if (ImGui::Button("Search")) {
            message = Data::getItemPrice("T8_BAG", "Caerleon,Bridgewatch", "2");
        }
        ImGui::Text(message.c_str());

    } ImGui::End();
}
