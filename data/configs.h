#pragma once

#include <map>
#include <string>
#include <ini/inicpp.h>

namespace Data {
    void readComponentPrices();

    ini::IniFile getComponentPrices(bool parse = false);

    void changePrice(const char* type, const char* tier, int value);

    void savePrices();
}
