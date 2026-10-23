#include "editData.h"

#include <imgui.h>
#include <iostream>
#include <json/value.h>

#include "../../data/data.h"
#include "../algo/search.h"
#include <json/writer.h>

static Json::Value ItemData;
static bool itemSet = false;
static std::vector<std::string> newIngridient;
static std::vector<int> amounts;
static int newNutrition = 0;
static int newNutritionNeeded = 0;

void edit::init() {
    search::init();
}


void edit::draw() {
    std::string res;
    if (!itemSet) res = search::search("load item");

    if (!res.empty()) {
        //std::cout << res << std::endl;

        ItemData = Data::getItemData(res);
        //std::cout << ItemData << std::endl;
        itemSet = true;

        newNutritionNeeded = ItemData["nutritionNeeded"].asInt();
        newNutrition = ItemData["nutrition"].asInt();

        for (auto &item : ItemData["Recipe"]) {
            newIngridient.push_back(item["UniqueName"].asString());
            amounts.push_back(item["Amount"].asInt());
        }
    }

    if (itemSet) {
        ImGui::Text("loaded item: %s\n\n", ItemData["Name"].asCString());
        ImGui::Text("Unique name: %s", ItemData["UniqueName"].asCString());
        ImGui::Text("name: %s", ItemData["Name"].asCString());
        ImGui::Text("tier: %s",  ItemData["Tier"].asCString());
        ImGui::Text("nutrition: %i",  ItemData["nutrition"].asInt());
        ImGui::Text("nutrition needed: %i",  ItemData["nutritionNeeded"].asInt());

        ImGui::Text("\n");
        ImGui::InputInt("edit nutrition", &newNutrition);
        ImGui::InputInt("edit nutrition needed", &newNutritionNeeded);

        ImGui::Text("\n");
        ImGui::Text("\ncurrent Recipe:\n");
        for (auto &item : ItemData["Recipe"]) {
            ImGui::Text("   %s x %i", item["UniqueName"].asCString(), item["Amount"].asInt());
        }

        ImGui::Text("\nedit recipe:\n");
        std::string ing = search::search("add ingriedient");

        ImGui::Text("\n\n");
        if (ing != "") {
            if (std::find(newIngridient.begin(), newIngridient.end(), ing) == newIngridient.end()) {
                Json::Value ingriedient = Data::getItemData(ing);
                newIngridient.push_back(ingriedient["UniqueName"].asString());
                amounts.push_back(1);
            }
        }

        for (int i = 0; i < newIngridient.size(); i++) {
            if (newIngridient[i] != "none" && newIngridient[i] != "") {
                ImGui::SetNextItemWidth(200);
                std::string label = " x " + newIngridient[i];
                ImGui::InputInt(label.c_str(), &amounts[i]);
                ImGui::SameLine();
                ImGui::SetNextItemWidth(200);
                if (ImGui::Button(("remove " + newIngridient[i]).c_str())) {
                    newIngridient.erase(newIngridient.begin() + i);
                    amounts.erase(amounts.begin() + i);
                }
            }
        }

        ImGui::Text("\n");
        if (ImGui::Button("save Data")) {
            std::cout << "saved recipe: " << std::endl;
            Json::Value newRec(Json::arrayValue); //make recipe to Json value TODO make it Json in the first place

            for (int i = 0; i < newIngridient.size(); i++) {
                std::cout << newIngridient[i] << "x" << amounts[i] << std::endl;

                Json::Value ingr(Json::objectValue);
                ingr["UniqueName"] = newIngridient[i].c_str();
                ingr["Amount"] = amounts[i];
                newRec.append(ingr);
            }

            if (newRec.empty()) {
                Json::Value ingr(Json::objectValue);
                ingr["UniqueName"] = "none";
                ingr["Amount"] = 0;
                newRec.append(ingr);
            }

            std::cout << "saved Values: " << newNutrition << " " << newNutritionNeeded << "\n";

            //edit values
            ItemData["nutrition"] = newNutrition;
            ItemData["nutritionNeeded"] = newNutritionNeeded;
            ItemData["Recipe"]=newRec;

            //save newItem into corresponding file
            Data::setItemData(ItemData);
            itemSet = false;

            newIngridient.clear();
            amounts.clear();
        }

        ImGui::Text("\n\n");
        if (ImGui::Button("unload item")) {
            itemSet = false;
        }
    }
}
