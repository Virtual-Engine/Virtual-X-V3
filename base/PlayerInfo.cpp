#include "invoker/Natives.hpp"
#include "PlayerInfo.hpp"
#include "fiber.hpp"
#include "ui/interface.hpp"
#include "ScriptGloabals.h"
namespace VX
{
	PlayerInfo g_PlayerInfo;
	void PlayerInfo::Init(std::uint32_t player, bool show)
	{

		if (!show) return;
		Hash Street[2]{};
		float RoundedDistance{};
		Ped PlayerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		Vehicle Vehicle = PED::GET_VEHICLE_PED_IS_IN(PlayerPed, false);
		Vector3 PedCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
		Vector3 Coords = ENTITY::GET_ENTITY_COORDS(PlayerPed, false);
		Hash VehicleHash = ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_IN(PlayerPed, 0));
		bool Connected = NETWORK::NETWORK_IS_SESSION_ACTIVE();
		bool InVehicle = PED::IS_PED_IN_ANY_VEHICLE(PlayerPed, true);
		PATHFIND::GET_STREET_NAME_AT_COORD(Coords.x, Coords.y, Coords.z, &Street[0], &Street[1]);
		const char* RID = "Nigga";
		int netHandle[13];
		NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, netHandle, 13);

		if (yesyes2)
		{
			RID = "Private";
		}
		else
		{
			RID = NETWORK::NETWORK_MEMBER_ID_FROM_GAMER_HANDLE(&netHandle[0]);
		}

		std::stringstream coordx;
		coordx << std::fixed << std::setprecision(0) << Coords.x;
		std::string COORDX = coordx.str();

		std::stringstream coordy;
		coordy << std::fixed << std::setprecision(0) << Coords.y;
		std::string COORDY = coordy.str();

		std::stringstream coordz;
		coordz << std::fixed << std::setprecision(0) << Coords.z;
		std::string COORDZ = coordz.str();

		int HealthProgress = ENTITY::GET_ENTITY_HEALTH(PlayerPed) * 100 / ENTITY::GET_ENTITY_MAX_HEALTH(PlayerPed);

		int ArmorProgress = PED::GET_PED_ARMOUR(PlayerPed) * 100 / PLAYER::GET_PLAYER_MAX_ARMOUR(player);
		std::ostringstream WantedLevel; WantedLevel << "~s~" << PLAYER::GET_PLAYER_WANTED_LEVEL(player);




		const char* empty = "";
		float speed = ENTITY::GET_ENTITY_SPEED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player));
		int inInterior = INTERIOR::GET_INTERIOR_FROM_ENTITY(PlayerPed);

		bool frnd;


		NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(player);
		bool self, Friend, Cutscene, Modder, Modded, Host, Interior, Talking = false;

		const char* sender = PLAYER::GET_PLAYER_NAME(player);

		float distance = GetDistanceFloat(PedCoords, Coords);
		std::ostringstream Distance;
		Distance << distance;



		const char* direction = "";
		float pedHeading = ENTITY::GET_ENTITY_HEADING_FROM_EULERS(PlayerPed);
		if (pedHeading < 90)
			direction = "North ";
		else if (pedHeading > 90 && pedHeading < 180)
			direction = "East ";
		else if (pedHeading > 180 && pedHeading < 270)
			direction = "South ";
		else if (pedHeading > 270 && pedHeading < 360)
			direction = "West ";

		//int kills = *ScriptGlobal(1590908).Add(player, 874).Add(205).Add(28).As<int*>();

		std::stringstream heading;
		heading << std::fixed << std::setprecision(0) << pedHeading;
		std::string Heading = heading.str();

		std::string ipaddress;
		char ipBuf[32] = {};
		char buffer[32] = {};

		int rank = *ScriptGlobal(1590908).Add(player, 874).Add(205).Add(6).As<int*>();
		long long money = *ScriptGlobal(1590908).Add(player, 874).Add(205).Add(3).As<long long*>();
		int _handle = *ScriptGlobal(1590908).Add(player, 874).Add(205).Add(56).As<int*>();
		int handle2 = *ScriptGlobal(1590908).Add(player, 874).Add(205).Add(3).As<int*>();
		int bankMoney = _handle - handle2;
		int totalmoney = money + bankMoney;

		if (ENTITY::DOES_ENTITY_EXIST(PlayerPed))
		{
			Box(PLAYER::GET_PLAYER_NAME(player));
			Box("SLT");
			MultiInfo("Rank", std::to_string(rank), "Health", std::to_string(ENTITY::GET_ENTITY_HEALTH(PlayerPed)));
			MultiInfo("Cash", std::to_string(money), "Armor", std::to_string(PED::GET_PED_ARMOUR(PlayerPed)));
			MultiInfo("Bank", std::to_string(bankMoney), "Total", std::to_string(totalmoney));
			MultiInfo("Wanted Level", std::to_string(PLAYER::GET_PLAYER_WANTED_LEVEL(player)) + "/5", "Fake Wanted Level", std::to_string(PLAYER::GET_PLAYER_FAKE_WANTED_LEVEL(player)) + "/6");
			MultiInfo("Coords", "[" + COORDX + "," + COORDY + "," + COORDZ + "]", "Heading", direction + Heading);
			MultiInfo("Distance", (char*)Distance.str().c_str(), "Script Host", (NETWORK::NETWORK_GET_HOST_OF_SCRIPT("freemode", -1, 0) == player) ? "Yes" : "No");
			MultiInfo("Invincibility", PLAYER::GET_PLAYER_INVINCIBLE(player) ? "Yes" : "No", "Invisible", !ENTITY::IS_ENTITY_VISIBLE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player)) ? "Yes" : "No");
			MultiInfo("Cutscene:", NETWORK::IS_PLAYER_IN_CUTSCENE(player) ? "~s~Yes" : "~s~No", "Interior:", inInterior ? "~s~Yes" : "~s~No");
			Info("Vehicle", PED::IS_PED_IN_ANY_VEHICLE(PlayerPed, 1) ? HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_IN(PlayerPed, 0)))) : "None");
			Info("Zone", &("~s~" + (std::string)HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(ZONE::GET_NAME_OF_ZONE(Coords.x, Coords.y, Coords.z)))[0]);
			Info("Street", HUD::GET_STREET_NAME_FROM_HASH_KEY(Street[0]));
			Info("RID", RID);
			Info("Modder", "No");
			Info("Input", PAD::IS_USING_KEYBOARD_AND_MOUSE(0) ? "Keyboard" : "Controller");
			//GetRenderer()->PlayerInfo("Kills", KILL.c_str());
			Info("Weapon", Weaponheld(player).c_str());
			Info("Ped Type", std::to_string(PED::GET_PED_TYPE(player)));
			Info("Ping", "0");
		}
	}
	void PlayerInfo::Update(std::uint32_t player, bool show)
	{
		Init(player, show);
		MapPanel();
		InfoMap();
	}
	void PlayerInfo::Box(std::string name)
	{
		if (GetRenderer()->m_menu_pos.x > 0.5f)
			GetRenderer()->X_InfoFloat = GetRenderer()->m_menu_pos.x - 0.25f;
		else
			GetRenderer()->X_InfoFloat = GetRenderer()->m_menu_pos.x + 0.25f;

		//name
		GRAPHICS::DRAW_RECT(
			GetRenderer()->X_InfoFloat,
			GetRenderer()->m_menu_pos.y + 0.014f,
			0.26f, 0.0275f,
			GetRenderer()->m_background_playerinfo.r, GetRenderer()->m_background_playerinfo.g, GetRenderer()->m_background_playerinfo.b, GetRenderer()->m_background_playerinfo.a,
			0.f);

		//name line
		GRAPHICS::DRAW_RECT(
			GetRenderer()->X_InfoFloat,
			GetRenderer()->m_menu_pos.y,
			0.26f, 0.001f,
			255, 255, 255, 255,
			0.f);


		GetRenderer()->PlayerInfoText(name,
			{ 255, 255, 255, 255, 1 },
			{ GetRenderer()->X_InfoFloat - 0.127f, GetRenderer()->m_menu_pos.y },
			GetRenderer()->get_spirit_scale(0.38f),
			0,
			0);

		//main line
		GRAPHICS::DRAW_RECT(
			GetRenderer()->X_InfoFloat,
			GetRenderer()->m_menu_pos.y + 0.035f,
			0.26f, 0.001f,
			255, 255, 255, 255,
			0.f);


		GetRenderer()->Y_InfoFloat = GetRenderer()->m_menu_pos.y + 0.0492f;
	}
	void PlayerInfo::Info(std::string option, std::string option2)
	{
		//main
		GRAPHICS::DRAW_RECT(
			GetRenderer()->X_InfoFloat,
			GetRenderer()->Y_InfoFloat - 0.001f,
			0.26f, 0.025f,
			GetRenderer()->m_background_playerinfo.r, GetRenderer()->m_background_playerinfo.g, GetRenderer()->m_background_playerinfo.b, GetRenderer()->m_background_playerinfo.a,
			0.f);

		GetRenderer()->PlayerInfoText(option,
			{ 255,255,255,255 },
			{ GetRenderer()->X_InfoFloat - 0.1265f, GetRenderer()->Y_InfoFloat - 0.01f },
			GetRenderer()->get_spirit_scale(0.25f),
			0,
			0);

		HUD::SET_TEXT_WRAP(0.f, GetRenderer()->X_InfoFloat + 0.125f);

		GetRenderer()->PlayerInfoText(option2,
			{ 255,255,255,255 },
			{ GetRenderer()->X_InfoFloat,
			GetRenderer()->Y_InfoFloat - 0.01f },
			GetRenderer()->get_spirit_scale(0.25f),
			false,
			true);

		GetRenderer()->Y_InfoFloat += 0.025f;
	}
	void PlayerInfo::MultiInfo(std::string option, std::string option2, std::string option3, std::string option4)
	{
		//main
		GRAPHICS::DRAW_RECT(
			GetRenderer()->X_InfoFloat,
			GetRenderer()->Y_InfoFloat - 0.001f,
			0.26f, 0.025f,
			GetRenderer()->m_background_playerinfo.r, GetRenderer()->m_background_playerinfo.g, GetRenderer()->m_background_playerinfo.b, GetRenderer()->m_background_playerinfo.a,
			0.f);

		GetRenderer()->PlayerInfoText(option,
			{ 255,255,255,255 },
			{ GetRenderer()->X_InfoFloat - 0.1265f, GetRenderer()->Y_InfoFloat - 0.01f },
			GetRenderer()->get_spirit_scale(0.25f),
			0,
			0);

		HUD::SET_TEXT_WRAP(0.f, GetRenderer()->X_InfoFloat - 0.0045f);

		GetRenderer()->PlayerInfoText(option2,
			{ 255,255,255,255 },
			{ GetRenderer()->X_InfoFloat - 0.0045f,
			GetRenderer()->Y_InfoFloat - 0.01f },
			GetRenderer()->get_spirit_scale(0.25f),
			false,
			true);

		//Divider
		GetRenderer()->DrawRect(
			GetRenderer()->X_InfoFloat,
			GetRenderer()->Y_InfoFloat,
			0.00125f,
			0.015f,
			{ 255, 255, 255, 255 });

		GetRenderer()->PlayerInfoText(option3,
			{ 255,255,255,255 },
			{ GetRenderer()->X_InfoFloat + 0.005f,
			GetRenderer()->Y_InfoFloat - 0.01f },
			GetRenderer()->get_spirit_scale(0.25f),
			0,
			0);

		HUD::SET_TEXT_WRAP(0.f, GetRenderer()->X_InfoFloat + 0.125f);

		GetRenderer()->PlayerInfoText(option4,
			{ 255,255,255,255 },
			{ GetRenderer()->X_InfoFloat + 0.125f,
			GetRenderer()->Y_InfoFloat - 0.01f },
			GetRenderer()->get_spirit_scale(0.25f),
			0,
			1);

		GetRenderer()->Y_InfoFloat += 0.025f;
	}
	void PlayerInfo::MapPanel() {
		if (hidemap) {
			float temp = 14;
			// Calculate Y Coord
			float bg_Y = ((temp * 0.035f) / 2.0f) + 0.159f;
			float bg_length = temp * 0.035f;
			float xPos = m_position.x;
			float yPos = m_position.y;
			float offsety = 0.06f;
			float offsetx = 0.184f;

			DrawSprite2("mp_freemode_mc", "debugmap", offsetx + xPos + 0.15f, offsety + yPos + bg_length / 2 + 0.021f - 0.008f, (0.340703125f / 16 * 9) - 0.051f, bg_length - 0.042f - 0.016f, 0, 255, 255, 255, 255);
		}
	}
	void PlayerInfo::InfoMap()
	{
		if (hidemap) {
			float yPos = m_position.y;
			float xPos = m_position.x;
			float offsety = 0.05f;
			float offsetx = 0.184f;
			for (int i = 0; i < 32; i++)
			{
				if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer))) {
					Vector3 player = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 0);
					DrawSprite1("shared", "menuplus_32", offsetx + xPos + 0.070f + relevateX(player.x), offsety + yPos - 0.083f / 2 + 0.49f + 0.208f - relevateY(player.y), 0.25f, 0.25f, 0, 107, 5, 255, 180);
				}
			}
			Vector3 playerSelected = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 0);
			//DrawSprite1("shared", "menuplus_32", offsetx + xPos - 0.09f + relevateX(playerSelected.x), offsety + yPos - 0.083f / 2 + 0.49f + 0.208f - relevateY(playerSelected.y), 0.25f, 0.25f, 0, 255, 0, 0, 255);
			Vector3 m_coordinates;
			//Utility::DrawSprite1("shared", "newstar_32", offsetx + xPos + 0.070f + Utility::relevateX(m_coordinates.x), offsety + yPos - 0.083f / 2 + 0.49f + 0.208f -Utility::relevateY(m_coordinates.y), 0.25f, 0.25f, 0, 255, 0, 0, 200);
		}
	}
	void PlayerInfo::DrawSprite2(const char* textureDict, const char* textureName, float screenX, float screenY, float scaleX, float scaleY, float heading, int red, int green, int blue, int alpha) {
		if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(textureDict)) { GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(textureDict, 0); }
		GRAPHICS::DRAW_SPRITE(textureDict, textureName, screenX, screenY, scaleX, scaleY, heading, red, green, blue, alpha);
	}
	void PlayerInfo::DrawSprite1(const char* textureDict, const char* textureName, float screenX, float screenY, float scaleX, float scaleY, float heading, int red, int green, int blue, int alpha) {
		if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(textureDict)) { GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(textureDict, 0); }
		GRAPHICS::DRAW_SPRITE(textureDict, textureName, screenX, screenY, scaleX / 16, scaleY / 9, heading, red, green, blue, alpha);
	}
	float PlayerInfo::relevateX(float x) {
		return ((0.340703125f / 10000) * x + (0.340703125f / 10000) * 4000) / 16 * 9;
	}
	float PlayerInfo::relevateY(float y) {
		return ((0.49f / 12000) * y + (0.49f / 12000) * 8000);
	}
	float PlayerInfo::GetDistanceFloat(Vector3 pointA, Vector3 pointB) {
		float a_x = pointA.x;
		float a_y = pointA.y;
		float a_z = pointA.z;
		float b_x = pointB.x;
		float b_y = pointB.y;
		float b_z = pointB.z;
		double x_ba = (double)(b_x - a_x);
		double y_ba = (double)(b_y - a_y);
		double z_ba = (double)(b_z - a_z);
		double y_2 = y_ba * y_ba;
		double x_2 = x_ba * x_ba;
		double sum_2 = y_2 + x_2;
		return(float)sqrt(sum_2 + z_ba);
	}
	std::string PlayerInfo::Weaponheld(Player player)
	{
		Hash weaponHash;
		WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), &weaponHash, 0);
		switch (weaponHash)
		{	//New hashes MK2  0xBFE256D4, 0x88374054, 0xCB96392F, 0x78A97CD0, 0x555AF99A, 0x394F415C, 0xFAD1F1C9, 0x969C3D67, 0x84D6FAFD, 0xDBBD7280, 0xA914799, 0x6A6C02E0
		case -1569615261:
			return "Unarmed";
			break;
		case -1716189206:
			return "Knife";
			break;
		case 1737195953:
			return "Nightstick";
			break;
		case 1317494643:
			return "Hammer";
			break;
		case -1786099057:
			return "Bat";
			break;
		case -2067956739:
			return "Crowbar";
			break;
		case 1141786504:
			return "Golfclub";
			break;
		case -102323637:
			return "Bottle";
			break;
		case -1834847097:
			return "Dagger";
			break;
		case -102973651:
			return "Hatchet";
			break;
		case -656458692:
			return "Knuckle Duster";
			break;
		case -581044007:
			return "Machete";
			break;
		case -1951375401:
			return "Flashlight";
			break;
		case -538741184:
			return "Switch Blade";
			break;
		case -1810795771:
			return "Poolcue";
			break;
		case 419712736:
			return "Wrench";
			break;
		case -853065399:
			return "Battle Axe";
			break;
		case 0x3813FC08:
			return "Stone Hatchet";
			break;
		case 453432689:
			return "Pistol";
			break;
		case 3219281620:
			return "Pistol Mk2";
			break;
		case 1593441988:
			return "Combat Pistol";
			break;
		case -1716589765:
			return "Pistol 50";
			break;
		case -1076751822:
			return "SNS Pistol";
			break;
		case 0x88374054:
			return "SNS Pistol Mk2";
			break;
		case -771403250:
			return "Heavy Pistol";
			break;
		case 137902532:
			return "Vintage Pistol";
			break;
		case -598887786:
			return "Marksman Pistol";
			break;
		case -1045183535:
			return "Revolver";
			break;
		case 0xCB96392F:
			return "Revolver Mk2";
			break;
		case 584646201:
			return "AP Pistol";
			break;
		case 911657153:
			return "Stun Gun";
			break;
		case 1198879012:
			return "Flare Gun";
			break;
		case 0x97EA20B8:
			return "Double Action Revolver";
			break;
		case 0xAF3696A1:
			return "Up-n-Atomizer";
			break;
		case 324215364:
			return "Micro SMG";
			break;
		case -619010992:
			return "Machine Pistol";
			break;
		case 736523883:
			return "SMG";
			break;
		case 2024373456:
			return "SMG Mk2";
			break;
		case -270015777:
			return "Assault SMG";
			break;
		case 171789620:
			return "Combat PDW";
			break;
		case -1660422300:
			return "MG";
			break;
		case 2144741730:
			return "Combat MG";
			break;
		case 368662592:
			return "Combat MG Mk2";
			break;
		case 1627465347:
			return "Gusenberg";
			break;
		case -1121678507:
			return "Mini SMG";
			break;
		case 0x476BF155:
			return "Unholy Hellbringer";
			break;
		case -1074790547:
			return "Assault Rifle";
			break;
		case 961495388:
			return "Assault Rifle Mk2";
			break;
		case -2084633992:
			return "Carbine Rifle";
			break;
		case 4208062921:
			return "Carbine Rifle Mk2";
			break;
		case -1357824103:
			return "Advanced Rifle";
			break;
		case -1063057011:
			return "Special Carbine";
			break;
		case 0x969C3D67:
			return "Special Carbine Mk2";
			break;
		case 2132975508:
			return "Bullpup Rifle";
			break;
		case 0x84D6FAFD:
			return "Bullpup Rifle Mk2";
			break;
		case 1649403952:
			return "Compact Rifle";
			break;
		case 100416529:
			return "Sniper Rifle";
			break;
		case 205991906:
			return "Heavy Sniper";
			break;
		case 177293209:
			return "Heavy Sniper Mk2";
			break;
		case -952879014:
			return "Marksman Rifle";
			break;
		case 0x6A6C02E0:
			return "Marksman Rifle Mk2";
			break;
		case 487013001:
			return "Pump Shotgun";
			break;
		case 0x555AF99A:
			return "Pump Shotgun Mk2";
			break;
		case 2017895192:
			return "Sawnoff Shotgun";
			break;
		case -1654528753:
			return "Bullpup Shotgun";
			break;
		case -494615257:
			return "Assault Shotgun";
			break;
		case -1466123874:
			return "Musket";
			break;
		case 984333226:
			return "Heavy Shotgun";
			break;
		case -275439685:
			return "Double Barrel Shotgun";
			break;
		case 317205821:
			return "Sweeper Shotgun";
			break;
		case -1568386805:
			return "Grenade Launcher";
			break;
		case -1312131151:
			return "RPG";
			break;
		case 1119849093:
			return "Minigun";
			break;
		case 2138347493:
			return "Firework";
			break;
		case 1834241177:
			return "Railgun";
			break;
		case 1672152130:
			return "Homing Launcher";
			break;
		case 1305664598:
			return "Grenade Launcher Smoke";
			break;
		case 125959754:
			return "Compact Launcher";
			break;
		case 0xB62D1F67:
			return "Widowmaker";
			break;
		case -1813897027:
			return "Grenade";
			break;
		case 741814745:
			return "Sticky Bomb";
			break;
		case -1420407917:
			return "Proximity Mine";
			break;
		case -1600701090:
			return "BZ Gas";
			break;
		case 615608432:
			return "Molotov";
			break;
		case 101631238:
			return "Fire Extinguisher";
			break;
		case 883325847:
			return "Petrol Can";
			break;
		case 1233104067:
			return "Flare";
			break;
		case 600439132:
			return "Ball";
			break;
		case 126349499:
			return "Snowball";
			break;
		case -37975472:
			return "Smoke Grenade";
			break;
		case -1169823560:
			return "Pipebomb";
			break;
		case -72657034:
			return "Parachute";
			break;

		default:
			return "None Found";
			break;
		}
		return "Unknown";
	}
	PlayerInfo* GetPlayerInfo() { return &g_PlayerInfo; }
}
