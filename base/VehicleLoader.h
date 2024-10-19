#include "JSON/json.hpp"
#include "invoker/Natives.hpp"
#include "fiber.hpp"
#include "dirs.h"
#include "queue.h"

namespace VX
{
	inline Entity m_current_ent{};
	inline float m_heading{};
	inline Hash m_veh_model_hash{};
	inline bool m_running = false;
	inline bool m_shutdown_preview = false;
	inline std::chrono::time_point<std::chrono::steady_clock> m_rotation_start_time;

	Vector3 subtract(Vector3 a, Vector3 b) {
		Vector3 result;
		result.x = a.x - b.x;
		result.y = a.y - b.y;
		result.z = a.z - b.z;
		return result;
	}

	Vector3 multiply(Vector3 v, float scalar) {
		Vector3 result;
		result.x = v.x * scalar;
		result.y = v.y * scalar;
		result.z = v.z * scalar;
		return result;
	}

	Vector3 rotation_to_direction(Vector3 rotation) {
		float radPitch = rotation.x * (3.14159265358979323846 / 180.0f);
		float radYaw = rotation.z * (3.14159265358979323846 / 180.0f);

		Vector3 direction;
		direction.x = -sin(radYaw) * cos(radPitch);
		direction.y = cos(radYaw) * cos(radPitch);
		direction.z = sin(radPitch);

		return direction;
	}

	Vector3 add(Vector3 a, Vector3 b) {
		Vector3 result;
		result.x = a.x + b.x;
		result.y = a.y + b.y;
		result.z = a.z + b.z;
		return result;
	}

	bool request_model(Hash hash) {
		if (STREAMING::HAS_MODEL_LOADED(hash)) {
			return true;
		}

		bool has_loaded;

		if (STREAMING::IS_MODEL_VALID(hash) && STREAMING::IS_MODEL_IN_CDIMAGE(hash)) {
			do {
				has_loaded = STREAMING::HAS_MODEL_LOADED(hash);
				if (has_loaded)
					break;

				STREAMING::REQUEST_MODEL(hash);

				fiber::current()->sleep();
			} while (!has_loaded);

			return true;
		}

		return false;
	}

