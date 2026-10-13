#include "searchSingleItem.h"
#include "../data/data.h"

static std::string message = "please search";

void searchSingleItem() {
    if (ImGui::Button("Search")) {
        auto temp = Data::getItemPrices("8608", "Bridgewatch", "0");

    }
    ImGui::Text(message.c_str());
}
