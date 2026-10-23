#pragma once
#include <string>
#include <json/json.h>

namespace Data {
    Json::Value getItemDataAODP(const char *ID, const char* cities, const char* quality);
    Json::Value decodeJson(std::string message);
    Json::Value readJson(const char* path);
    Json::Value getItemData(std::string name);
    void setItemData(Json::Value item);

    void makeCats();

    std::vector<std::string>* getCategories();
    std::vector<std::array<std::string, 2>>* getSubCats();
    std::vector<std::array<std::string, 4>>* getItems();

}