	Vehicle spawn(Hash hash, Vector3 location, float heading, bool is_networked, bool script_veh) {
		if (request_model(hash)) {
			auto veh =
				VEHICLE::CREATE_VEHICLE(hash, location.x, location.y, location.z, heading, is_networked, script_veh, false);

			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);

			return veh;
		}
		return 0;
	}

	inline void preview_vehicle(Hash hash) {
		if (m_running && m_veh_model_hash != hash) {
			if (m_running)
				m_shutdown_preview = true;
			return;
		}

		if (!m_running) {
			m_veh_model_hash = hash;
		}

		if (m_running) {
			return;
		}

		m_running = true;
		g_queue.add([&] {
			m_heading = 0.f;
			m_rotation_start_time = std::chrono::steady_clock::now();

			while (!m_shutdown_preview && g_running && GetRenderer()->m_opened
				&& GetRenderer()->m_current_sub_menu
				&& !GetRenderer()->m_UpKeyPressed && !GetRenderer()->m_down_pressed && !GetRenderer()->m_BackKeyPressed) {
				Vector3 location{};

				if (m_current_ent == 0) {
					m_current_ent = spawn(m_veh_model_hash, location, 0.f, false, false);
					if (m_current_ent) {
						ENTITY::FREEZE_ENTITY_POSITION(m_current_ent, true);
						ENTITY::SET_ENTITY_ALPHA(m_current_ent, 170, false);
						ENTITY::SET_ENTITY_COLLISION(m_current_ent, false, false);
						ENTITY::SET_ENTITY_COMPLETELY_DISABLE_COLLISION(m_current_ent, false, false);
						ENTITY::SET_ENTITY_CAN_BE_DAMAGED(m_current_ent, false);
						ENTITY::SET_ENTITY_PROOFS(m_current_ent, true, true, true, true, true, true, true, true);
						ENTITY::SET_CAN_CLIMB_ON_ENTITY(m_current_ent, false);
						OBJECT::SET_OBJECT_ALLOW_LOW_LOD_BUOYANCY(m_current_ent, false);
					}
				}

				ENTITY::SET_ENTITY_HEADING(m_current_ent, m_heading);
				Vector3 minimum, maximum;
				MISC::GET_MODEL_DIMENSIONS(m_current_ent, &minimum, &maximum);
				Vector3 camera_rotation = CAM::GET_FINAL_RENDERED_CAM_ROT(0);
				Vector3 gameplay_camera_direction = rotation_to_direction(camera_rotation);
				Vector3 size = subtract(maximum, minimum); // Remplace 'maximum - minimum'
				Vector3 gameplay_camera_position = add(CAM::GET_FINAL_RENDERED_CAM_COORD(), multiply(gameplay_camera_direction, 5.f));
				Vector3 vehicle_spawn_position = add(gameplay_camera_position, multiply(gameplay_camera_direction, size.y));

				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(m_current_ent,
					vehicle_spawn_position.x,
					vehicle_spawn_position.y,
					vehicle_spawn_position.z,
					FALSE,
					FALSE,
					FALSE);

				GetRenderer()->DrawInWorldBox(m_current_ent, { 255, 255, 255, 255 });

				auto now = std::chrono::steady_clock::now();
				auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_rotation_start_time)
					.count()
					/ 1000.0;

				m_heading = (elapsed_time / 10.0) * 360.0;
				m_heading = fmod(m_heading, 360.0);

				fiber::current()->sleep();
			}

			ENTITY::DELETE_ENTITY(&m_current_ent);

			m_veh_model_hash = {};
			m_shutdown_preview = false;
			m_running = false;
			m_current_ent = NULL;
			});
	}

	int32_t Spoiler, FBumper, RBumper, SSkirt, Exhaust, Grille, Chasis, Hood, Fender, RFender, Roof, Engine, Brakes, Transmission, Horns, Suspension, Armor, Turbo, TSmoke, Xenon, Wheels, Windows, Plateholder, Vanity, Trims, Ornaments, Dashboard, Dial, DoorSpeaker, Seats, SteeringWheel, Shifter, Plaques, Speakers, Trunk, Hydraulics, EngineBlock, Filter, Struts, Arch, Aerials, TrimTwo, Tank, Livery = 0;
	enum VehicleModTypes
	{
		MOD_SPOILER = 0,
		MOD_FRONTBUMPER = 1,
		MOD_REARBUMPER = 2,
		MOD_SIDESKIRT = 3,
		MOD_EXHAUST = 4,
		MOD_CHASSIS = 5, // or roll cage
		MOD_GRILLE = 6,
		MOD_HOOD = 7,
		MOD_FENDER = 8,
		MOD_RIGHTFENDER = 9,
		MOD_ROOF = 10,
		MOD_ENGINE = 11,
		MOD_BRAKES = 12,
		MOD_TRANSMISSION = 13,
		MOD_HORNS = 14,
		MOD_SUSPENSION = 15,
		MOD_ARMOR = 16,
		MOD_UNK17 = 17, // ModToggleTurbo use 18
		MOD_TURBO = 18,
		MOD_UNK19 = 19, // ModToggleTireSmoke use 20
		MOD_TIRESMOKE = 20,
		MOD_UNK21 = 21, // ModToggleXenon use 22
		MOD_XENONLIGHTS = 22,
		MOD_FRONTWHEELS = 23,
		MOD_BACKWHEELS = 24, // Bikes only

		// Benny's
		MOD_PLATEHOLDER = 25,
		MOD_VANITY_PLATES = 26,
		MOD_TRIM = 27,
		MOD_ORNAMENTS = 28,
		MOD_DASHBOARD = 29,
		MOD_DIAL = 30,
		MOD_DOOR_SPEAKER = 31,
		MOD_SEATS = 32,
		MOD_STEERINGWHEEL = 33,
		MOD_SHIFTER_LEAVERS = 34,
		MOD_PLAQUES = 35,
		MOD_SPEAKERS = 36,
		MOD_TRUNK = 37,
		MOD_HYDRULICS = 38,
		MOD_ENGINE_BLOCK = 39,
		MOD_AIR_FILTER = 40,
		MOD_STRUTS = 41,
		MOD_ARCH_COVER = 42,
		MOD_AERIALS = 43,
		MOD_TRIM_2 = 44,
		MOD_TANK = 45,
		MOD_WINDOWS = 46,
		MOD_UNK47 = 47, // idk
		MOD_LIVERY = 48,
	};
	void save(std::string name) {
		std::string MenuFolderPath = util::dirs::get_directories()->get_vehicle();

		nlohmann::json jsonData;

		jsonData["Vehicle"]["Red"] = handred1;
		jsonData["Vehicle"]["Green"] = handgreen2;
		jsonData["Vehicle"]["Blue"] = handblue3;

		jsonData["Vehicle"]["Red1"] = handred4;
		jsonData["Vehicle"]["Green1"] = handgreen5;
		jsonData["Vehicle"]["Blue1"] = handblue6;

		jsonData["Vehicle"]["Xenon"] = Xenon;

		jsonData["Vehicle"]["Red2"] = neon.r;
		jsonData["Vehicle"]["Green2"] = neon.g;
		jsonData["Vehicle"]["Blue2"] = neon.b;

		jsonData["Vehicle"]["Right"] = neonright;
		jsonData["Vehicle"]["Left"] = neonleft;
		jsonData["Vehicle"]["Front"] = neonfront;
		jsonData["Vehicle"]["Back"] = neonback;

		jsonData["Vehicle"]["Spoiler"] = Spoiler;
		jsonData["Vehicle"]["Front Bumper"] = FBumper;
		jsonData["Vehicle"]["Rear Bumper"] = RBumper;
		jsonData["Vehicle"]["Wheels"] = Wheels;
		jsonData["Vehicle"]["Side Skirt"] = SSkirt;
		jsonData["Vehicle"]["Exhaust"] = Exhaust;
		jsonData["Vehicle"]["Grille"] = Grille;
		jsonData["Vehicle"]["Chassis"] = Chasis;
		jsonData["Vehicle"]["Hood"] = Hood;
		jsonData["Vehicle"]["Fender"] = Fender;
		jsonData["Vehicle"]["Right Fender"] = RFender;
		jsonData["Vehicle"]["Roof"] = Roof;
		jsonData["Vehicle"]["Windows"] = Windows;

		jsonData["Vehicle"]["Engine"] = Engine;
		jsonData["Vehicle"]["Brakes"] = Brakes;
		jsonData["Vehicle"]["Transmission"] = Transmission;
		jsonData["Vehicle"]["Horns"] = Horns;
		jsonData["Vehicle"]["Suspension"] = Suspension;
		jsonData["Vehicle"]["Armor"] = Armor;

		Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		jsonData["Vehicle"]["Model"] = ENTITY::GET_ENTITY_MODEL(veh);

		std::ofstream outputFile(MenuFolderPath + name + ".json");
		outputFile << jsonData.dump(4);
		outputFile.close();
	}
	void load(std::string name) {
		int modifiedItems{ 0 };
		try {
			std::string MenuFolderPath = util::dirs::get_directories()->get_vehicle();
			std::ifstream inputFile(MenuFolderPath + name + ".json");
			if (inputFile.is_open()) {
				nlohmann::json jsonData;
				inputFile >> jsonData;
				inputFile.close();


				nlohmann::json& json = jsonData["Vehicle"];


				g_gta_utility.spawn_vehicle(json["Model"]);

				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);


				VEHICLE::SET_VEHICLE_MOD(veh, MOD_XENONLIGHTS, json["Xenon"], false);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, json["Red"], json["Green"], json["Blue"]);
				VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, json["Red1"], json["Green1"], json["Blue1"]);
				VEHICLE::SET_VEHICLE_NEON_COLOUR(veh, json["Red2"], json["Green2"], json["Blue2"]);

				VEHICLE::SET_VEHICLE_NEON_ENABLED(veh, 0, json["Left"]);
				VEHICLE::SET_VEHICLE_NEON_ENABLED(veh, 1, json["Right"]);
				VEHICLE::SET_VEHICLE_NEON_ENABLED(veh, 2, json["Front"]);
				VEHICLE::SET_VEHICLE_NEON_ENABLED(veh, 3, json["Back"]);

				VEHICLE::SET_VEHICLE_MOD(json["Model"], MOD_SPOILER, json["Spoiler"], false);
				VEHICLE::SET_VEHICLE_MOD(veh, MOD_FRONTBUMPER, json["Front Bumper"], false);
				VEHICLE::SET_VEHICLE_MOD(veh, MOD_REARBUMPER, json["Rear Bumper"], false);
				VEHICLE::SET_VEHICLE_MOD(veh, MOD_FRONTWHEELS, json["Wheels"], false);
				VEHICLE::SET_VEHICLE_MOD(veh, MOD_SIDESKIRT, json["Side Skirt"], false);
				VEHICLE::SET_VEHICLE_MOD(veh, MOD_EXHAUST, json["Exhaust"], false);
				VEHICLE::SET_VEHICLE_MOD(veh, MOD_GRILLE, json["Grille"], false);
				VEHICLE::SET_VEHICLE_MOD(veh, MOD_CHASSIS, json["Chassis"], false);
				VEHICLE::SET_VEHICLE_MOD(veh, MOD_HOOD, json["Hood"], false);
				VEHICLE::SET_VEHICLE_MOD(veh, MOD_FENDER, json["Fender"], false);
				VEHICLE::SET_VEHICLE_MOD(veh, MOD_RIGHTFENDER, json["Right Fender"], false);
				VEHICLE::SET_VEHICLE_MOD(veh, MOD_ROOF, json["Roof"], false);
				VEHICLE::SET_VEHICLE_MOD(veh, MOD_WINDOWS, json["Windows"], false);

				VEHICLE::SET_VEHICLE_MOD(veh, MOD_ENGINE, json["Engine"], false);
				VEHICLE::SET_VEHICLE_MOD(veh, MOD_BRAKES, json["Brakes"], false);
				VEHICLE::SET_VEHICLE_MOD(veh, MOD_TRANSMISSION, json["Transmission"], false);
				VEHICLE::SET_VEHICLE_MOD(veh, MOD_HORNS, json["Horns"], false);
				VEHICLE::SET_VEHICLE_MOD(veh, MOD_SUSPENSION, json["Suspension"], false);
				VEHICLE::SET_VEHICLE_MOD(veh, MOD_ARMOR, json["Armor"], false);


			}
		}
		catch (const std::exception& e) {
			g_log.send("Json", e.what());
		}
	}
}