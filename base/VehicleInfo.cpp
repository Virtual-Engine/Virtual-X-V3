#include "invoker/Natives.hpp"
#include "VehicleInfo.hpp"
#include "fiber.hpp"
#include "ui/interface.hpp"
namespace VX
{
	VehicleInfo g_VehicleInfo;

	void VehicleInfo::Update(Hash model)
	{

	}
	void VehicleInfo::Stats(Hash model)
	{
		int scaleform = GRAPHICS::REQUEST_SCALEFORM_MOVIE("mp_car_stats_01");
		if (!GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(scaleform)) {
			scaleform = GRAPHICS::REQUEST_SCALEFORM_MOVIE("mp_car_stats_01");
		}
		else {
			GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(scaleform, "SET_VEHICLE_INFOR_AND_STATS");
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_TEXTURE_NAME_STRING(HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(model)));
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_TEXTURE_NAME_STRING("MPCarHUD"); //MPCarHUD
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_TEXTURE_NAME_STRING("fathom"); //fathom
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_TEXTURE_NAME_STRING("Top Speed");
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_TEXTURE_NAME_STRING("Acceleration");
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_TEXTURE_NAME_STRING("Braking");
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_TEXTURE_NAME_STRING("Traction");

			int val1 = round((VEHICLE::GET_VEHICLE_MODEL_ESTIMATED_MAX_SPEED(model) * 1.5f));
			int val2 = VEHICLE::GET_VEHICLE_MODEL_ACCELERATION(model) * 2.5f * 100;
			int val3 = VEHICLE::GET_VEHICLE_MODEL_MAX_BRAKING(model) / 4.0f * 100;
			int val4 = VEHICLE::GET_VEHICLE_MODEL_MAX_TRACTION(model) / 3.0f * 100;

			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(Clamp(val1, 0, 100));
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(Clamp(val2, 0, 100));
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(Clamp(val3, 0, 100));
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(Clamp(val4, 0, 100));
			GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
		}
		GRAPHICS::DRAW_SCALEFORM_MOVIE(scaleform, m_positionSclVeh.x + 0.602f, m_positionSclVeh.y, 1.0f, 1.0f, 255, 255, 255, 255, 0);
	}
	void VehicleInfo::DisplayVehicle(std::string texture1, std::string texture2)
	{
		float VehBannerWidth = 0.13f;
		float VehBannerHeight = 0.045f;
		RGBA line{ 255, 255, 255, 255 };
		float lineX = { GetRenderer()->m_menu_pos.x - 0.19f };
		float lineY = 0.2451f;

		GetRenderer()->Spriter(texture1, texture2, m_positionSclVeh.x + 0.60f, 0.1870f, 0.180f, 0.165f, 0, 255, 255, 255, 255);
	}
	int VehicleInfo::Clamp(int val, int min, int max) {
		return val < min ? min : val > max ? max : val;
	}
	bool VehicleInfo::ClampV2(int val, int min, int max) {
		return val < min ? min : val > max ? max : val;
	}

	VehicleInfo* GetVehicleInfo() { return &g_VehicleInfo; }
}
