#include "search.h"

#include <imgui.h>
#include <iostream>
#include <vector>
#include "../../data/data.h"


static int currentItemCat = 0;
static int currentItemSubCat = 0;
static int currentItem = 0;

static const char* const tiers[9] = {"none", "1", "2", "3", "4", "5", "6", "7", "8"};
static const char* const enchants[6] = {"none", "0", "1", "2", "3", "4"};

static int selectedTier = 0;
static int selectedEnchant = 0;

static std::vector<std::string>* pCategories;
static std::vector<std::array<std::string, 2>>* pSubCats;
static std::vector<std::array<std::string, 5>>* pItems;

static char* buf;

void search::init() {
    pCategories = Data::getCategories();
    pSubCats = Data::getSubCats();
    pItems = Data::getItems();
    currentItem = 0;
    currentItemCat = 0;
    currentItemSubCat = 0;

    buf = new char[256]{""};
}

std::string search::search(std::string prompt) {
    ImGui::Text("Filter search");
    ImGui::SetNextItemWidth(300);
    if (ImGui::BeginCombo("Category", pCategories->at(currentItemCat).c_str())) {
        for (int i = 0; i < pCategories->size(); i++) {
            if (ImGui::Selectable(pCategories->at(i).c_str())) {
                currentItemCat = i;
                currentItemSubCat = 0;
                currentItem = 0;
            }
        }
        ImGui::EndCombo();
    }

    ImGui::SameLine();

    std::vector <std::string> sc;
    for (auto &scat : *pSubCats) {
        if (pCategories->at(currentItemCat) == scat.at(1) || currentItemCat == 0 || scat.at(1) == "all") {
            sc.push_back(scat.at(0));
        }
    }

    ImGui::SetNextItemWidth(300);
    if (ImGui::BeginCombo("subCategory", sc.at(currentItemSubCat).c_str())) {
        for (int i = 0; i < sc.size(); i++) {
            if (ImGui::Selectable(sc.at(i).c_str())) {
                currentItemSubCat = i;
                currentItem = 0;
            }
        }
        ImGui::EndCombo();
    }

    ImGui::SetNextItemWidth(300);
    if (ImGui::BeginCombo("Tiers", tiers[selectedTier])) {
        for (int i = 0; i < 9; i++) {
            if (ImGui::Selectable(tiers[i])) {
                selectedTier = i;
                currentItem = 0;
            }
        }
        ImGui::EndCombo();
    }

    ImGui::SameLine();

    ImGui::SetNextItemWidth(300);
    if (ImGui::BeginCombo("Enchantement", enchants[selectedEnchant])) {
        for (int i = 0; i < 6; i++) {
            if (ImGui::Selectable(enchants[i])) {
                selectedEnchant = i;
                currentItem = 0;
            }
        }
        ImGui::EndCombo();
    }

    //input for search here
    ImGui::Text("");
    ImGui::SetNextItemWidth(400);
    if (ImGui::InputText("search", buf, 256)) currentItem = 0;

    ImGui::Text("\nselect item");

    std::vector <std::string> it;
    std::string searchString = buf;
    std::transform(searchString.begin(), searchString.end(), searchString.begin(),
            [](unsigned char c){ return std::tolower(c); });

    for (auto &i : *pItems) {

        std::string name = i.at(0);
        std::transform(name.begin(), name.end(), name.begin(),
            [](unsigned char c){ return std::tolower(c); });

        if ((i.at(1) == "all" || sc.at(currentItemSubCat) == i.at(1)               //  vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
                || (std::find(sc.begin(), sc.end(), i.at(1)) != sc.end() && currentItemSubCat == 0)) //subcat is or contains the wanted cat or is all
            && (i.at(2) == tiers[selectedTier] || selectedTier == 0 || i.at(2) == "all")                            //selected tier is correct or none
            && (i.at(3) == enchants[selectedEnchant] || selectedEnchant == 0 || i.at(3) == "all")                       //selected enchant is correct or none
            && (name.find(searchString) != std::string::npos || strlen(buf) == 0 || name == "none")) {                //search input

            it.push_back(i.at(0));
        }
    }

    if (it.size() == 0) {
        it.push_back("none");
    }

    ImGui::SetNextItemWidth(300);
    if (ImGui::BeginCombo("Item", it.at(currentItem).c_str())) {
        for (int i = 0; i < it.size(); i++) {
            if (ImGui::Selectable(it.at(i).c_str())) {
                currentItem = i;
            }
        }
        ImGui::EndCombo();
    }

    ImGui::SameLine();

    if (ImGui::Button("reset filters")) {
        selectedEnchant = 0;
        selectedTier = 0;
        currentItemSubCat = 0;
        currentItemCat = 0;
        currentItem = 0;
        delete buf;
        buf = new char[256]{""};
    }

    if (ImGui::Button(prompt.c_str())) {
        return it.at(currentItem).c_str();
    }

    return "";
}

