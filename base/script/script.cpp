#include "../ui/interface.hpp"
#include "../manager.hpp"
#include "script.hpp"
#include "../invoker/Natives.hpp"
#include "../log/log.hpp"
#include "../Self.h"
#include "../SelfMenu.h"
#include "../Handler.h"
#include "../Models.h"
#include "../Vision.h"
#include "../VehicleLoader.h"
#include "../PlayerOverseer.h"
#include <shellapi.h>
#include "../UtilWeapon.h"
#include "../clouds.h"
#include "../Weather.h"
#include "../TeleportLocation.h"
#include "../globalHandle.h"
#include "../Rank.h"
#include "../Increase.h"
#include "../Object.h"
#include "../scaleform.h"
#include "../ThemeLoader.h"
#include "../spoofing.h"
#include "../Settings.hpp"
#include "../animatedYTD.h"
#include "../reclass.h"
#include "../WeaponPreview.h"
#include "../option.hpp"
#include "../PlayerInfo.hpp"
#include "../ScriptGloabals.h"
#include "../VehicleInfo.hpp"
#include "../OutfitsComponents.hpp"
#include "../MenuInput.hpp"
#include "../CustomInput.hpp"
#include "../MapMods.h"
#include "../ScriptHookV.hpp"
#include "../xml.hpp"
#include "../Teleport.hpp"
#include "../animatedYTD.h"
#include "../core/core.hpp"
std::vector<std::string> m_outfitFiles;
static Vehicle trainHandle;

