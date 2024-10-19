#include "invoker/Natives.hpp"
#include "Teleport.hpp"
#include "fiber.hpp"
#include "ui/interface.hpp"
#include "JSON/json.hpp"
#include "dirs.h"
namespace VX
{
	Teleport g_Teleport;

	void Teleport::Save(String fileName, Vector3 Coordinates)
	{
		bool dupe = false;
		int new_dupe = 1;
		if (std::filesystem::exists(std::format("{}{}.json", util::dirs::get_directories()->get_teleport(), fileName))) {
			for (int i = 1; i < 100; i++) {
				if (std::filesystem::exists(std::format("{}{} ({}).json", util::dirs::get_directories()->get_teleport(), fileName, i))) {
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
			if (dupe) output = std::ofstream(std::format("{}{} ({}).json", util::dirs::get_directories()->get_teleport(), fileName, new_dupe));
			else output = std::ofstream(std::format("{}{}.json", util::dirs::get_directories()->get_teleport(), fileName));

			nlohmann::json j;

			j["Teleport"]["x"] = Coordinates.x;
			j["Teleport"]["y"] = Coordinates.y;
			j["Teleport"]["z"] = Coordinates.z;

			output << j.dump(4);
			output.close();
		}
		catch (std::exception& e) {
			g_log.send("Error", "%s", e.what());
		}
	}
	void Teleport::Load(std::string name)
	{
		try {
			std::ifstream input(std::format("{}{}.json", util::dirs::get_path(teleport), name));
			if (input.good()) {
				nlohmann::json json;
				input >> json;
				input.close();

				nlohmann::json& jsondata = json["Teleport"];

				Vector3 Coordinates;
				Coordinates.x = jsondata["x"];
				Coordinates.y = jsondata["y"];
				Coordinates.z = jsondata["z"];

				to_coords(PLAYER::PLAYER_PED_ID(), Coordinates, false, false);
			}
		}
		catch (std::exception& e) {
			g_log.send("Error", "%s", e.what());
		}
	}
	void Teleport::to_coords(Entity e, Vector3 coords, bool AutoCorrectGroundHeight, bool IgnoreCurrentPedVehicle)
	{
		Entity TargetEntity = e;
		bool TeleportTransition = TargetEntity == PLAYER::PLAYER_PED_ID();


		if (ENTITY::IS_AN_ENTITY(TargetEntity))
		{
			request_network_control(TargetEntity);

			if (PED::IS_PED_IN_ANY_VEHICLE(TargetEntity, false) && !IgnoreCurrentPedVehicle)
			{
				TargetEntity = PED::GET_VEHICLE_PED_IS_USING(TargetEntity);
			}

			if (!AutoCorrectGroundHeight)
			{
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(TargetEntity, coords.x, coords.y, coords.z, false, false, true);
			}
			else
			{
				bool GroundFound = false;
				static std::array<float, 21> GroundCheckHeight = { 0.0f, 50.0f, 100.0f, 150.0f, 200.0f, 250.0f, 300.0f, 350.0f, 400.0f, 450.0f, 500.0f, 550.0f, 600.0f, 650.0f, 700.0f, 750.0f, 800.0f, 850.0f, 900.0f, 950.0f, 1000.00f };

				for (const float& CurrentHeight : GroundCheckHeight)
				{
					ENTITY::SET_ENTITY_COORDS_NO_OFFSET(TargetEntity, coords.x, coords.y, CurrentHeight, false, false, true);
					fiber::current()->sleep();
					if (MISC::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, CurrentHeight, &coords.z, false, false))
					{
						GroundFound = true;
						coords.z += 3.0f;
						break;
					}
				}

				if (!GroundFound)
				{
					Vector3 ClosestRoadCoord;
					if (PATHFIND::GET_CLOSEST_ROAD(coords.x, coords.y, coords.z, 1.0f, 1,
						&ClosestRoadCoord, &ClosestRoadCoord, NULL, NULL, NULL, NULL))
					{
						coords = ClosestRoadCoord;
					}

				}
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(TargetEntity, coords.x, coords.y, coords.z, false, false, true);
			}
			if (TeleportTransition)
				STREAMING::SWITCH_TO_MULTI_SECONDPART(TargetEntity);
		}
	}
	void Teleport::request_network_control(Entity Entity)
	{
		int EntityTick = 0;
		int IdTick = 0;
		while (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(Entity) && EntityTick <= 25)
		{
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Entity);
			EntityTick++;
		}
		if (NETWORK::NETWORK_IS_SESSION_STARTED())
		{
			int netID = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(Entity);
			while (!NETWORK::NETWORK_HAS_CONTROL_OF_NETWORK_ID(netID) && IdTick <= 25)
			{
				NETWORK::NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(netID);
				IdTick++;
			}
			NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netID, true);
		}
	}

	Teleport* GetTeleport() { return &g_Teleport; }
}
