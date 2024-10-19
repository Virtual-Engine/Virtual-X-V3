#include "invoker/invoker.hpp"
#include "invoker/Natives.hpp"
#include "Self.h"
#include "ScriptGloabals.h"
#include "Bones.h"
#include "UtilVector.h"
#include "ControlUtil.h"
#include "MemoryEdit.h"
#include "Blip.h"
#include "Rank.h"
#include "Timer.h"
#include <timeapi.h>
#include "shellapi.h"
#include "animatedYTD.h"
namespace VX
{

	void Godmod(bool toggle)
	{
		if (toggle)
		{
			ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), 1);
			ENTITY::SET_ENTITY_PROOFS(PLAYER::PLAYER_PED_ID(), true, true, true, true, true, true, true, true);
		}
		else
		{
			ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), 1);
		}
	}
	void invisible(bool toggle)
	{
		if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
		{
			if (toggle)
			{
				ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), false, 0);
			}
			else ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), true, 0);
		}

	}
	void OffRadar(bool toggle)
	{
		if (toggle)
		{
			*ScriptGlobal(2657704).Add(PLAYER::PLAYER_ID(), 463).Add(210).As<bool*>() = 1;
			*ScriptGlobal(2672524).Add(57).As<int32_t*>() = NETWORK::GET_NETWORK_TIME();
		}
	}
	void Alpha()
	{
		ENTITY::SET_ENTITY_ALPHA(PLAYER::PLAYER_PED_ID(), alpha, 0);
	}
	void SpinBot(bool toggle)
	{
		if (toggle)
		{
			static int Heading;
			Heading++;
			Heading++;
			Heading++;
			Heading++;
			Heading++;
			Heading++;
			Heading++;
			Heading++;
			Heading++;
			Heading++;
			Heading++;
			Heading++;
			ENTITY::SET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID(), Heading);
		}
		else
		{
			!NULL;
		}
	}
	void NeverWanted(bool toggle)
	{
		if (toggle)
		{
			PLAYER::SET_MAX_WANTED_LEVEL(6);
			PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 0, 0);
			PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), 0);
			LevelWanted = 0;
		}
	}
	void SetWantedLevel()
	{
		PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), LevelWanted, 0);
		PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), 0);
	}
	void fakewanted()
	{
		MISC::SET_FAKE_WANTED_LEVEL(LevelFakeWanted);
	}
	void NoRagodoll(bool toggle)
	{
		if (toggle)
		{
			PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(PLAYER::PLAYER_PED_ID(), false);
			PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), false);
		}
		else
		{
			PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(PLAYER::PLAYER_PED_ID(), true);
			PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), true);
		}
	}
	void AlwaysRagdoll(bool toggle)
	{
		if (toggle)
		{
			PED::SET_PED_RAGDOLL_ON_COLLISION(PLAYER::PLAYER_PED_ID(), true);
		}
		else
		{
			PED::SET_PED_RAGDOLL_ON_COLLISION(PLAYER::PLAYER_PED_ID(), false);
		}
	}
	void DieOnRagdoll(bool toggle)
	{
		if (toggle)
		{
			PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 33, true);
		}
		else
		{
			PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 33, false);
		}
	}
	void Thermal(bool toggle)
	{
		if (toggle)
		{
			GRAPHICS::SET_SEETHROUGH(true);
		}
		else
		{
			GRAPHICS::SET_SEETHROUGH(false);
		}
	}
	void Night(bool toggle)
	{
		if (toggle)
		{
			GRAPHICS::SET_NIGHTVISION(true);
		}
		else
		{
			GRAPHICS::SET_NIGHTVISION(false);
		}
	}
	void firebreath(bool toggle)
	{
		if (toggle)
		{
			float XPos = 0.02, YPos = 0.2, ZPos = 0.0, XOff = 90.0, YOff = -100.0, ZOff = 90.0;
			STREAMING::REQUEST_NAMED_PTFX_ASSET("core");
			GRAPHICS::USE_PARTICLE_FX_ASSET("core"); {
				int ptfx = GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE("ent_sht_flame", PLAYER::PLAYER_PED_ID(), XPos, YPos, ZPos,
					XOff, YOff, ZOff, 0x796e, 1, 1, 1, 1);	}
			STREAMING::REMOVE_PTFX_ASSET();
		}
	}
	void DeadEye(bool toggle)
	{
		if (toggle)
		{
			MISC::SET_TIME_SCALE(0.6);
		}
		else
		{
			if (g_SlowMotion)
				MISC::SET_TIME_SCALE(0.2);
			else
				MISC::SET_TIME_SCALE(1);
		}
	}
	void Handtrails(bool toggle)
	{
		if (toggle)
		{
			STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcpaparazzo1");
			GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcpaparazzo1");
			GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE("scr_mich4_firework_sparkle_spawn", PLAYER::PLAYER_PED_ID(), 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, SKEL_L_Hand, handscale, false, false, false);
			GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_COLOUR(handred / 255, handgreen / 255, handblue / 255);
			GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_ALPHA(handalpha / 255);

			STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcpaparazzo1");
			GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcpaparazzo1");
			GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE("scr_mich4_firework_sparkle_spawn", PLAYER::PLAYER_PED_ID(), 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, SKEL_R_Hand, handscale, false, false, false);
			GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_COLOUR(handred / 255, handgreen / 255, handblue / 255);
			GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_ALPHA(handalpha / 255);
		}
	}
	void PTFXCALLBoneless(const char* call1, const char* call2, const char* name, int bone)
	{
		STREAMING::REQUEST_NAMED_PTFX_ASSET(call1);
		GRAPHICS::USE_PARTICLE_FX_ASSET(call2);
		int ptfx = GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(name, PLAYER::PLAYER_PED_ID(), 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.0f, bone, m_GlowScale, 1, 1, 1);
		STREAMING::REMOVE_PTFX_ASSET();
	}
	void GlowManager(bool toggle)
	{
		if (toggle)
		{
			if (m_Head) { PTFXCALLBoneless(m_ParticleCalls0[m_ParticleIterator], m_ParticleCalls0[m_ParticleIterator], m_ParticleCalls1[m_ParticleIterator], 0x796e); }
			if (m_RightHand) { PTFXCALLBoneless(m_ParticleCalls0[m_ParticleIterator], m_ParticleCalls0[m_ParticleIterator], m_ParticleCalls1[m_ParticleIterator], 0xdead); }
			if (m_LeftHand) { PTFXCALLBoneless(m_ParticleCalls0[m_ParticleIterator], m_ParticleCalls0[m_ParticleIterator], m_ParticleCalls1[m_ParticleIterator], 0x8cbd); }
			if (m_RightFood) { PTFXCALLBoneless(m_ParticleCalls0[m_ParticleIterator], m_ParticleCalls0[m_ParticleIterator], m_ParticleCalls1[m_ParticleIterator], 0xcc4d); }
			if (m_LeftFood) { PTFXCALLBoneless(m_ParticleCalls0[m_ParticleIterator], m_ParticleCalls0[m_ParticleIterator], m_ParticleCalls1[m_ParticleIterator], 0x3779); }
		}
	}
	void WalkUnderWater(bool toggle)
	{
		if (toggle)
		{
			auto playerPed = PLAYER::PLAYER_PED_ID();
			if (ENTITY::IS_ENTITY_IN_WATER(playerPed))
			{
				PED::SET_PED_CONFIG_FLAG(playerPed, 65, false);
				PED::SET_PED_CONFIG_FLAG(playerPed, 66, false);
				PED::SET_PED_CONFIG_FLAG(playerPed, 168, false);

				if (PED::IS_PED_JUMPING(playerPed))
				{
					ENTITY::APPLY_FORCE_TO_ENTITY(playerPed, true, 0, 0, 0.7f, 0, 0, 0, true, true, true, true, false, true);
				}

				if (ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(playerPed) > 1.2f)
				{
					PED::SET_PED_CONFIG_FLAG(playerPed, 60, false);
					PED::SET_PED_CONFIG_FLAG(playerPed, 61, false);
					PED::SET_PED_CONFIG_FLAG(playerPed, 104, false);
					PED::SET_PED_CONFIG_FLAG(playerPed, 276, false);
					PED::SET_PED_CONFIG_FLAG(playerPed, 76, true);
					ENTITY::APPLY_FORCE_TO_ENTITY(playerPed, true, 0, 0, -0.7f, 0, 0, 0, true, true, true, true, false, true);
				}

				if (BRAIN::GET_IS_TASK_ACTIVE(playerPed, 281) && PED::IS_PED_SWIMMING(playerPed) && PED::IS_PED_SWIMMING_UNDER_WATER(playerPed))
				{
					BRAIN::CLEAR_PED_TASKS_IMMEDIATELY(playerPed);
				}
			}
		}
	}
	void WalkOnWater(bool toggle)
	{
		if (toggle)
		{
			Hash ferris = MISC::GET_HASH_KEY("prop_container_ld2");
			Vector3 me = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0);
			float water;
			static int timer = 0;
			static Object model;

			WATER::SET_DEEP_OCEAN_SCALER(-1.f);
			if (WATER::GET_WATER_HEIGHT(me.x, me.y, me.z, &water))
			{
				if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1))
				{

					if (GetTickCount() - timer >= 0)
					{
						model = OBJECT::CREATE_OBJECT(ferris, me.x, me.y, me.z, 1, 1, 1);
						g_utility.RequestControlOfEnt(model);
						ENTITY::SET_ENTITY_VISIBLE(model, 0, 0);
						ENTITY::FREEZE_ENTITY_POSITION(model, 1);
						ENTITY::SET_ENTITY_ROTATION(model, 0, 0, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), 0, 0);
						ENTITY::SET_ENTITY_COORDS(model, me.x, me.y, water - 2.8f, 0, 0, 0, 1);
						timer = GetTickCount();
					}

				}
			}
			if (ENTITY::DOES_ENTITY_EXIST(model))
			{
				g_utility.RequestControlOfEnt(model);
				OBJECT::DELETE_OBJECT(&model);
			}
		}

	}
	void ModifyWater(bool toggle)
	{
		if (toggle)
		{
			Vector3 Coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
			WATER::MODIFY_WATER(Coords.x, Coords.y, -10, 10);
			WATER::MODIFY_WATER(Coords.x + 2, Coords.y, -10, 10);
			WATER::MODIFY_WATER(Coords.x, Coords.y + 2, -10, 10);
			WATER::MODIFY_WATER(Coords.x + 2, Coords.y + 2, -10, 10);
			WATER::MODIFY_WATER(Coords.x + 4, Coords.y, -10, 10);
			WATER::MODIFY_WATER(Coords.x, Coords.y + 4, -10, 10);
			WATER::MODIFY_WATER(Coords.x + 4, Coords.y + 4, -10, 10);
			WATER::MODIFY_WATER(Coords.x + 6, Coords.y, -10, 10);
			WATER::MODIFY_WATER(Coords.x, Coords.y + 6, -10, 10);
			WATER::MODIFY_WATER(Coords.x + 6, Coords.y + 6, -10, 10);
			WATER::MODIFY_WATER(Coords.x + 8, Coords.y, -10, 10);
			WATER::MODIFY_WATER(Coords.x, Coords.y + 8, -10, 10);
			WATER::MODIFY_WATER(Coords.x + 8, Coords.y + 8, -10, 10);
		}
	}
	void neonLight()
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		VEHICLE::SET_VEHICLE_NEON_ENABLED(veh, 0, neonleft);
		VEHICLE::SET_VEHICLE_NEON_ENABLED(veh, 1, neonright);
		VEHICLE::SET_VEHICLE_NEON_ENABLED(veh, 2, neonfront);
		VEHICLE::SET_VEHICLE_NEON_ENABLED(veh, 3, neonback);
	}
	Object create_attached_ramp(Entity attach_to, uint32_t model, int pos = 0, bool opacitated = true) {
		STREAMING::REQUEST_MODEL(model);

		Vector3 min, max;
		MISC::GET_MODEL_DIMENSIONS(model, &min, &max);

		Vector3 dim = { max.x - min.x, max.y - min.y, max.z - min.z };

		Vector3 coords = ENTITY::GET_ENTITY_COORDS(attach_to, true);

		//*(unsigned short*)GetPointers()->set_this_thread_networked = 0x9090;
		Object ramp = OBJECT::CREATE_OBJECT1(model, coords, true, true, false);
		//*(unsigned short*)GetPointers()->set_this_thread_networked = 0x0574;

		switch (pos) {

		case 0:ENTITY::ATTACH_ENTITY_TO_ENTITY2(ramp, attach_to, 0, /**/{ (-1) * dim.x, 0, -0.5 }, /**/{ 0, 0, 270 }, true, true, true, false, 2, true, 0);
			break;

		case 1:ENTITY::ATTACH_ENTITY_TO_ENTITY2(ramp, attach_to, 0, /**/{ dim.x, 0, -0.5 }, /**/{ 0, 0, 90 }, true, true, true, false, 2, true, 0);
			break;
		}

		if (opacitated) {
			ENTITY::SET_ENTITY_ALPHA(ramp, 100, true);
		}

		return ramp;
	}
	void PlayerLis_giveweapon()
	{
		uint32_t Weapons[] = { 0x184140A1, 0xDB26713A, 0x45CD9CF3, 0xC78D71B4, 0x92A27487, 0x958A4A8F, 0xF9E6AA4B, 0x84BD7BFD, 0xA2719263, 0x8BB05FD7, 0x440E4788, 0x4E875F73, 0xF9DCBF2D, 0xD8DF3C3C, 0x99B507EA, 0xDD5DF8D9, 0xDFE37640, 0x678B81B1, 0x19044EE0, 0xCD274149, 0x94117305, 0x3813FC08, /* Melee  */   0x1B06D571, 0xBFE256D4, 0x5EF9FEC4, 0x22D8FE39, 0x3656C8C1, 0x99AEEB3B, 0xBFD21232, 0x88374054, 0xD205520E, 0x83839C4, 0x47757124, 0xDC4DB296, 0xC1B3C3D1, 0xCB96392F, 0x97EA20B8, /* Handguns */  0x13532244, 0x2BE6766B, 0x2BE6766B, 0xEFE7E2DF, 0x0A3D4D34, 0xDB1AA450, 0xBD248B55, /* Submachine Guns */  0x1D073A89, 0x555AF99A, 0x7846A318, 0xE284C527, 0x9D61E50F, 0xA89CB99E, 0x3AABBBAA, 0xEF951FBB, 0x12E82D3D,   /* Shotguns */ 0xBFEFFF6D, 0x394F415C, 0x83BF0278, 0xFAD1F1C9, 0xAF113F99, 0xC0A3098D, 0x969C3D67, 0x7F229F94, 0x84D6FAFD, 0x624FE830,  /* Assault Rifles */ 0x9D07F764, 0x7FD62962, 0xDBBD7280, 0x61012683,   /* Light Machine Guns */ 0x05FC3C11, 0x0C472FE2, 0xA914799, 0xC734385A, 0x6A6C02E0, /* Sniper Rifles  */ 0xB1CA77B1, 0xA284510B, 0x4DD2DC56, 0x42BF8A85, 0x7F7497E5, 0x6D544C99, 0x63AB0442, 0x0781FE4A, /* Heavy Weapons  */ 0x93E220BD, 0xA0973D5E, 0x24B17070, 0x2C3731D9, 0xAB564B93, 0x787F0BB, 0xBA45E8B8, 0x23C9F95C, 0xFDBC8A50, 0x497FACC3,  /*Throwables  */ 0x34A67B97, 0xFBAB5776, 0x060EC506,  /*Miscellaneous  */ 0xAF3696A1, 0x476BF155, 0xB62D1F67,	  /* 1.46  */ 0x2B5EF5EC, 0x2CE227AC, 0x832A1A76, 0x917F6C8C,  /* Casino  */  /* 1.61 */ -610080759, 1853742572, -774507221 /* Criminal Enterprise */ };
		for (int i = 0; i < (sizeof(Weapons) / 4); i++) {
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), Weapons[i], 9999, 1);
		}
	}
	void PlayerList_giveweaponMK1()
	{
		uint32_t WeaponsMK1[] = { 0x99B507EA, 0x678B81B1, 0x4E875F73, 0x958A4A8F, 0x3813FC08, 0x440E4788, 0x84BD7BFD, 0x1B06D571, 0x5EF9FEC4,
			0x22D8FE39, 0x99AEEB3B, 0x13532244, 0x2BE6766B, 0xEFE7E2DF, 0xBFEFFF6D, 0x83BF0278, 0xAF113F99, 0x9D07F764,
			0x7FD62962, 0x1D073A89, 0x7846A318, 0xE284C527, 0x9D61E50F, 0x3656C8C1, 0x05FC3C11, 0x0C472FE2, 0x33058E22,
			0xA284510B, 0x4DD2DC56, 0xB1CA77B1, 0x687652CE, 0x42BF8A85, 0x93E220BD, 0x2C3731D9, 0xFDBC8A50, 0x24B17070,
			0x060EC506, 0x34A67B97, 0xFDBADCED, 0x23C9F95C, 0x497FACC3, 0xF9E6AA4B, 0x61012683, 0xC0A3098D, 0xD205520E,
			0xBFD21232, 0x7F229F94, 0x92A27487, 0x083839C4, 0x7F7497E5, 0xA89CB99E, 0x3AABBBAA, 0xC734385A, 0x787F0BB,
			0x47757124, 0xD04C944D, 0x3813FC08 };
		for (int i = 0; i < (sizeof(WeaponsMK1) / 4); i++) {
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), WeaponsMK1[i], 9999, 1);
		}
	}
	void PlayerList_giveweaponMK2()
	{
		uint32_t WeaponsMK2[] = { 0xBFE256D4, 0x78A97CD0, 0xDBBD7280, 0x394F415C, 0xFAD1F1C9, 0xA914799 };
		for (int i = 0; i < (sizeof(WeaponsMK2) / 4); i++) {
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), WeaponsMK2[i], 9999, 1);
		}
	}
	void NoClip(std::size_t type, float speed, bool toggle)
	{
		if (toggle)
		{
			auto ped = PLAYER::PLAYER_PED_ID();
			Vector3 gameplay_cam_coord{ CAM::GET_GAMEPLAY_CAM_COORD() };
			Vector3 entity_coords{ ENTITY::GET_ENTITY_COORDS(ped, true) };
			auto startDist = std::distance(&gameplay_cam_coord, &entity_coords);
			auto pos = ENTITY::GET_ENTITY_COORDS(ped, false);

			switch (type)
			{
			case 0:
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ped, pos.x, pos.y, pos.z, false, false, false);
				if (AlphaNoclipBool)
				{
					ENTITY::SET_ENTITY_ALPHA(PLAYER::PLAYER_PED_ID(), AlphaNoclip, 0);
				}
				if (SpinNoclip)
				{
					static int Heading;
					Heading++;
					Heading++;
					Heading++;
					Heading++;
					Heading++;
					ENTITY::SET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID(), Heading);
				}
				if (GetAsyncKeyState(0x53) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 268)) //s
				{
					if (IsKeyPressed(VK_LSHIFT) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 21))
						startDist -= 3.0;
					if (IsKeyPressed(VK_SPACE) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 22))
						startDist += .5;

					startDist -= speed;
					startDist -= .3f;
					Vector3 coords = AddV3(ENTITY::GET_ENTITY_COORDS(ped, 1), MultiplyV3(RotationToDirectionV3(CAM::GET_GAMEPLAY_CAM_ROT(0)), startDist));

					ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ped, coords.x, coords.y, coords.z, false, false, false);
				}
				if (GetAsyncKeyState(0x57) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 269)) //w
				{
					if (IsKeyPressed(VK_LSHIFT) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 21))
						startDist += 3.0;
					if (IsKeyPressed(VK_SPACE) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 22))
						startDist -= .5;

					startDist += speed;
					startDist += 1.f;
					Vector3 coords = AddV3(ENTITY::GET_ENTITY_COORDS(ped, 1), MultiplyV3(RotationToDirectionV3(CAM::GET_GAMEPLAY_CAM_ROT(0)), startDist));

					ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ped, coords.x, coords.y, coords.z, false, false, false);
				}

				break;
			case 1:
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ped, pos.x, pos.y, pos.z, true, true, true);
				if (AlphaNoclipBool)
				{
					ENTITY::SET_ENTITY_ALPHA(PLAYER::PLAYER_PED_ID(), AlphaNoclip, 0);
				}
				if (SpinNoclip)
				{
					static int Heading;
					Heading++;
					Heading++;
					Heading++;
					Heading++;
					Heading++;
					ENTITY::SET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID(), Heading);
				}
				if (GetAsyncKeyState(0x53) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 268)) //s
				{
					if (IsKeyPressed(VK_LSHIFT) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 21))
						startDist -= 3.0;
					if (IsKeyPressed(VK_SPACE) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 22))
						startDist += .5;

					startDist -= speed;
					startDist -= .3f;
					Vector3 coords = AddV3(ENTITY::GET_ENTITY_COORDS(ped, 1), MultiplyV3(RotationToDirectionV3(CAM::GET_GAMEPLAY_CAM_ROT(0)), startDist));

					ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ped, coords.x, coords.y, coords.z, true, true, true);
				}
				if (GetAsyncKeyState(0x57) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 269)) //w
				{
					if (IsKeyPressed(VK_LSHIFT) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 21))
						startDist += 3.0;
					if (IsKeyPressed(VK_SPACE) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 22))
						startDist -= .5;

					startDist += speed;
					startDist += 1.f;
					Vector3 coords = AddV3(ENTITY::GET_ENTITY_COORDS(ped, 1), MultiplyV3(RotationToDirectionV3(CAM::GET_GAMEPLAY_CAM_ROT(0)), startDist));

					ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ped, coords.x, coords.y, coords.z, true, true, true);
				}
				break;
			}
		}
	}
	void SuperJump(bool toggle)
	{
		if (toggle)
			MISC::SET_SUPER_JUMP_THIS_FRAME(PLAYER::PLAYER_ID()); //will trigger a superjump flag if in online, will be visible to modders
	}
	void BeastJump(bool toggle)
	{
		if (toggle)
		{
			MISC::SET_SUPER_JUMP_THIS_FRAME(PLAYER::PLAYER_ID());
		}
	}
	void Ninjajump(bool toggle)
	{
		if (toggle)
		{
			static int flip;
			MISC::SET_SUPER_JUMP_THIS_FRAME(PLAYER::PLAYER_ID());
			if (PED::IS_PED_JUMPING(PLAYER::PLAYER_PED_ID()))
			{
				if (ENTITY::IS_ENTITY_IN_AIR(PLAYER::PLAYER_PED_ID()))
				{
					flip -= 10;
					ENTITY::SET_ENTITY_ROTATION(PLAYER::PLAYER_PED_ID(), flip, 0, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), 0, 0);
				}
			}
		}
	}
	void FastRun(bool toggle)
	{
		if (toggle)
		{
			PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(PLAYER::PLAYER_ID(), FastRunSpeed);
		}
		else

		{
			PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(PLAYER::PLAYER_ID(), 1.0f);
		}
	}
	void PaintGun(bool toggle)
	{
		if (toggle)
		{
			static std::vector<Vector3> a;
			Vector3 b;
			if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &b)); {
				a.push_back(b);
			}
			for (auto pos : a) {
				GRAPHICS::DRAW_LIGHT_WITH_RANGE1(pos, m_color.r, m_color.g, m_color.b, m_range, m_intensity);

			}
		}
		else
		{
			NULL;
		}
	}
	void giveallweapon()
	{
		uint32_t Weapons[] = { 0x184140A1, 0xDB26713A, 0x45CD9CF3, 0xC78D71B4, 0x92A27487, 0x958A4A8F, 0xF9E6AA4B, 0x84BD7BFD, 0xA2719263, 0x8BB05FD7, 0x440E4788, 0x4E875F73, 0xF9DCBF2D, 0xD8DF3C3C, 0x99B507EA, 0xDD5DF8D9, 0xDFE37640, 0x678B81B1, 0x19044EE0, 0xCD274149, 0x94117305, 0x3813FC08, /* Melee  */   0x1B06D571, 0xBFE256D4, 0x5EF9FEC4, 0x22D8FE39, 0x3656C8C1, 0x99AEEB3B, 0xBFD21232, 0x88374054, 0xD205520E, 0x83839C4, 0x47757124, 0xDC4DB296, 0xC1B3C3D1, 0xCB96392F, 0x97EA20B8, /* Handguns */  0x13532244, 0x2BE6766B, 0x2BE6766B, 0xEFE7E2DF, 0x0A3D4D34, 0xDB1AA450, 0xBD248B55, /* Submachine Guns */  0x1D073A89, 0x555AF99A, 0x7846A318, 0xE284C527, 0x9D61E50F, 0xA89CB99E, 0x3AABBBAA, 0xEF951FBB, 0x12E82D3D,   /* Shotguns */ 0xBFEFFF6D, 0x394F415C, 0x83BF0278, 0xFAD1F1C9, 0xAF113F99, 0xC0A3098D, 0x969C3D67, 0x7F229F94, 0x84D6FAFD, 0x624FE830,  /* Assault Rifles */ 0x9D07F764, 0x7FD62962, 0xDBBD7280, 0x61012683,   /* Light Machine Guns */ 0x05FC3C11, 0x0C472FE2, 0xA914799, 0xC734385A, 0x6A6C02E0, /* Sniper Rifles  */ 0xB1CA77B1, 0xA284510B, 0x4DD2DC56, 0x42BF8A85, 0x7F7497E5, 0x6D544C99, 0x63AB0442, 0x0781FE4A, /* Heavy Weapons  */ 0x93E220BD, 0xA0973D5E, 0x24B17070, 0x2C3731D9, 0xAB564B93, 0x787F0BB, 0xBA45E8B8, 0x23C9F95C, 0xFDBC8A50, 0x497FACC3,  /*Throwables  */ 0x34A67B97, 0xFBAB5776, 0x060EC506,  /*Miscellaneous  */ 0xAF3696A1, 0x476BF155, 0xB62D1F67,	  /* 1.46  */ 0x2B5EF5EC, 0x2CE227AC, 0x832A1A76, 0x917F6C8C,  /* Casino  */  /* 1.61 */ -610080759, 1853742572, -774507221 /* Criminal Enterprise */ };
		for (int i = 0; i < (sizeof(Weapons) / 4); i++) {
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), Weapons[i], 9999, 1);
		}
	}
	void giveweapon(Hash hash)
	{
		WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), hash, 9999, 1);
	}
	void moneyGun(bool toggle)
	{
		if (toggle)
		{
			Vector3 coords;
			if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &coords)) {
				constexpr int CashHash = -1666779307;
				STREAMING::REQUEST_MODEL(CashHash);
				Entity e = OBJECT::CREATE_AMBIENT_PICKUP(0x1E9A99F8, coords.x, coords.y, coords.z + 2, 0, moneyNumber, CashHash, false, true);
				ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&e);
			}
		}
	}
	void ShootWater(bool toggle)
	{
		if (toggle)
		{
			Ped playerPed = PLAYER::PLAYER_PED_ID();

			if (g_utility.is_ped_shooting(playerPed))
			{
				Vector3 coords;
				if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(playerPed, &coords))
				{
					FIRE::ADD_EXPLOSION(coords.x, coords.y, coords.z, 13, 10.0f, false, false, false, false);
				}

			}
		}
	}
	void DeadEyeGun(bool toggle)
	{
		if (toggle)
		{
			if (PED::GET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), PED_FLAG_IS_AIMING, 1)) {
				MISC::SET_TIME_SCALE(0.35f);
				if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID())) {
					MISC::SET_TIME_SCALE(0.2f);
					GRAPHICS::SET_TIMECYCLE_MODIFIER("Death");
				}
				else {
					GRAPHICS::CLEAR_TIMECYCLE_MODIFIER();
				}
				GRAPHICS::ANIMPOSTFX_PLAY("ExplosionJosh3", -1, true);
			}
			else {
				MISC::SET_TIME_SCALE(1.0f);
				GRAPHICS::CLEAR_TIMECYCLE_MODIFIER();
				GRAPHICS::ANIMPOSTFX_STOP("ExplosionJosh3");
			}
		}
	}
	void RainbowCamo(bool toggle)
	{
		if (toggle)
		{
			Ped playerPed = PLAYER::PLAYER_PED_ID();
			static LPCSTR weaponNames[] = {
				"WEAPON_KNIFE", "WEAPON_NIGHTSTICK", "WEAPON_HAMMER", "WEAPON_BAT", "WEAPON_GOLFCLUB", "WEAPON_CROWBAR",
				"WEAPON_PISTOL", "WEAPON_COMBATPISTOL", "WEAPON_APPISTOL", "WEAPON_PISTOL50", "WEAPON_MICROSMG", "WEAPON_SMG",
				"WEAPON_ASSAULTSMG", "WEAPON_ASSAULTRIFLE", "WEAPON_CARBINERIFLE", "WEAPON_ADVANCEDRIFLE", "WEAPON_MG",
				"WEAPON_COMBATMG", "WEAPON_PUMPSHOTGUN", "WEAPON_SAWNOFFSHOTGUN", "WEAPON_ASSAULTSHOTGUN", "WEAPON_BULLPUPSHOTGUN",
				"WEAPON_STUNGUN", "WEAPON_SNIPERRIFLE", "WEAPON_HEAVYSNIPER", "WEAPON_GRENADELAUNCHER", "WEAPON_GRENADELAUNCHER_SMOKE",
				"WEAPON_RPG", "WEAPON_MINIGUN", "WEAPON_GRENADE", "WEAPON_STICKYBOMB", "WEAPON_SMOKEGRENADE", "WEAPON_BZGAS",
				"WEAPON_MOLOTOV", "WEAPON_FIREEXTINGUISHER", "WEAPON_PETROLCAN", "WEAPON_SNSPISTOL", "WEAPON_SPECIALCARBINE",
				"WEAPON_HEAVYPISTOL", "WEAPON_BULLPUPRIFLE", "WEAPON_HOMINGLAUNCHER", "WEAPON_PROXMINE", "WEAPON_SNOWBALL",
				"WEAPON_VINTAGEPISTOL", "WEAPON_DAGGER", "WEAPON_FIREWORK", "WEAPON_MUSKET", "WEAPON_MARKSMANRIFLE", "WEAPON_HEAVYSHOTGUN",
				"WEAPON_GUSENBERG", "WEAPON_HATCHET", "WEAPON_RAILGUN", "WEAPON_FLAREGUN",
				"WEAPON_KNUCKLE", "GADGET_NIGHTVISION", "GADGET_PARACHUTE", "WEAPON_MARKSMANPISTOL"
			};
			for (int i = 0; i < sizeof(weaponNames) / sizeof(weaponNames[0]); i++)
			{
				if (WEAPON::HAS_PED_GOT_WEAPON(playerPed, MISC::GET_HASH_KEY((char*)weaponNames[i]), 0))
				{
					WEAPON::SET_PED_WEAPON_TINT_INDEX(playerPed, MISC::GET_HASH_KEY((char*)weaponNames[i]), rand() % 8);
				}
			}
		}

	}
	void ForceGun(bool toggle)
	{
		if (toggle)
		{
			Entity EntityTarget;
			Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
			Vector3 dir = RotationToDirectionV3(rot);
			if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &EntityTarget))
			{
				if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
				{
					if (ENTITY::IS_ENTITY_A_PED(EntityTarget)
						&& PED::IS_PED_IN_ANY_VEHICLE(EntityTarget, 1)) {
						EntityTarget = PED::GET_VEHICLE_PED_IS_IN(EntityTarget, 0);
					}
					ENTITY::APPLY_FORCE_TO_ENTITY(EntityTarget, 1, dir.x * 100000.0f, dir.y * 100000.0f, dir.z * 100000.0f, 0.0f, 0.0f, 0.0f, 0, 0, 1, 1, 0, 1);
				}
			}
		}
	}
	inline float GravityGunGoto(float aimX, float entityX)
	{
		static float GravityGunVeloPos;
		if (aimX > 0 && entityX > 0)
		{
			GravityGunVeloPos = aimX - (entityX);
		}

		if (aimX < 0 && entityX < 0)
		{
			GravityGunVeloPos = aimX - (entityX);
		}

		if (aimX > 0 && entityX < 0)
		{
			GravityGunVeloPos = aimX + (entityX);
		}

		if (aimX < 0 && entityX > 0)
		{
			GravityGunVeloPos = aimX + (entityX);
		}

		return GravityGunVeloPos;
	}
	void GravityBug(bool toggle)
	{
		if (toggle)
		{
			static bool oneperswitch{ false };
			static int zoom = 10;
			static Entity entitiess;
			static Entity entitiesss;

			switch (GravityGunSize)
			{
			case 0:

				if (GetAsyncKeyState(VK_RBUTTON) || PAD::IS_CONTROL_PRESSED(2, 25))
				{

					if (LockOnEntity)
					{
						if (entitiess == 0)
						{
							PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &entitiess);
						}
					}
					else
					{
						PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &entitiess);
					}



					Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
					Vector3 dir = RotationToDirectionV3(rot);
					Vector3 spawnPosition = AddV3(CAM::GET_GAMEPLAY_CAM_COORD(), MultiplyV3(dir, zoom));

					if (ENTITY::IS_ENTITY_A_PED(entitiess) && PED::IS_PED_IN_ANY_VEHICLE(entitiess, 0))
					{
						entitiess = PED::GET_VEHICLE_PED_IS_IN(entitiess, 0);
					}

					Vector3 getcoors = ENTITY::GET_ENTITY_COORDS(entitiess, 0);
					float getaimcoorsX = GravityGunGoto(spawnPosition.x, getcoors.x);
					float getaimcoorsY = GravityGunGoto(spawnPosition.y, getcoors.y);
					float getaimcoorsZ = GravityGunGoto(spawnPosition.z, getcoors.z);
					ENTITY::SET_ENTITY_VELOCITY(entitiess, getaimcoorsX * g_Velocity, getaimcoorsY * g_Velocity, getaimcoorsZ * g_Velocity);

					if (GetAsyncKeyState(VK_LBUTTON) || PAD::IS_CONTROL_PRESSED(2, 24))
					{

						g_utility.RequestControlOfEnt(entitiess);
						Entity Vehicle = entitiess;
						ENTITY::APPLY_FORCE_TO_ENTITY(Vehicle, 1, dir.x * g_Force * 1000, dir.y * g_Force * 1000, dir.z * g_Force * 1000, 0.0f, 0.0f, 0.0f, 0, 0, 1, 1, 0, 1);
						Vehicle = entitiesss;
						entitiess = entitiesss;

					}


					if (PAD::IS_DISABLED_CONTROL_PRESSED(2, 261))
					{
						zoom += g_PullPushStrength;
					}
					if (PAD::IS_DISABLED_CONTROL_PRESSED(2, 262))
					{
						zoom -= g_PullPushStrength;

					}
				}

				break;
			case 1:
				Entity currEnt;
				static int zoom = 10;
				if (GetAsyncKeyState(VK_RBUTTON) || PAD::IS_CONTROL_PRESSED(2, 25))
				{

					PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &currEnt);
					if (std::find(GravityGunDatabase.begin(), GravityGunDatabase.end(), currEnt) != GravityGunDatabase.end()) {}
					else if (GravityGunDatabase.size() > m_GravityGunEntityCount) {}
					else { GravityGunDatabase.push_back(currEnt); }

					for (std::int32_t entities : GravityGunDatabase)
					{

						Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
						Vector3 dir = RotationToDirectionV3(rot);
						Vector3 spawnPosition = AddV3(CAM::GET_GAMEPLAY_CAM_COORD(), MultiplyV3(dir, zoom));

						if (ENTITY::IS_ENTITY_A_PED(entities) && PED::IS_PED_IN_ANY_VEHICLE(entities, 0))
						{
							entities = PED::GET_VEHICLE_PED_IS_IN(entities, 0);
						}



						Vector3 getcoors = ENTITY::GET_ENTITY_COORDS(entities, 0);
						float getaimcoorsX = GravityGunGoto(spawnPosition.x, getcoors.x);
						float getaimcoorsY = GravityGunGoto(spawnPosition.y, getcoors.y);
						float getaimcoorsZ = GravityGunGoto(spawnPosition.z, getcoors.z);
						ENTITY::SET_ENTITY_VELOCITY(entities, getaimcoorsX * g_Velocity, getaimcoorsY * g_Velocity, getaimcoorsZ * g_Velocity);

						if (GetAsyncKeyState(VK_LBUTTON) || PAD::IS_CONTROL_PRESSED(2, 24))
						{

							g_utility.RequestControlOfEnt(entities);
							Entity Vehicle = entities;
							ENTITY::APPLY_FORCE_TO_ENTITY(Vehicle, 1, dir.x * g_Force * 1000, dir.y * g_Force * 1000, dir.z * g_Force * 1000, 0.0f, 0.0f, 0.0f, 0, 0, 1, 1, 0, 1);
							ENTITY::DELETE_ENTITY(&Vehicle);
							GravityGunDatabase.clear();
							ENTITY::DELETE_ENTITY(&Vehicle);
							GravityGunDatabase.erase(GravityGunDatabase.begin(), GravityGunDatabase.end());
							ENTITY::DELETE_ENTITY(&Vehicle);
							free((void*)Vehicle);
							std::vector<std::int32_t>().swap(GravityGunDatabase);


						}

					}
					if (PAD::IS_DISABLED_CONTROL_PRESSED(2, 261))
					{
						zoom += g_PullPushStrength;
					}
					if (PAD::IS_DISABLED_CONTROL_PRESSED(2, 262))
					{
						zoom -= g_PullPushStrength;
					}
				}

				break;
			}

		}
	}
	void PropellantGun(bool toggle, float SpawnDistance, std::uint32_t Model, float Speed)
	{
		if (toggle)
		{
			if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
			{
				float startDistance = GetDistanceFloat(CAM::GET_GAMEPLAY_CAM_COORD(), ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true));
				float endDistance = GetDistanceFloat(CAM::GET_GAMEPLAY_CAM_COORD(), ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true));
				startDistance += SpawnDistance;
				endDistance += 1000.0;
				if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
				{
					if (!WEAPON::HAS_WEAPON_ASSET_LOADED(Model))
					{
						WEAPON::REQUEST_WEAPON_ASSET(Model, 31, false);
					}
					MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(AddV3(CAM::GET_GAMEPLAY_CAM_COORD(), MultiplyV3(RotationToDirectionV3(CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).x, AddV3(CAM::GET_GAMEPLAY_CAM_COORD(), MultiplyV3(RotationToDirectionV3(CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).y, AddV3(CAM::GET_GAMEPLAY_CAM_COORD(), MultiplyV3(RotationToDirectionV3(CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).z, AddV3(CAM::GET_GAMEPLAY_CAM_COORD(), MultiplyV3(RotationToDirectionV3(CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).x, AddV3(CAM::GET_GAMEPLAY_CAM_COORD(), MultiplyV3(RotationToDirectionV3(CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).y, AddV3(CAM::GET_GAMEPLAY_CAM_COORD(), MultiplyV3(RotationToDirectionV3(CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).z, Speed, 1, Model, PLAYER::PLAYER_PED_ID(), 1, 0, -1.0);
				}
			}
		}
	}
	void YoinkGun(bool toggle)
	{

		if (toggle)
		{
			Entity Target;
			Vehicle Car;
			if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &Car) && (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &Target)))
			{

				g_utility.RequestControlOfEnt(Target);

				if (ENTITY::IS_ENTITY_A_PED(Target) && PED::IS_PED_IN_ANY_VEHICLE(Target, 1))
				{
					Car = PED::GET_VEHICLE_PED_IS_IN(Target, 0);
					if (PED::IS_PED_IN_VEHICLE(Target, Car, 1))
					{
						ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Target, 1, 1);
						ENTITY::DELETE_ENTITY(&Target);
						PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Target, -1);
					}
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Target, -1);
				}

			}
			if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
			{
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Target, -1);
			}
		}

	}
	void Magnet(bool toggle)
	{
		if (toggle)
		{
			static float zoom{ 10.f };

			if (GetAsyncKeyState(VK_RBUTTON))
			{
				if (zoom < 40.f)
				{
					if (PAD::IS_DISABLED_CONTROL_PRESSED(2, 261))
					{
						zoom += 2.f;
					}
				}
				if (PAD::IS_DISABLED_CONTROL_PRESSED(2, 262))
				{
					zoom -= 2.f;

				}
				const int pedElements = 10;
				const int pedArrSize = pedElements * 2 + 2;
				int ped[pedArrSize];
				ped[0] = pedElements;
				int pedcount = PED::GetPedNearbyVehicles(PLAYER::PLAYER_PED_ID(), ped);

				const int numElements = 10;
				const int arrSize = numElements * 2 + 2;
				int veh[arrSize];
				veh[0] = numElements;
				int count = PED::GetPedNearbyVehicles(PLAYER::PLAYER_PED_ID(), veh);



				if (veh != 0 | ped != 0)
				{
					for (int i = 0; i < count; i++)
					{
						int ofsettedID = i * 2 + 2;
						if (ENTITY::IS_ENTITY_A_PED(veh[ofsettedID]) && PED::IS_PED_IN_ANY_VEHICLE(veh[ofsettedID], false))
						{
							veh[ofsettedID] = PED::GET_VEHICLE_PED_IS_IN(veh[ofsettedID], false);
						}

						Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
						Vector3 dir = RotationToDirectionV3(rot);
						Vector3 pos = AddV3(CAM::GET_GAMEPLAY_CAM_COORD(), MultiplyV3(dir, zoom));
						Vector3 coords = ENTITY::GET_ENTITY_COORDS(veh[ofsettedID], 0);

						GRAPHICS::DRAW_MARKER_SPHERE(pos.x, pos.y, pos.z, 4.f, magnetGunR, magnetGunG, magnetGunB, 0.5f);

						g_utility.RequestControlOfEnt(ped[ofsettedID]);

						float getaimcoorsX = GravityGunGoto(pos.x, coords.x);
						float getaimcoorsY = GravityGunGoto(pos.y, coords.y);
						float getaimcoorsZ = GravityGunGoto(pos.z, coords.z);

						ENTITY::SET_ENTITY_VELOCITY(ped[ofsettedID], getaimcoorsX * 2.f, getaimcoorsY * 2.f, getaimcoorsZ * 2.f);
						ENTITY::SET_ENTITY_VELOCITY(veh[ofsettedID], getaimcoorsX * 2.f, getaimcoorsY * 2.f, getaimcoorsZ * 2.f);
					}
				}
			}
		}
	}

	void EnityGunVehicle(bool toggle, const char* SelectedVehicle, float SpawnDistance, float LaunchSpeed)
	{
		if (toggle)
		{
			if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
			{
				DWORD model = MISC::GET_HASH_KEY(SelectedVehicle);
				Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
				Vector3 dir = RotationToDirectionV3(rot);
				Vector3 CamPosition = CAM::GET_GAMEPLAY_CAM_COORD();
				Vector3 PlayerPosition = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				float spawnDistance = GetDistanceFloat(CamPosition, PlayerPosition);
				spawnDistance += SpawnDistance;
				Vector3 spawnPosition = AddV3(CamPosition, MultiplyV3(dir, spawnDistance));

				if (ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID()))
				{
					if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
					{
						Vector3 playerOffset = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0, 5, 0);
						if (PED::IS_PED_ON_FOOT(PLAYER::PLAYER_PED_ID()))
						{
							STREAMING::REQUEST_MODEL(model);

							Vehicle veh = VEHICLE::CREATE_VEHICLE(model, spawnPosition.x, spawnPosition.y, spawnPosition.z, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), NETWORK::NETWORK_IS_IN_SESSION(), 1, 0);
							VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, LaunchSpeed);
							STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
							ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);

						}
					}
				}
			}
		}
	}
	void RapidFire(bool toggle)
	{
		if (toggle)
		{
			if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
				Vector3 gameplayCam = CAM::GET_FINAL_RENDERED_CAM_COORD();
				Vector3 gameplayCamRot = CAM::GET_GAMEPLAY_CAM_ROT(0);
				Vector3 gameplayCamDirection = RotationToDirectionV3(gameplayCamRot);
				Vector3 startCoords = AddV3(gameplayCam, (MultiplyV3(gameplayCamDirection, 1.0f)));
				Vector3 endCoords = AddV3(startCoords, MultiplyV3(gameplayCamDirection, 500.0f));
				Hash weaponhash;
				WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &weaponhash, 1);
				if (PAD::IS_CONTROL_PRESSED(2, 208) || (GetKeyState(VK_LBUTTON) & 0x8000)) {
					MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(startCoords.x, startCoords.y, startCoords.z, endCoords.x, endCoords.y, endCoords.z, 50, 1, weaponhash, PLAYER::PLAYER_PED_ID(), 1, 1, 0xbf800000);
				}
			}
		}
	}
	void TeleportGun(bool toggle)
	{
		if (toggle)
		{
			if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
			{
				Vector3 coords;
				if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &coords))
				{
					ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), coords.x, coords.y, coords.z, 0, 0, 0, 1);
				}
			}
		}
	}
	void LaserSight(bool toggle)
	{
		if (PLAYER::IS_PLAYER_FREE_AIMING(PLAYER::PLAYER_ID()))
		{
			if (toggle)
			{
				auto camrot = CAM::GET_GAMEPLAY_CAM_ROT(0);
				auto camdir = RotationToDirectionV3(camrot);
				auto start = ENTITY::GET_ENTITY_COORDS(WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(PLAYER::PLAYER_PED_ID(), 0), 1);
				auto end = AddV3(CAM::GET_GAMEPLAY_CAM_COORD(), MultiplyV3(camdir, 1.f));

				GRAPHICS::DRAW_LINE(start.x, start.y, start.z, end.x, end.y, end.z, laserR, laserG, laserB, 255);
			}
		}

	}
	void DeleteGun(bool toggle)
	{
		if (toggle)
		{
			if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
			{
				Entity Delete;
				if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &Delete)) {

					if (ENTITY::DOES_ENTITY_EXIST(Delete) && NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Delete) && PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
					{
						ENTITY::DETACH_ENTITY(Delete, 1, 1);
						ENTITY::SET_ENTITY_COORDS_NO_OFFSET(Delete, 0, 0, 0, 0, 0, 0);
						ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Delete, 0, 1);
						ENTITY::DELETE_ENTITY(&Delete);
					}
				}
			}
		}
	}
	void AirstrikeGun(bool toggle)
	{
		if (toggle)
		{
			if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
			{
				Vector3 shoot;
				if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &shoot))
				{
					Hash weaponAssetRocket = MISC::GET_HASH_KEY("WEAPON_VEHICLE_ROCKET");
					if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
					{
						WEAPON::REQUEST_WEAPON_ASSET(weaponAssetRocket, 31, 0);
					}

					MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(shoot.x, shoot.y, shoot.z + 25, shoot.x, shoot.y, shoot.z, 100, 1, weaponAssetRocket, PLAYER::PLAYER_PED_ID(), 1, 0, 1000.0);
				}
			}
		}
	}
	void EntityGunObject(bool toggle, const char* SelectedObject, float SpawnDistance, float LaunchSpeed)
	{
		if (toggle)
		{
			if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
			{
				Vector3 Rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
				Vector3 Dir = RotationToDirectionV3(Rot);
				Vector3 CPosition = CAM::GET_GAMEPLAY_CAM_COORD();
				Vector3 PlayerPosition = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				float spawnDistance = GetDistanceFloat(CPosition, PlayerPosition); spawnDistance += SpawnDistance;
				Vector3 SPosition = AddV3(CPosition, MultiplyV3(Dir, spawnDistance));
				DWORD Model = MISC::GET_HASH_KEY(SelectedObject);
				Object ObJect = OBJECT::CREATE_OBJECT(Model, SPosition.x, SPosition.y, SPosition.z, 1, 1, 1);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(Model);
				if (ENTITY::DOES_ENTITY_EXIST(ObJect))
				{
					ENTITY::SET_ENTITY_RECORDS_COLLISIONS(ObJect, true);
					ENTITY::APPLY_FORCE_TO_ENTITY(ObJect, 1, Dir.x * LaunchSpeed, Dir.y * LaunchSpeed, Dir.z * LaunchSpeed, 0.0f, 0.0f, 0.0f, 0, 0, 1, 1, 0, 1);
				}
			}
		}
	}
	void ExplosiveAmmo(bool toggle)
	{
		if (toggle)
		{
			MISC::SET_EXPLOSIVE_AMMO_THIS_FRAME(PLAYER::PLAYER_ID());
			MISC::SET_EXPLOSIVE_AMMO_THIS_FRAME(PLAYER::PLAYER_PED_ID());
			MISC::SET_EXPLOSIVE_AMMO_THIS_FRAME(PLAYER::GET_PLAYER_PED(-1));
		}
		else
		{
			NULL;
		}
	}
	inline Vector3 GetWaypointCoords() {
		static Vector3 zero;
		Vector3 coords;

		bool blipFound = false;
		int blipIterator = HUD::GET_WAYPOINT_BLIP_ENUM_ID();
		for (Blip i = HUD::GET_FIRST_BLIP_INFO_ID(blipIterator); HUD::DOES_BLIP_EXIST(i) != 0; i = HUD::GET_NEXT_BLIP_INFO_ID(blipIterator)) {
			if (HUD::GET_BLIP_INFO_ID_TYPE(i) == 4) {
				coords = HUD::GET_BLIP_INFO_ID_COORD(i);
				blipFound = true;
				break;
			}
		}
		if (blipFound) return coords;

		return zero;
	}
	void DriveToWaypoint() {
		if (HUD::IS_WAYPOINT_ACTIVE()) {
			Vector3 waypoint = GetWaypointCoords();
			std::int32_t l_vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
			if (PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID())) {
				TASK::TASK_VEHICLE_DRIVE_TO_COORD(PLAYER::PLAYER_PED_ID(), l_vehicle, waypoint.x, waypoint.y, waypoint.z, 40, 1, ENTITY::GET_ENTITY_MODEL(l_vehicle), 7, 6, -1);
			}
			else;
		}
		else;
	}
	void StopAutoDrive() {
		if (PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID())) {
			Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
			TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
			PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
		}
	}
	void Autofix(bool toggle)
	{
		if (toggle)
		{
			if (VEHICLE::GET_DOES_VEHICLE_HAVE_DAMAGE_DECALS(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0)))
			{
				VEHICLE::SET_VEHICLE_FIXED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0));
			}
			VEHICLE::SET_VEHICLE_HAS_UNBREAKABLE_LIGHTS(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 1);
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 0);
		}
	}
	void AutoFlip(bool toggle)
	{
		if (toggle)
		{
			std::int32_t l_vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
			float l_roll = ENTITY::GET_ENTITY_ROLL(l_vehicle);
			if (ENTITY::IS_ENTITY_UPSIDEDOWN(l_vehicle) && (l_roll > 160 || l_roll < -160)) {
				if (!ENTITY::IS_ENTITY_IN_AIR(l_vehicle) && !ENTITY::IS_ENTITY_IN_WATER(l_vehicle) && !VEHICLE::IS_THIS_MODEL_A_PLANE(l_vehicle) && !VEHICLE::IS_THIS_MODEL_A_HELI(l_vehicle)) {
					g_utility.RequestControlOfEnt(l_vehicle);
					ENTITY::SET_ENTITY_ROTATION(l_vehicle, 0, 0, ENTITY::GET_ENTITY_ROTATION(l_vehicle, 2).z, 2, 1);
				}
			}
		}
	}
	void Driftmode(bool toggle)
	{
		if (toggle)
		{
			if (GetAsyncKeyState(VK_SPACE))
				VEHICLE::SET_VEHICLE_REDUCE_GRIP(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 1);
			else
				VEHICLE::SET_VEHICLE_REDUCE_GRIP(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 0);
		}
	}
	void DriveOnWater(bool toggle)
	{
		if (toggle)
		{
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				Hash ferris = MISC::GET_HASH_KEY("prop_container_ld2");
				Vector3 me = ENTITY::GET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 0);
				float water;
				static int timer = 0;
				static Object model;

				WATER::SET_DEEP_OCEAN_SCALER(-1.f);
				if (WATER::GET_WATER_HEIGHT(me.x, me.y, me.z, &water))
				{
					if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1))
					{

						if (GetTickCount() - timer >= 0)
						{
							model = OBJECT::CREATE_OBJECT(ferris, me.x, me.y, me.z, 1, 1, 1);
							g_utility.RequestControlOfEnt(model);
							ENTITY::SET_ENTITY_VISIBLE(model, 0, 0);
							ENTITY::FREEZE_ENTITY_POSITION(model, 1);
							ENTITY::SET_ENTITY_ROTATION(model, 0, 0, ENTITY::GET_ENTITY_HEADING(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0)), 0, 0);
							ENTITY::SET_ENTITY_COORDS(model, me.x, me.y, water - 2.7f, 0, 0, 0, 1);
							timer = GetTickCount();
						}

					}
				}
				if (ENTITY::DOES_ENTITY_EXIST(model))
				{
					g_utility.RequestControlOfEnt(model);
					OBJECT::DELETE_OBJECT(&model);
				}
			}
		}
	}
	void DriveUnderWater(bool toggle)
	{
		if (toggle)
		{
			VEHICLE::SET_VEHICLE_ENGINE_ON(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), true, true, true);
		}
	}
	void ForceVehicleToGround(bool toggle)
	{
		if (toggle)
		{
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 0);
			}
		}
	}
	void ThreeSixtyVehicle(bool toggle)
	{
		if (toggle)
		{
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false));
				Vector3 Rot = ENTITY::GET_ENTITY_ROTATION(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 2);
				Rot.z = Rot.z + 2.0;
				ENTITY::SET_ENTITY_ROTATION(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 0, 0, Rot.z, 2, 1);
			}
		}
	}
	void EngineAlwaysOn(bool toggle)
	{
		if (toggle)
		{
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				VEHICLE::SET_VEHICLE_ENGINE_ON(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), true, true, true);
			}
		}
	}
	void GlitchVehicle(bool toggle)
	{
		if (toggle)
		{
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0));
			Vector3 Rot = ENTITY::GET_ENTITY_ROTATION(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 20);
			Rot.z = Rot.z + 20.0;
			ENTITY::SET_ENTITY_ROTATION(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 0, 0, Rot.z, 20, 10);
		}
	}
	void CustomWheelPTFX(const char* streamName, const char* PTFXName, const char* wheel)
	{

		int myVeh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		STREAMING::REQUEST_NAMED_PTFX_ASSET(streamName);
		if (STREAMING::HAS_NAMED_PTFX_ASSET_LOADED(streamName))
		{
			Vector3 pos2 = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(myVeh, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(myVeh, wheel));
			GRAPHICS::USE_PARTICLE_FX_ASSET(streamName);
			GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(PTFXName, pos2.x, pos2.y, pos2.z, 0.f, 0.f, 0.f, m_GlowScale0, false, false, false, false);
		}
		else STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
	}
	void GlowManager0(bool toggle)
	{
		if (toggle)
		{
			if (m_RightFrontWheel) { CustomWheelPTFX(m_ParticleCalls00[m_ParticleIterator0], m_ParticleCalls10[m_ParticleIterator0], "wheel_rf"); }
			if (m_LeftFrontWheel) { CustomWheelPTFX(m_ParticleCalls00[m_ParticleIterator0], m_ParticleCalls10[m_ParticleIterator0], "wheel_lf"); }
			if (m_RightBackWheel) { CustomWheelPTFX(m_ParticleCalls00[m_ParticleIterator0], m_ParticleCalls10[m_ParticleIterator0], "wheel_rr"); }
			if (m_LeftBackWheel) { CustomWheelPTFX(m_ParticleCalls00[m_ParticleIterator0], m_ParticleCalls10[m_ParticleIterator0], "wheel_lr"); }
		}
	}
	void VehicleFly(bool toggle, float speed)
	{
		if (toggle)
		{
			if (PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()) != NULL) {
				std::int32_t l_vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);

				VEHICLE::SET_VEHICLE_GRAVITY(l_vehicle, false);

				Vector3 GCR = CAM::GET_GAMEPLAY_CAM_ROT(2);
				ENTITY::SET_ENTITY_ROTATION(l_vehicle, GCR.x, GCR.y, GCR.z, 2, 1);

				if (PAD::IS_DISABLED_CONTROL_PRESSED(2, 87)) //INPUT_VEH_FLY_THROTTLE_UP
				{
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(l_vehicle, speed);
				}
				else
				{
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(l_vehicle, 0.0f);
				}
			}

		}
	}
	void Hornboost(bool toggle)
	{
		if (toggle && PAD::IS_CONTROL_PRESSED(2, 86)) //INPUT_VEH_HORN
		{
			std::int32_t l_vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			std::float_t s_VehicleSpeed = ENTITY::GET_ENTITY_SPEED(l_vehicle);

			if (!ENTITY::DOES_ENTITY_EXIST(l_vehicle)) return;

			if (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(l_vehicle) != 0) {
				NETWORK::SET_NETWORK_ID_CAN_MIGRATE(l_vehicle, true);
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(l_vehicle);
			}

			if (m_AudioBoost)
			{
				AUDIO::SET_VEHICLE_BOOST_ACTIVE(l_vehicle, true);
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(l_vehicle, s_VehicleSpeed + m_SpeedBoost);
				AUDIO::SET_VEHICLE_BOOST_ACTIVE(l_vehicle, false);
			}
			else
			{
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(l_vehicle, s_VehicleSpeed + m_SpeedBoost);
			}

			if (m_BoostEffect)
			{
				GRAPHICS::SET_TIMECYCLE_MODIFIER("RaceTurboLight");
			}

		}
	}
	void Seatbelt(bool toggle)
	{
		if (toggle)
		{
			PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), 1);
			PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 32, false);
		}
	}
	void VehicleInvincible(bool toggle)
	{
		if (toggle)
		{
			VEHICLE::SET_VEHICLE_HAS_UNBREAKABLE_LIGHTS(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 1);
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 0);
			ENTITY::SET_ENTITY_INVINCIBLE(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 1);
		}
	}
	void RenderScorched(bool toggle)
	{
		if (toggle)
		{
			ENTITY::SET_ENTITY_RENDER_SCORCHED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), static_cast<int>(g_Scorched));
		}
		else
		{
			NULL;
		}
	}
	void VehicleRamp(bool front, bool back, bool left, bool right)
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
		Hash ramp = MISC::GET_HASH_KEY("lts_prop_lts_ramp_01");

		if (ENTITY::DOES_ENTITY_EXIST(veh))
		{
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(veh);

			if (front)
			{
				std::int32_t Object = OBJECT::CREATE_OBJECT(ramp, 0.f, 0.f, 0.f, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), 1, 0);
				if (ENTITY::DOES_ENTITY_EXIST(Object))
				{
					ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, veh, 0, 0, 5, 0.3f, 0, 0, 180, 0, 0, 0, 0, 2, 1, 0);
					ENTITY::SET_ENTITY_COLLISION(Object, 1, 0);
				}
			}

			if (back)
			{
				std::int32_t Object = OBJECT::CREATE_OBJECT(ramp, 0.f, 0.f, 0.f, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), 1, 0);
				if (ENTITY::DOES_ENTITY_EXIST(Object))
				{
					ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, veh, 0, 0, -5, 0.3f, 0, 0, 360, 0, 0, 0, 0, 2, 1, 0);
					ENTITY::SET_ENTITY_COLLISION(Object, 1, 0);
				}
			}

			if (left)
			{
				std::int32_t Object = OBJECT::CREATE_OBJECT(ramp, 0.f, 0.f, 0.f, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), 1, 0);
				if (ENTITY::DOES_ENTITY_EXIST(Object))
				{
					ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, veh, 0, -5, 0, 0.3f, 0, 0, -90, 0, 0, 0, 0, 2, 1, 0);
					ENTITY::SET_ENTITY_COLLISION(Object, 1, 0);
				}
			}

			if (right)
			{
				std::int32_t Object = OBJECT::CREATE_OBJECT(ramp, 0.f, 0.f, 0.f, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), 1, 0);
				if (ENTITY::DOES_ENTITY_EXIST(Object))
				{
					ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, veh, 0, 5, 0, 0.3f, 0, 0, 90, 0, 0, 0, 0, 2, 1, 0);
					ENTITY::SET_ENTITY_COLLISION(Object, 1, 0);
				}
			}

		}

	}
	void vehicle_acrobatics(int type)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), true))
		{
			switch (type)
			{
			case 0:
				ENTITY::APPLY_FORCE_TO_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 1, 0.f, 0.f, 7.0f, 0.f, 0.f, 0.f, 0, true, true, true, false, false); //bunny hop
				break;
			case 1:
				ENTITY::APPLY_FORCE_TO_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 1, 0.f, 0.f, 10.0f, -7.f, 0.f, 0.f, 0, true, true, true, false, false); //kickflip
				break;
			case 2:
				ENTITY::APPLY_FORCE_TO_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 1, 0.f, 0.f, 13.0f, 0.f, -6.f, 0.f, 0, true, true, true, false, false); //frontflip
				break;
			case 3:
				ENTITY::APPLY_FORCE_TO_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 1, 0.f, 0.f, 13.0f, 0.f, 6.f, 0.f, 0, true, true, true, false, false); //backflip
				break;
			}
		}
	}
	void SetClouds(const char* cloudtexture)
	{
		MISC::LOAD_CLOUD_HAT(cloudtexture, 3.f);
	}
	void SPMoney(bool add, int value, bool reset)
	{
		for (int i = 0; i < 3; i++)
		{
			char statNameFull[32];
			sprintf_s(statNameFull, "SP%d_TOTAL_CASH", i);
			Hash hash = MISC::GET_HASH_KEY(statNameFull);
			int val;
			STATS::STAT_GET_INT(hash, &val, -1);
			if (add) {
				val += value;
				g_utility.notifyMap("Added Money");
			}
			else {
				val -= value;
				g_utility.notifyMap("Remove Money");
			}
			if (reset) {
				val = 0;
				g_utility.notifyMap("Removed all Money");
			}
			STATS::STAT_SET_INT(hash, val, 1);
		}
	}
	void VehicleManager(bool explodeVehs, bool deleteVehs, bool rainbowVehs, bool maxVehs, bool boostVehs)
	{
		if (explodeVehs || deleteVehs || rainbowVehs || maxVehs || boostVehs)
		{
			const int ElementAmount = 10;
			const int ArrSize = ElementAmount * 2 + 2;

			Vehicle* vehs = new Vehicle[ArrSize];
			vehs[0] = ElementAmount;
			int VehFound = PED::GetPedNearbyVehicles(PLAYER::PLAYER_PED_ID(), vehs);

			for (int i = 0; i < VehFound; i++)
			{
				int OffsetID = i * 2 + 2;
				if (vehs[OffsetID] != PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false))
				{
					g_utility.RequestControlOfEnt(vehs[OffsetID]);
					Vector3 coords = ENTITY::GET_ENTITY_COORDS(vehs[OffsetID], false);
					if (explodeVehs) { FIRE::ADD_EXPLOSION(coords.x, coords.y, coords.z, 0, 1000.f, true, false, 0.f, 0); }
					if (deleteVehs) { ENTITY::SET_ENTITY_COORDS_NO_OFFSET(vehs[OffsetID], 6400.f, 6400.f, 0.f, false, false, false); }
					if (rainbowVehs)
					{
						VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehs[OffsetID], rand() % 255, rand() % 255, rand() % 255);
						VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehs[OffsetID], rand() % 255, rand() % 255, rand() % 255);
					}
					if (boostVehs)
					{
						VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehs[OffsetID], 300.0);
					}
				}
			}
			delete vehs;
		}
	}
	void Ramp()
	{
		Hash model = MISC::GET_HASH_KEY("lts_prop_lts_ramp_01");
		Hash model1 = MISC::GET_HASH_KEY("prop_skate_halfpipe_cr");
		switch (RampIndex)
		{
		case 0:



			for (int i = 0; i < g_RampCount; i++)
			{
				float length2 = 5.4f;
				Vector3 me = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.f, (length2 * i), i);
				Object ramp = OBJECT::CREATE_OBJECT(model, me.x, me.y, me.z - 1.75f, 1, 1, 1);
				ENTITY::SET_ENTITY_HEADING(ramp, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
				g_Ramp.push_back(ramp);
			}

			break;
		case 1:


			float length1 = 9.25f;
			for (int i = 0; i < g_RampCount; i++)
			{
				Vector3 me = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.f, (length1 * i), 0.f);
				Object ramp = OBJECT::CREATE_OBJECT(model1, me.x, me.y, me.z - 1.75f, 1, 1, 1);
				ENTITY::SET_ENTITY_HEADING(ramp, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
				g_Ramp.push_back(ramp);
			}

			break;
		}
	}
	void DeleteRamp()
	{
		for (auto ramp : g_Ramp)
		{
			ENTITY::DELETE_ENTITY(&ramp);
		}
	}
	Vector3 TPCoords;
	void TeleportFunction(Vector3 coords)
	{
		int Handle = PLAYER::PLAYER_PED_ID();
		if (PED::IS_PED_IN_ANY_VEHICLE(Handle, 0))
		{
			ENTITY::SET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_IN(Handle, false), coords.x, coords.y, coords.z, 0, 0, 0, 1);
		}
		else
			ENTITY::SET_ENTITY_COORDS(Handle, coords.x, coords.y, coords.z, 0, 0, 0, 1);

	}
	Vector3 GetBlipIcon()
	{
		static Vector3 zero;
		Vector3 coords;

		bool blipFound = false;
		// search for marker blip
		int blipIterator = HUD::GET_WAYPOINT_BLIP_ENUM_ID();
		for (Blip i = HUD::GET_FIRST_BLIP_INFO_ID(blipIterator); HUD::DOES_BLIP_EXIST(i) != 0; i = HUD::GET_NEXT_BLIP_INFO_ID(blipIterator))
		{
			if (HUD::GET_BLIP_INFO_ID_TYPE(i) == 4)
			{
				coords = HUD::GET_BLIP_INFO_ID_COORD(i);
				blipFound = true;
				break;
			}
		}
		if (blipFound)
		{
			return coords;
		}

		return zero;
	}
	float m_directions[6] = { 5.f, 5.f, 5.f, 5.f, 5.f, 5.f };
	void teleport_direction(int direction) {
		Vector3 coords = { 0.f, 0.f, 0.f };

		switch (direction) {
		case 0:
			coords.y = m_directions[0] + 1.f;
			break;
		case 1:
			coords.y = (m_directions[1] * -1.f) + 1.f;
			break;
		case 2:
			coords.z = m_directions[2] + 1.f;
			break;
		case 3:
			coords.z = (m_directions[3] * -1.f) + 1.f;
			break;
		case 4:
			coords.x = (m_directions[4] * -1.f) + 1.f;
			break;
		case 5:
			coords.x = m_directions[5] + 1.f;
			break;
		}

		Vector3 world = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), coords.x, coords.y, coords.z);
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(PLAYER::PLAYER_PED_ID(), world.x, world.y, world.z, false, false, false);

	}
	bool get_blip_location(Vector3& location, int sprite, int color = -1)
	{
		Blip blip;
		for (blip = HUD::GET_FIRST_BLIP_INFO_ID(sprite); HUD::DOES_BLIP_EXIST(blip) && color != -1 && HUD::GET_BLIP_COLOUR(blip) != color; blip = HUD::GET_NEXT_BLIP_INFO_ID(sprite))
			;

		if (!HUD::DOES_BLIP_EXIST(blip) || (color != -1 && HUD::GET_BLIP_COLOUR(blip) != color))
			return false;

		location = HUD::GET_BLIP_COORDS(blip);

		return true;
	}
	bool get_objective_location(Vector3& location)
	{
		if (get_blip_location(location, (int)BlipIcons::Circle, (int)BlipColors::YellowMission))
			return true;
		if (get_blip_location(location, (int)BlipIcons::Circle, (int)BlipColors::YellowMission2))
			return true;
		if (get_blip_location(location, (int)BlipIcons::Circle, (int)BlipColors::Mission))
			return true;
		if (get_blip_location(location, (int)BlipIcons::RaceFinish, (int)BlipColors::None))
			return true;
		if (get_blip_location(location, (int)BlipIcons::Circle, (int)BlipColors::Green))
			return true;
		if (get_blip_location(location, (int)BlipIcons::Circle, (int)BlipColors::Blue))
			return true;
		if (get_blip_location(location, (int)BlipIcons::CrateDrop))
			return true;

		static const int blips[] = { 1, 57, 128, 129, 130, 143, 144, 145, 146, 271, 286, 287, 288 };
		for (const auto& blip : blips)
		{
			if (get_blip_location(location, blip, 5))
				return true;
		}

		return false;
	}
	void SetRank(int rpvalue)
	{
		if (rpvalue < 0 && rpvalue > 8000)
		{
			rpvalue = 8000;
		}
		STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_XP_FM"), Levels1[rpvalue], 0);
		STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CHAR_XP_FM"), Levels1[rpvalue], 0);

	}
