#include "data.h"
#include <filesystem>
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <fstream>
#include <cpp-httplib/httplib.h>

static std::vector<std::array<std::string, 4>>* pItems = new std::vector<std::array<std::string, 4>> {{"none", "all", "all", "all"}, {"hello",  "all", "1", "0"}, {"sweetie", "ieufiuefh2", "1", "0"}};
static std::vector<std::array<std::string, 2>>* pSubCats = new std::vector<std::array<std::string, 2>> {{"none", "all"}};
static std::vector<std::string>* pCategories = new std::vector<std::string> {"none" };
static httplib::Client cli("https://europe.albion-online-data.com");

Json::Value Data::getItemData(const char *ID, const char *cities, const char *quality) {
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

Json::Value Data::readJson(const char* path) {

     std::ifstream file(path);
     std::string fileContents;
     std::string line;

     while (getline (file, line)) {
          fileContents += line + "\n";
     }

     return decodeJson(fileContents);
}

void Data::makeCats() {
     auto cats = readJson("../enums/categories/cats.json");

     auto members = cats.getMemberNames();

     for (const auto& name : cats.getMemberNames()) {
          pCategories->push_back(name);

          for (const auto& subCat : cats[name]) {
               pSubCats->push_back({subCat.asString(), name});
          }
     }
}

std::vector<std::string>* Data::getCategories() {
     return pCategories;
}

std::vector<std::array<std::string, 2>>* Data::getSubCats() {
     return pSubCats;
}

std::vector<std::array<std::string, 4>>* Data::getItems() {
     return pItems;
}
