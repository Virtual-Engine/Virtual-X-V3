#include "invoker/Natives.hpp"
#include "OutfitsComponents.hpp"
#include "fiber.hpp"
#include "ui/interface.hpp"
#include "JSON/json.hpp"
#include "dirs.h"
namespace VX
{
	OutfitsComponents g_OutfitsComponents;

	void OutfitsComponents::Save(String fileName)
	{
		bool dupe = false;
		int new_dupe = 1;
		if (std::filesystem::exists(std::format("{}{}.json", util::dirs::get_directories()->get_outfits(), fileName))) {
			for (int i = 1; i < 100; i++) {
				if (std::filesystem::exists(std::format("{}{} ({}).json", util::dirs::get_directories()->get_outfits(), fileName, i))) {
					new_dupe = i + 1;
				}
				else {
					if (i != 1) {
						dupe = true;
						break;
					}
				}
			}
		}
		try {
			std::ofstream output;
			if (dupe) output = std::ofstream(std::format("{}{} ({}).json", util::dirs::get_directories()->get_outfits(), fileName, new_dupe));
			else output = std::ofstream(std::format("{}{}.json", util::dirs::get_directories()->get_outfits(), fileName));

			nlohmann::json j;

			int props[2][3];
			for (size_t i = 0; i < 3; i++) {
				props[0][i] = PED::GET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), i);
				props[1][i] = PED::GET_PED_PROP_TEXTURE_INDEX(PLAYER::PLAYER_PED_ID(), i);
			}

			int components[2][12];
			for (size_t i = 0; i < 12; i++) {
				components[0][i] = PED::GET_PED_DRAWABLE_VARIATION(PLAYER::PLAYER_PED_ID(), i);
				components[1][i] = PED::GET_PED_TEXTURE_VARIATION(PLAYER::PLAYER_PED_ID(), i);
			}

			j["outfit"]["components"] = nlohmann::json::array({
				{ components[0][0], components[0][1], components[0][2], components[0][3], components[0][4], components[0][5], components[0][6], components[0][7], components[0][8], components[0][9], components[0][10], components[0][11] },
				{ components[1][0], components[1][1], components[1][2], components[1][3], components[1][4], components[1][5], components[1][6], components[1][7], components[1][8], components[1][9], components[1][10], components[1][11] }
				});

			j["outfit"]["props"] = nlohmann::json::array({
				{ props[0][0], props[0][1], props[0][2] },
				{ props[1][0], props[1][1], props[1][2] }
				});

			j["outfit"]["model"] = ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID());

			output << j.dump(4);
			output.close();
		}
		catch (std::exception& e) {
			g_log.send("Error", "%s", e.what());
		}
	}

	void OutfitsComponents::Load(std::string name)
	{
		try {
			std::ifstream input(std::format("{}{}.json", util::dirs::get_path(outfits), name));
			if (input.good()) {
				nlohmann::json json;
				input >> json;
				input.close();

				nlohmann::json& jsondata = json["outfit"];

				auto components = jsonGet<std::vector<std::vector<int>>>(json["outfit"], "components", { { 0 } });
				auto props = jsonGet<std::vector<std::vector<int>>>(json["outfit"], "props", { { 0 } });

				for (size_t i = 0; i < 12; i++) {
					PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), i, components[0][i], components[1][i], 0);
				}

				for (size_t i = 0; i < 3; i++) {
					PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), i, props[0][i], props[1][i], 1);
				}
			}
		}
		catch (std::exception& e) {
			g_log.send("Error", "%s", e.what());
		}
	}

	OutfitsComponents* GetOutfitsComponents() { return &g_OutfitsComponents; }
}