#include <timeapi.h>
	inline int t = 0;
	inline int delay = 100;
	void moneyDrop(bool toggle)
	{
		if (toggle)
		{

			Ped playerped = PLAYER::PLAYER_PED_ID();
			if (!ENTITY::DOES_ENTITY_EXIST(playerped)) return;
			constexpr int CashHash = -1666779307;
			STREAMING::REQUEST_MODEL(CashHash);
			Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0);
			Entity e = OBJECT::CREATE_AMBIENT_PICKUP(0x1E9A99F8, playerPosition.x, playerPosition.y, playerPosition.z + 2, 0, 2500, CashHash, false, true);
			ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&e);

		}
		else
		{

		}

	}
	void DiscordInstruct()
	{
		ShellExecuteA(0, 0, "https://discord.gg/PMgvjW8mgZ", 0, 0, SW_SHOW);
	}
	void join_type(eSessionType session) {

		*ScriptGlobal(2695915).As<int*>() = (session == eSessionType::SC_TV ? 1 : 0);// If SC TV Then Enable Spectator Mode

		if (session == eSessionType::LEAVE_ONLINE)
			*ScriptGlobal(1574589).Add(2).As<int*>() = -1;
		else
			*ScriptGlobal(1575017).As<int*>() = (int)session;

		*ScriptGlobal(1574589).As<int*>() = 1;
		fiber::current()->sleep();
		*ScriptGlobal(1574589).As<int*>() = 0;

	}
	void SpawnVehicle(uint32_t model)
	{
		*ScriptGlobal(4540731).As<bool*>() = 1;
		std::uint32_t l_CurrentVehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		std::float_t _heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
		Vector3 s_coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
		std::float_t s_VehicleSpeed = ENTITY::GET_ENTITY_SPEED(l_CurrentVehicle);
		Vehicle _veh = VEHICLE::CREATE_VEHICLE(model, s_coords.x + 2.f, s_coords.y, s_coords.z, _heading, true, true, true);
		const char* vehname = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(model));
		DECORATOR::DECOR_SET_INT(_veh, "Player_Vehicle", NETWORK::NETWORK_HASH_FROM_PLAYER_HANDLE(PLAYER::PLAYER_ID()));
		DECORATOR::DECOR_SET_INT(_veh, "MPBitset", 0);
		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(_veh);
		VEHICLE::SET_VEHICLE_ENGINE_ON(_veh, true, true, true);
		VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(_veh, 0);

		VEHICLE::SET_VEHICLE_FORWARD_SPEED(_veh, s_VehicleSpeed);

	}
	void Vehicle_Preview_3D(Hash model, Entity vehicle)
	{

		if (GetRenderer()->m_opened == false) {
			ENTITY::DELETE_ENTITY(&vehicle);
			fiber::current()->sleep();
			goto skipTick;
		}

		if (STREAMING::IS_MODEL_VALID(model))
		{
			Ped Player = PLAYER::PLAYER_PED_ID();
			float heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
			if (ENTITY::GET_ENTITY_MODEL(vehicle) == model) {
				float heading = ENTITY::GET_ENTITY_HEADING(vehicle);

				Vector3 Coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Player, 0, 6.0f, 0.5f);
				ENTITY::SET_ENTITY_COORDS(vehicle, Coords.x, Coords.y, Coords.z, false, false, false, false);

				ENTITY::SET_ENTITY_HEADING(vehicle, heading >= 360.f ? 0 : heading + 2.f);
				ENTITY::SET_ENTITY_COLLISION(vehicle, false, false);
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(vehicle, 1);

				goto skipTick;
			}
			else
			{
				ENTITY::DELETE_ENTITY(&vehicle);
			}


			STREAMING::REQUEST_MODEL(model);
			if (!STREAMING::HAS_MODEL_LOADED(model)) goto skipTick;

			Vector3 Coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Player, 0, 6.0f, 0.5f);

			// VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(Veh);
			ENTITY::SET_ENTITY_COLLISION(vehicle, false, false);
			ENTITY::SET_ENTITY_ALPHA(vehicle, 150, 0);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);

		}
		else
		{
			fiber::current()->sleep();
			ENTITY::DELETE_ENTITY(&vehicle);
		}
	skipTick:;
	}
	static bool bReset = true;
	void Spectate(bool toggle)
	{
		if (toggle)
		{
			const auto ped = PLAYER::PLAYER_PED_ID();
			const auto target = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);

			NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(true, target);
			NETWORK::NETWORK_OVERRIDE_RECEIVE_RESTRICTIONS_ALL(false);
			HUD::SET_MINIMAP_IN_SPECTATOR_MODE(true, target);
			HUD::SET_BLIP_ALPHA(HUD::GET_MAIN_PLAYER_BLIP_ID(), 255);

			STREAMING::SET_FOCUS_ENTITY(target);

			bReset = false;
		}
	}
	void Selfloop()
	{
		Godmod(GodMod);
		invisible(Invisible);
		OffRadar(Offradar);
		Alpha();
		SpinBot(Spin);
		NeverWanted(Neverwanted);
		SetWantedLevel();
		fakewanted();
		NoRagodoll(NoRagDoll);
		AlwaysRagdoll(Alwaysragdoll);
		DieOnRagdoll(DieonRagdoll);
		Thermal(thermal);
		Night(night);
		firebreath(FireBreath);
		DeadEye(DeadEyeMotion);
		Handtrails(m_Handtrails);
		GlowManager(glowmanager);
		WalkUnderWater(WalkunderWater);
		WalkOnWater(WalkonWater);
		ModifyWater(ModiffyWater);
		neonLight();
		NoClip(NoclipIterator, g_NoClipSpeed, g_NoClip);
		SuperJump(Superjump);
		BeastJump(Beastjump);
		Ninjajump(NinjaJump);
		FastRun(Fastrun);
		PaintGun(Paintgun);
		moneyGun(MoneyGun);
		ShootWater(WaterShoot);
		//FlamingAmmo(Flame);
		DeadEyeGun(DeadEyegun);
		RainbowCamo(RainBowCamo);
		ForceGun(Forcegun);
		GravityBug(GravityGun);
		EnityGunVehicle(EntityVehicleGun, m_EntityVehicle[m_EntityVehicleIterator], m_VehicleSpawnDistance, m_VehicleLaunchSpeed);
		PropellantGun(BulletSwap, m_PropellantSpawnDistance, m_PropellantHashes[m_EntityPropellantIterator], m_ObjectPropellantSpeed);
		YoinkGun(g_YoinkGun);
		Magnet(m_Magnet);
		RapidFire(m_RapidFire);
		TeleportGun(Teleportgun);
		LaserSight(Laserlight);
		DeleteGun(Deletegun);
		AirstrikeGun(Airstrikegun);
		EntityGunObject(EntityObjectGun, m_EntityObject[m_EntityObjectIterator], m_ObjectSpawnDistance, m_ObjectLaunchSpeed);
		ExplosiveAmmo(Explosivebullet);
		Autofix(AutoFix);
		AutoFlip(Autoflip);
		Driftmode(DriftMode);
		DriveOnWater(DriveonWater);
		DriveUnderWater(DriveunderWater);
		ForceVehicleToGround(ForceVehicletoGround);
		ThreeSixtyVehicle(ThreeSixty);
		EngineAlwaysOn(EngineAlwayson);
		GlitchVehicle(Glitch);
		GlowManager0(ParticleVehicle);
		//VehicleRockets(g_VehicleWeapons, VehicleWeaponHashes[VehicleWeaponIterator], g_WeaponSpeed, g_Lasersight, PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()));
		if (g_BypassSpeed) { ENTITY::SET_ENTITY_MAX_SPEED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 10000000.f); }
		ENTITY::SET_ENTITY_COLLISION(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), g_Collision, true);
		if (InvisibleVehicle) { ENTITY::SET_ENTITY_VISIBLE(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), false, 0); }
		VehicleFly(g_VehicleFly, g_FlySpeed);


		if (g_JumpIterator)
		{
			int veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			switch (g_JumpIterator)
			{
			case 0:
				break;
			case 1:
				if (GetAsyncKeyState(VK_SPACE) & 1 && PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
					ENTITY::APPLY_FORCE_TO_ENTITY(veh, 1, 0 + ENTITY::GET_ENTITY_FORWARD_X(veh), 0 + ENTITY::GET_ENTITY_FORWARD_Y(veh), 10.f, 0, 0, 0, 1, 0, 1, 1, 1, 1);
				}
				break;
			case 2:
				if (GetAsyncKeyState(VK_SPACE) && PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
					ENTITY::APPLY_FORCE_TO_ENTITY(veh, 1, 0 + ENTITY::GET_ENTITY_FORWARD_X(veh), 0 + ENTITY::GET_ENTITY_FORWARD_Y(veh), 0.5f, 0, 0, 0, 1, 0, 1, 1, 1, 1);
				}
				break;
			}
		}
		Seatbelt(g_Seatbelt);
		VehicleInvincible(g_InvincibleVehicle);
		RenderScorched(g_Scorched);
		//HornBoost2(Hornboost2);
		Hornboost(m_Hornboost);
		VehicleManager(m_ExplodeNearVehs, m_DeleteNearVehs, m_RainbowNearVehs, false, m_BoostNearVehs);
		moneyDrop(moneydrop);
		Spectate(spectator);

		if (g_EnableLight)
		{
			Vector3 me = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0);
			GRAPHICS::DRAW_LIGHT_WITH_RANGE(me.x, me.y, me.z - 2, g_LightRed, g_LightGreen, g_LightBlue, 999, g_LigtIntensity);
		}
		if (g_TimeEnable) NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(g_Hour, g_Minute, g_Second);
		if (g_PauseTime) CLOCK::PAUSE_CLOCK(true);
		else CLOCK::PAUSE_CLOCK(false);
	}
}