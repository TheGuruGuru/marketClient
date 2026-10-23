#include "craftingPriceCalc.h"
#include "../../data/data.h"
#include <imgui.h>
#include <iostream>

#include "../algo/search.h"

std::vector<std::string> queue;

void craftingCalc::init() {
    search::init();
}

void craftingCalc::draw() {
    std::string res = search::search("add recipe");

    if (res != "") {
        //do something -> add to crafting queue
        std::cout << res << std::endl;

        if (std::find(queue.begin(), queue.end(), res) == queue.end()) {
            queue.push_back(res);
        }
    }

    ImGui::Text("Queue: \n\n");

    for (auto &el : queue) {
        ImGui::Text(el.c_str());
    }
}