namespace VX {
	script g_script;
	std::vector<std::string> m_pluginFiles;
	std::vector<HMODULE> m_pluginHandles;
	void LoadASI(std::string fileName) {
		//auto lib = LoadLibraryA(va("%s/%s.asi", util::dirs::get_directories()->get_shv(), fileName.c_str()));
		//m_pluginHandles.push_back(lib);
	}
	void home_submenu() {
		if (GetRenderer()->FirstTabSelected)
		{
			addOption()->Submenu("Self", self_submenu);
			addOption()->Submenu("Player", player_submenu);
			addOption()->Submenu("Vehicle", Vehicle_submenu);
			addOption()->Submenu("Weapon", Weapon_submenu);
			addOption()->Submenu("Misc", Misc_submenu);
			addOption()->Submenu("Protection", Protection_submenu);
			addOption()->Submenu("Teleports", Teleport_submenu);
			addOption()->Submenu("Network", Network_submenu);
			addOption()->Submenu("Recovery", Recovery_submenu);
			addOption()->Submenu("ScriptHookV", ScriptHookV_Submenu);
			if (GetRenderer()->tab_activate)
			{
				GetRenderer()->tab_activate = true;
			}
			else
			{
				addOption()->Submenu("Spawner", Spawner_submenu);
			}
			addOption()->Submenu("Settings", settings_submenu);
		}
		else if (GetRenderer()->SecondTabSelected)
		{
			addOption()->Submenu("Vehicle", spawner_submenu);
			addOption()->Submenu("Object", Spawner_object);
			addOption()->Submenu("Map Mods", Spawner_mapmods, "Custom location, ramp, parkour");
			addOption()->Submenu("XML Vehicle", Spawner_xml, "Custom Vehicle .xml modded");
		}
	}
	void Spawner_xml()
	{
		std::vector<std::string> xml = util::dirs::get_files_in_directory(util::dirs::get_directories()->get_xml(), ".xml");
			if (xml.size()) {
				for (std::string& xmls : xml) {
					if (GetRenderer()->draw_regular(xmls.c_str()))
					{
						LoadSpoonerFile(xmls.c_str());
					}
				}
			}
	}
	void Spawner_mapmods()
	{
		for (const auto& entry : std::filesystem::directory_iterator(util::dirs::get_directories()->get_mapmods())) {
			auto const pos = entry.path().filename().string().find_last_of('.');
			std::string option = entry.path().filename().string().substr(0, pos);
			std::string mapModPath = entry.path().string();

			if (GetRenderer()->draw_regular(option.c_str()))
			{
				std::fstream mapModFile(mapModPath);
				json j = json::parse(mapModFile);

				for (auto i = 0; i < j.size(); i++) {
					auto& iterator = j[i];
					std::string Name = iterator[0].get<std::string>();
					Hash Model = iterator[1].get<DWORD>();
					float PosX = iterator[2].get<float>();
					float PosY = iterator[3].get<float>();
					float PosZ = iterator[4].get<float>();
					float Pitch = iterator[5].get<float>();
					float Roll = iterator[6].get<float>();
					float Yaw = iterator[7].get<float>();
					Object Obj = SpawnMapModObject(Name.c_str(), false,  PosX, PosY, PosZ );
					ENTITY::SET_ENTITY_ROTATION(Obj, Pitch, Roll, Yaw, 2, false);
				}
			}
		}
	}
	void Spawner_submenu()
	{
		addOption()->Submenu("Vehicle", spawner_submenu);
		addOption()->Submenu("Object", Spawner_object);
		addOption()->Submenu("Map Mods", Spawner_mapmods);
		addOption()->Submenu("XML Vehicle", Spawner_xml);
	}
	void Spawner_object()
	{
		if (GetRenderer()->draw_regular("Spawn Input"))
		{
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
			MISC::DISPLAY_ONSCREEN_KEYBOARD(true, "Input Object", "", "", "", "", "", 20);
			while (MISC::UPDATE_ONSCREEN_KEYBOARD() == 0) {
				fiber::current()->sleep();
			}
			if (!MISC::GET_ONSCREEN_KEYBOARD_RESULT()) {
				return;
			}
			SpawnObject((MISC::GET_ONSCREEN_KEYBOARD_RESULT()));
		}
		for (int i = 0; i < 9465; i++) {
			if (GetRenderer()->draw_regular(m_objectmodels[i]))
			{
				SpawnObject(m_objectmodels[i]);
			}
		}
	}
	void Protection_submenu()
	{
		addOption()->BoolOption("Bounty", &p_PROTECTION_BOUNTY);
		addOption()->BoolOption("Claim Bounty", &p_PROTECTION_CLAIM_BOUNTY);
		addOption()->BoolOption("Ceo Ban", &p_PROTECTION_CEO_BAN);
		addOption()->BoolOption("Ceo Kick", &p_PROTECTION_CEO_KICK);
		addOption()->BoolOption("Ceo Money", &p_PROTECTION_CEO_MONEY);
		addOption()->BoolOption("Clear Wanted", &p_PROTECTION_CLEAR_WANTED);
		addOption()->BoolOption("Fake Deposit", &p_PROTECTION_FAKE_DEPOSIT);
		addOption()->BoolOption("Force Mission", &p_PROTECTION_FORCE_MISSION);
		addOption()->BoolOption("Personal Vehicle", &p_PROTECTION_PERSONAL_VEHICLE);
		addOption()->BoolOption("Off Radar", &p_PROTECTION_OFF_RADAR);
		addOption()->BoolOption("Rotate Cam", &p_PROTECTION_ROTATE_CAM);
		addOption()->BoolOption("Force Cutscene", &p_PROTECTION_FORCE_CUTSCENE);
		addOption()->BoolOption("Force Island", &p_PROTECTION_FORCE_ISLAND);
		addOption()->BoolOption("Sound Spam", &p_PROTECTION_SOUND_SPAM);
		addOption()->BoolOption("Spectate", &p_PROTECTION_SPECTATE);
		addOption()->BoolOption("Force Apartment", &p_PROTECTION_FORCE_APARTMENT);
		addOption()->BoolOption("Transaction Error", &p_PROTECTION_TRANSACTION_ERROR);
		addOption()->BoolOption("Vehicle Kick", &p_PROTECTION_VEHICLE_KICK);
		addOption()->BoolOption("Network Bail", &p_PROTECTION_NETWORK_BAIL);
		addOption()->BoolOption("Freeze", &p_PROTECTION_FREEZE);
		addOption()->BoolOption("Bribe", &p_PROTECTION_BRIBE);
		addOption()->BoolOption("Block Passive", &p_PROTECTION_BLOCK_PASSIVE);
		addOption()->BoolOption("Kick", &p_PROTECTION_KICK);
		addOption()->BoolOption("Crash", &p_PROTECTION_CRASH);
	}
	void player_submenu()
	{
		for (std::uint32_t i = 0; i < 32; ++i)
		{
			if (auto ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))
			{
				std::string name = PLAYER::GET_PLAYER_NAME(i);

				if (i == PLAYER::PLAYER_ID())
					name.append(" ~b~[Me]");
				if (name == "XIFI_ENG") {
					name.append(" ~p~[Dev]");
				}
				if (i == NETWORK::NETWORK_GET_HOST_OF_SCRIPT("Freemode", 4294967295, 0))
					name.append(" ~y~[Script Host]");
				if (g_utility.is_player_friend(i))
					name.append(" ~g~[Friend]");
				if (g_utility.is_player_in_interior(i))
					name.append(" ~p~[Interior]");

				if (addOption()->Submenu(name.c_str(), selected_player_submenu))
				{
					g_SelectedPlayer = i;
				}

			}
		}
	}
	void Network_submenu()
	{
		GetRenderer()->draw_regular("Virtual X its not menu for GTA Online");
		//addOption()->Submenu("Session Finder", Network_sessionfinder);
		//addOption()->Submenu("Spoofer", Network_spoofer);
		//GetRenderer()->draw_sub("Extra Sensory Perseption", Network_esp);
	}
	void Network_sessionfinder()
	{
		for (const auto& session_type : sessions) {
			if (GetRenderer()->draw_regular(session_type.name))
			{
				join_type(session_type.id);
			}
		}
	}
	void Network_esp()
	{

	}
	void Network_spoofer()
	{
		const char* og_name = PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID());
		if (GetRenderer()->draw_regular("Input Name"))
		{
			GetRenderer()->m_opened = false;
			MISC::DISPLAY_ONSCREEN_KEYBOARD(true, (char*)"Input Name", (char*)"", (char*)"", (char*)"", (char*)"", (char*)"", 20);
			while (MISC::UPDATE_ONSCREEN_KEYBOARD() == 0) {
				fiber::current()->sleep();
			}
			if (!MISC::GET_ONSCREEN_KEYBOARD_RESULT())
				return;
			m_name = MISC::GET_ONSCREEN_KEYBOARD_RESULT();
			GetRenderer()->m_opened = false;
		}
		if (GetRenderer()->draw_regular("Reset"))
		{
			m_name = og_name;
		}
		std::string preview = std::format("Apply: {}{}{}{}", textSettingsValues[textSettingsId], textColorsValues[textColorsId], textIconsValues[textIconsId], m_name.c_str());
		std::string name_to_apply = std::format("{}{}{}{}", textSettingsValues[textSettingsId], textColorsValues[textColorsId], textIconsValues[textIconsId], m_name.c_str());
		GetRenderer()->draw_regular(preview.c_str());
		addOption()->BreakOption("Settings");
		GetRenderer()->draw_array("Color", textColorsLabels, &textColorsId);
		GetRenderer()->draw_array("Style", textSettingsLabels, &textSettingsId);
		GetRenderer()->draw_array("Icon", textIconsLabels, &textIconsId);
	}
	void self_submenu()
	{
		addOption()->Submenu("Animation", Self_Animation);
		addOption()->Submenu("Handtrails", Self_handtrails);
		addOption()->Submenu("Models", Self_models);
		addOption()->Submenu("Movement", Self_movement);
		addOption()->Submenu("Outfits", Self_outfits);
		addOption()->Submenu("Particles", Self_particles);
		addOption()->Submenu("Vision", Self_vision);
		addOption()->Submenu("Water", Self_water);
		addOption()->Submenu("General", Self_general);


	}
	void Self_general()
	{
		addOption()->BoolOption("Invisible", &Invisible);
		addOption()->BoolOption("Godmod", &GodMod);
		addOption()->BoolOption("Off Radar", &Offradar);
		GetRenderer()->draw_number("Opacity", &alpha, 0, 255, 10);
		addOption()->BoolOption("Spin", &Spin);
		addOption()->BoolOption("Never Wanted", &Neverwanted);
		GetRenderer()->draw_number("Level Wanted", &LevelWanted, 0, 5, 1);
		GetRenderer()->draw_number("Level Fake Wanted", &LevelFakeWanted, 0, 6, 1);
		if (GetRenderer()->draw_regular("Clear Wanted Level"))
		{
			PLAYER::CLEAR_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_PED_ID());
			LevelWanted = 0;
			g_utility.notifyMap("Clear Wanted Succesfuly");
		}
		addOption()->BoolOption("No Ragdoll", &NoRagDoll);
		addOption()->BoolOption("Always Ragdoll", &Alwaysragdoll);
		addOption()->BoolOption("Die On Ragdoll", &DieonRagdoll);
		addOption()->BoolOption("Thermal", &thermal);
		addOption()->BoolOption("Night", &night);
		addOption()->BoolOption("FireBreath", &FireBreath);
		addOption()->BoolOption("DeadEyeMotion", &DeadEyeMotion);
		addOption()->BoolOption("SlowMotion", &g_SlowMotion);
		if (GetRenderer()->draw_regular("Skip Cutscene"))
		{
			CUTSCENE::REMOVE_CUTSCENE();
			g_utility.notifyMap("Skip Cutscene Succesfuly");

		}
		if (GetRenderer()->draw_regular("Wet Clothes"))
		{
			PED::SET_PED_WETNESS_HEIGHT(PLAYER::GET_PLAYER_PED(-1), 20);
		}
		if (GetRenderer()->draw_regular("Dry your Clothes"))
		{
			PED::CLEAR_PED_WETNESS(PLAYER::GET_PLAYER_PED(-1));
		}
		if (GetRenderer()->draw_regular("Clear blood Stains"))
		{
			PED::CLEAR_PED_BLOOD_DAMAGE(PLAYER::GET_PLAYER_PED(-1));
		}
		if (GetRenderer()->draw_regular("Max Health"))
		{
			ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), ENTITY::GET_ENTITY_MAX_HEALTH(PLAYER::PLAYER_PED_ID()), 0);
			g_utility.notifyMap("Max Health Succesfuly");

		}
		if (GetRenderer()->draw_regular("Max Armor"))
		{
			PED::SET_PED_ARMOUR(PLAYER::PLAYER_PED_ID(), PLAYER::GET_PLAYER_MAX_ARMOUR(PLAYER::PLAYER_ID()));
			g_utility.notifyMap("Max Armor Succesfuly");
		}
		if (GetRenderer()->draw_regular("Max Armor"))
		{
			PED::CLEAR_PED_BLOOD_DAMAGE(PLAYER::PLAYER_PED_ID());
			g_utility.notifyMap("Clean Succesfuly");
		}
	}
	void Self_Animation()
	{
		if (GetRenderer()->draw_regular("Stop All Animation"))
		{
			BRAIN::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID()); BRAIN::CLEAR_PED_SECONDARY_TASK(PLAYER::PLAYER_PED_ID());
		}
		if (GetRenderer()->draw_regular("SexReceiver"))
		{
			g_utility.Animation("rcmpaparazzo_2", "shag_loop_poppy");
		}
		if (GetRenderer()->draw_regular("SexGiver"))
		{
			g_utility.Animation("rcmpaparazzo_2", "shag_loop_a");
		}
		if (GetRenderer()->draw_regular("Stripper Dance"))
		{
			g_utility.Animation("mini@strip_club@private_dance@part1", "priv_dance_p1");
		}
		if (GetRenderer()->draw_regular("Pole Dance"))
		{
			g_utility.Animation("mini@strip_club@pole_dance@pole_dance1", "pd_dance_01");
		}
		if (GetRenderer()->draw_regular("PushUps"))
		{
			g_utility.Animation("amb@world_human_push_ups@male@base", "base");
		}
		if (GetRenderer()->draw_regular("SitUps"))
		{
			g_utility.Animation("amb@world_human_sit_ups@male@base", "base");
		}
		if (GetRenderer()->draw_regular("Celebrate"))
		{
			g_utility.Animation("rcmfanatic1celebrate", "celebrate");
		}
		if (GetRenderer()->draw_regular("Electrocution"))
		{
			g_utility.Animation("ragdoll@human", "electrocute");
		}
		if (GetRenderer()->draw_regular("Suicide"))
		{
			g_utility.Animation("mp_suicide", "pistol");
		}
		if (GetRenderer()->draw_regular("Showering"))
		{
			g_utility.Animation("mp_safehouseshower@male@", "male_shower_idle_b");
		}
		if (GetRenderer()->draw_regular("Dance verse"))
		{
			g_utility.Animation("special_ped@mountain_dancer@monologue_4@monologue_4a", "mnt_dnc_verse");
		}
		if (GetRenderer()->draw_regular("Heaven Dance"))
		{
			g_utility.Animation("special_ped@mountain_dancer@monologue_1@monologue_1a", "mtn_dnc_if_you_want_to_get_to_heaven");
		}
	}
	void Self_models()
	{
		for (int i = 0; i < 683; i++) {
			if (GetRenderer()->draw_regular(m_models[i].m_name))
			{
				g_utility.ChangeModel(m_models[i].m_model);
			}
		}
	}
	void Self_vision()
	{
		for (int i = 0; i < 26; i++) {
			if (GetRenderer()->draw_regular(visions[i].m_name))
			{
				GRAPHICS::SET_TIMECYCLE_MODIFIER(visions[i].m_vision);
			}
		}
	}
	void Self_handtrails()
	{
		addOption()->BoolOption("Enable", &m_Handtrails);
		GetRenderer()->draw_number("Scale", &handscale, 0, 2, 0.1f);
		addOption()->BreakOption("Color");
		GetRenderer()->draw_number("Red", &handred, 0, 255, 1);
		GetRenderer()->draw_number("Green", &handgreen, 0, 255, 1);
		GetRenderer()->draw_number("Blue", &handblue, 0, 255, 1);
		GetRenderer()->draw_number("Opacity", &handalpha, 0, 255, 1);
	}
	void Self_particles()
	{
		addOption()->BoolOption("Enable", &glowmanager);
		GetRenderer()->draw_number("Scale", &m_GlowScale, 0, 2, 0.1f);
		GetRenderer()->draw_array("Particle", m_Particle, &m_ParticleIterator);
		addOption()->BreakOption("part of the character");
		addOption()->BoolOption("Head", &m_Head);
		addOption()->BoolOption("Rigth Hand", &m_RightHand);
		addOption()->BoolOption("Left Hand", &m_LeftHand);
		addOption()->BoolOption("Rigth Foot", &m_RightFood);
		addOption()->BoolOption("Left Foot", &m_LeftFood);
	}
	void Self_water()
	{
		addOption()->BoolOption("Walk Under Water", &WalkunderWater);
		addOption()->BoolOption("Walk On Water", &WalkonWater);
		addOption()->BoolOption("Move Water Away", &ModiffyWater);
	}
	void Self_outfits()
	{
		addOption()->Submenu("Load Outfits", Self_loadoutfits);
		if (GetRenderer()->draw_regular("Save Outfits"))
		{
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
			MISC::DISPLAY_ONSCREEN_KEYBOARD(true, (char*)"Name Outfit:", (char*)"", (char*)"", (char*)"", (char*)"", (char*)"", 32);
			while (MISC::UPDATE_ONSCREEN_KEYBOARD() == 0) {
				fiber::current()->sleep();
			}
			if (!MISC::GET_ONSCREEN_KEYBOARD_RESULT()) {
				return;
			}
			GetOutfitsComponents()->Save(MISC::GET_ONSCREEN_KEYBOARD_RESULT());
		}
		if (GetRenderer()->draw_number("Hat", &face, 0, 200, 1, 3))
		{
			PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 0, face, 0, 1);
		}
		if (GetRenderer()->draw_number("Hat variation", &faceVar, 0, 200, 1, 3))
		{
			PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 0, face, faceVar, 1);
		}
		if (GetRenderer()->draw_number("Glasses", &glasses, 0, 200, 1, 3))
		{
			PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 1, glasses, 0, 1);
		}
		if (GetRenderer()->draw_number("Glasses variation", &glassesVar, 0, 200, 1))
		{
			PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 1, glasses, glassesVar, 1);
		}
		if (GetRenderer()->draw_number("Ear pieces", &ears, 0, 200, 1, 3))
		{
			PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 1, ears, 0, 1);
		}
		if (GetRenderer()->draw_number("Ears variation", &earsVar, 0, 200, 1, 3))
		{
			PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 1, ears, earsVar, 1);
		}
		for (size_t i = 0; i < 12; i++) {
			if (GetRenderer()->draw_number(apparanceLabel[i], &components[i], 0, 200, 1, 3))
			{
				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), i, components[i], 0, 0);


			}
			if (GetRenderer()->draw_number(apparanceComponentLabel[i], &componentsVar[i], 0, 200, 1, 3))
			{
				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), i, components[i], componentsVar[i], 0);

			}

		}
	}
	void Self_loadoutfits()
	{
		addOption()->BreakOption("Outfits");
		std::vector<std::string> outfits = util::dirs::get_files_in_directory(util::dirs::get_directories()->get_outfits(), ".json");
		if (outfits.size()) {
			for (std::string& outfit : outfits) {
				if (GetRenderer()->draw_regular(outfit.c_str()))
				{
					GetOutfitsComponents()->Load(outfit.c_str());
				}
			}
		}
		else
		{
			GetRenderer()->draw_regular("~c~Empty");
		}
	}
	void Vehicle_loadVehicle()
	{
		addOption()->BreakOption("Vehicle");
		std::vector<std::string> vehicles = util::dirs::get_files_in_directory(util::dirs::get_directories()->get_vehicle(), ".json");
		if (vehicles.size()) {
			for (std::string& vehicle : vehicles) {
				if (GetRenderer()->draw_regular(vehicle.c_str()))
				{
					load(vehicle.c_str());
				}
			}
		}
		else
		{
			GetRenderer()->draw_regular("~c~Empty");
		}
	}
	void Self_movement()
	{
		addOption()->BoolNumberOption("No-Clip", &g_NoClip, &g_NoClipSpeed, 0, 20.f, 1);
		//GetRenderer()->draw_array("Type", NoclipTypes, &NoclipIterator);
		addOption()->BoolNumberOption("Alpha", &AlphaNoclipBool, &AlphaNoclip, 0, 255, 10);
		addOption()->BoolOption("Spin", &SpinNoclip);
		addOption()->BreakOption("Jump");
		addOption()->BoolOption("SuperJump", &Superjump);
		addOption()->BoolOption("BeastJump", &Beastjump);
		addOption()->BoolOption("NinjaJump", &NinjaJump);
		addOption()->BoolNumberOption("Fast Run", &Fastrun, &FastRunSpeed, 0, 1.49, 0.1);

	}
	void Vehicle_submenu()
	{
		addOption()->Submenu("Los Santos Custom", Vehicle_lossantoscustom);
		addOption()->Submenu("Ramp", Vehicle_ramps);
		addOption()->Submenu("Acrobatics", Vehicle_acrobatics);
		addOption()->Submenu("Fly", Vehicle_fly);
		addOption()->Submenu("Particle", Vehicle_particle);
		addOption()->Submenu("General", Vehicle_general);

	}
	void Vehicle_general()
	{
		if (GetRenderer()->draw_regular("Auto Pilot"))
		{
			DriveToWaypoint();
		}
		if (GetRenderer()->draw_regular("Stop Pilot"))
		{
			DriveToWaypoint();
		}
		addOption()->BoolOption("Auto Fix", &AutoFix);
		addOption()->BoolOption("Auto Flip", &Autoflip);
		addOption()->BoolOption("Drift", &DriftMode);
		addOption()->BoolOption("Drive On Water", &DriveonWater);
		addOption()->BoolOption("Drive Under Water", &DriveunderWater);
		addOption()->BoolOption("Force To ground", &ForceVehicletoGround);
		addOption()->BoolOption("360", &ThreeSixty);
		addOption()->BoolOption("Glitch", &Glitch);
		addOption()->BoolOption("Engine Always On", &EngineAlwayson);
		addOption()->BoolOption("Render Scorched", &g_Scorched);
		addOption()->BoolOption("Seatbelt", &g_Seatbelt);
		if (GetRenderer()->draw_regular("Plate"))
		{
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
			MISC::DISPLAY_ONSCREEN_KEYBOARD(true, (char*)"Plate:", (char*)"", (char*)"", (char*)"", (char*)"", (char*)"", 32);
			while (MISC::UPDATE_ONSCREEN_KEYBOARD() == 0) {
				fiber::current()->sleep();
			}
			if (!MISC::GET_ONSCREEN_KEYBOARD_RESULT()) {
				return;
			}
			int Vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
			VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(Vehicle, MISC::GET_ONSCREEN_KEYBOARD_RESULT());
		}
		if (GetRenderer()->draw_regular("Flip"))
		{
			VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 0);
		}
		if (GetRenderer()->draw_regular("Open Doors"))
		{
			for (int i = 0; i < 6; i++) {
				VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), i, true, false);
			}
		}
		if (GetRenderer()->draw_regular("Close Doors"))
		{
			VEHICLE::SET_VEHICLE_DOORS_SHUT(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), true);
		}
		if (GetRenderer()->draw_regular("Delete Doors"))
		{
			Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			for (int DoorIndex = 0; DoorIndex <= 6; DoorIndex++) {
				VEHICLE::SET_VEHICLE_DOOR_BROKEN(playerVeh, DoorIndex, 1);
			}
		}
		if (GetRenderer()->draw_regular("Clean"))
		{
			GRAPHICS::WASH_DECALS_FROM_VEHICLE(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 100.0f);
		}
	}
	void Vehicle_lossantoscustom()
	{
		addOption()->Submenu("Load Vehicle", Vehicle_loadVehicle);
		if (GetRenderer()->draw_regular("Save Vehicle"))
		{
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
			MISC::DISPLAY_ONSCREEN_KEYBOARD(true, (char*)"Name Vehicle:", (char*)"", (char*)"", (char*)"", (char*)"", (char*)"", 32);
			while (MISC::UPDATE_ONSCREEN_KEYBOARD() == 0) {
				fiber::current()->sleep();
			}
			if (!MISC::GET_ONSCREEN_KEYBOARD_RESULT()) {
				return;
			}
			save(MISC::GET_ONSCREEN_KEYBOARD_RESULT());
		}
		addOption()->Submenu("Color Primary", Vehicle_colorprimary);
		addOption()->Submenu("Color Secondary", Vehicle_colorsecondary);
		addOption()->Submenu("Lights", Vehicle_lights);
		addOption()->Submenu("Custom", Vehicle_custom);
		addOption()->Submenu("Performance", Vehicle_performance);
		if (GetRenderer()->draw_regular("Max Upgrade"))
		{
			VEHICLE::SET_VEHICLE_MOD_KIT(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 0);
			Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			for (int i = 0; i < 50; i++) { VEHICLE::SET_VEHICLE_MOD(veh, i, VEHICLE::GET_NUM_VEHICLE_MODS(veh, i) - 1, false); }
			VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, 2);
		}
		if (GetRenderer()->draw_regular("Repair"))
		{
			VEHICLE::SET_VEHICLE_FIXED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false));
			VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false));
			VEHICLE::SET_VEHICLE_DIRT_LEVEL(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 0.0f);
			VEHICLE::SET_VEHICLE_ENGINE_HEALTH(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 2000.0f);
			VEHICLE::SET_VEHICLE_BODY_HEALTH(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 2000.0f);
		}
		if (GetRenderer()->draw_regular("Wash"))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
			VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, 0);
		}
	}
	void Vehicle_colorprimary()
	{
		GetRenderer()->draw_number("Red", &handred1, 0, 255, 1);
		GetRenderer()->draw_number("Green", &handgreen2, 0, 255, 1);
		GetRenderer()->draw_number("Blue", &handblue3, 0, 255, 1);
		if (GetRenderer()->draw_regular("Aplied Color"))
		{
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, handred1, handgreen2, handblue3);
			}
			else
			{
				!NULL;
			}
		}
	}
	void Vehicle_colorsecondary()
	{
		GetRenderer()->draw_number("Red", &handred4, 0, 255, 1);
		GetRenderer()->draw_number("Green", &handgreen5, 0, 255, 1);
		GetRenderer()->draw_number("Blue", &handblue6, 0, 255, 1);
		if (GetRenderer()->draw_regular("Aplied Color"))
		{
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, handred4, handgreen5, handblue6);
			}
			else
			{
				!NULL;
			}
		}
	}
	void Vehicle_lights()
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		if (GetRenderer()->draw_number("Xenon", &Xenon, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_XENONLIGHTS), 1, 3))
		{
			VEHICLE::SET_VEHICLE_MOD(veh, MOD_XENONLIGHTS, Xenon, false);
		}
		GetRenderer()->draw_number("Red", &neon.r, 0, 255, 1);
		GetRenderer()->draw_number("Green", &neon.g, 0, 255, 1);
		GetRenderer()->draw_number("Blue", &neon.b, 0, 255, 1);
		if (GetRenderer()->draw_regular("Aplied Color"))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_NEON_COLOUR(veh, neon.r, neon.g, neon.b);
		}
		addOption()->BoolOption("Left", &neonleft);
		addOption()->BoolOption("Right", &neonright);
		addOption()->BoolOption("Front", &neonfront);
		addOption()->BoolOption("Back", &neonback);

	}
	void Vehicle_custom()
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		if (GetRenderer()->draw_number("Spoiler", &Spoiler, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_SPOILER), 1, 3))
		{
			VEHICLE::SET_VEHICLE_MOD(veh, MOD_SPOILER, Spoiler, false);
		}
		if (GetRenderer()->draw_number("Front Bumper", &FBumper, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_FRONTBUMPER), 1, 3))
		{
			VEHICLE::SET_VEHICLE_MOD(veh, MOD_FRONTBUMPER, FBumper, false);
		}
		if (GetRenderer()->draw_number("Rear Bumper", &RBumper, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_REARBUMPER), 1, 3))
		{
			VEHICLE::SET_VEHICLE_MOD(veh, MOD_REARBUMPER, RBumper, false);
		}
		if (GetRenderer()->draw_number("Wheels", &Wheels, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_FRONTWHEELS), 1, 3))
		{
			VEHICLE::SET_VEHICLE_MOD(veh, MOD_FRONTWHEELS, Wheels, false);
		}
		if (GetRenderer()->draw_number("Side Skirt", &SSkirt, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_SIDESKIRT), 1, 3))
		{
			VEHICLE::SET_VEHICLE_MOD(veh, MOD_SIDESKIRT, SSkirt, false);
		}
		if (GetRenderer()->draw_number("Exhaust", &Exhaust, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_EXHAUST), 1, 3))
		{
			VEHICLE::SET_VEHICLE_MOD(veh, MOD_EXHAUST, Exhaust, false);
		}
		if (GetRenderer()->draw_number("Grille", &Grille, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_GRILLE), 1, 3))
		{
			VEHICLE::SET_VEHICLE_MOD(veh, MOD_GRILLE, Grille, false);
		}
		if (GetRenderer()->draw_number("Chassis", &Chasis, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_CHASSIS), 1, 3))
		{
			VEHICLE::SET_VEHICLE_MOD(veh, MOD_CHASSIS, Chasis, false);
		}
		if (GetRenderer()->draw_number("Hood", &Hood, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_HOOD), 1, 3))
		{
			VEHICLE::SET_VEHICLE_MOD(veh, MOD_HOOD, Hood, false);
		}
		if (GetRenderer()->draw_number("Fender", &Fender, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_FENDER), 1, 3))
		{
			VEHICLE::SET_VEHICLE_MOD(veh, MOD_FENDER, Fender, false);
		}
		if (GetRenderer()->draw_number("Rigtht Fender", &RFender, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_RIGHTFENDER), 1, 3))
		{
			VEHICLE::SET_VEHICLE_MOD(veh, MOD_RIGHTFENDER, RFender, false);
		}
		if (GetRenderer()->draw_number("Roof", &Roof, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ROOF), 1, 3))
		{
			VEHICLE::SET_VEHICLE_MOD(veh, MOD_ROOF, Roof, false);
		}
		if (GetRenderer()->draw_number("Window", &Windows, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_WINDOWS), 1, 3))
		{
			VEHICLE::SET_VEHICLE_MOD(veh, MOD_WINDOWS, Windows, false);
		}
	}
	void Vehicle_performance()
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		if (GetRenderer()->draw_number("Engine", &Engine, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ENGINE), 1, 3))
		{
			VEHICLE::SET_VEHICLE_MOD(veh, MOD_ENGINE, Engine, false);
		}
		if (GetRenderer()->draw_number("Brakes", &Brakes, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_BRAKES), 1, 3))
		{
			VEHICLE::SET_VEHICLE_MOD(veh, MOD_BRAKES, Brakes, false);
		}
		if (GetRenderer()->draw_number("Transmission", &Transmission, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_TRANSMISSION), 1, 3))
		{
			VEHICLE::SET_VEHICLE_MOD(veh, MOD_TRANSMISSION, Transmission, false);
		}
		if (GetRenderer()->draw_number("Horns", &Horns, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_HORNS), 1, 3))
		{
			VEHICLE::SET_VEHICLE_MOD(veh, MOD_HORNS, Horns, false);
		}
		if (GetRenderer()->draw_number("Suspension", &Suspension, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_SUSPENSION), 1, 3))
		{
			VEHICLE::SET_VEHICLE_MOD(veh, MOD_SUSPENSION, Suspension, false);
		}
		if (GetRenderer()->draw_number("Armor", &Armor, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ARMOR), 1, 3))
		{
			VEHICLE::SET_VEHICLE_MOD(veh, MOD_ARMOR, Armor, false);
		}
	}
	void Vehicle_ramps()
	{
		static bool m_Rampfront;
		static bool m_Rampback;
		static bool m_Rampleft;
		static bool m_Rampright;
		addOption()->BoolOption("Front", &m_Rampfront);
		addOption()->BoolOption("Back", &m_Rampback);
		addOption()->BoolOption("Left", &m_Rampleft);
		addOption()->BoolOption("Right", &m_Rampright);
		if (GetRenderer()->draw_regular("Create"))
		{
			VehicleRamp(m_Rampfront, m_Rampback, m_Rampleft, m_Rampright);
		}
		if (GetRenderer()->draw_regular("Delete"))
		{
			for (int i = 0; i < 4; i++)
			{
				static Hash ramp = MISC::GET_HASH_KEY("lts_prop_lts_ramp_01");
				Vector3 pedpos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0);
				Object ObjToDelete = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(pedpos.x, pedpos.y, pedpos.z, 10.f, ramp, 0, 1, 1);
				OBJECT::DELETE_OBJECT(&ObjToDelete);
			}
		}
	}
	void Vehicle_acrobatics()
	{
		if (GetRenderer()->draw_regular("Front Flip"))
		{
			vehicle_acrobatics(2);
		}
		if (GetRenderer()->draw_regular("Side Flip"))
		{
			vehicle_acrobatics(1);
		}
		if (GetRenderer()->draw_regular("Back Flip"))
		{
			vehicle_acrobatics(3);
		}
		if (GetRenderer()->draw_regular("Bunny Flip"))
		{
			vehicle_acrobatics(0);
		}
	}
	void Vehicle_fly()
	{
		if (addOption()->BoolOption("Enabled", &g_VehicleFly))
		{
			if (g_VehicleFly) {}
			else { VEHICLE::SET_VEHICLE_GRAVITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), true); }
		}
		addOption()->BoolOption("Collision", &g_Collision);
		addOption()->BoolOption("Bypass Speed", &g_BypassSpeed);
		GetRenderer()->draw_number("Speed", &g_FlySpeed, 0, 100, 0.5f);
	}
	void Vehicle_particle()
	{
		addOption()->BoolOption("Enabled", &ParticleVehicle);
		GetRenderer()->draw_number("Scale", &m_GlowScale0, 0, 2, 0.1f);
		GetRenderer()->draw_array("Particle", m_Particle0, &m_ParticleIterator0);
		addOption()->BreakOption("Part of vehicle");
		addOption()->BoolOption("Right Front Wheel", &m_RightFrontWheel);
		addOption()->BoolOption("Left Front Wheel", &m_RightFrontWheel);
		addOption()->BoolOption("Right Back Wheel", &m_RightBackWheel);
		addOption()->BoolOption("Left Back Wheel", &m_RightBackWheel);
	}
	void selected_player_submenu()
	{
		GetPlayerInfo()->Update(g_SelectedPlayer, 1);
		addOption()->BoolOption("Spectator", &spectator);
		if (GetRenderer()->draw_regular("Teleport to player"))
		{
			auto ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
			Vector3 xyzcoords = ENTITY::GET_ENTITY_COORDS(ped, true);
			ENTITY::SET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(-1), xyzcoords.x, xyzcoords.y, xyzcoords.z, 1, 1, 1, 1);
		}
		//addOption()->Submenu("Overseer", PlayerList_overseer);
		addOption()->Submenu("Friendly", PlayerList_Friendly);
		addOption()->Submenu("Vehicle", PlayerList_vehicle);
		addOption()->Submenu("Evil", PlayerList_evil);

	}
	void PlayerList_overseer()
	{
		GetPlayerInfo()->Update(g_SelectedPlayer, 1);
		if (GetRenderer()->draw_regular("Add player"))
		{

			add_player(PLAYER::GET_PLAYER_NAME(g_SelectedPlayer));

		}
		addOption()->BreakOption("Player");
		GetRenderer()->draw_regular("~c~~italic~SOON");


	}
	void PlayerList_Friendly()
	{
		GetPlayerInfo()->Update(g_SelectedPlayer, 1);
		if (GetRenderer()->draw_regular("Gift Vehicle"))
		{
			Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(vehicle, TRUE, TRUE);
			DECORATOR::DECOR_REGISTER("PV_Slot", 3);
			DECORATOR::DECOR_REGISTER("Player_Vehicle", 3);
			DECORATOR::DECOR_SET_BOOL(vehicle, "IgnoredByQuickSave", FALSE);
			DECORATOR::DECOR_SET_INT(vehicle, "Player_Vehicle", NETWORK::NETWORK_HASH_FROM_PLAYER_HANDLE(g_SelectedPlayer));
			VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, FALSE);
		}
		if (GetRenderer()->draw_link("Tutoriel"))
		{
			ShellExecuteA(0, 0, "https://www.youtube.com/watch?v=behP5588RvY", 0, 0, SW_SHOW);
		}
		if (GetRenderer()->draw_regular("Drop Health & armor"))
		{
			if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 1)) {
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 0.0f, 0.0f, 0.0f);
				OBJECT::CREATE_AMBIENT_PICKUP(MISC::GET_HASH_KEY("PICKUP_ARMOUR_STANDARD"), coords.x, coords.y, coords.z, 0, 100000, 1, 0, 1);
				OBJECT::CREATE_AMBIENT_PICKUP(MISC::GET_HASH_KEY("PICKUP_HEALTH_STANDARD"), coords.x, coords.y, coords.z, 0, 100000, 1, 0, 1);
			}
		}
		if (GetRenderer()->draw_regular("Drop Parachute"))
		{
			Ped selectedplayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
			if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
			Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(1735599485, pos.x, pos.y, pos.z + 1.5, 0, 100000, 1, 0, 1);
		}
		if (GetRenderer()->draw_regular("Give All Weapon"))
		{
			PlayerLis_giveweapon();
		}
		if (GetRenderer()->draw_regular("Give All Weapon MK1"))
		{
			PlayerList_giveweaponMK1();
		}
		if (GetRenderer()->draw_regular("Give All Weapon MK2"))
		{
			PlayerList_giveweaponMK2();
		}
		if (GetRenderer()->draw_regular("Copy Outfits"))
		{
			if (g_SelectedPlayer != PLAYER::PLAYER_ID())
			{
				Ped SelectedPlayerPedHandle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
				for (int i = 0; i < 12; i++)
				{
					PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), i, PED::GET_PED_DRAWABLE_VARIATION(SelectedPlayerPedHandle, i), PED::GET_PED_TEXTURE_VARIATION(SelectedPlayerPedHandle, i), PED::GET_PED_PALETTE_VARIATION(SelectedPlayerPedHandle, i));
				}
			}

		}
		if (GetRenderer()->draw_regular("Semi-God"))
		{
			Hash oball = MISC::GET_HASH_KEY("prop_juicestand");
			int orangeball = OBJECT::CREATE_OBJECT(oball, 0, 0, 0, true, 1, 0);
			g_utility.RequestControlOfEnt(orangeball);
			ENTITY::SET_ENTITY_VISIBLE(orangeball, 0, 0);
			ENTITY::ATTACH_ENTITY_TO_ENTITY(orangeball, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 2, 1, 0);
		}
		if (GetRenderer()->draw_regular("Send Friend Request"))
		{
			int handle[76]; //var num3 = sub_34009(A_0, (A_1) + 264, (A_1) + 272);
			NETWORK::NETWORK_HANDLE_FROM_PLAYER(g_SelectedPlayer, &handle[0], 13);
			NETWORK::NETWORK_ADD_FRIEND(&handle[0], "Join the Cult");
		}
		if (GetRenderer()->draw_regular("Profile"))
		{
			int handle[76];
			NETWORK::NETWORK_HANDLE_FROM_PLAYER(g_SelectedPlayer, &handle[0], 13);
			NETWORK::NETWORK_SHOW_PROFILE_UI(&handle[0]);
		}

	}
	void PlayerList_vehicle()
	{
		GetPlayerInfo()->Update(g_SelectedPlayer, 1);
		if (GetRenderer()->draw_regular("Launch"))
		{
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), true));
			if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), true)))
			{
				ENTITY::APPLY_FORCE_TO_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), true), 1, 0, 0, 300, 0, 0, 0, 1, false, true, true, true, true);
			}
		}
		if (GetRenderer()->draw_regular("Boost"))
		{
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED(g_SelectedPlayer), 0))
			{
				Player playerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(playerPed, 0);
				{
					g_utility.RequestControlOfEnt(veh);
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 300.0);
				}
			}
		}
		if (GetRenderer()->draw_regular("Rotate 180"))
		{
			Ped Player = PLAYER::PLAYER_PED_ID(); Vehicle Vehicle = PED::GET_VEHICLE_PED_IS_IN(Player, 0); float Heading = ENTITY::GET_ENTITY_HEADING(Vehicle);
			if (ENTITY::DOES_ENTITY_EXIST(Player)) {
				Vector3 flipCar180Coords = ENTITY::GET_ENTITY_COORDS(Vehicle, 1);
				if (Heading > 180.0) Heading -= 180.0; else Heading += 180.0; ENTITY::SET_ENTITY_COORDS(Vehicle, flipCar180Coords.x, flipCar180Coords.y, flipCar180Coords.z, 0, 0, 0, 1);
				ENTITY::SET_ENTITY_HEADING(Vehicle, Heading); VEHICLE::SET_VEHICLE_FORWARD_SPEED(Vehicle, ENTITY::GET_ENTITY_SPEED(Vehicle));
			}
		}
		if (GetRenderer()->draw_regular("Kick"))
		{
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false))
				BRAIN::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer));
		}
		if (GetRenderer()->draw_regular("Smash Windows"))
		{
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), true))
			{
				Vehicle UserVeh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false);
				VEHICLE::SMASH_VEHICLE_WINDOW(UserVeh, 10);
				VEHICLE::SMASH_VEHICLE_WINDOW(UserVeh, 9);
				VEHICLE::SMASH_VEHICLE_WINDOW(UserVeh, 8);
				VEHICLE::SMASH_VEHICLE_WINDOW(UserVeh, 7);
				VEHICLE::SMASH_VEHICLE_WINDOW(UserVeh, 6);
				VEHICLE::SMASH_VEHICLE_WINDOW(UserVeh, 5);
				VEHICLE::SMASH_VEHICLE_WINDOW(UserVeh, 4);
				VEHICLE::SMASH_VEHICLE_WINDOW(UserVeh, 3);
				VEHICLE::SMASH_VEHICLE_WINDOW(UserVeh, 2);
				VEHICLE::SMASH_VEHICLE_WINDOW(UserVeh, 1);
				VEHICLE::SMASH_VEHICLE_WINDOW(UserVeh, 0);
			}
		}
	}
	void PlayerList_evil()
	{
		GetPlayerInfo()->Update(g_SelectedPlayer, 1);
		if (GetRenderer()->draw_regular("Ragdoll"))
		{
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false);
			FIRE::ADD_EXPLOSION(coords.x, coords.y, coords.z, 0, 30.f, false, true, 0.f, true);
		}
		if (GetRenderer()->draw_regular("Kill"))
		{
			Vector3 GetPlayerCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(g_SelectedPlayer), true);
			FIRE::ADD_EXPLOSION(GetPlayerCoords.x, GetPlayerCoords.y, GetPlayerCoords.z, 29, 20, true, false, 0, false);
			PED::EXPLODE_PED_HEAD(PLAYER::GET_PLAYER_PED(g_SelectedPlayer), 0x145F1012);
		}
		if (GetRenderer()->draw_regular("Clone"))
		{
			PED::CLONE_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 1, 1, 1);
		}
		if (GetRenderer()->draw_regular("Cage"))
		{
			Vector3 remotePos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 0);
			OBJECT::CREATE_OBJECT(959275690, remotePos.x, remotePos.y, remotePos.z - 1.f, true, false, false);
		}
	}
	void Weapon_submenu()
	{
		addOption()->Submenu("Weapons", Weapon_weapons);
		addOption()->Submenu("Tints", Weapon_tints);
		addOption()->Submenu("Gravity", Weapon_gravity);
		addOption()->Submenu("Magnet", Weapon_magnet);
		addOption()->Submenu("Laser Lights", Weapon_laser);
		addOption()->Submenu("Object", Weapon_Object);
		addOption()->Submenu("Paint", Weapon_paint);
		if (GetRenderer()->draw_regular("Give All Weapon"))
		{
			giveallweapon();
		}
		addOption()->BoolOption("Explosive", &Explosivebullet);
		addOption()->BoolOption("RapidFire", &m_RapidFire);
		addOption()->BoolOption("Teleport", &Teleportgun);
		addOption()->BoolOption("Delete", &Deletegun);
		addOption()->BoolOption("Dead Eye", &DeadEyegun);
		addOption()->BoolOption("Delete", &Deletegun);
		addOption()->BoolOption("Money", &MoneyGun);
		if (MoneyGun)
		{
			GetRenderer()->draw_number("Montant", &moneyNumber, 0, 10000, 100);
		}
		addOption()->BoolOption("Drive It", &g_YoinkGun);
		addOption()->BoolOption("Water", &WaterShoot);
		addOption()->BoolOption("Force", &Forcegun);
		addOption()->BoolOption("Airstrike", &Airstrikegun);
	}
	void Weapon_weapons()
	{
		addOption()->Submenu("Assault Rifles", Weapon_ar);
		addOption()->Submenu("Heavy", Weapon_heavy);
		addOption()->Submenu("Lights Machine Guns", Weapon_mg);
		addOption()->Submenu("Melees", Weapon_melee);
		addOption()->Submenu("Misc", Weapon_misc);
		addOption()->Submenu("Pistols", Weapon_pistol);
		addOption()->Submenu("Shotguns", Weapon_shotguns);
		addOption()->Submenu("Sniper Rifles", Weapon_spr);
		addOption()->Submenu("Submachine Guns", Weapon_submachineguns);
		addOption()->Submenu("Throwables", Weapon_th);
	}
	void Weapon_misc()
	{
		for (auto& weaponV2MISC : WeaponV2Misc) {
			if (GetRenderer()->m_current_option == GetRenderer()->m_option_count + 1)
			{
				std::string pic[2] = { "**Invalid**", "**Invalid**" };
				for (int i = 0; i < 200; i++)
				{
					if (weaponV2MISC.m_nameV2MC == WeaponPreviews[i].name) {
						pic[0] = WeaponPreviews[i].WeaponPreviewDict;
						pic[1] = WeaponPreviews[i].WeaponName;
						break;
					}
				}
				//Scaleform_Weapon(weapon.hashWeapon);
				DisplayWeapon(pic[0], pic[1]);
			}
			if (GetRenderer()->draw_regular(weaponV2MISC.m_nameV2MC))
			{
				giveweapon(weaponV2MISC.hashWeaponV2MC);
			}
		}
	}
	void Weapon_th()
	{
		for (auto& weaponV2TH : WeaponV2TH) {
			if (GetRenderer()->m_current_option == GetRenderer()->m_option_count + 1)
			{
				std::string pic[2] = { "**Invalid**", "**Invalid**" };
				for (int i = 0; i < 200; i++)
				{
					if (weaponV2TH.m_nameV2TH == WeaponPreviews[i].name) {
						pic[0] = WeaponPreviews[i].WeaponPreviewDict;
						pic[1] = WeaponPreviews[i].WeaponName;
						break;
					}
				}
				//Scaleform_Weapon(weapon.hashWeapon);
				DisplayWeapon(pic[0], pic[1]);
			}
			if (GetRenderer()->draw_regular(weaponV2TH.m_nameV2TH))
			{
				giveweapon(weaponV2TH.hashWeaponV2TH);
			}
		}
	}
	void Weapon_heavy()
	{
		for (auto& weaponV2HV : WeaponV2HV) {
			if (GetRenderer()->m_current_option == GetRenderer()->m_option_count + 1)
			{
				std::string pic[2] = { "**Invalid**", "**Invalid**" };
				for (int i = 0; i < 100; i++)
				{
					if (weaponV2HV.m_nameV2HV == WeaponPreviews[i].name) {
						pic[0] = WeaponPreviews[i].WeaponPreviewDict;
						pic[1] = WeaponPreviews[i].WeaponName;
						break;
					}
				}
				//Scaleform_Weapon(weapon.hashWeapon);
				DisplayWeapon(pic[0], pic[1]);
			}
			if (GetRenderer()->draw_regular(weaponV2HV.m_nameV2HV))
			{
				giveweapon(weaponV2HV.hashWeaponV2HV);
			}
		}
	}
	void Weapon_spr()
	{
		for (auto& weaponV2SP : WeaponV2SP) {
			if (GetRenderer()->m_current_option == GetRenderer()->m_option_count + 1)
			{
				std::string pic[2] = { "**Invalid**", "**Invalid**" };
				for (int i = 0; i < 100; i++)
				{
					if (weaponV2SP.m_nameV2SP == WeaponPreviews[i].name) {
						pic[0] = WeaponPreviews[i].WeaponPreviewDict;
						pic[1] = WeaponPreviews[i].WeaponName;
						break;
					}
				}
				//Scaleform_Weapon(weapon.hashWeapon);
				DisplayWeapon(pic[0], pic[1]);
			}
			if (GetRenderer()->draw_regular(weaponV2SP.m_nameV2SP))
			{
				giveweapon(weaponV2SP.hashWeaponV2SP);
			}
		}
	}
	void Weapon_mg()
	{
		for (auto& weaponV2MG : WeaponV2MG) {
			if (GetRenderer()->m_current_option == GetRenderer()->m_option_count + 1)
			{
				std::string pic[2] = { "**Invalid**", "**Invalid**" };
				for (int i = 0; i < 100; i++)
				{
					if (weaponV2MG.m_nameV2MG == WeaponPreviews[i].name) {
						pic[0] = WeaponPreviews[i].WeaponPreviewDict;
						pic[1] = WeaponPreviews[i].WeaponName;
						break;
					}
				}
				//Scaleform_Weapon(weapon.hashWeapon);
				DisplayWeapon(pic[0], pic[1]);
			}
			if (GetRenderer()->draw_regular(weaponV2MG.m_nameV2MG))
			{
				giveweapon(weaponV2MG.hashWeaponV2MG);
			}
		}
	}
	void Weapon_ar()
	{
		for (auto& weaponV2AR : WeaponV2AR) {
			if (GetRenderer()->m_current_option == GetRenderer()->m_option_count + 1)
			{
				std::string pic[2] = { "**Invalid**", "**Invalid**" };
				for (int i = 0; i < 100; i++)
				{
					if (weaponV2AR.m_nameV2AR == WeaponPreviews[i].name) {
						pic[0] = WeaponPreviews[i].WeaponPreviewDict;
						pic[1] = WeaponPreviews[i].WeaponName;
						break;
					}
				}
				//Scaleform_Weapon(weapon.hashWeapon);
				DisplayWeapon(pic[0], pic[1]);
				//preview_weapon(weaponV2AR.hashWeaponV2AR);
			}
			if (GetRenderer()->draw_regular(weaponV2AR.m_nameV2AR))
			{
				giveweapon(weaponV2AR.hashWeaponV2AR);
			}
		}
	}
	void Weapon_shotguns()
	{
		for (auto& weaponV2SHG : WeaponV2SHG) {
			if (GetRenderer()->m_current_option == GetRenderer()->m_option_count + 1)
			{
				std::string pic[2] = { "**Invalid**", "**Invalid**" };
				for (int i = 0; i < 100; i++)
				{
					if (weaponV2SHG.m_nameV2SHG == WeaponPreviews[i].name) {
						pic[0] = WeaponPreviews[i].WeaponPreviewDict;
						pic[1] = WeaponPreviews[i].WeaponName;
						break;
					}
				}
				//Scaleform_Weapon(weapon.hashWeapon);
				DisplayWeapon(pic[0], pic[1]);
			}
			if (GetRenderer()->draw_regular(weaponV2SHG.m_nameV2SHG))
			{
				giveweapon(weaponV2SHG.hashWeaponV2SHG);
			}
		}
	}
	void Weapon_submachineguns()
	{
		for (auto& weaponV2SMG : WeaponV2SMG) {
			if (GetRenderer()->m_current_option == GetRenderer()->m_option_count + 1)
			{
				std::string pic[2] = { "**Invalid**", "**Invalid**" };
				for (int i = 0; i < 100; i++)
				{
					if (weaponV2SMG.m_nameV2SMG == WeaponPreviews[i].name) {
						pic[0] = WeaponPreviews[i].WeaponPreviewDict;
						pic[1] = WeaponPreviews[i].WeaponName;
						break;
					}
				}
				//Scaleform_Weapon(weapon.hashWeapon);
				DisplayWeapon(pic[0], pic[1]);
			}
			if (GetRenderer()->draw_regular(weaponV2SMG.m_nameV2SMG))
			{
				giveweapon(weaponV2SMG.hashWeaponV2SMG);
			}
		}
	}
	void Weapon_pistol()
	{
		for (auto& weaponV2P : WeaponV2PS) {
			if (GetRenderer()->m_current_option == GetRenderer()->m_option_count + 1)
			{
				std::string pic[2] = { "**Invalid**", "**Invalid**" };
				for (int i = 0; i < 100; i++)
				{
					if (weaponV2P.m_nameV2P == WeaponPreviews[i].name) {
						pic[0] = WeaponPreviews[i].WeaponPreviewDict;
						pic[1] = WeaponPreviews[i].WeaponName;
						break;
					}
				}
				//Scaleform_Weapon(weapon.hashWeapon);
				DisplayWeapon(pic[0], pic[1]);
			}
			if (GetRenderer()->draw_regular(weaponV2P.m_nameV2P))
			{
				giveweapon(weaponV2P.hashWeaponV2P);
			}
		}
	}
	void Weapon_melee()
	{
		for (auto& weapon : WeaponV2) {
			if (GetRenderer()->m_current_option == GetRenderer()->m_option_count + 1)
			{
				std::string pic[2] = { "**Invalid**", "**Invalid**" };
				for (int i = 0; i < 100; i++)
				{
					if (weapon.m_name == WeaponPreviews[i].name) {
						pic[0] = WeaponPreviews[i].WeaponPreviewDict;
						pic[1] = WeaponPreviews[i].WeaponName;
						break;
					}
				}
				//Scaleform_Weapon(weapon.hashWeapon);
				DisplayWeapon(pic[0], pic[1]);
			}
			if (GetRenderer()->draw_regular(weapon.m_name))
			{
				giveweapon(weapon.hashWeapon);
			}
		}
	}
	void Weapon_tints()
	{
		addOption()->BoolOption("Rainbow", &RainBowCamo);
		if (GetRenderer()->draw_regular("Normal"))
		{
			Weapons;
			for (int i = 0; i < (sizeof(Weapons) / 4); i++) {
				WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), Weapons[i], 0);
			}
		}
		if (GetRenderer()->draw_regular("Green"))
		{
			Weapons;
			for (int i = 0; i < (sizeof(Weapons) / 4); i++) {
				WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), Weapons[i], 1);
			}
		}
		if (GetRenderer()->draw_regular("Gold"))
		{
			Weapons;
			for (int i = 0; i < (sizeof(Weapons) / 4); i++) {
				WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), Weapons[i], 2);
			}
		}
		if (GetRenderer()->draw_regular("Pink"))
		{
			Weapons;
			for (int i = 0; i < (sizeof(Weapons) / 4); i++) {
				WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), Weapons[i], 3);
			}
		}
		if (GetRenderer()->draw_regular("Army"))
		{
			Weapons;
			for (int i = 0; i < (sizeof(Weapons) / 4); i++) {
				WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), Weapons[i], 4);
			}
		}
		if (GetRenderer()->draw_regular("LSPD"))
		{
			Weapons;
			for (int i = 0; i < (sizeof(Weapons) / 4); i++) {
				WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), Weapons[i], 5);
			}
		}
		if (GetRenderer()->draw_regular("Orange"))
		{
			Weapons;
			for (int i = 0; i < (sizeof(Weapons) / 4); i++) {
				WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), Weapons[i], 6);
			}
		}
		if (GetRenderer()->draw_regular("Platinium"))
		{
			Weapons;
			for (int i = 0; i < (sizeof(Weapons) / 4); i++) {
				WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), Weapons[i], 7);
			}
		}
	}
	void Weapon_paint()
	{
		addOption()->BoolOption("Enabled", &Paintgun);
		GetRenderer()->draw_number("Range", &m_range, 0, 255, 1);
		GetRenderer()->draw_number("Intensify", &m_intensity, 0, 255, 1);
		addOption()->BreakOption("Color");
		GetRenderer()->draw_number("Red", &m_color.r, 0, 255, 1);
		GetRenderer()->draw_number("Green", &m_color.g, 0, 255, 1);
		GetRenderer()->draw_number("Blue", &m_color.b, 0, 255, 1);
		GetRenderer()->draw_number("Opacity", &m_color.a, 0, 255, 1);
	}
	void Weapon_gravity()
	{
		//GetRenderer()->draw_array("Type", GravityGunStyle, &GravityGunSize);
		addOption()->BoolOption("Enabled", &GravityGun);
		if (GravityGunSize == 1)
		{
			GetRenderer()->draw_number("Entities", &m_GravityGunEntityCount, 0, 20, 1);
		}
		else
		{
			addOption()->BoolOption("Lock on entities", &LockOnEntity);

		}
		GetRenderer()->draw_number("Force", &g_Force, 0, 100, 0.5);
		GetRenderer()->draw_number("Velocity", &g_Velocity, 0, 100, 0.5);
		GetRenderer()->draw_number("Pull/Push Strength", &g_PullPushStrength, 0, 100, 0.5);
	}
	void Weapon_Object()
	{
		GetRenderer()->draw_array("Object", m_EntityObject, &m_EntityObjectIterator);
		GetRenderer()->draw_number("Velocity", &m_ObjectLaunchSpeed, 0, 20, 0.5);
		GetRenderer()->draw_number("Distance", &m_ObjectSpawnDistance, 0, 20, 0.5);
		addOption()->BoolOption("Enabled", &EntityObjectGun);
	}
	void Weapon_magnet()
	{
		addOption()->BoolOption("Magnet", &m_Magnet);
		addOption()->BreakOption("Color");
		GetRenderer()->draw_number("Red", &magnetGunR, 0, 255, 1);
		GetRenderer()->draw_number("Green", &magnetGunG, 0, 255, 1);
		GetRenderer()->draw_number("Blue", &magnetGunB, 0, 255, 1);
	}
	void Weapon_laser()
	{
		addOption()->BoolOption("Laser", &Laserlight);
		addOption()->BreakOption("Color");
		GetRenderer()->draw_number("Red", &laserR, 0, 255, 1);
		GetRenderer()->draw_number("Green", &laserG, 0, 255, 1);
		GetRenderer()->draw_number("Blue", &laserB, 0, 255, 1);
	}
	void Misc_submenu()
	{
		addOption()->Submenu("Trains", Misc_train);
		addOption()->Submenu("Clouds", Misc_clouds);
		addOption()->Submenu("Map Color", Misc_mapcolor);
		addOption()->Submenu("Story Mode", Misc_strorymode);
		addOption()->Submenu("Times", Misc_times);
		addOption()->Submenu("Traffic", Misc_traffic);
		addOption()->Submenu("Weathers", Misc_weather); 
		if (GetRenderer()->draw_regular("Skip Custscene"))
		{
			CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
		}
	}
	void Misc_train()
	{
		if (GetRenderer()->draw_regular("Drive Nearest Train"))
		{
			const int ElementAmount = 10;
			const int ArrSize = ElementAmount * 2 + 2;

			Vehicle* vehs = new Vehicle[ArrSize];
			vehs[0] = ElementAmount;
			int VehFound = PED::GetPedNearbyVehicles(PLAYER::PLAYER_PED_ID(), vehs);

			for (int i = 0; i < VehFound; i++) {
				int offsettedID = i * 2 + 2;
				if (vehs[offsettedID] != NULL && ENTITY::DOES_ENTITY_EXIST(vehs[offsettedID])) {
					if (VEHICLE::IS_THIS_MODEL_A_TRAIN(ENTITY::GET_ENTITY_MODEL(vehs[offsettedID]))) {
						trainHandle = vehs[offsettedID];
						PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), trainHandle, -1);
						//Notify(cprintf("Found Train", trainHandle)).Send(NotifySuccess);
						if (PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0) == trainHandle)
							break;
					}
				}
			}
		}
		if (GetRenderer()->draw_regular("Quit Train"))
		{
			BRAIN::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
			trainHandle = 0;
		}
		if (GetRenderer()->draw_regular("Delete Train"))
		{
			VEHICLE::DELETE_MISSION_TRAIN(&trainHandle);
		}
	}
	void Misc_clouds()
	{
		if (GetRenderer()->draw_regular("Clear"))
		{
			VEHICLE::DELETE_MISSION_TRAIN(&trainHandle);
		}
		for (int i = 0; i < 16; i++) {
			if (GetRenderer()->draw_regular(clouds[i].m_name))
			{
				SetClouds(clouds[i].m_cloud);
			}
		}
	}
	void Misc_mapcolor()
	{
		addOption()->BoolOption("Enabled", &g_EnableLight);
		GetRenderer()->draw_number("Intensify", &g_LigtIntensity, 0, 100, 1);
		GetRenderer()->draw_number("Red", &g_LightRed, 0, 255, 1);
		GetRenderer()->draw_number("Green", &g_LightGreen, 0, 255, 1);
		GetRenderer()->draw_number("Blue", &g_LightBlue, 0, 255, 1);
	}
	void Misc_times()
	{
		addOption()->BoolOption("Enabled", &g_TimeEnable);
		addOption()->BoolOption("Pause", &g_PauseTime);
		GetRenderer()->draw_number("Hours", &g_Hour, 0, 23, 1);
		GetRenderer()->draw_number("Minutes", &g_Minute, 0, 59, 1);
		GetRenderer()->draw_number("Seconds", &g_Second, 0, 59, 1);
	}
	void Misc_strorymode()
	{
		if (GetRenderer()->draw_regular("Added 1M"))
		{
			SPMoney(true, 1000000, false);
		}
		if (GetRenderer()->draw_regular("Remove 1M"))
		{
			SPMoney(false, 1000000, false);
		}
		if (GetRenderer()->draw_regular("Remove All Money"))
		{
			SPMoney(false, 0, true);
		}
	}
	void Misc_traffic()
	{
		addOption()->BoolOption("Delete Vehicle", &m_DeleteNearVehs);
		addOption()->BoolOption("Explode Vehicle", &m_ExplodeNearVehs);
		addOption()->BoolOption("Rainbow Vehicle", &m_RainbowNearVehs);
		addOption()->BoolOption("Launch Nearby Vehicle", &m_BoostNearVehs);
	}
	void Misc_weather()
	{
		for (int i = 0; i < 16; i++) {
			if (GetRenderer()->draw_regular(weathers[i].m_name))
			{
				MISC::SET_WEATHER_TYPE_NOW_PERSIST(weathers[i].m_weather);
			}
		}
		if (GetRenderer()->draw_regular("Lightning"))
		{
			MISC::FORCE_LIGHTNING_FLASH();
		}
	}
	void Misc_rampbuilder()
	{
		GetRenderer()->draw_array("Type", RampTypes, &RampIndex);
		GetRenderer()->draw_number("Amount", &g_RampCount, 0, 100, 1);
		if (GetRenderer()->draw_regular("Create"))
		{
			Ramp();
		}
		if (GetRenderer()->draw_regular("Delete"))
		{
			DeleteRamp();
		}
	}
	void Teleport_submenu()
	{

		if (GetRenderer()->draw_regular("Teleport to Waypoint"))
		{
			Vector3 coords = GetBlipIcon();
			Ped ped = PLAYER::PLAYER_PED_ID();

			if (coords.x == 0 && coords.y == 0) { return; }

			if (PED::IS_PED_IN_ANY_VEHICLE(ped, 0))
				ped = PED::GET_VEHICLE_PED_IS_USING(ped);

			bool isGroundAvailable = false;
			std::vector<float> GROUND_HEIGHT{ 100.0f, 150.0f, 50.0f, 0.0f, 200.0f, 250.0f, 300.0f, 350.0f, 400.0f, 450.0f, 500.0f, 550.0f, 600.0f, 650.0f, 700.0f, 750.0f, 800.0f };

			for (int i = 0; i < GROUND_HEIGHT.size(); i++)
			{
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ped, coords.x, coords.y, GROUND_HEIGHT[i], 0, 0, 1);



				if (MISC::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, GROUND_HEIGHT[i], &coords.z, 0, 0))
				{
					isGroundAvailable = true;
					coords.z += 3.0;
					break;
				}
			}
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ped, coords.x, coords.y, coords.z, 0, 0, 1);
		}
		if (GetRenderer()->draw_regular("Teleport to Objective"))
		{
			Vector3 location;

			if (get_objective_location(location))
			{
				PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), location.x, location.y, location.z);
			}
		}
		if (GetRenderer()->draw_regular("Teleport Forward"))
		{
			teleport_direction(0);
		}
		if (GetRenderer()->draw_regular("Teleport Backward"))
		{
			teleport_direction(1);
		}
		if (GetRenderer()->draw_regular("Teleport Up"))
		{
			teleport_direction(2);
		}
		if (GetRenderer()->draw_regular("Teleport Down"))
		{
			teleport_direction(4);
		}
		addOption()->Submenu("Load Teleportation", Teleport_loadteleport);
		if (GetRenderer()->draw_regular("Save Teleportation"))
		{
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
			MISC::DISPLAY_ONSCREEN_KEYBOARD(true, (char*)"Name teleport:", (char*)"", (char*)"", (char*)"", (char*)"", (char*)"", 32);
			while (MISC::UPDATE_ONSCREEN_KEYBOARD() == 0) {
				fiber::current()->sleep();
			}
			if (!MISC::GET_ONSCREEN_KEYBOARD_RESULT()) {
				return;
			}
			GetTeleport()->Save(MISC::GET_ONSCREEN_KEYBOARD_RESULT(), ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false));
		}
		//GetRenderer()->draw_sub("Indoors", Teleport_indoors);
		//GetRenderer()->draw_sub("Outdoors", Teleport_outdoors);
		//GetRenderer()->draw_sub("Los Santos Custom", Teleport_lossantoscustom);
		//GetRenderer()->draw_sub("Clothes Shop", Teleport_clotheshop);
		//GetRenderer()->draw_sub("Airports", Teleport_airport);
		//GetRenderer()->draw_sub("Ammunation", Teleport_ammunation);
		//GetRenderer()->draw_sub("Barber Shop", Teleport_barbershop);
		//GetRenderer()->draw_sub("Tatoo Shop", Teleport_tatooshop);
		//GetRenderer()->draw_sub("Stores", Teleport_store);
	}
	void Teleport_loadteleport()
	{
		addOption()->BreakOption("Teleportation");
		std::vector<std::string> teleports = util::dirs::get_files_in_directory(util::dirs::get_directories()->get_teleport(), ".json");
		if (teleports.size()) {
			for (std::string& teleport : teleports) {
				if (GetRenderer()->draw_regular(teleport.c_str()))
				{
					GetTeleport()->Load(teleport.c_str());
				}
			}
		}
		else
		{
			GetRenderer()->draw_regular("~c~Empty");
		}
	}
	void Teleport_outdoors()
	{
		for (int i = 0; i < 16; i++)
		{
			if (GetRenderer()->draw_regular(TPLocationsOutdoor[i].Name))
			{
				Vector3 coords{ TPLocationsOutdoor[i].X, TPLocationsOutdoor[i].Y, TPLocationsOutdoor[i].Z };
				GetTeleport()->to_coords(PLAYER::PLAYER_PED_ID(), coords, true, false);
			}
		}
	}
	void Teleport_indoors()
	{
		for (int i = 0; i < 16; i++)
		{
			if (GetRenderer()->draw_regular(TPLocationsIndoor[i].Name))
			{
				Vector3 coords{ TPLocationsIndoor[i].X, TPLocationsIndoor[i].Y, TPLocationsIndoor[i].Z };
				TeleportFunction(coords);
			}
		}
	}
	void Teleport_lossantoscustom()
	{
		for (int i = 0; i < 16; i++)
		{
			if (GetRenderer()->draw_regular(TPLocationsLSC[i].Name))
			{
				Vector3 coords{ TPLocationsLSC[i].X, TPLocationsLSC[i].Y, TPLocationsLSC[i].Z };
				GetTeleport()->to_coords(PLAYER::PLAYER_PED_ID(), coords, true, false);
			}
		}
	}
	void Teleport_clotheshop()
	{
		for (int i = 0; i < 16; i++)
		{
			if (GetRenderer()->draw_regular(TPLocationsCS[i].Name))
			{
				Vector3 coords{ TPLocationsCS[i].X, TPLocationsCS[i].Y, TPLocationsCS[i].Z };
				TeleportFunction(coords);
			}
		}
	}
	void Teleport_airport()
	{
		for (int i = 0; i < 16; i++)
		{
			if (GetRenderer()->draw_regular(TPLocationsAirport[i].Name))
			{
				Vector3 coords{ TPLocationsAirport[i].X, TPLocationsAirport[i].Y, TPLocationsAirport[i].Z };
				TeleportFunction(coords);
			}
		}
	}
	void Teleport_ammunation()
	{
		for (int i = 0; i < 16; i++)
		{
			if (GetRenderer()->draw_regular(TPLocationsAmmo[i].Name))
			{
				Vector3 coords{ TPLocationsAmmo[i].X, TPLocationsAmmo[i].Y, TPLocationsAmmo[i].Z };
				TeleportFunction(coords);
			}
		}
	}
	/*void Teleport_barbershop()
	{
		for (int i = 0; i < 16; i++)
		{
			if (GetRenderer()->draw_regular(TPLocationsBS[i].Name))
			{
				Vector3 coords{ TPLocationsBS[i].X, TPLocationsBS[i].Y, TPLocationsBS[i].Z };
				TeleportFunction(coords);
			}
		}
	}*/
	void Teleport_tatooshop()
	{
		for (int i = 0; i < 16; i++)
		{
			if (GetRenderer()->draw_regular(TPLocationsTS[i].Name))
			{
				Vector3 coords{ TPLocationsTS[i].X, TPLocationsTS[i].Y, TPLocationsTS[i].Z };
				TeleportFunction(coords);
			}
		}
	}
	void Teleport_store()
	{
		for (int i = 0; i < 16; i++)
		{
			if (GetRenderer()->draw_regular(TPLocationsStores[i].Name))
			{
				Vector3 coords{ TPLocationsStores[i].X, TPLocationsStores[i].Y, TPLocationsStores[i].Z };
				TeleportFunction(coords);
			}
		}
	}

	struct asi_mod {
		HMODULE m_module;
		std::string name;
	};
	std::map<std::string, HMODULE> m_plugin_handles;
	void load_asi(std::string script) {
		auto lib = LoadLibraryA(g_utility.get_documents_path().append("\\Virtual X\\").append("asi\\").append(script).c_str());
		m_plugin_handles.insert({ script, lib });
	}

	void ScriptHookV_Submenu()
	{
		addOption()->Submenu("Download Asi", Download_ScriptHookV_Submenu);
		addOption()->BreakOption("Asi");
		auto filePath = std::filesystem::path(g_utility.get_documents_path().append("\\Virtual X\\").append("asi"));
		std::filesystem::directory_iterator dirIt{ filePath.string() };
		static std::string hdrName{};
		for (auto&& dirEntry : dirIt) {
			if (dirEntry.is_regular_file()) {
				auto path = dirEntry.path();
				if (path.has_filename()) {
					if (path.extension().string() == ".asi") {
						if (GetRenderer()->draw_regular(path.filename().string().c_str())) {
							load_asi(path.filename().string());
						}
					}
				}
			}
		}
		/*addOption()->BreakOption("Running Script");
		for (auto& penis : m_plugin_handles) {
			if (GetRenderer()->draw_regular(penis.first.c_str())) {
				script_hook_v::script_unregister(penis.second);
				m_plugin_handles.erase(penis.first);
			}
		}*/
	}

	void Download_ScriptHookV_Submenu()
	{
		if (GetRenderer()->draw_regular("Rampage")) {
			ShellExecuteA(0, 0, "https://www.gta5-mods.com/scripts/rampage-trainer", 0, 0, SW_SHOW);
		}
		if (GetRenderer()->draw_regular("Menyoo")) {
			ShellExecuteA(0, 0, "https://www.gta5-mods.com/scripts/menyoo-pc-sp", 0, 0, SW_SHOW);
		}
		if (GetRenderer()->draw_regular("Native Trainer")) {
			ShellExecuteA(0, 0, "https://www.gta5-mods.com/tools/script-hook-v", 0, 0, SW_SHOW);
		}
		if (GetRenderer()->draw_regular("Enhanced Native Trainer")) {
			ShellExecuteA(0, 0, "https://www.gta5-mods.com/scripts/enhanced-native-trainer-zemanez-and-others", 0, 0, SW_SHOW);
		}
		if (GetRenderer()->draw_regular("Halloween")) {
			ShellExecuteA(0, 0, "https://www.gta5-mods.com/scripts/halloween-mod-menu", 0, 0, SW_SHOW);
		}
		if (GetRenderer()->draw_regular("Firah")) {
			ShellExecuteA(0, 0, "https://www.gta5-mods.com/scripts/firah-menu-v1", 0, 0, SW_SHOW);
		}
		if (GetRenderer()->draw_regular("Bodyguard")) {
			ShellExecuteA(0, 0, "https://www.gta5-mods.com/scripts/bodyguard-menu", 0, 0, SW_SHOW);
		}
		if (GetRenderer()->draw_regular("Rigidz")) {
			ShellExecuteA(0, 0, "https://www.gta5-mods.com/scripts/rigidz-trainer-menu-tarackhun", 0, 0, SW_SHOW);
		}
		if (GetRenderer()->draw_regular("And More go in GTAV Mods")) {
			ShellExecuteA(0, 0, "https://www.gta5-mods.com/", 0, 0, SW_SHOW);
		}
	}
	

	void Recovery_submenu()
	{
		addOption()->Submenu("Increase", Recovery_increase);
		addOption()->Submenu("Money", Recovery_money);
		addOption()->Submenu("RP", Recovery_rp);
		addOption()->Submenu("Stats", Recovery_stats);
		addOption()->Submenu("Unlocks", Recovery_unlocks);
		addOption()->BreakOption("General");
		if (GetRenderer()->draw_regular("Skip The Data Breaches Setups"))
		{
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_GANGOPS_FLOW_MISSION_PROG"), 503, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_GANGOPS_HEIST_STATUS"), 229383, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_GANGOPS_FLOW_NOTIFICATIONS"), 1557, 1);
		}
		if (GetRenderer()->draw_regular("Skip The Bogdan Problem Setups"))
		{
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_APPROACH"), 2, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_TARGET"), 3, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_BITSET1"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_DISRUPTSHIP"), 3, 1);
		}
		if (GetRenderer()->draw_regular("Skip The Doomsday Scenario Setups"))
		{
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_APPROACH"), 2, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_TARGET"), 3, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_BITSET1"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_DISRUPTSHIP"), 3, 1);
		}
		if (GetRenderer()->draw_regular("Complete Objectives"))
		{
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_COMPLETEDAILYOBJ"), 100, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_COMPLETEDAILYOBJTOTAL"), 100, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_TOTALDAYCOMPLETED"), 100, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_TOTALWEEKCOMPLETED"), 400, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_TOTALMONTHCOMPLETED"), 1800, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CONSECUTIVEDAYCOMPLETED"), 30, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CONSECUTIVEWEEKCOMPLETED"), 4, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CONSECUTIVEMONTHCOMPLETE"), 1, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_COMPLETEDAILYOBJSA"), 100, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_COMPLETEDAILYOBJTOTALSA"), 100, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_TOTALDAYCOMPLETEDSA"), 100, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_TOTALWEEKCOMPLETEDSA"), 400, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_TOTALMONTHCOMPLETEDSA"), 1800, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CONSECUTIVEDAYCOMPLETEDSA"), 30, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CONSECUTIVEWEEKCOMPLETEDSA"), 4, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CONSECUTIVEMONTHCOMPLETESA"), 1, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_DAILYOBJCOMPLETEDSA"), 100, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_DAILYOBJCOMPLETED"), 100, true);
		}
		if (GetRenderer()->draw_regular("Redesign Character"))
		{
			STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP0_FM_CHANGECHAR_ASKED"), 0, 1);
		}
		if (GetRenderer()->draw_regular("Reset Orbital Cooldown"))
		{
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ORBITAL_CANNON_COOLDOWN"), 0, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_ORBITAL_CANNON_COOLDOWN"), 0, 0);
		}
		if (GetRenderer()->draw_regular("Max Snacks"))
		{
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_NO_BOUGHT_YUM_SNACKS"), 99999999, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_NO_BOUGHT_HEALTH_SNACKS"), 99999999, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_NO_BOUGHT_EPIC_SNACKS"), 99999999, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CIGARETTES_BOUGHT"), 99999999, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_NUMBER_OF_ORANGE_BOUGHT"), 99999999, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_NUMBER_OF_BOURGE_BOUGHT"), 99999999, 0);
		}
		if (GetRenderer()->draw_regular("Max Office Money"))
		{
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_LIFETIME_BUY_COMPLETE"), 1223, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_LIFETIME_BUY_UNDERTAKEN"), 1223, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_LIFETIME_SELL_COMPLETE"), 434, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_LIFETIME_SELL_UNDERTAKEN"), 434, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_LIFETIME_CONTRA_EARNINGS"), 1220000000, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_LIFETIME_BUY_COMPLETE"), 1223, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_LIFETIME_BUY_UNDERTAKEN"), 1223, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_LIFETIME_SELL_COMPLETE"), 434, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_LIFETIME_SELL_UNDERTAKEN"), 434, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_LIFETIME_CONTRA_EARNINGS"), 1220000000, 0);
		}
		if (GetRenderer()->draw_regular("Max Nightclub Popularity"))
		{
			char sbuf[50];
			int stat_r;
			STATS::STAT_GET_INT(MISC::GET_HASH_KEY("MPPLY_LAST_MP_CHAR"), &stat_r, 1);
			snprintf(sbuf, sizeof(sbuf), "MP%i%s", stat_r, "CLUB_POPULARITY");
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY(sbuf), 1000, 1);
		}

	}
	void Recovery_money()
	{
		addOption()->BoolOption("Drop", &moneydrop);
		addOption()->BreakOption("~italic~~c~Money");
		if (GetRenderer()->draw_regular("Add 100 Million"))
		{
			SPMoney(true, 1000000000, false);
		}
		if (GetRenderer()->draw_regular("Add 50 Million"))
		{
			SPMoney(true, 500000000, false);
		}
		if (GetRenderer()->draw_regular("Add 25 Million"))
		{
			SPMoney(true, 250000000, false);
		}
		if (GetRenderer()->draw_regular("Add 15 Million"))
		{
			SPMoney(true, 150000000, false);
		}
		if (GetRenderer()->draw_regular("Add 10 Million"))
		{
			SPMoney(true, 100000000, false);
		}
		if (GetRenderer()->draw_regular("Add 5 Million"))
		{
			SPMoney(true, 500000000, false);
		}
		if (GetRenderer()->draw_regular("Add 1 Million"))
		{
			SPMoney(true, 100000000, false);
		}
	}
	void Recovery_rp()
	{
		if (GetRenderer()->draw_number("Level", &levelrp, 0, 8000, 1))
		{
			if (IsKeyPressed(VK_NUMPAD5))
			{
				if (levelrp > 8000)
					levelrp = 8000;
				if (levelrp < 0)
					levelrp = 0;

			}
		}
		if (GetRenderer()->draw_regular("Set Level"))
		{
			SetRank(levelrp);
		}
	}
	void Recovery_increase()
	{
		if (GetRenderer()->draw_regular("Stamina"))
		{
			IncreaseStamina();
		}
		if (GetRenderer()->draw_regular("Strenght"))
		{
			IncreaseStrength();
		}
		if (GetRenderer()->draw_regular("Loungh"))
		{
			InceaseLoungh();
		}
		if (GetRenderer()->draw_regular("Driving"))
		{
			IncreaseDriving();
		}
		if (GetRenderer()->draw_regular("Fly"))
		{
			IncreaseFly();
		}
		if (GetRenderer()->draw_regular("Shooting"))
		{
			IncreaseShooting();
		}
		if (GetRenderer()->draw_regular("Stealth"))
		{
			IncreaseStealth();
		}
	}
	void Recovery_stats()
	{
		if (GetRenderer()->draw_regular("Max Stats"))
		{
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STAM"), 100, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STRN"), 100, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_LUNG"), 100, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_DRIV"), 100, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_FLY"), 100, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_SHO"), 100, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STL"), 100, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STAM"), 100, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STRN"), 100, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_LUNG"), 100, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_DRIV"), 100, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_FLY"), 100, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_SHO"), 100, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STL"), 100, 0);
		}
		if (GetRenderer()->draw_regular("Stamina"))
		{
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STAM"), 100, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STAM"), 100, 0);
		}
		if (GetRenderer()->draw_regular("Driving"))
		{
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_DRIV"), 100, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_DRIV"), 100, 0);
		}
		if (GetRenderer()->draw_regular("Flying"))
		{
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_FLY"), 100, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_FLY"), 100, 0);
		}
		if (GetRenderer()->draw_regular("Strenght"))
		{
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STRN"), 100, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STRN"), 100, 0);
		}
		if (GetRenderer()->draw_regular("LungCap"))
		{
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_LUNG"), 100, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_LUNG"), 100, 0);
		}
		if (GetRenderer()->draw_regular("Stealth"))
		{
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STL"), 100, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STL"), 100, 0);
		}
		if (GetRenderer()->draw_regular("Shooting"))
		{
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_SHO"), 100, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_SHO"), 100, 0);
		}

	}
	void Recovery_unlocks()
	{
		if (GetRenderer()->draw_regular("Achievements"))
		{
			PLAYER::GIVE_ACHIEVEMENT_TO_PLAYER;
			STATS::STAT_SET_INT(0x53c59a8e, -1, 1); // MPPLY_HEIST_ACH_TRACKER
			STATS::STAT_SET_INT(0x796d2d6a, 25, 1); // MPPLY_AWD_FM_CR_DM_MADE
			STATS::STAT_SET_INT(0xd5d5279d, 25, 1); // MPPLY_AWD_FM_CR_RACES_MADE
			STATS::STAT_SET_INT(0xe00c1321, 100, 1); // MPPLY_AWD_FM_CR_PLAYED_BY_PEEP
			Hash StatsBools[] =
			{
				// MP0_AWD_FM_GOLF_HOLE_IN_1 MP0_AWD_FM_SHOOTRANG_GRAN_WON MP0_AWD_FM_TENNIS_STASETWIN MP0_AWD_FM6DARTCHKOUT MP0_AWD_FMATTGANGHQ
				0x22d9626f, 0x2bfe2b98, 0xcca40e6,  0xb6c51652, 0x49e3d35b,
				// MP0_AWD_BUY_EVERY_GUN MP0_AWD_FMWINEVERYGAMEMODE MP0_AWD_FM25DIFFERENTDM MP0_AWD_FM_TENNIS_5_SET_WINS MP0_AWD_FM25DIFFERENTRACES
				0x21f81ca1, 0xbdda53b4, 0x59de4ddc, 0x69e7c068, 0xb4f06c2f,
				// MP0_AWD_FM25DIFITEMSCLOTHES MP0_AWD_FMFULLYMODDEDCAR MP0_AWD_FMKILL3ANDWINGTARACE MP0_AWD_FMKILLSTREAKSDM MP0_AWD_FMMOSTKILLSGANGHIDE
				0x9ba12d14, 0xe9472bb4, 0x43d56fad, 0x3099c3fe, 0x5941fbad,
				// MP0_AWD_FMMOSTKILLSSURVIVE MP0_AWD_FMRACEWORLDRECHOLDER MP0_AWD_FMPICKUPDLCCRATE1ST MP0_AWD_FMWINCUSTOMRACE MP0_MP0_AWD_FMWINALLRACEMODES
				0xc41b8767, 0x655e0bad, 0x2ae837e4, 0x71212ddf, 0xda28ebe4,
				// MP0_AWD_FMTATTOOALLBODYPARTS
				0xe3520842
			};
			for (Hash h : StatsBools)
				STATS::STAT_SET_BOOL(h, 1, 1);
			STATS::STAT_SET_INT(0x723f39d6, 4, 1); // MP0_AWD_PASSENGERTIME
			STATS::STAT_SET_INT(0x653a8f83, 4, 1); // MP0_AWD_TIME_IN_HELICOPTER
			STATS::STAT_SET_INT(0x45e1432a, 5, 1); // MP0_MOST_FLIPS_IN_ONE_JUMP
			STATS::STAT_SET_INT(0xe9e500bc, 5, 1); // MP0_MOST_SPINS_IN_ONE_JUMP
			STATS::STAT_SET_INT(0x833d3192, 10, 1); // MP0_AWD_FMHORDWAVESSURVIVE
			STATS::STAT_SET_INT(0x12f3b311, 20, 1); // MP0_AWD_HOLD_UP_SHOPS
			Hash Stats25[] =
			{
				// MP0_AWD_CAR_BOMBS_ENEMY_KILLS MP0_AWD_FM_GOLF_WON MP0_AWD_FM_SHOOTRANG_CT_WON MP0_AWD_FM_SHOOTRANG_RT_WON MP0_AWD_FM_SHOOTRANG_TG_WON
				0xaae88a2f, 0xe847156c, 0x741f0838, 0xeac04cce, 0x898dab76, 0x1AF2DE9E, 0xA1787290, 0x5F76739A, 0x2C177BAD,
				// MP0_AWD_FM_TENNIS_WON MP0_AWD_SECURITY_CARS_ROBBED MP0_AWD_LAPDANCES MP0_MOST_ARM_WRESTLING_WINS MP0_AWD_NO_HAIRCUTS
				0xe51a03e4, 0x5413e4e9, 0x4314583e, 0xd9da214e, 0xa43c7aac, 0xEC234AE2, 0x46533E0C, 0xF29D01D9, 0x3EDE081C, 0xC55AAFAA,
				// MP0_AWD_WIN_AT_DARTS MP0_AWD_FM_GOLF_BIRDIES MP0_AWD_FM_TENNIS_ACE MP0_AWD_PARACHUTE_JUMPS_20M MP0_AWD_PARACHUTE_JUMPS_50M
				0x279625d2, 0x978c6413, 0x7036f468, 0x1e3139c0, 0xd95051b7, 0x61F5DB39, 0x786E5B58, 0xAE352AA3, 0xAFBB09A3, 0x2F6C1441,
				// MP0_AIR_LAUNCHES_OVER_40M MP0_AWD_FMCRATEDROPS MP0_AWD_FMKILLBOUNTY MP0_AWD_FMSHOOTDOWNCOPHELI MP0_AWD_FMRALLYWONDRIVE
				0x8a8786e7, 0x2671fd3,  0xfb6b31f1, 0xee270322, 0xbb5b1a96, 0xE7939C0B, 0x144E7D9F, 0x4F6CDED8, 0xF5EDCABA, 0xB43E0E1A,
				// MP0_AWD_FMRALLYWONNAV MP0_AWD_FMWINAIRRACE MP0_AWD_FMWINRACETOPOINTS MP0_AWD_FMWINSEARACE MP0_AWD_FMBASEJMP
				0x6ae2181d, 0x40bf1a36, 0xa11bb5b6, 0xc5c0f286, 0xe54057bd, 0xB1590553, 0x16F2FD31, 0x5A1942E7, 0x58857E4, 0xFA2E93FF,
				// MP0_AWD_FM_RACE_LAST_FIRST MP0_AWD_FM_RACES_FASTEST_LAP
				0x25609da9, 0xc13d4f3a, 0x3A2621D6, 0xE751F17
			};
		}
		if (GetRenderer()->draw_regular("Fast Run"))
		{
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_ABILITY_1_UNLCK"), -1, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_ABILITY_2_UNLCK"), -1, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_ABILITY_3_UNLCK"), -1, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_ABILITY_1_UNLCK"), -1, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_ABILITY_2_UNLCK"), -1, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_ABILITY_3_UNLCK"), -1, true);
		}
		if (GetRenderer()->draw_regular("Prize Ride"))
		{
			STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP0_CARMEET_PV_CHLLGE_CMPLT"), true, true);

		}
		if (GetRenderer()->draw_regular("Unlock Heist"))
		{
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHASE"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHASE2"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHASE3"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHASE4"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHASE5"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHASE6"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHASE7"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHASE8"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHASE9"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHASE10"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHASE11"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHASE12"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_KIT_1_FM_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_KIT_2_FM_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_KIT_3_FM_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_KIT_4_FM_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_KIT_5_FM_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_KIT_6_FM_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_KIT_7_FM_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_KIT_8_FM_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_KIT_9_FM_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_KIT_10_FM_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_KIT_11_FM_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_KIT_12_FM_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_races_won"), 100, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_number_turbo_starts_in_race"), 100, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_usjs_found"), 50, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_usjs_completed"), 50, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_awd_fmwinairrace"), 50, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_awd_fmwinsearace"), 50, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_awd_fmrallywonnav"), 50, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_awd_fmrallywondrive "), 500, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_awd_fm_races_fastest_lap"), 500, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_char_fm_carmod_0_unlck"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_char_fm_carmod_1_unlck"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_char_fm_carmod_2_unlck"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_char_fm_carmod_3_unlck"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_char_fm_carmod_4_unlck"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_char_fm_carmod_5_unlck"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_char_fm_carmod_6_unlck"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_char_fm_carmod_7_unlck"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_VEHICLE_1_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_VEHICLE_2_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_ABILITY_1_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_ABILITY_2_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_ABILITY_3_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_PACKAGE_1_COLLECT"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_PACKAGE_2_COLLECT"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_PACKAGE_3_COLLECT"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_PACKAGE_4_COLLECT"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_PACKAGE_5_COLLECT"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_PACKAGE_6_COLLECT"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_PACKAGE_7_COLLECT"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_PACKAGE_8_COLLECT"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_PACKAGE_9_COLLECT"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_HEALTH_1_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_HEALTH_2_UNLCK"), -1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_HOLDUPS_BITSET"), -1, 0);
		}
		if (GetRenderer()->draw_regular("Unlocks LSC"))
		{
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_RACES_WON"), 50, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_1_UNLCK"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_2_UNLCK"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_3_UNLCK"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_4_UNLCK"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_5_UNLCK"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_6_UNLCK"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_7_UNLCK"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FMRALLYWONDRIVE"), 1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FMRALLYWONNAV"), 1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FMWINSEARACE"), 1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FMWINAIRRACE"), 1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_NUMBER_TURBO_STARTS_IN_RACE"), 50, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_USJS_COMPLETED"), 50, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_RACES_FASTEST_LAP"), 50, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_NUMBER_SLIPSTREAMS_IN_RACE"), 100, 1);
			STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP0_AWD_FMRACEWORLDRECHOLDER"), 1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_ENEMYDRIVEBYKILLS"), 600, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_USJS_COMPLETED"), 50, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_USJS_FOUND"), 50, 0);
			STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP0_AWD_FMWINALLRACEMODES"), 1, 0);
			STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP0_AWD_FMWINEVERYGAMEMODE"), 1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DB_PLAYER_KILLS"), 1000, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_KILLS_PLAYERS"), 1000, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FMHORDWAVESSURVIVE"), 21, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_CAR_BOMBS_ENEMY_KILLS"), 25, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_TDM_MVP"), 60, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_HOLD_UP_SHOPS"), 20, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_RACES_WON"), 101, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_NO_ARMWRESTLING_WINS"), 21, 0);
			STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP0_AWD_FMATTGANGHQ"), 1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FMBBETWIN"), 50000, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_DM_WINS"), 51, 0);
			STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP0_AWD_FMFULLYMODDEDCAR"), 1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_DM_TOTALKILLS"), 500, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MPPLY_DM_TOTAL_DEATHS"), 412, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MPPLY_TIMES_FINISH_DM_TOP_3"), 36, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_PLAYER_HEADSHOTS"), 623, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_DM_WINS"), 63, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_TDM_WINS"), 13, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_GTA_RACES_WON"), 12, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_GOLF_WON"), 2, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_TG_WON"), 2, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_RT_WON"), 2, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_CT_WON"), 2, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_GRAN_WON"), 2, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_TENNIS_WON"), 2, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MPPLY_TENNIS_MATCHES_WON"), 2, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MPPLY_TOTAL_TDEATHMATCH_WON"), 63, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MPPLY_TOTAL_RACES_WON"), 101, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MPPLY_TOTAL_DEATHMATCH_LOST"), 23, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MPPLY_TOTAL_RACES_LOST"), 36, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_25_KILLS_STICKYBOMBS"), 50, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_50_KILLS_GRENADES"), 50, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_GRENADE_ENEMY_KILLS "), 50, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_20_KILLS_MELEE"), 50, 0);
		}
		if (GetRenderer()->draw_regular("Full Recovery"))
		{
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_XP_FM"), 2165850, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STAM"), 100, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STRN"), 100, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_LUNG"), 100, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_DRIV"), 100, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_FLY"), 100, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_SHO"), 100, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STL"), 100, 0);

			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_tattoo_fm_unlocks_1"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_tattoo_fm_unlocks_2"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_tattoo_fm_unlocks_3"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_tattoo_fm_unlocks_4"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_tattoo_fm_unlocks_5"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_tattoo_fm_unlocks_6"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_tattoo_fm_unlocks_7"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_tattoo_fm_unlocks_8"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_tattoo_fm_unlocks_9"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_tattoo_fm_unlocks_10"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_tattoo_fm_unlocks_11"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_tattoo_fm_unlocks_12"), -1, 1);

			STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP0_AWD_FMRACEWORLDRECHOLDER"), 1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_ENEMYDRIVEBYKILLS"), 600, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_USJS_COMPLETED"), 50, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_USJS_FOUND"), 50, 0);
			STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP0_AWD_FMWINALLRACEMODES"), 1, 0);
			STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP0_AWD_FMWINEVERYGAMEMODE"), 1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DB_PLAYER_KILLS"), 1000, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_KILLS_PLAYERS"), 1000, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FMHORDWAVESSURVIVE"), 21, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_CAR_BOMBS_ENEMY_KILLS"), 25, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_TDM_MVP"), 60, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_HOLD_UP_SHOPS"), 20, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_RACES_WON"), 101, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_NO_ARMWRESTLING_WINS"), 21, 0);
			STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP0_AWD_FMATTGANGHQ"), 1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FMBBETWIN"), 50000, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_DM_WINS"), 51, 0);
			STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP0_AWD_FMFULLYMODDEDCAR"), 1, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_DM_TOTALKILLS"), 500, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MPPLY_DM_TOTAL_DEATHS"), 412, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MPPLY_TIMES_FINISH_DM_TOP_3"), 36, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_PLAYER_HEADSHOTS"), 623, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_DM_WINS"), 63, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_TDM_WINS"), 13, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_GTA_RACES_WON"), 12, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_GOLF_WON"), 2, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_TG_WON"), 2, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_RT_WON"), 2, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_CT_WON"), 2, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_GRAN_WON"), 2, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_TENNIS_WON"), 2, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MPPLY_TENNIS_MATCHES_WON"), 2, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MPPLY_TOTAL_TDEATHMATCH_WON"), 63, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MPPLY_TOTAL_RACES_WON"), 101, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MPPLY_TOTAL_DEATHMATCH_LOST"), 23, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MPPLY_TOTAL_RACES_LOST"), 36, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_25_KILLS_STICKYBOMBS"), 50, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_50_KILLS_GRENADES"), 50, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_GRENADE_ENEMY_KILLS"), 50, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_20_KILLS_MELEE"), 50, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MOLOTOV_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CMBTPISTOL_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_PISTOL50_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_APPISTOL_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MICROSMG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SMG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ASLTSMG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ASLTRIFLE_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CRBNRIFLE_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ADVRIFLE_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CMBTMG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ASLTMG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_PUMP_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SAWNOFF_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_BULLPUP_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ASLTSHTGN_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SNIPERRFL_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_HVYSNIPER_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_GRNLAUNCH_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_RPG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MINIGUNS_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_GRENADE_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SMKGRENADE_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_STKYBMB_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MOLOTOV_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_1"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_1"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_2"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_3"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_4"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_5"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_6"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_7"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_1"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_2"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_3"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_4"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_5"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_6"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_7"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_1"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_2"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_3"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_4"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_5"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_6"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_7"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_1"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_2"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_3"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_4"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_5"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_6"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_7"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_1"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_2"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_3"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_4"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_5"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_6"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_7"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_1"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_2"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_3"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_4"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_5"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_6"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_7"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_8"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_9"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_10"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_OUTFIT"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_1"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_2"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_3"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_4"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_5"), -1, 1);;
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_6"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_7"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_1"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_2"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_3"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_4"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_5"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_6"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_7"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_1"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_2"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_3"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_4"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_5"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_6"), -1, 1);;
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_7"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_1"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_2"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_3"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_4"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_5"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_6"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_7"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_1"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_2"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_3"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_4"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_5"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_6"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_7"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_1"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_2"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_3"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_4"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_5"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_6"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_7"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_8"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_9"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_10"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_OUTFIT"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TORSO"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_1"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_2"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_3"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_4"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_5"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_6"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_7"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL2"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL2_1"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_DECL"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TEETH"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TEETH_1"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TEETH_2"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_TORSO"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_1"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_2"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_3"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_4"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_5"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_6"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_7"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL2"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL2_1"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_DECL"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_TEETH"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_TEETH_1"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_TEETH_2"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_0"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_1"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_2"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_3"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_4"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_5"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_6"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_7"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_8"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_9"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_10"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_11"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_12"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_13"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_14"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_15"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_16"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_17"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_18"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_19"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_21"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_22"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_23"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_24"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_24"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_25"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_26"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_27"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_28"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_29"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_30"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_31"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_32"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_33"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_34"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_35"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_36"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_37"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_38"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_39"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_40"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_1"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_2"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_3"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_4"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_5"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_6"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_7"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_8"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_9"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_10"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_11"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_12"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_13"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_1"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_10"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_11"), -1, 1);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_12"), -1, 1);
		}
	}
	void settings_submenu() {
		addOption()->Submenu("Settings", Settings_general);
		addOption()->Submenu("Profils", Settings_theme);
		addOption()->Submenu("Credits", Settings_credit);
		//addOption()->BoolOption("Numpad Controls", g_settings.options["key_numpad"].get<bool*>());
		//addOption()->BoolOption("Draw Instructional", g_settings.options["Draw_Instructional"].get<bool*>());
		/*if (GetRenderer()->draw_link("Save Config"))
		{
			g_settings.save();
		}*/
		if (GetRenderer()->draw_regular("Attach Log"))
		{
			g_log.attach();
		}
		if (GetRenderer()->draw_regular("Dettach Log"))
		{
			g_log.detach();
		}
		if (GetRenderer()->draw_link("Discord"))
		{
			ShellExecuteA(0, 0, "https://discord.gg/2D3PEnJhe8", 0, 0, SW_SHOW);
		}
	}
	void Settings_credit()
	{
		if (GetRenderer()->draw_link("Dev | Zenith"))
		{
			ShellExecuteA(0, 0, "https://discord.gg/2D3PEnJhe8", 0, 0, SW_SHOW);
		}
	}
	void Settings_theme()
	{
		if (GetRenderer()->draw_regular("Save"))
		{
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
			MISC::DISPLAY_ONSCREEN_KEYBOARD(true, (char*)"Name Profil:", (char*)"", (char*)"", (char*)"", (char*)"", (char*)"", 32);
			while (MISC::UPDATE_ONSCREEN_KEYBOARD() == 0) {
				fiber::current()->sleep();
			}
			if (!MISC::GET_ONSCREEN_KEYBOARD_RESULT()) {
				return;
			}
			SaveProfil(MISC::GET_ONSCREEN_KEYBOARD_RESULT());
		}
		addOption()->BreakOption("Profils");
		std::vector<std::string> profiles = util::dirs::get_files_in_directory(util::dirs::get_directories()->get_theme(), ".json");
		if (profiles.size()) {
			for (std::string& profil : profiles) {
				if (GetRenderer()->draw_regular(profil.c_str()))
				{
					LoadProfil(profil.c_str());
				}
			}
		}
		else
		{
			GetRenderer()->draw_regular("~c~Empty");
		}
	}
	void Settings_general()
	{
		addOption()->Submenu("Header", settings_header_submenu);
		addOption()->Submenu("Tab", tab_custom);
		addOption()->Submenu("Sub", sub_color);
		addOption()->Submenu("Options", settings_options_submenu);
		addOption()->Submenu("Footer", settings_footer_submenu);
		addOption()->Submenu("Toggle", toggle_color);
		addOption()->Submenu("Break", break_color);
		addOption()->Submenu("PlayerInfo", settings_playerinfo_submenu);
		addOption()->ColorOption("Color Box", GetRenderer()->m_cPrimary);
		addOption()->BreakOption("Positions");
		GetRenderer()->draw_number("Menu Pos X", &GetRenderer()->m_menu_pos.x, 0.01f, 1.f, 0.01f);
		GetRenderer()->draw_number("Menu Pos Y", &GetRenderer()->m_menu_pos.y, 0.01f, 1.f, 0.01f);
		GetRenderer()->draw_number("Width", &GetRenderer()->m_width, 0.01f, 1.f, 0.01f);
		GetRenderer()->draw_number("Scale", &GetRenderer()->m_global_scale, 0.1f, 10.f, 0.1f);
	}
	void tab_custom()
	{
		addOption()->BoolOption("Tab", &GetRenderer()->tab_activate);
		if (GetRenderer()->tab_activate)
		{
			GetRenderer()->draw_number("Height", &GetRenderer()->m_tab_font_size, 0.0f, 2.f, 0.01f);
			GetRenderer()->draw_number("Font", &GetRenderer()->m_tab_font, 0, 7, 1);
			GetRenderer()->draw_number("Font Size", &GetRenderer()->m_tab_font_size, 0.0f, 2.f, 0.01f);
			addOption()->BreakOption("Selected");
			//addOption()->ColorOption("Color", GetRenderer()->tab_color_selected);
			GetRenderer()->draw_number("Red", &GetRenderer()->tab_color_selected.r, 0, 255, 1);
			GetRenderer()->draw_number("Green", &GetRenderer()->tab_color_selected.g, 0, 255, 1);
			GetRenderer()->draw_number("Blue", &GetRenderer()->tab_color_selected.b, 0, 255, 1);
			GetRenderer()->draw_number("Alpha", &GetRenderer()->tab_color_selected.a, 0, 255, 1);
			addOption()->BreakOption("Unselected");
			//addOption()->ColorOption("Color", GetRenderer()->tab_color_unselected);
			GetRenderer()->draw_number("Red", &GetRenderer()->tab_color_unselected.r, 0, 255, 1);
			GetRenderer()->draw_number("Green", &GetRenderer()->tab_color_unselected.g, 0, 255, 1);
			GetRenderer()->draw_number("Blue", &GetRenderer()->tab_color_unselected.b, 0, 255, 1);
			GetRenderer()->draw_number("Alpha", &GetRenderer()->tab_color_unselected.a, 0, 255, 1);
		}
	}
	void sub_color()
	{
		GetRenderer()->draw_number("Sub Height", &GetRenderer()->m_submenu_height, 0.f, 0.070f, 0.001f, false);
		GetRenderer()->draw_number("Font Size", &GetRenderer()->m_submenu_font_size, 0.0f, 2.f, 0.01f);
		GetRenderer()->draw_number("Font", &GetRenderer()->m_submenu_font, 0.0f, 2.f, 0.01f);
		addOption()->BreakOption("Color");
		//addOption()->ColorOption("Color", GetRenderer()->m_submenu_backgound);
		GetRenderer()->draw_number("Red", &GetRenderer()->m_submenu_backgound.r, 0, 255, 1);
		GetRenderer()->draw_number("Green", &GetRenderer()->m_submenu_backgound.g, 0, 255, 1);
		GetRenderer()->draw_number("Blue", &GetRenderer()->m_submenu_backgound.b, 0, 255, 1);
		GetRenderer()->draw_number("Alpha", &GetRenderer()->m_submenu_backgound.a, 0, 255, 1);
		addOption()->BreakOption("Color Text");
		//addOption()->ColorOption("Color", GetRenderer()->m_submenu_text);
		GetRenderer()->draw_number("Red", &GetRenderer()->m_submenu_text.r, 0, 255, 1);
		GetRenderer()->draw_number("Green", &GetRenderer()->m_submenu_text.g, 0, 255, 1);
		GetRenderer()->draw_number("Blue", &GetRenderer()->m_submenu_text.b, 0, 255, 1);
		GetRenderer()->draw_number("Alpha", &GetRenderer()->m_submenu_text.a, 0, 255, 1);
	}
	void settings_options_submenu() {
		addOption()->Submenu("Option Text Color", settings_options_text_color);
		addOption()->Submenu("Scroller", option_color);
		GetRenderer()->draw_number("Option Height", &GetRenderer()->m_option_height, 0.f, 0.070f, 0.001f, false);
		GetRenderer()->draw_number("Font Size", &GetRenderer()->m_option_font_size, 0.0f, 2.f, 0.01f);
		GetRenderer()->draw_number("Font", &GetRenderer()->m_option_font, 0, 7);
		GetRenderer()->draw_number("Rotated Arrow Size", &GetRenderer()->m_arrow_rotated_size, 0.f, 0.1f, 0.001f, false);
	}
	void option_color()
	{
		//addOption()->ColorOption("Color", GetRenderer()->m_scroller_color);
		GetRenderer()->draw_number("Red", &GetRenderer()->m_scroller_color.r, 0, 255, 1);
		GetRenderer()->draw_number("Green", &GetRenderer()->m_scroller_color.g, 0, 255, 1);
		GetRenderer()->draw_number("Blue", &GetRenderer()->m_scroller_color.b, 0, 255, 1);
		GetRenderer()->draw_number("Alpha", &GetRenderer()->m_scroller_color.a, 0, 255, 1);
	}
	void toggle_color()
	{
		addOption()->BoolOption("Preview : ", &preview_toggle);
		GetRenderer()->draw_number("Toggle Size", &GetRenderer()->m_toggle_size, 0.f, 0.1f, 0.001f, false);
		addOption()->BreakOption("Color On");
		//addOption()->ColorOption("Color", GetRenderer()->m_toggle_color_on);
		GetRenderer()->draw_number("Red", &GetRenderer()->m_toggle_color_on.r, 0, 255, 1);
		GetRenderer()->draw_number("Green", &GetRenderer()->m_toggle_color_on.g, 0, 255, 1);
		GetRenderer()->draw_number("Blue", &GetRenderer()->m_toggle_color_on.b, 0, 255, 1);
		GetRenderer()->draw_number("Alpha", &GetRenderer()->m_toggle_color_on.a, 0, 255, 1);
		addOption()->BreakOption("Color Off");
		//addOption()->ColorOption("Color", GetRenderer()->m_toggle_color_off);
		GetRenderer()->draw_number("Red", &GetRenderer()->m_toggle_color_off.r, 0, 255, 1);
		GetRenderer()->draw_number("Green", &GetRenderer()->m_toggle_color_off.g, 0, 255, 1);
		GetRenderer()->draw_number("Blue", &GetRenderer()->m_toggle_color_off.b, 0, 255, 1);
		GetRenderer()->draw_number("Alpha", &GetRenderer()->m_toggle_color_off.a, 0, 255, 1);
	}
	void break_color()
	{
		addOption()->BreakOption("Exemple");
		GetRenderer()->draw_number("Font Size", &GetRenderer()->m_break_font_size, 0.0f, 2.f, 0.01f);
		GetRenderer()->draw_number("Font", &GetRenderer()->m_option_font, 0, 7);
		//addOption()->ColorOption("Color", GetRenderer()->m_break_text);
		GetRenderer()->draw_number("Red", &GetRenderer()->m_break_text.r, 0, 255, 1);
		GetRenderer()->draw_number("Green", &GetRenderer()->m_break_text.g, 0, 255, 1);
		GetRenderer()->draw_number("Blue", &GetRenderer()->m_break_text.b, 0, 255, 1);
		GetRenderer()->draw_number("Alpha", &GetRenderer()->m_break_text.a, 0, 255, 1);
	}
	void settings_header_submenu() {
		addOption()->Submenu("Header Background Color", settings_header_bg_color);
		addOption()->Submenu("Header Text", settings_header_text_color);
		addOption()->BoolOption("Render Globe", &GetHeader()->m_render_glare);
		GetRenderer()->draw_number("Header Height", &GetRenderer()->m_header_height, 0.f, 0.200f, 0.001f, false);

	}
	void settings_header_text_color()
	{
		addOption()->BoolOption("Text", &GetRenderer()->HeaderText);
		GetRenderer()->draw_number("Font", &GetRenderer()->m_header_font, 0, 7);
		GetRenderer()->draw_number("Font Height", &GetRenderer()->m_header_font_size, 0, 7);
		//addOption()->ColorOption("Color", GetRenderer()->m_header_text);
		GetRenderer()->draw_number("Red", &GetRenderer()->m_header_text.r, 0, 255, 1);
		GetRenderer()->draw_number("Green", &GetRenderer()->m_header_text.g, 0, 255, 1);
		GetRenderer()->draw_number("Blue", &GetRenderer()->m_header_text.b, 0, 255, 1);
		GetRenderer()->draw_number("Alpha", &GetRenderer()->m_header_text.a, 0, 255, 1);
		GetRenderer()->draw_rect(GetRenderer()->m_header_text, Vector2(GetRenderer()->m_menu_pos.x, GetRenderer()->m_draw_base_y + (GetRenderer()->m_option_height / 2.f)), Vector2(GetRenderer()->m_width, GetRenderer()->m_option_height));
	}
	void settings_submenu_submenu() {
		GetRenderer()->draw_number("Red", &GetRenderer()->m_scroller_color.r, 0, 255, 1);
		GetRenderer()->draw_number("Green", &GetRenderer()->m_scroller_color.g, 0, 255, 1);
		GetRenderer()->draw_number("Blue", &GetRenderer()->m_scroller_color.b, 0, 255, 1);
		GetRenderer()->draw_number("Alpha", &GetRenderer()->m_scroller_color.a, 0, 255, 1);

	}
	void settings_options_text_color() {
		//addOption()->ColorOption("Color", GetRenderer()->m_option_text);
		GetRenderer()->draw_number("Red", &GetRenderer()->m_option_text.r, 0, 255, 1);
		GetRenderer()->draw_number("Green", &GetRenderer()->m_option_text.g, 0, 255, 1);
		GetRenderer()->draw_number("Blue", &GetRenderer()->m_option_text.b, 0, 255, 1);
		GetRenderer()->draw_number("Alpha", &GetRenderer()->m_option_text.a, 0, 255, 1);
		addOption()->BreakOption("Selected");
		//addOption()->ColorOption("Color", GetRenderer()->m_option_text_selected);
		GetRenderer()->draw_number("Red", &GetRenderer()->m_option_text_selected.r, 0, 255, 1);
		GetRenderer()->draw_number("Green", &GetRenderer()->m_option_text_selected.g, 0, 255, 1);
		GetRenderer()->draw_number("Blue", &GetRenderer()->m_option_text_selected.b, 0, 255, 1);
		GetRenderer()->draw_number("Alpha", &GetRenderer()->m_option_text_selected.a, 0, 255, 1);
	}
	void settings_header_bg_color() {
		GetRenderer()->draw_number("Red", &GetRenderer()->m_header_back_ground.r, 0, 255, 1);
		GetRenderer()->draw_number("Green", &GetRenderer()->m_header_back_ground.g, 0, 255, 1);
		GetRenderer()->draw_number("Blue", &GetRenderer()->m_header_back_ground.b, 0, 255, 1);
		GetRenderer()->draw_number("Alpha", &GetRenderer()->m_header_back_ground.a, 0, 255, 1);
		GetRenderer()->draw_rect(GetRenderer()->m_header_back_ground, Vector2(GetRenderer()->m_menu_pos.x, GetRenderer()->m_draw_base_y + (GetRenderer()->m_option_height / 2.f)), Vector2(GetRenderer()->m_width, GetRenderer()->m_option_height));
	}
	void settings_footer_submenu() {
		addOption()->Submenu("Footer Background Color", settings_footer_submenu_bg_color);
		addOption()->Submenu("Footer Sprite Color", settings_footer_submenu_sprite_color);
		GetRenderer()->draw_number("Footer Height", &GetRenderer()->m_footer_height, 0.f, 0.170f, 0.001f, false);
		GetRenderer()->draw_number("Footer Sprite Size", &GetRenderer()->m_footer_arrow_size, 0.f, 0.170f, 0.001f, false);
	}
	void settings_footer_submenu_sprite_color()
	{
		GetRenderer()->draw_number("Red", &GetRenderer()->m_sprite_color.r, 0, 255, 1);
		GetRenderer()->draw_number("Green", &GetRenderer()->m_sprite_color.g, 0, 255, 1);
		GetRenderer()->draw_number("Blue", &GetRenderer()->m_sprite_color.b, 0, 255, 1);
		GetRenderer()->draw_number("Alpha", &GetRenderer()->m_sprite_color.a, 0, 255, 1);
		GetRenderer()->draw_rect(GetRenderer()->m_sprite_color, Vector2(GetRenderer()->m_menu_pos.x, GetRenderer()->m_draw_base_y + (GetRenderer()->m_option_height / 2.f)), Vector2(GetRenderer()->m_width, GetRenderer()->m_option_height));
	}
	void settings_footer_submenu_bg_color() {
		GetRenderer()->draw_number("Red", &GetRenderer()->m_footer_background.r, 0, 255, 1);
		GetRenderer()->draw_number("Green", &GetRenderer()->m_footer_background.g, 0, 255, 1);
		GetRenderer()->draw_number("Blue", &GetRenderer()->m_footer_background.b, 0, 255, 1);
		GetRenderer()->draw_number("Alpha", &GetRenderer()->m_footer_background.a, 0, 255, 1);
		GetRenderer()->draw_rect(GetRenderer()->m_footer_background, Vector2(GetRenderer()->m_menu_pos.x, GetRenderer()->m_draw_base_y + (GetRenderer()->m_option_height / 2.f)), Vector2(GetRenderer()->m_width, GetRenderer()->m_option_height));
	}
	void settings_playerinfo_submenu()
	{
		GetPlayerInfo()->Update(PLAYER::PLAYER_ID(), 1);
		GetRenderer()->draw_number("Font", &GetRenderer()->m_playerinfo_font, 0, 7);
		addOption()->BreakOption("Color");
		GetRenderer()->draw_number("Red", &GetRenderer()->m_background_playerinfo.r, 0, 255, 1);
		GetRenderer()->draw_number("Green", &GetRenderer()->m_background_playerinfo.g, 0, 255, 1);
		GetRenderer()->draw_number("Blue", &GetRenderer()->m_background_playerinfo.b, 0, 255, 1);
		GetRenderer()->draw_number("Opacity", &GetRenderer()->m_background_playerinfo.a, 0, 255, 1);

	}
	void draw_animated_header()
	{
		std::vector<SpriteAnimation> m_animatedHeaders;
		SpriteAnimation lightning(40, true);
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader00" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader01" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader02" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader03" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader04" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader05" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader06" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader07" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader08" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader09" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader11" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader12" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader13" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader14" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader15" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader16" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader17" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader18" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader19" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader20" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader21" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader22" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader23" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader24" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader25" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader26" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader27" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader28" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader29" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader30" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader31" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader32" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader33" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader34" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader35" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader36" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader37" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader38" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader39" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader40" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader41" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader42" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader43" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader44" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader45" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader46" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader47" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader48" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader49" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader50" });

		//m_animatedHeaders.push_back(def);
		//m_animatedHeaders.push_back(rainbow);
		m_animatedHeaders.push_back(lightning);
	}
	void spawner_submenu() {
		//draw_animated_header();
		addOption()->Submenu("Settings", Spawner_settings);
		if (GetRenderer()->draw_regular("Spawn Input Name"))
		{
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
			MISC::DISPLAY_ONSCREEN_KEYBOARD(true, "Input Vehicle", "", "", "", "", "", 20);
			while (MISC::UPDATE_ONSCREEN_KEYBOARD() == 0) {
				fiber::current()->sleep();
			}
			if (!MISC::GET_ONSCREEN_KEYBOARD_RESULT()) {
				return;
			}
			g_gta_utility.spawn_vehicle(g_utility.Joaat(MISC::GET_ONSCREEN_KEYBOARD_RESULT()));
		}
		for (std::int32_t i = 0; i < 23; i++) {
			if (addOption()->Submenu(g_gta_utility.get_vehicle_class_name(i), spawner_vehicle_submenu)) {
				m_selected_vehicle_class = i;
			}
		}
	}
	void Spawner_settings()
	{
		addOption()->BoolOption("Invincible", &g_gta_utility.g_SpawnInvinc);
		addOption()->BoolOption("In vehicle", &g_gta_utility.Sitinvehicle);
		addOption()->BoolOption("Max", &g_gta_utility.MaxVehiclespawn);
	}
	void spawner_vehicle_submenu() {
		if (GetPointers()->m_vehicle_hash_pool != nullptr) {
			for (std::int32_t i = 0; i < GetPointers()->m_vehicle_hash_pool->capacity; i++) {
				std::uint64_t info = GetPointers()->m_vehicle_hash_pool->get(i);
				if (info != NULL) {
					if ((*(BYTE*)(info + 157) & 0x1F) == 5) {
						std::string make_ptr = (char*)((uintptr_t)info + 0x2A4);
						std::string model_ptr = (char*)((uintptr_t)info + 0x298);
						if (VEHICLE::GET_VEHICLE_CLASS_FROM_NAME(joaat(model_ptr)) == m_selected_vehicle_class) {
							std::stringstream ss;
							std::string make(make_ptr);
							std::string model(model_ptr);
							if (make[0] || model[0]) {
								make = HUD::GET_LABEL_TEXT_(make.c_str());
								model = HUD::GET_LABEL_TEXT_(model.c_str());
								if (make != "NULL" && model != "NULL") {
									ss << make << " " << model;
								}
								else if (model != "NULL") {
									ss << model;
								}
								else {
									ss << "Unknown";
								}
							}
							if (GetRenderer()->m_current_option == GetRenderer()->m_option_count + 1)
							{
								std::string pic[2] = { "**Invalid**", "**Invalid**" };
								for (int i = 0; i < 267; i++)
								{
									if (*(std::uint32_t*)(info + 0x18) == VehiclePreviews[i].hashvehicle) {
										pic[0] = VehiclePreviews[i].vehiclePreviewDict;
										pic[1] = VehiclePreviews[i].vehicleName;
										break;
									}
								}
								GetVehicleInfo()->DisplayVehicle(pic[0], pic[1]);
								GetVehicleInfo()->Stats(*(std::uint32_t*)(info + 0x18));
								preview_vehicle(*(std::uint32_t*)(info + 0x18));
							}
							if (GetRenderer()->draw_regular(ss.str().c_str())) {
								g_gta_utility.spawn_vehicle(*(std::uint32_t*)(info + 0x18));
							}
						}
					}
				}
			}
		}
	}
	void main_script() {
		GetScaleform()->DrawLargeMessage("~p~Virtual X", "Welcome to Virtual X Service", 600);
		//g_utility.notifyMap("");
		while (true) {
			GetMenuInput()->Init();
			GetRenderer()->draw_tick();
			if (GetRenderer()->m_opened) {
				GetRenderer()->disbale_controls();
			}
			Selfloop();
			fiber::current()->sleep();
		}
	}
	void script::detach() {
		g_log.send("Fibers", "Removed Main Fiber");
	}
	script* GetScript() { return &g_script; };
}