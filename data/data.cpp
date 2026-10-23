#include "data.h"
#include <filesystem>
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <fstream>
#include <cpp-httplib/httplib.h>

static std::vector<std::array<std::string, 5>>* pItems = new std::vector<std::array<std::string, 5>> {};
static std::vector<std::array<std::string, 2>>* pSubCats = new std::vector<std::array<std::string, 2>> {{"none", "all"}};
static std::vector<std::string>* pCategories = new std::vector<std::string> {"none" };
static httplib::Client cli("https://europe.albion-online-data.com");

Json::Value Data::getItemDataAODP(const char *ID, const char *cities, const char *quality) {
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

std::string Data::getItemSubCategory(std::string name) {
     Json::Value root;
     std::string subCat = "";

     for (auto &item : *pItems) { //get subcategory of item
          if (item[5] == name) {
               subCat = item[1];
               break;
          }
     }

     return subCat;
}

Json::Value Data::getItemData(std::string name) {
     Json::Value root;
     std::string cat = "";
     std::string subCat = "";

     for (auto &item : *pItems) { //get subcategory of item
          if (item[0] == name) {
               subCat = item[1];
               break;
          }
     }
     if (subCat == "") {
          std::cout << "error sc" << std::endl;
     }

     for (auto &item : *pSubCats) { //get category of subcategory
          if (item[0] == subCat) {
               cat = item[1];
               break;
          }
     }
     if (cat == "") {
          std::cout << "error c" << std::endl;
     }

     std::string path = "../data/categories/" + cat + ".json";
     root = readJson(path.c_str());

     //std::cout << root << std::endl;

     Json::Value Item;

     name.erase(name.size()-1); //remove the tier from the name again
     name.erase(name.size()-1);
     name.erase(name.size()-1);
     name.erase(name.size()-1);


     for (auto &item : root[subCat]) {
          if (item["Name"].asString() == name) {
               return item;
          }
     }

     return "error getting item";

}

void Data::setItemData(Json::Value Item) {
     Json::Value root;
     std::string cat = "";
     std::string subCat = "";

     for (auto &item : *pItems) { //get subcategory of item
          if (item[0] == Item["Name"].asString() + " " + Item["Tier"].asString()) {
               subCat = item[1];
               break;
          }
     }
     if (subCat == "") {
          std::cout << "error sc" << std::endl;
     }

     for (auto &item : *pSubCats) { //get category of subcategory
          if (item[0] == subCat) {
               cat = item[1];
               break;
          }
     }
     if (cat == "") {
          std::cout << "error c" << std::endl;
     }

     std::string path = "../data/categories/" + cat + ".json";
     root = readJson(path.c_str());

     for (auto &item : root[subCat]) {
          if (item["Name"].asString() == Item["Name"].asString()) {
               item = Item;
          }
     }

     std::ofstream file_id(path);

     Json::StyledWriter styledWriter;
     file_id << styledWriter.write(root);

     file_id.close();

}

int Data::getItemPrice(std::string city, std::string uName) {
     Json::Value root;
     root = readJson(("../data/prices/" + city + ".json").c_str());

     return root[uName].asInt();
}

void Data::setItemPrice(std::string city, std::string uName, int price) {
     Json::Value root;
     root = readJson(("../data/prices/" + city + ".json").c_str());

     root[uName] = price;

     std::ofstream file_id("../data/prices/" + city + ".json");

     Json::StyledWriter styledWriter;
     file_id << styledWriter.write(root);

     file_id.close();
}

void Data::makeCats() {
     for (const auto & entry : std::filesystem::directory_iterator("../data/categories")){
          std::string name = entry.path().filename().replace_extension("").string();

          if (name != "none") {
               pCategories->push_back(name);
               //std::cout << name << std::endl;
               Json::Value category = readJson(("../data/categories/" + name + ".json").c_str());

               for (const auto& subCat : category.getMemberNames()) {
                    pSubCats->push_back({subCat, name});
                    Json::Value Items = category[subCat];

                    for (const auto& item : Items) {
                         if (item["Name"].asString() != "") {
                              std::string s = item["Tier"].asString();

                              std::vector<std::string> tokens;
                              if (s.length() == 3) {

                                   size_t pos = 0;
                                   std::string token;
                                   while ((pos = s.find(".")) != std::string::npos) {
                                        token = s.substr(0, pos);
                                        tokens.push_back(token);
                                        s.erase(0, pos + 1);
                                   }
                                   tokens.push_back(s);
                              } else {
                                   tokens.push_back("1");
                                   tokens.push_back("0");
                              }

                              pItems->push_back({item["Name"].asString() + " " + item["Tier"].asString(), subCat, tokens[0], tokens[1], item["UniqueName"].asString()});
                         }
                    }
               }
          }
     }
}


std::vector<std::string>* Data::getCategories() {
     return pCategories;
}

std::vector<std::array<std::string, 2>>* Data::getSubCats() {
     return pSubCats;
}

std::vector<std::array<std::string, 5>>* Data::getItems() {
     return pItems;
}
