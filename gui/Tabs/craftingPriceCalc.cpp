#include "craftingPriceCalc.h"
#include "../../data/data.h"
#include <imgui.h>
#include <iostream>

#include "../algo/search.h"

static std::vector<std::string> queue;
static std::vector<Json::Value> items;
static std::vector<int> prices;
static std::array<std::string, 7> cities = {"blackMarket", "bridgewatch", "caerleon", "fortsterling", "lymhurst", "martlock", "thetfort"};
static int currentCity = 0;
static int totalPriceCraft = 0;
static int totalPriceBuy = 0;


void craftingCalc::init() {
    search::init();
    items.clear();
    prices.clear();
    queue.clear();
}

void craftingCalc::draw() {

    ImGui::SetNextItemWidth(300);
    if (ImGui::BeginCombo("City", cities.at(currentCity).c_str())) {
        for (int i = 0; i < cities.size(); i++) {
            if (ImGui::Selectable(cities.at(i).c_str())) {
                currentCity = i;
            }
        }
        ImGui::EndCombo();
    }

    std::string res = search::search("add recipe");


    if (res != "") {
        //do something -> add to crafting queue
        std::cout << res << std::endl;

        if (std::find(queue.begin(), queue.end(), res) == queue.end()) {
            queue.push_back(res);
            items.push_back(Data::getItemData(res));
            prices.push_back(Data::getItemPrice(cities[currentCity], items.at(items.size() - 1)["UniqueName"].asString()));
        }
    }

    ImGui::Text("\n\n");

    for (int i = 0; i < items.size(); i++) {
        ImGui::Text("item: %s", items[i]["Name"].asCString());
        ImGui::Text("buying price: %i" , prices[i]);
        ImGui::Text("crafting price:");
        int price = 0;
        for (auto &it : items[i]["Recipe"]) {
            int add = Data::getItemPrice(cities[currentCity], it["UniqueName"].asString()) * it["Amount"].asInt();
            price += add;
            ImGui::Text("price: %i" , add);
            ImGui::SameLine();
            ImGui::Text("(%i *", Data::getItemPrice(cities[currentCity], it["UniqueName"].asString()));
            ImGui::SameLine();
            ImGui::Text(" %i)", it["Amount"].asInt());
        }
        ImGui::Text("\n");
        totalPriceBuy = 0;
        totalPriceCraft = 0;
        totalPriceCraft += price;
        totalPriceBuy += prices[i];
    }

    ImGui::Text("\n==============================\ncraftingprice in total: %i", totalPriceCraft);
    ImGui::Text("\nbuying price in total: %i", totalPriceBuy);
}

