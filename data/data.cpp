#include "data.h"

#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <httplib.h>


static httplib::Client cli("https://europe.albion-online-data.com");

Json::Value Data::getItemPrices(const char *ID, const char* cities, const char* quality) {
     std::string path = "/api/v2/stats/prices/" + std::string(ID) + ".json?locations=" + std::string(cities);

     if (quality != "0") {
          path += + "&qualities=" + std::string(quality);
     }

     auto res = cli.Get(path);
     printf("%s\n", res->body.c_str());

     Json::Value root;

     if (res != nullptr && res->status == 200) {
          root = decodeJson(res->body);
          if (root != NULL) {
               return root;
          }
          return "error reading json";
     }
     return "error fetching data";
}


Json::Value Data::decodeJson(std::string message) {

     Json::Value root;
     Json::Reader reader;

     bool parsingSuccessful = reader.parse(message, root);

     if (!parsingSuccessful) return NULL;

     return root;
}