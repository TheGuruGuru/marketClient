#pragma once
#include <string>
#include <json/json.h>

namespace Data {
    Json::Value getItemPrices(const char *ID, const char* cities, const char* quality);

    Json::Value decodeJson(std::string message);
}
