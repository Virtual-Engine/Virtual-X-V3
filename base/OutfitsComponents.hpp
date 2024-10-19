#pragma once
#include "invoker/Natives.hpp"

namespace VX
{
	class OutfitsComponents
	{
	private:

	public:
		void Save(String fileName);
		void Load(std::string name);
	};

	OutfitsComponents* GetOutfitsComponents();

	inline int hair = 0;
	inline int face = 0;
	inline int glasses = 0;
	inline int ears = 0;
	inline int faceVar = 0;
	inline int glassesVar = 0;
	inline int earsVar = 0;
	inline int components[12] = { 0 };
	inline int componentsVar[12] = { 0 };

	inline String apparanceLabel[] = {
		"Face",
		"Masks",
		"Hair",
		"Torso",
		"Legs",
		"Parachute / Misc",
		"Shoes",
		"Extra 1",
		"Tops 1",
		"Body Armor",
		"Crew Emblem",
		"Tops 2",
		"Hat"
	};
	inline String apparanceComponentLabel[] = {
		"Face variation",
		"Masks variation",
		"Hair variation",
		"Torso variation",
		"Legs variation",
		"Parachute / Misc variation",
		"Shoes variation",
		"Extra 1 variation",
		"Tops 1 variation",
		"Body Armor variation",
		"Crew Emblem variation",
		"Tops 2 variation",
		"Hat variation"
	};
}