#include "configs.h"

ini::IniFile components;

void Data::readComponentPrices() {
    components.load("../components.ini");
}

ini::IniFile Data::getComponentPrices(bool parse) {
    if (parse) readComponentPrices();
    return components;
}

void Data::changePrice(const char* type, const char *tier, int value) {
    components[type][tier] = value;
}

void Data::savePrices() {
    components.save("components.ini");
}
