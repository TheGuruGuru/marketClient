#include "mainWindow.h"

#include "../data/data.h"
#include "searchSingleItem.h"

#include "../enums/windowEnums.h"


static std::string message = "Hello";
static openWindow window = SEARCH_SINGLE_ITEM;

void render(ImVec2 windowSize) {

    ImGui::SetNextWindowSize(ImVec2(windowSize.x *0.15, windowSize.y));
    ImGui::SetNextWindowPos(ImVec2(0, 0));

    if (ImGui::Begin("Menu", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize)) {

        if (ImGui::Button("Search for single Item")) {
            window = SEARCH_SINGLE_ITEM;
        }
        if (ImGui::Button("Empty")) {
            window = EMPTY;
        }

    } ImGui::End();

    ImGui::SetNextWindowSize(ImVec2(windowSize.x *0.85, windowSize.y));
    ImGui::SetNextWindowPos(ImVec2(windowSize.x * 0.15, 0));

    if (ImGui::Begin("mainWindow", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize)) {
        switch (window) {
            case SEARCH_SINGLE_ITEM:
                searchSingleItem();
                break;
            case EMPTY:
                break;
            default:
                break;
        }
    } ImGui::End();
}
