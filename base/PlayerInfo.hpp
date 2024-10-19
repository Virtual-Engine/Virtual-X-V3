#pragma once
#include "invoker/Natives.hpp"

namespace VX
{
	class PlayerInfo
	{
	private:

	public:
		Vector2 m_position;
		bool hidemap = true;
		bool yesyes2 = false;
	public:
		void Init(std::uint32_t player, bool show);
		void Box(std::string name);
		void Info(std::string option, std::string option2);
		void MultiInfo(std::string option, std::string option2, std::string option3, std::string option4);
		void Update(std::uint32_t player, bool show);
		void MapPanel();
		void InfoMap();
		void DrawSprite2(const char* textureDict, const char* textureName, float screenX, float screenY, float scaleX, float scaleY, float heading, int red, int green, int blue, int alpha);
		void DrawSprite1(const char* textureDict, const char* textureName, float screenX, float screenY, float scaleX, float scaleY, float heading, int red, int green, int blue, int alpha);
		float relevateX(float x);
		float relevateY(float y);
		float GetDistanceFloat(Vector3 pointA, Vector3 pointB);
		std::string Weaponheld(Player player);
	};

	PlayerInfo* GetPlayerInfo();
}