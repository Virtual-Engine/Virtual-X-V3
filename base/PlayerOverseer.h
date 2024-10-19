#include "common.hpp"
#include "JSON/json.hpp"
#include "dirs.h"
#include "rlGamerInfoBase.hpp"
#include "rlSessionInfo.h"

namespace VX
{
    using json = nlohmann::json;
    void add_player(const char* itemName) {
        std::string filePath = g_utility.get_documents_path() + "\\Virtual X\\Player\\players.json";
        if (!std::ifstream(filePath)) {
            json initialData = {
                {"items", json::array()}
            };
            std::ofstream initialOutputFile(filePath);
            initialOutputFile << std::setw(4) << initialData << std::endl;
            initialOutputFile.close();
        }

        std::ifstream inputFile(filePath);
        json data;
        inputFile >> data;
        inputFile.close();

        for (const auto& item : data["items"]) {
            std::string itemName2 = item["name"];
        }

        json newItem = {
            {"name", itemName}
           
        };


        data["items"].push_back(newItem);

        std::ofstream outputFile(filePath);
        outputFile << std::setw(4) << data << std::endl;
        outputFile.close();
    }
}