#include "common.hpp"
#include "invoker/Natives.hpp"
#include "fiber.hpp"

namespace VX
{
	
	inline Object SpawnMapModObject(String toSpawn, bool blip, float coordsX, float coordsY, float coordsZ) {
		DWORD model = g_utility.GetHashKey(toSpawn);
		Object object;
		if (STREAMING::IS_MODEL_IN_CDIMAGE(model)) {
			g_utility.SimpleRequestModel(model);
			object = OBJECT::CREATE_OBJECT(model, coordsX, coordsY, coordsZ, 1, 1, 0);
			if (blip) {
				auto blip = HUD::ADD_BLIP_FOR_ENTITY(object);
				HUD::SET_BLIP_SPRITE(blip, 351);
				HUD::SET_BLIP_COLOUR(blip, 4);
			}
		}
		return object;
	}
}