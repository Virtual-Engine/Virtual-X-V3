#pragma once
#include "../common.hpp"
#include "../rage/classes.hpp"
namespace VX {

	typedef const char* String;

	class input
	{
	public:
		bool initialize();
		bool is_key_pressed(int virtual_key);
	public:
		HWND m_hwnd{};
	};
	input* GetInput();

	class utility
	{
	 public:
		std::string get_documents_path();
		void notifyMap(const char* fmt, ...);
		void Animation(const char* anim, const char* animid);
		void ChangeModel(const char* To_Change);
		void RequestControlOfEnt(Entity entity);
		bool is_player_in_interior(Player player);
		bool is_player_friend(Player player);
		void SetVehicleWheelColor(int color);
		Vehicle vehicle(bool includeLast = false);
		Vector3 coords(Entity entity = 0);
		bool has_string_attached(const std::string& first, const std::string& check);
		bool is_ped_shooting(Ped ped);
		std::uint32_t Joaat(const char* str);
		void load_ytd(const char* file_name);
		const char* fixed_decimel(float number);
		void SetHeader(int header);
		RGBA HSVToRGB(float h, float s, float v);
		void DoTimedFunction(int* timer, int timeMS);
		void DoTimedFunctionV2(int* timer, int timeMS);
		Hash GetHashKey(String str);
		void SimpleRequestModel(int model);
	
	};
	inline utility g_utility;

	class math {
	public:
		float convert_360(float base, float min, float max);
		float deg_to_rad(float degs);
		
	};
	inline math g_math;

	class gta_utility {
	public:
		bool MaxVehiclespawn = true;
		bool Sitinvehicle = true;
		bool g_SpawnInvinc = false;
		const char* draw_keyboard();
		const char* get_vehicle_class_name(int id);
		void request_model(std::uint32_t hash);
		Vehicle spawn_vehicle(std::uint32_t hash);
		rage::scrProgram* get_program_by_hash(std::uint32_t hash);
	};
	inline gta_utility g_gta_utility;
}