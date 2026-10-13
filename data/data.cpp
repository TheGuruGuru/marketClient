#include "data.h"

#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <httplib.h>
static httplib::Client cli("https://europe.albion-online-data.com");

std::string Data::getItemPrice(const char *ID, const char* cities, const char* quality){
     std::string path = "/api/v2/stats/prices/" + std::string(ID) + ".json?locations=" + std::string(cities) + "&qualities=" + std::string(quality);

     auto res = cli.Get(path);
     printf("%s\n", res->body.c_str());

     return res->body;
}