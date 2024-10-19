#pragma once
#include "invoker/Natives.hpp"

namespace VX
{
	class Teleport
	{
	private:

	public:
		void Save(String fileName, Vector3 Coordinates);
		void Load(std::string name);
		void to_coords(Entity e, Vector3 coords, bool AutoCorrectGroundHeight, bool IgnoreCurrentPedVehicle);
		void request_network_control(Entity Entity);
	};

	Teleport* GetTeleport();
}