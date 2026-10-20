#include "mainWindow.h"

#include <iostream>

#include "Tabs/craftingPriceCalc.h"

#include "../enums/windowEnums.h"


static std::string message = "Hello";
static openWindow window = CRAFTING_PRICE_CALC;

void render(ImVec2 windowSize) {

    ImGui::SetNextWindowSize(ImVec2(windowSize.x *0.15, windowSize.y));
    ImGui::SetNextWindowPos(ImVec2(0, 0));

    if (ImGui::Begin("Menu", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize)) {

        if (ImGui::Button("crafting price calculator")) {
            if (window != CRAFTING_PRICE_CALC) {
                window = CRAFTING_PRICE_CALC;
                craftingCalc::init();
            }
        }
        ImGui::End();
    }

    ImGui::SetNextWindowSize(ImVec2(windowSize.x *0.85, windowSize.y));
    ImGui::SetNextWindowPos(ImVec2(windowSize.x * 0.15, 0));

    if (ImGui::Begin("mainWindow", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize)) {
        switch (window) {
            case CRAFTING_PRICE_CALC:
                craftingCalc::draw();
                break;
            default:
                std::cout << "Error: no tab selected" << std::endl;
                break;
        }
        ImGui::End();
    }
}
