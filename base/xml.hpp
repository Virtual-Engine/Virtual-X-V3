#include "common.hpp"
#include "invoker/Natives.hpp"
#include "plugixml.hpp"
#include "pugiconfig.hpp"
#include "dirs.h"
using namespace pugi;
namespace VX
{
	inline bool deletePreviousCreation;
	inline bool spawnWithCollision;
	static std::vector<Entity> spoonerSpawnedVehicles;
	static std::vector<Entity> spoonerSpawnedAttachments;
	static std::vector<std::string> fileNames;
	inline int spoonerInitialHandle = 0;
	inline int spoonerVehicleHandle = 0;
	struct SpoonerAttachments {
		struct sVehicleProperties {
			struct sColours {
				int Primary;
				int Secondary;
				int Pearl;
				int Rim;
				int Mod1_a;
				int Mod1_b;
				int Mod1_c;
				int Mod2_a;
				int Mod2_b;
				bool IsPrimaryColourCustom;
				bool IsSecondaryColourCustom;
				int Cust1_R;
				int Cust1_G;
				int Cust1_B;
				int Cust2_R;
				int Cust2_G;
				int Cust2_B;
				int TyreSmoke_R;
				int TyreSmoke_G;
				int TyreSmoke_B;
				int LrInterior;
				int LrDashboard;
			} Colours;

			struct sNeons {
				bool Left;
				bool Right;
				bool Front;
				bool Back;
				int R;
				int G;
				int B;
			} Neons;

			struct sDoorsOpen {
				bool BackLeftDoor;
				bool BackRightDoor;
				bool FrontLeftDoor;
				bool FrontRightDoor;
				bool Hood;
				bool Trunk;
				bool Trunk2;
			} DoorsOpen;

			struct sDoorsBroken {
				bool BackLeftDoor;
				bool BackRightDoor;
				bool FrontLeftDoor;
				bool FrontRightDoor;
				bool Hood;
				bool Trunk;
				bool Trunk2;
			} DoorsBroken;

			struct sTyresBursted {
				bool FrontLeft;
				bool FrontRight;
				bool _2;
				bool _3;
				bool BackLeft;
				bool BackRight;
				bool _6;
				bool _7;
				bool _8;
			} TyresBursted;

			struct sMods {
				std::string _0;
				std::string _1;
				std::string _2;
				std::string _3;
				std::string _4;
				std::string _5;
				std::string _6;
				std::string _7;
				std::string _8;
				std::string _9;
				std::string _10;
				std::string _11;
				std::string _12;
				std::string _13;
				std::string _14;
				std::string _15;
				std::string _16;
				bool _17;
				bool _18;
				bool _19;
				bool _20;
				bool _21;
				bool _22;
				std::string _23;
				std::string _24;
				std::string _25;
				std::string _26;
				std::string _27;
				std::string _28;
				std::string _29;
				std::string _30;
				std::string _31;
				std::string _32;
				std::string _33;
				std::string _34;
				std::string _35;
				std::string _36;
				std::string _37;
				std::string _38;
				std::string _39;
				std::string _40;
				std::string _41;
				std::string _42;
				std::string _43;
				std::string _44;
				std::string _45;
				std::string _46;
				std::string _47;
				std::string _48;
			} Mods;

			int Livery;
			std::string NumberPlateText;
			int NumberPlateIndex;
			int WheelType;
			bool WheensInvisible;
			std::string EngineSoundName;
			int WindowTint;
			bool BulletProofTyres;
			float DirtLevel;
			float PaintFade;
			int RoofState;
			bool SirenActive;
			bool EngineOn;
			int EngineHealth;
			bool LightsOn;
			int IsRadioLoud;
			int LockStatus;
			int RpmMultiplier;
			int TorqueMultiplier;
			int HeadlightIntensity;
		} VehicleProperties;

		struct sPedProperties {
			struct sPedProps {
				std::string _0;
				std::string _1;
				std::string _2;
				std::string _3;
				std::string _4;
				std::string _5;
				std::string _6;
				std::string _7;
				std::string _8;
				std::string _9;
			} PedProps;

			struct sPedComps {
				std::string _0;
				std::string _1;
				std::string _2;
				std::string _3;
				std::string _4;
				std::string _5;
				std::string _6;
				std::string _7;
				std::string _8;
				std::string _9;
				std::string _10;
				std::string _11;
			} PedComps;

			bool IsStill;
			Hash CurrentWeapon;
			bool RelationshipGroupAltered;
			Hash RelationshipGroup;
			bool ScenarioActive;
			bool AnimActive;
			std::string AnimDict;
			std::string AnimName;
		} PedProperties;

		struct sAttachment {
			bool IsAttached;
			int AttachedTo;
			int BoneIndex;
			Vector3 Position;
			Vector3 Rotation;
		} Attachment;

		struct sOriginalPlacement {
			Vector3 Position;
			Vector3 Rotation;
		} Placement;

		int InitialHandle;
		int Handle;
		int Type;
		Hash ModelHash;
		bool Dynamic;
		bool FrozenPosition;
		int OpacityLevel;
		int LodDistance;
		bool IsVisible;
		int MaxHealth;
		int Health;
		bool HasGravity;
		bool IsOnFire;
		bool IsInvincible;
		bool IsBulletProof;
		bool IsCollisionProof;
		bool IsExplosionProof;
		bool IsFireProof;
		bool IsMeleeProof;
		bool IsOnlyDamagedByPlayer;
	};
	inline SpoonerAttachments SpawnEntityFromXmlNode(xml_node node) {
		SpoonerAttachments data;
		data.Type = node.child("Type").text().as_int();
		data.FrozenPosition = node.child("FrozenPos").text().as_bool();
		data.ModelHash = node.child("ModelHash").text().as_uint();
		data.Dynamic = node.child("Dynamic").text().as_bool();
		data.InitialHandle = node.child("InitialHandle").text().as_int();
		data.OpacityLevel = node.child("OpacityLevel").text().as_int();
		data.LodDistance = node.child("LodDistance").text().as_int();
		data.IsVisible = node.child("IsVisible").text().as_bool();
		data.Health = node.child("Health").text().as_int();
		data.MaxHealth = node.child("MaxHealth").text().as_int();
		data.IsOnFire = node.child("IsOnFire").text().as_bool();
		data.IsInvincible = node.child("IsInvincible").text().as_bool();
		data.IsBulletProof = node.child("IsBulletProof").text().as_bool();
		data.IsCollisionProof = node.child("IsCollisionProof").text().as_bool();
		data.IsExplosionProof = node.child("IsExplosionProof").text().as_bool();
		data.IsFireProof = node.child("IsFireProof").text().as_bool();
		data.IsMeleeProof = node.child("IsMeleeProof").text().as_bool();
		data.IsOnlyDamagedByPlayer = node.child("IsOnlyDamagedByPlayer").text().as_bool();
		data.HasGravity = node.child("HasGravity").text().as_bool(true);

		data.Placement.Position =
			Vector3(node.child("PositionRotation").child("X").text().as_float(),
				node.child("PositionRotation").child("Y").text().as_float(),
				node.child("PositionRotation").child("Z").text().as_float());
		data.Placement.Rotation =
			Vector3(node.child("PositionRotation").child("Pitch").text().as_float(),
				node.child("PositionRotation").child("Roll").text().as_float(),
				node.child("PositionRotation").child("Yaw").text().as_float());

		data.Attachment.IsAttached =
			node.child("Attachment").attribute("isAttached").as_bool();
		data.Attachment.BoneIndex =
			node.child("Attachment").child("BoneIndex").text().as_int();
		data.Attachment.Position =
			Vector3(node.child("Attachment").child("X").text().as_float(),
				node.child("Attachment").child("Y").text().as_float(),
				node.child("Attachment").child("Z").text().as_float());
		data.Attachment.Rotation =
			Vector3(node.child("Attachment").child("Pitch").text().as_float(),
				node.child("Attachment").child("Roll").text().as_float(),
				node.child("Attachment").child("Yaw").text().as_float());
		if (node.child("Attachment").child("AttachedTo").text().as_string() == "VEHICLE") {
			data.Attachment.AttachedTo = spoonerVehicleHandle;
		}
		else {
			data.Attachment.AttachedTo =
				node.child("Attachment").child("AttachedTo").text().as_int();
		}
		g_utility.SimpleRequestModel(data.ModelHash);

		switch (data.Type) {
		case 1:
		{ // ped
			data.Handle = PED::CREATE_PED(21,
				data.ModelHash,
				data.Placement.Position.x,
				data.Placement.Position.y,
				data.Placement.Position.z,
				1,
				1,
				0);
			if (ENTITY::DOES_ENTITY_EXIST(data.Handle)) {
				ENTITY::FREEZE_ENTITY_POSITION(data.Handle, data.FrozenPosition);

				PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(data.Handle, false);
				PED::SET_PED_CAN_SWITCH_WEAPON(data.Handle, false);

				//SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(data.Handle, true);
				PED::SET_PED_FLEE_ATTRIBUTES(data.Handle, 0, 0);
				PED::SET_PED_COMBAT_ATTRIBUTES(data.Handle, 17, 1);

				if (data.OpacityLevel < 255)
					ENTITY::SET_ENTITY_ALPHA(data.Handle, data.OpacityLevel, 0);
				ENTITY::SET_ENTITY_LOD_DIST(data.Handle, data.LodDistance);
				ENTITY::SET_ENTITY_VISIBLE(data.Handle, data.IsVisible, 1);

				if (data.MaxHealth)
					ENTITY::SET_ENTITY_MAX_HEALTH(data.Handle, data.MaxHealth);
				if (data.Health)
					ENTITY::SET_ENTITY_HEALTH(data.Handle, data.Health, false);

				ENTITY::SET_ENTITY_INVINCIBLE(data.Handle, data.IsInvincible);
				ENTITY::SET_ENTITY_PROOFS(data.Handle, data.IsBulletProof, data.IsFireProof, data.IsExplosionProof, data.IsCollisionProof, data.IsMeleeProof, 1, 1, 1);
				ENTITY::SET_ENTITY_ONLY_DAMAGED_BY_PLAYER(data.Handle, data.IsOnlyDamagedByPlayer);

				auto pedProperties = node.child("PedProperties");

				if (pedProperties.child("IsStill").text().as_bool()) {
					TASK::TASK_STAND_STILL(data.Handle, -1);
				}

				if (pedProperties.child("CanRagdoll"))
					PED::SET_PED_CAN_RAGDOLL(
						data.Handle,
						pedProperties.child("CanRagdoll").text().as_bool());

				if (pedProperties.child("HasShortHeight").text().as_bool()) {
					// *reinterpret_cast<byte*>(PoolManager::GetEntityAddress(data.Handle) + 0x8A) = 100;
				}

				PED::SET_PED_ARMOUR(data.Handle,
					pedProperties.child("Armour").text().as_int());

				if (pedProperties.child("CurrentWeapon")) {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(
						data.Handle,
						pedProperties.child("CurrentWeapon").text().as_uint(),
						9999,
						1);
				}

				if (pedProperties.child("PedProps")) {
					for (auto nodeProps = pedProperties.child("PedProps").first_child(); nodeProps;
						nodeProps = nodeProps.next_sibling()) {
						int modType = std::stoi(std::string(nodeProps.name()).substr(1));
						std::string modValueStr = nodeProps.text().as_string();
						if (modValueStr.find(",") != std::string::npos) {
							//stoi(modValueStr.substr(0, modValueStr.find(","))) ------- stoi(modValueStr.substr(modValueStr.find(",") + 1))
						}
					}
				}

				if (pedProperties.child("PedComps")) {
					for (auto nodeComps = pedProperties.child("PedComps").first_child(); nodeComps;
						nodeComps = nodeComps.next_sibling()) {
						int modType = std::stoi(std::string(nodeComps.name()).substr(1));
						std::string modValueStr = nodeComps.text().as_string();
						if (modValueStr.find(",") != std::string::npos) {
							PED::SET_PED_COMPONENT_VARIATION(
								data.Handle,
								modType,
								stoi(modValueStr.substr(0, modValueStr.find(","))),
								stoi(modValueStr.substr(modValueStr.find(",") + 1)),
								0);
						}
					}
				}

				if (pedProperties.child("RelationshipGroupAltered").text().as_bool()) {
					PED::SET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(
						data.Handle,
						pedProperties.child("RelationshipGroup").text().as_uint());
				}

				if (pedProperties.child("ScenarioActive").text().as_bool()) {
					TASK::TASK_START_SCENARIO_IN_PLACE(
						data.Handle,
						(char*)pedProperties.child("ScenarioName").text().as_string(),
						0,
						1);
				}

				if (pedProperties.child("AnimActive").text().as_bool()) {
					char* animDict =
						(char*)pedProperties.child("AnimDict").text().as_string();
					char* animName =
						(char*)pedProperties.child("AnimName").text().as_string();

					STREAMING::REQUEST_ANIM_DICT(animDict);
					TASK::TASK_PLAY_ANIM(data.Handle, animDict, animName, 8, 0, -1, 9, 0, 0, 0, 0);
				}
			}
			break;
		}
		case 2:
		{ // vehicle
			data.Handle = VEHICLE::CREATE_VEHICLE(data.ModelHash,
				data.Placement.Position.x,
				data.Placement.Position.y,
				data.Placement.Position.z,
				1,
				1,
				data.Dynamic,
				1);
			if (ENTITY::DOES_ENTITY_EXIST(data.Handle)) {
				ENTITY::FREEZE_ENTITY_POSITION(data.Handle, data.FrozenPosition);

				VEHICLE::SET_VEHICLE_MOD_KIT(data.Handle, 0);
				if (data.OpacityLevel < 255)
					ENTITY::SET_ENTITY_ALPHA(data.Handle, data.OpacityLevel, 0);
				ENTITY::SET_ENTITY_LOD_DIST(data.Handle, data.LodDistance);
				ENTITY::SET_ENTITY_VISIBLE(data.Handle, data.IsVisible, 1);

				if (data.MaxHealth)
					ENTITY::SET_ENTITY_MAX_HEALTH(data.Handle, data.MaxHealth);
				if (data.Health)
					ENTITY::SET_ENTITY_HEALTH(data.Handle, data.Health, false);

				VEHICLE::SET_VEHICLE_GRAVITY(data.Handle, data.HasGravity);


				ENTITY::SET_ENTITY_INVINCIBLE(data.Handle, data.IsInvincible);
				ENTITY::SET_ENTITY_PROOFS(data.Handle, data.IsBulletProof, data.IsFireProof, data.IsExplosionProof, data.IsCollisionProof, data.IsMeleeProof, 1, 1, 1);
				ENTITY::SET_ENTITY_ONLY_DAMAGED_BY_PLAYER(data.Handle, data.IsOnlyDamagedByPlayer);

				auto vehicleProperties = node.child("VehicleProperties");

				VEHICLE::SET_VEHICLE_LIVERY(
					data.Handle,
					vehicleProperties.child("Livery").text().as_int());

				auto vehicleColors = vehicleProperties.child("Colours");

				int currentPrimaryColor, currentSecondaryColor;
				VEHICLE::GET_VEHICLE_COLOURS(data.Handle, &currentPrimaryColor, &currentSecondaryColor);
				VEHICLE::SET_VEHICLE_COLOURS(
					data.Handle,
					vehicleColors.child("Primary").text().as_int(),
					currentSecondaryColor);
				VEHICLE::GET_VEHICLE_COLOURS(data.Handle, &currentPrimaryColor, &currentSecondaryColor);
				VEHICLE::SET_VEHICLE_COLOURS(
					data.Handle,
					currentPrimaryColor,
					vehicleColors.child("Secondary").text().as_int());

				int currentPearlescentColor, currentWheelColor;
				VEHICLE::GET_VEHICLE_EXTRA_COLOURS(data.Handle, &currentPearlescentColor, &currentWheelColor);
				VEHICLE::SET_VEHICLE_EXTRA_COLOURS(
					data.Handle,
					vehicleColors.child("Pearl").text().as_int(),
					currentWheelColor);
				VEHICLE::GET_VEHICLE_EXTRA_COLOURS(data.Handle, &currentPearlescentColor, &currentWheelColor);
				VEHICLE::SET_VEHICLE_EXTRA_COLOURS(
					data.Handle,
					currentPearlescentColor,
					vehicleColors.child("Rim").text().as_int());

				bool isPrimaryColourCustom =
					vehicleColors.child("IsPrimaryColourCustom").text().as_bool();
				bool isSecondaryColourCustom =
					vehicleColors.child("IsSecondaryColourCustom").text().as_bool();

			RGBA vehicleColor;

				if (isPrimaryColourCustom) {
					vehicleColor.r = vehicleColors.child("Cust1_R").text().as_int();
					vehicleColor.g = vehicleColors.child("Cust1_G").text().as_int();
					vehicleColor.b = vehicleColors.child("Cust1_B").text().as_int();
					VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(data.Handle,
						vehicleColor.r,
						vehicleColor.g,
						vehicleColor.b);
				}

				if (isSecondaryColourCustom) {
					vehicleColor.r = vehicleColors.child("Cust2_R").text().as_int();
					vehicleColor.g = vehicleColors.child("Cust2_G").text().as_int();
					vehicleColor.b = vehicleColors.child("Cust2_B").text().as_int();
					VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(data.Handle,
						vehicleColor.r,
						vehicleColor.g,
						vehicleColor.b);
				}

				vehicleColor.r = vehicleColors.child("tyreSmoke_R").text().as_int();
				vehicleColor.g = vehicleColors.child("tyreSmoke_G").text().as_int();
				vehicleColor.b = vehicleColors.child("tyreSmoke_B").text().as_int();
				VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(data.Handle,
					vehicleColor.r,
					vehicleColor.g,
					vehicleColor.b);

				int mod1a = vehicleColors.child("Mod1_a").text().as_int();
				int mod1b = vehicleColors.child("Mod1_b").text().as_int();
				int mod1c = vehicleColors.child("Mod1_c").text().as_int();
				VEHICLE::SET_VEHICLE_MOD_COLOR_1(data.Handle, mod1a, mod1b, mod1c);

				int mod2a = vehicleColors.child("Mod2_a").text().as_int();
				int mod2b = vehicleColors.child("Mod2_b").text().as_int();
				VEHICLE::SET_VEHICLE_MOD_COLOR_2(data.Handle, mod2a, mod2b);

				VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(
					data.Handle,
					(char*)vehicleProperties.child("NumberPlateText").text().as_string());
				VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(
					data.Handle,
					vehicleProperties.child("NumberPlateIndex").text().as_int());
				VEHICLE::SET_VEHICLE_WHEEL_TYPE(
					data.Handle,
					vehicleProperties.child("WheelType").text().as_int());

				std::string engineSoundName =
					vehicleProperties.child("EngineSoundName").text().as_string();
				//if (!engineSoundName.empty()) _FORCE_VEHICLE_ENGINE_AUDIO(data.Handle, (char*)engineSoundName.c_str());

				VEHICLE::SET_VEHICLE_WINDOW_TINT(
					data.Handle,
					vehicleProperties.child("WindowTint").text().as_int());
				VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(
					data.Handle,
					!vehicleProperties.child("BulletProofTyres").text().as_bool());
				VEHICLE::SET_VEHICLE_DIRT_LEVEL(
					data.Handle,
					vehicleProperties.child("DirtLevel").text().as_float());
				VEHICLE::SET_VEHICLE_ENVEFF_SCALE(
					data.Handle,
					vehicleProperties.child("PaintFade").text().as_float());

				switch (vehicleProperties.child("RoofState").text().as_int()) {
				case 0:
				case 3:
					VEHICLE::RAISE_CONVERTIBLE_ROOF(data.Handle, false);
					break;
				case 2:
				case 1:
					VEHICLE::LOWER_CONVERTIBLE_ROOF(data.Handle, false);
					break;
				}

				VEHICLE::SET_VEHICLE_SIREN(
					data.Handle,
					vehicleProperties.child("SirenActive").text().as_bool());

				if (vehicleProperties.child("EngineOn"))
					VEHICLE::SET_VEHICLE_ENGINE_ON(
						data.Handle,
						vehicleProperties.child("EngineOn").text().as_bool(),
						true,
						0);
				if (vehicleProperties.child("EngineHealth"))
					VEHICLE::SET_VEHICLE_ENGINE_HEALTH(
						data.Handle,
						vehicleProperties.child("EngineHealth").text().as_int());

				if (vehicleProperties.child("LightsOn"))
					VEHICLE::SET_VEHICLE_LIGHTS(
						data.Handle,
						vehicleProperties.child("LightsOn").text().as_bool() ? 3 : 4);
				if (vehicleProperties.child("IsRadioLoud").text().as_int(0)) {
					AUDIO::SET_VEHICLE_RADIO_LOUD(
						data.Handle,
						vehicleProperties.child("IsRadioLoud").text().as_bool());
					AUDIO::SET_VEHICLE_RADIO_ENABLED(data.Handle, true);
				}

				VEHICLE::SET_VEHICLE_DOORS_LOCKED(
					data.Handle,
					vehicleProperties.child("LockStatus").text().as_int());

				auto vehicleNeons = vehicleProperties.child("Neons");

				VEHICLE::SET_VEHICLE_NEON_ENABLED(
					data.Handle,
					0,
					vehicleNeons.child("Left").text().as_bool());
				VEHICLE::SET_VEHICLE_NEON_ENABLED(
					data.Handle,
					1,
					vehicleNeons.child("Right").text().as_bool());
				VEHICLE::SET_VEHICLE_NEON_ENABLED(
					data.Handle,
					2,
					vehicleNeons.child("Front").text().as_bool());
				VEHICLE::SET_VEHICLE_NEON_ENABLED(
					data.Handle,
					3,
					vehicleNeons.child("Back").text().as_bool());
				VEHICLE::SET_VEHICLE_NEON_COLOUR(data.Handle,
					vehicleNeons.child("R").text().as_int(),
					vehicleNeons.child("G").text().as_int(),
					vehicleNeons.child("B").text().as_int());

				auto vehicleModExtras = vehicleProperties.child("ModExtras");

				for (auto nodeVehicleModExtrasObject = vehicleModExtras.first_child(); nodeVehicleModExtrasObject;
					nodeVehicleModExtrasObject = nodeVehicleModExtrasObject.next_sibling()) {
					VEHICLE::SET_VEHICLE_EXTRA(
						data.Handle,
						std::stoi(std::string(nodeVehicleModExtrasObject.name()).substr(1)),
						!nodeVehicleModExtrasObject.text().as_bool());
				}

				auto vehicleMods = vehicleProperties.child("Mods");

				for (auto nodeVehicleModsObject = vehicleMods.first_child(); nodeVehicleModsObject;
					nodeVehicleModsObject = nodeVehicleModsObject.next_sibling()) {
					int modType = stoi(std::string(nodeVehicleModsObject.name()).substr(1));
					std::string modValueStr = nodeVehicleModsObject.text().as_string();
					if (modValueStr.find(",") == std::string::npos) {
						VEHICLE::TOGGLE_VEHICLE_MOD(data.Handle,
							modType,
							nodeVehicleModsObject.text().as_bool());
					}
					else {
						VEHICLE::SET_VEHICLE_MOD(
							data.Handle,
							modType,
							stoi(modValueStr.substr(0, modValueStr.find(","))),
							stoi(modValueStr.substr(modValueStr.find(",") + 1)) ? true : false);
					}
				}

				auto vehicleDoorsOpen = vehicleProperties.child("DoorsOpen");

				if (vehicleDoorsOpen) {
					if (vehicleDoorsOpen.child("BackLeftDoor").text().as_bool()) {
						VEHICLE::SET_VEHICLE_DOOR_OPEN(data.Handle, 2, false, true);
						AUDIO::PLAY_VEHICLE_DOOR_OPEN_SOUND(data.Handle, 1);
					}
					else {
						VEHICLE::SET_VEHICLE_DOOR_SHUT(data.Handle, 2, true);
						AUDIO::PLAY_VEHICLE_DOOR_CLOSE_SOUND(data.Handle, 1);
					}

					if (vehicleDoorsOpen.child("BackRightDoor").text().as_bool()) {
						VEHICLE::SET_VEHICLE_DOOR_OPEN(data.Handle, 3, false, true);
						AUDIO::PLAY_VEHICLE_DOOR_OPEN_SOUND(data.Handle, 1);
					}
					else {
						VEHICLE::SET_VEHICLE_DOOR_SHUT(data.Handle, 3, true);
						AUDIO::PLAY_VEHICLE_DOOR_CLOSE_SOUND(data.Handle, 1);
					}

					if (vehicleDoorsOpen.child("FrontLeftDoor").text().as_bool()) {
						VEHICLE::SET_VEHICLE_DOOR_OPEN(data.Handle, 0, false, true);
						AUDIO::PLAY_VEHICLE_DOOR_OPEN_SOUND(data.Handle, 1);
					}
					else {
						VEHICLE::SET_VEHICLE_DOOR_SHUT(data.Handle, 0, true);
						AUDIO::PLAY_VEHICLE_DOOR_CLOSE_SOUND(data.Handle, 1);
					}

					if (vehicleDoorsOpen.child("FrontRightDoor").text().as_bool()) {
						VEHICLE::SET_VEHICLE_DOOR_OPEN(data.Handle, 1, false, true);
						AUDIO::PLAY_VEHICLE_DOOR_OPEN_SOUND(data.Handle, 1);
					}
					else {
						VEHICLE::SET_VEHICLE_DOOR_SHUT(data.Handle, 1, true);
						AUDIO::PLAY_VEHICLE_DOOR_CLOSE_SOUND(data.Handle, 1);
					}

					if (vehicleDoorsOpen.child("Hood").text().as_bool()) {
						VEHICLE::SET_VEHICLE_DOOR_OPEN(data.Handle, 4, false, true);
						AUDIO::PLAY_VEHICLE_DOOR_OPEN_SOUND(data.Handle, 1);
					}
					else {
						VEHICLE::SET_VEHICLE_DOOR_SHUT(data.Handle, 4, true);
						AUDIO::PLAY_VEHICLE_DOOR_CLOSE_SOUND(data.Handle, 1);
					}

					if (vehicleDoorsOpen.child("Trunk").text().as_bool()) {
						VEHICLE::SET_VEHICLE_DOOR_OPEN(data.Handle, 5, false, true);
						AUDIO::PLAY_VEHICLE_DOOR_OPEN_SOUND(data.Handle, 1);
					}
					else {
						VEHICLE::SET_VEHICLE_DOOR_SHUT(data.Handle, 5, true);
						AUDIO::PLAY_VEHICLE_DOOR_CLOSE_SOUND(data.Handle, 1);
					}

					if (vehicleDoorsOpen.child("Trunk2").text().as_bool()) {
						VEHICLE::SET_VEHICLE_DOOR_OPEN(data.Handle, 6, false, true);
						AUDIO::PLAY_VEHICLE_DOOR_OPEN_SOUND(data.Handle, 1);
					}
					else {
						VEHICLE::SET_VEHICLE_DOOR_SHUT(data.Handle, 6, true);
						AUDIO::PLAY_VEHICLE_DOOR_CLOSE_SOUND(data.Handle, 1);
					}
				}

				auto vehicleDoorsBroken = vehicleProperties.child("DoorsBroken");

				if (vehicleDoorsBroken) {
					if (vehicleDoorsBroken.child("BackLeftDoor").text().as_bool()) {
						VEHICLE::SET_VEHICLE_DOOR_BROKEN(data.Handle, 2, true);
					}

					if (vehicleDoorsBroken.child("BackRightDoor").text().as_bool()) {
						VEHICLE::SET_VEHICLE_DOOR_BROKEN(data.Handle, 3, true);
					}

					if (vehicleDoorsBroken.child("FrontLeftDoor").text().as_bool()) {
						VEHICLE::SET_VEHICLE_DOOR_BROKEN(data.Handle, 0, true);
					}

					if (vehicleDoorsBroken.child("FrontRightDoor").text().as_bool()) {
						VEHICLE::SET_VEHICLE_DOOR_BROKEN(data.Handle, 1, true);
					}

					if (vehicleDoorsBroken.child("Hood").text().as_bool()) {
						VEHICLE::SET_VEHICLE_DOOR_BROKEN(data.Handle, 4, true);
					}

					if (vehicleDoorsBroken.child("Trunk").text().as_bool()) {
						VEHICLE::SET_VEHICLE_DOOR_BROKEN(data.Handle, 5, true);
					}

					if (vehicleDoorsBroken.child("Trunk2").text().as_bool()) {
						VEHICLE::SET_VEHICLE_DOOR_BROKEN(data.Handle, 6, true);
					}
				}

				auto vehicleTyresBursted = vehicleProperties.child("TyresBursted");

				if (vehicleTyresBursted) {
					if (vehicleTyresBursted.child("FrontLeft").text().as_bool()) {
						if (!VEHICLE::GET_VEHICLE_TYRES_CAN_BURST(data.Handle))
							VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(data.Handle, true);
						VEHICLE::SET_VEHICLE_TYRE_BURST(data.Handle, 0, 1, 1000.f);
					}

					if (vehicleTyresBursted.child("FrontRight").text().as_bool()) {
						if (!VEHICLE::GET_VEHICLE_TYRES_CAN_BURST(data.Handle))
							VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(data.Handle, true);
						VEHICLE::SET_VEHICLE_TYRE_BURST(data.Handle, 1, 1, 1000.f);
					}

					if (vehicleTyresBursted.child("_2").text().as_bool()) {
						if (!VEHICLE::GET_VEHICLE_TYRES_CAN_BURST(data.Handle))
							VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(data.Handle, true);
						VEHICLE::SET_VEHICLE_TYRE_BURST(data.Handle, 2, 1, 1000.f);
					}

					if (vehicleTyresBursted.child("_3").text().as_bool()) {
						if (!VEHICLE::GET_VEHICLE_TYRES_CAN_BURST(data.Handle))
							VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(data.Handle, true);
						VEHICLE::SET_VEHICLE_TYRE_BURST(data.Handle, 3, 1, 1000.f);
					}

					if (vehicleTyresBursted.child("BackLeft").text().as_bool()) {
						if (!VEHICLE::GET_VEHICLE_TYRES_CAN_BURST(data.Handle))
							VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(data.Handle, true);
						VEHICLE::SET_VEHICLE_TYRE_BURST(data.Handle, 4, 1, 1000.f);
					}

					if (vehicleTyresBursted.child("BackRight").text().as_bool()) {
						if (!VEHICLE::GET_VEHICLE_TYRES_CAN_BURST(data.Handle))
							VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(data.Handle, true);
						VEHICLE::SET_VEHICLE_TYRE_BURST(data.Handle, 5, 1, 1000.f);
					}

					if (vehicleTyresBursted.child("_6").text().as_bool()) {
						if (!VEHICLE::GET_VEHICLE_TYRES_CAN_BURST(data.Handle))
							VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(data.Handle, true);
						VEHICLE::SET_VEHICLE_TYRE_BURST(data.Handle, 6, 1, 1000.f);
					}

					if (vehicleTyresBursted.child("_7").text().as_bool()) {
						if (!VEHICLE::GET_VEHICLE_TYRES_CAN_BURST(data.Handle))
							VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(data.Handle, true);
						VEHICLE::SET_VEHICLE_TYRE_BURST(data.Handle, 7, 1, 1000.f);
					}

					if (vehicleTyresBursted.child("_8").text().as_bool()) {
						if (!VEHICLE::GET_VEHICLE_TYRES_CAN_BURST(data.Handle))
							VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(data.Handle, true);
						VEHICLE::SET_VEHICLE_TYRE_BURST(data.Handle, 8, 1, 1000.f);
					}
				}

				auto vehicleRpmMultiplier = vehicleProperties.child("RpmMultiplier");
				auto vehicleTorqueMultiplier = vehicleProperties.child("TorqueMultiplier");
				auto vehicleMaxSpeed = vehicleProperties.child("MaxSpeed");
				auto vehicleHeadlightIntensity = vehicleProperties.child("HeadlightIntensity");

				if (vehicleRpmMultiplier) {
					VEHICLE::MODIFY_VEHICLE_TOP_SPEED(
						data.Handle,
						vehicleRpmMultiplier.text().as_float());
				}

				if (vehicleTorqueMultiplier) {
					VEHICLE::SET_VEHICLE_CHEAT_POWER_INCREASE(
						data.Handle,
						vehicleTorqueMultiplier.text().as_float());
				}

				if (vehicleMaxSpeed) {
					ENTITY::SET_ENTITY_MAX_SPEED(data.Handle,
						vehicleMaxSpeed.text().as_float());
				}

				if (vehicleHeadlightIntensity) {
					VEHICLE::SET_VEHICLE_LIGHT_MULTIPLIER(
						data.Handle,
						vehicleHeadlightIntensity.text().as_float());
				}
			}
			break;
		}
		case 3:
		{ // object

			data.Handle = OBJECT::CREATE_OBJECT(data.ModelHash,
				data.Placement.Position.x,
				data.Placement.Position.y,
				data.Placement.Position.z,
				1,
				1,
				data.Dynamic);
			if (ENTITY::DOES_ENTITY_EXIST(data.Handle)) {
				ENTITY::FREEZE_ENTITY_POSITION(data.Handle, data.FrozenPosition);

				if (data.OpacityLevel < 255)
					ENTITY::SET_ENTITY_ALPHA(data.Handle, data.OpacityLevel, 0);
				ENTITY::SET_ENTITY_LOD_DIST(data.Handle, data.LodDistance);
				ENTITY::SET_ENTITY_VISIBLE(data.Handle, data.IsVisible, 1);

				if (data.MaxHealth)
					ENTITY::SET_ENTITY_MAX_HEALTH(data.Handle, data.MaxHealth);
				if (data.Health)
					ENTITY::SET_ENTITY_HEALTH(data.Handle, data.Health, false);


				ENTITY::SET_ENTITY_INVINCIBLE(data.Handle, data.IsInvincible);
				ENTITY::SET_ENTITY_PROOFS(data.Handle, data.IsBulletProof, data.IsFireProof, data.IsExplosionProof, data.IsCollisionProof, data.IsMeleeProof, 1, 1, 1);

				ENTITY::SET_ENTITY_ONLY_DAMAGED_BY_PLAYER(data.Handle, data.IsOnlyDamagedByPlayer);
			}
			break;
		}
		}

		spoonerSpawnedAttachments.push_back(data.Handle);

		return data;
	}
	inline void LoadSpoonerFile(std::string fileName) { // LoadSpoonerFile("CoolCreation");
		ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), true, true);

		if (deletePreviousCreation) {
			for (auto& e : spoonerSpawnedVehicles) {
				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(e, 1, 1);
				ENTITY::DELETE_ENTITY(&e);
			}

			for (auto& e : spoonerSpawnedAttachments) {
				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(e, 1, 1);
				ENTITY::DELETE_ENTITY(&e);
			}
		}

		spoonerVehicleHandle = 0;
		spoonerInitialHandle = 0;

		xml_document doc;

		if (doc.load_file(
			va("%s/%s.xml", util::dirs::get_directories()->get_xml(), fileName.c_str()))
			.status
			!= pugi::status_ok) {
			return;
		}


		auto root = doc.child("Vehicle");
		if (root) {
			Hash vehicleHash = root.child("ModelHash").text().as_uint();
			spoonerInitialHandle = root.child("InitialHandle").text().as_int();

			g_utility.SimpleRequestModel(vehicleHash);

			Vector3 myCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0);

			float forward = 5.f;
			float playerHeading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());

			float xVect = forward * sin(g_math.deg_to_rad(playerHeading)) * -1.0f;
			float yVect = forward * cos(g_math.deg_to_rad(playerHeading));


			spoonerVehicleHandle = VEHICLE::CREATE_VEHICLE(vehicleHash,
				myCoords.x + xVect,
				myCoords.y + yVect,
				myCoords.z,
				playerHeading,
				true,
				true,
				true);

			spoonerSpawnedVehicles.push_back(spoonerVehicleHandle);

			DECORATOR::DECOR_SET_INT(spoonerVehicleHandle, "MPBitset", 0);
			VEHICLE::SET_VEHICLE_IS_STOLEN(spoonerVehicleHandle, false);

			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) {
				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0), 1, 1);
			}

			PED::SET_PED_INTO_VEHICLE(PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0), spoonerVehicleHandle, -1);
			VEHICLE::SET_VEHICLE_MOD_KIT(spoonerVehicleHandle, 0);

			PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), spoonerVehicleHandle, -1);

			int opacityLevel = root.child("OpacityLevel").text().as_int();
			if (opacityLevel < 255)
				ENTITY::SET_ENTITY_ALPHA(spoonerVehicleHandle, opacityLevel, 0);
			ENTITY::SET_ENTITY_LOD_DIST(spoonerVehicleHandle,
				root.child("LodDistance").text().as_int());

			if (!root.child("IsVisible").text().as_bool()) {
				//ENTITY::SET_ENTITY_ALPHA(spoonerVehicleHandle, 255, false);
				ENTITY::SET_ENTITY_VISIBLE(spoonerVehicleHandle, false, 1);
			}

			if (root.child("MaxHealth"))
				ENTITY::SET_ENTITY_MAX_HEALTH(spoonerVehicleHandle,
					root.child("MaxHealth").text().as_int());
			if (root.child("Health"))
				ENTITY::SET_ENTITY_HEALTH(spoonerVehicleHandle,
					root.child("Health").text().as_int(),
					false);

			VEHICLE::SET_VEHICLE_GRAVITY(spoonerVehicleHandle,
				root.child("HasGravity").text().as_bool(true));


			ENTITY::SET_ENTITY_INVINCIBLE(spoonerVehicleHandle,
				root.child("IsInvincible").text().as_bool());
			ENTITY::SET_ENTITY_PROOFS(spoonerVehicleHandle,
				root.child("IsBulletProof").text().as_bool(),
				root.child("IsFireProof").text().as_bool(),
				root.child("IsExplosionProof").text().as_bool(),
				root.child("IsCollisionProof").text().as_bool(),
				root.child("IsMeleeProof").text().as_bool(),
				1,
				1,
				1);
			ENTITY::SET_ENTITY_ONLY_DAMAGED_BY_PLAYER(
				spoonerVehicleHandle,
				root.child("IsOnlyDamagedByPlayer").text().as_bool());

			auto vehicleProperties = root.child("VehicleProperties");

			VEHICLE::SET_VEHICLE_LIVERY(spoonerVehicleHandle,
				vehicleProperties.child("Livery").text().as_int());

			auto vehicleColors = vehicleProperties.child("Colours");

			int currentPrimaryColor, currentSecondaryColor;
			VEHICLE::GET_VEHICLE_COLOURS(spoonerVehicleHandle, &currentPrimaryColor, &currentSecondaryColor);
			VEHICLE::SET_VEHICLE_COLOURS(spoonerVehicleHandle,
				vehicleColors.child("Primary").text().as_int(),
				currentSecondaryColor);
			VEHICLE::GET_VEHICLE_COLOURS(spoonerVehicleHandle, &currentPrimaryColor, &currentSecondaryColor);
			VEHICLE::SET_VEHICLE_COLOURS(spoonerVehicleHandle,
				currentPrimaryColor,
				vehicleColors.child("Secondary").text().as_int());

			int currentPearlescentColor, currentWheelColor;
			VEHICLE::GET_VEHICLE_EXTRA_COLOURS(spoonerVehicleHandle, &currentPearlescentColor, &currentWheelColor);
			VEHICLE::SET_VEHICLE_EXTRA_COLOURS(
				spoonerVehicleHandle,
				vehicleColors.child("Pearl").text().as_int(),
				currentWheelColor);
			VEHICLE::GET_VEHICLE_EXTRA_COLOURS(spoonerVehicleHandle, &currentPearlescentColor, &currentWheelColor);
			VEHICLE::SET_VEHICLE_EXTRA_COLOURS(spoonerVehicleHandle,
				currentPearlescentColor,
				vehicleColors.child("Rim").text().as_int());

			bool isPrimaryColourCustom =
				vehicleColors.child("IsPrimaryColourCustom").text().as_bool();
			bool isSecondaryColourCustom =
				vehicleColors.child("IsSecondaryColourCustom").text().as_bool();

			RGBA vehicleColor;

			if (isPrimaryColourCustom) {
				vehicleColor.r = vehicleColors.child("Cust1_R").text().as_int();
				vehicleColor.g = vehicleColors.child("Cust1_G").text().as_int();
				vehicleColor.b = vehicleColors.child("Cust1_B").text().as_int();
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(spoonerVehicleHandle,
					vehicleColor.r,
					vehicleColor.g,
					vehicleColor.b);
			}

			if (isSecondaryColourCustom) {
				vehicleColor.r = vehicleColors.child("Cust2_R").text().as_int();
				vehicleColor.g = vehicleColors.child("Cust2_G").text().as_int();
				vehicleColor.b = vehicleColors.child("Cust2_B").text().as_int();
				VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(spoonerVehicleHandle,
					vehicleColor.r,
					vehicleColor.g,
					vehicleColor.b);
			}

			vehicleColor.r = vehicleColors.child("tyreSmoke_R").text().as_int();
			vehicleColor.g = vehicleColors.child("tyreSmoke_G").text().as_int();
			vehicleColor.b = vehicleColors.child("tyreSmoke_B").text().as_int();
			VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(spoonerVehicleHandle,
				vehicleColor.r,
				vehicleColor.g,
				vehicleColor.b);

			int mod1a = vehicleColors.child("Mod1_a").text().as_int();
			int mod1b = vehicleColors.child("Mod1_b").text().as_int();
			int mod1c = vehicleColors.child("Mod1_c").text().as_int();
			VEHICLE::SET_VEHICLE_MOD_COLOR_1(spoonerVehicleHandle, mod1a, mod1b, mod1c);

			int mod2a = vehicleColors.child("Mod2_a").text().as_int();
			int mod2b = vehicleColors.child("Mod2_b").text().as_int();
			VEHICLE::SET_VEHICLE_MOD_COLOR_2(spoonerVehicleHandle, mod2a, mod2b);

			VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(
				spoonerVehicleHandle,
				(char*)vehicleProperties.child("NumberPlateText").text().as_string());
			VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(
				spoonerVehicleHandle,
				vehicleProperties.child("NumberPlateIndex").text().as_int());
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(
				spoonerVehicleHandle,
				vehicleProperties.child("WheelType").text().as_int());

			std::string engineSoundName =
				vehicleProperties.child("EngineSoundName").text().as_string();
			//if (!engineSoundName.empty()) _FORCE_VEHICLE_ENGINE_AUDIO(spoonerVehicleHandle, (char*)engineSoundName.c_str());

			VEHICLE::SET_VEHICLE_WINDOW_TINT(
				spoonerVehicleHandle,
				vehicleProperties.child("WindowTint").text().as_int());
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(
				spoonerVehicleHandle,
				!vehicleProperties.child("BulletProofTyres").text().as_bool());
			VEHICLE::SET_VEHICLE_DIRT_LEVEL(
				spoonerVehicleHandle,
				vehicleProperties.child("DirtLevel").text().as_float());
			VEHICLE::SET_VEHICLE_ENVEFF_SCALE(
				spoonerVehicleHandle,
				vehicleProperties.child("PaintFade").text().as_float());

			switch (vehicleProperties.child("RoofState").text().as_int()) {
			case 0:
			case 3:
				VEHICLE::RAISE_CONVERTIBLE_ROOF(spoonerVehicleHandle, false);
				break;
			case 2:
			case 1:
				VEHICLE::LOWER_CONVERTIBLE_ROOF(spoonerVehicleHandle, false);
				break;
			}

			VEHICLE::SET_VEHICLE_SIREN(
				spoonerVehicleHandle,
				vehicleProperties.child("SirenActive").text().as_bool());

			if (vehicleProperties.child("EngineOn"))
				VEHICLE::SET_VEHICLE_ENGINE_ON(
					spoonerVehicleHandle,
					vehicleProperties.child("EngineOn").text().as_bool(),
					true,
					0);
			if (vehicleProperties.child("EngineHealth"))
				VEHICLE::SET_VEHICLE_ENGINE_HEALTH(
					spoonerVehicleHandle,
					vehicleProperties.child("EngineHealth").text().as_int());

			if (vehicleProperties.child("LightsOn"))
				VEHICLE::SET_VEHICLE_LIGHTS(
					spoonerVehicleHandle,
					vehicleProperties.child("LightsOn").text().as_bool() ? 3 : 4);
			if (vehicleProperties.child("IsRadioLoud").text().as_int(0)) {
				AUDIO::SET_VEHICLE_RADIO_LOUD(
					spoonerVehicleHandle,
					vehicleProperties.child("IsRadioLoud").text().as_bool());
				AUDIO::SET_VEHICLE_RADIO_ENABLED(spoonerVehicleHandle, true);
			}

			VEHICLE::SET_VEHICLE_DOORS_LOCKED(
				spoonerVehicleHandle,
				vehicleProperties.child("LockStatus").text().as_bool());

			auto vehicleNeons = vehicleProperties.child("Neons");

			VEHICLE::SET_VEHICLE_NEON_ENABLED(spoonerVehicleHandle,
				0,
				vehicleNeons.child("Left").text().as_bool());
			VEHICLE::SET_VEHICLE_NEON_ENABLED(spoonerVehicleHandle,
				1,
				vehicleNeons.child("Right").text().as_bool());
			VEHICLE::SET_VEHICLE_NEON_ENABLED(spoonerVehicleHandle,
				2,
				vehicleNeons.child("Front").text().as_bool());
			VEHICLE::SET_VEHICLE_NEON_ENABLED(spoonerVehicleHandle,
				3,
				vehicleNeons.child("Back").text().as_bool());
			VEHICLE::SET_VEHICLE_NEON_COLOUR(spoonerVehicleHandle,
				vehicleNeons.child("R").text().as_int(),
				vehicleNeons.child("G").text().as_int(),
				vehicleNeons.child("B").text().as_int());

			auto vehicleModExtras = vehicleProperties.child("ModExtras");

			for (auto nodeVehicleModExtrasObject = vehicleModExtras.first_child(); nodeVehicleModExtrasObject;
				nodeVehicleModExtrasObject = nodeVehicleModExtrasObject.next_sibling()) {
				VEHICLE::SET_VEHICLE_EXTRA(
					spoonerVehicleHandle,
					std::stoi(std::string(nodeVehicleModExtrasObject.name()).substr(1)),
					!nodeVehicleModExtrasObject.text().as_bool());
			}

			auto vehicleMods = vehicleProperties.child("Mods");

			for (auto nodeVehicleModsObject = vehicleMods.first_child(); nodeVehicleModsObject;
				nodeVehicleModsObject = nodeVehicleModsObject.next_sibling()) {
				int modType = std::stoi(std::string(nodeVehicleModsObject.name()).substr(1));
				std::string modValueStr = nodeVehicleModsObject.text().as_string();
				if (modValueStr.find(",") == std::string::npos) {
					VEHICLE::TOGGLE_VEHICLE_MOD(spoonerVehicleHandle,
						modType,
						nodeVehicleModsObject.text().as_bool());
				}
				else {
					VEHICLE::SET_VEHICLE_MOD(
						spoonerVehicleHandle,
						modType,
						stoi(modValueStr.substr(0, modValueStr.find(","))) ? true : false,
						stoi(modValueStr.substr(modValueStr.find(",") + 1)) ? true : false);
				}
			}

			auto vehicleDoorsOpen = vehicleProperties.child("DoorsOpen");

			if (vehicleDoorsOpen) {
				if (vehicleDoorsOpen.child("BackLeftDoor").text().as_bool()) {
					VEHICLE::SET_VEHICLE_DOOR_OPEN(spoonerVehicleHandle, 2, false, true);
					AUDIO::PLAY_VEHICLE_DOOR_OPEN_SOUND(spoonerVehicleHandle, 1);
				}
				else {
					VEHICLE::SET_VEHICLE_DOOR_SHUT(spoonerVehicleHandle, 2, true);
					AUDIO::PLAY_VEHICLE_DOOR_CLOSE_SOUND(spoonerVehicleHandle, 1);
				}

				if (vehicleDoorsOpen.child("BackRightDoor").text().as_bool()) {
					VEHICLE::SET_VEHICLE_DOOR_OPEN(spoonerVehicleHandle, 3, false, true);
					AUDIO::PLAY_VEHICLE_DOOR_OPEN_SOUND(spoonerVehicleHandle, 1);
				}
				else {
					VEHICLE::SET_VEHICLE_DOOR_SHUT(spoonerVehicleHandle, 3, true);
					AUDIO::PLAY_VEHICLE_DOOR_CLOSE_SOUND(spoonerVehicleHandle, 1);
				}

				if (vehicleDoorsOpen.child("FrontLeftDoor").text().as_bool()) {
					VEHICLE::SET_VEHICLE_DOOR_OPEN(spoonerVehicleHandle, 0, false, true);
					AUDIO::PLAY_VEHICLE_DOOR_OPEN_SOUND(spoonerVehicleHandle, 1);
				}
				else {
					VEHICLE::SET_VEHICLE_DOOR_SHUT(spoonerVehicleHandle, 0, true);
					AUDIO::PLAY_VEHICLE_DOOR_CLOSE_SOUND(spoonerVehicleHandle, 1);
				}

				if (vehicleDoorsOpen.child("FrontRightDoor").text().as_bool()) {
					VEHICLE::SET_VEHICLE_DOOR_OPEN(spoonerVehicleHandle, 1, false, true);
					AUDIO::PLAY_VEHICLE_DOOR_OPEN_SOUND(spoonerVehicleHandle, 1);
				}
				else {
					VEHICLE::SET_VEHICLE_DOOR_SHUT(spoonerVehicleHandle, 1, true);
					AUDIO::PLAY_VEHICLE_DOOR_CLOSE_SOUND(spoonerVehicleHandle, 1);
				}

				if (vehicleDoorsOpen.child("Hood").text().as_bool()) {
					VEHICLE::SET_VEHICLE_DOOR_OPEN(spoonerVehicleHandle, 4, false, true);
					AUDIO::PLAY_VEHICLE_DOOR_OPEN_SOUND(spoonerVehicleHandle, 1);
				}
				else {
					VEHICLE::SET_VEHICLE_DOOR_SHUT(spoonerVehicleHandle, 4, true);
					AUDIO::PLAY_VEHICLE_DOOR_CLOSE_SOUND(spoonerVehicleHandle, 1);
				}

				if (vehicleDoorsOpen.child("Trunk").text().as_bool()) {
					VEHICLE::SET_VEHICLE_DOOR_OPEN(spoonerVehicleHandle, 5, false, true);
					AUDIO::PLAY_VEHICLE_DOOR_OPEN_SOUND(spoonerVehicleHandle, 1);
				}
				else {
					VEHICLE::SET_VEHICLE_DOOR_SHUT(spoonerVehicleHandle, 5, true);
					AUDIO::PLAY_VEHICLE_DOOR_CLOSE_SOUND(spoonerVehicleHandle, 1);
				}

				if (vehicleDoorsOpen.child("Trunk2").text().as_bool()) {
					VEHICLE::SET_VEHICLE_DOOR_OPEN(spoonerVehicleHandle, 6, false, true);
					AUDIO::PLAY_VEHICLE_DOOR_OPEN_SOUND(spoonerVehicleHandle, 1);
				}
				else {
					VEHICLE::SET_VEHICLE_DOOR_SHUT(spoonerVehicleHandle, 6, true);
					AUDIO::PLAY_VEHICLE_DOOR_CLOSE_SOUND(spoonerVehicleHandle, 1);
				}
			}

			auto vehicleDoorsBroken = vehicleProperties.child("DoorsBroken");

			if (vehicleDoorsBroken) {
				if (vehicleDoorsBroken.child("BackLeftDoor").text().as_bool()) {
					VEHICLE::SET_VEHICLE_DOOR_BROKEN(spoonerVehicleHandle, 2, true);
				}

				if (vehicleDoorsBroken.child("BackRightDoor").text().as_bool()) {
					VEHICLE::SET_VEHICLE_DOOR_BROKEN(spoonerVehicleHandle, 3, true);
				}

				if (vehicleDoorsBroken.child("FrontLeftDoor").text().as_bool()) {
					VEHICLE::SET_VEHICLE_DOOR_BROKEN(spoonerVehicleHandle, 0, true);
				}

				if (vehicleDoorsBroken.child("FrontRightDoor").text().as_bool()) {
					VEHICLE::SET_VEHICLE_DOOR_BROKEN(spoonerVehicleHandle, 1, true);
				}

				if (vehicleDoorsBroken.child("Hood").text().as_bool()) {
					VEHICLE::SET_VEHICLE_DOOR_BROKEN(spoonerVehicleHandle, 4, true);
				}

				if (vehicleDoorsBroken.child("Trunk").text().as_bool()) {
					VEHICLE::SET_VEHICLE_DOOR_BROKEN(spoonerVehicleHandle, 5, true);
				}

				if (vehicleDoorsBroken.child("Trunk2").text().as_bool()) {
					VEHICLE::SET_VEHICLE_DOOR_BROKEN(spoonerVehicleHandle, 6, true);
				}
			}

			auto vehicleTyresBursted = vehicleProperties.child("TyresBursted");

			if (vehicleTyresBursted) {
				if (vehicleTyresBursted.child("FrontLeft").text().as_bool()) {
					if (!VEHICLE::GET_VEHICLE_TYRES_CAN_BURST(spoonerVehicleHandle))
						VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(spoonerVehicleHandle, true);
					VEHICLE::SET_VEHICLE_TYRE_BURST(spoonerVehicleHandle, 0, 1, 1000.f);
				}

				if (vehicleTyresBursted.child("FrontRight").text().as_bool()) {
					if (!VEHICLE::GET_VEHICLE_TYRES_CAN_BURST(spoonerVehicleHandle))
						VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(spoonerVehicleHandle, true);
					VEHICLE::SET_VEHICLE_TYRE_BURST(spoonerVehicleHandle, 1, 1, 1000.f);
				}

				if (vehicleTyresBursted.child("_2").text().as_bool()) {
					if (!VEHICLE::GET_VEHICLE_TYRES_CAN_BURST(spoonerVehicleHandle))
						VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(spoonerVehicleHandle, true);
					VEHICLE::SET_VEHICLE_TYRE_BURST(spoonerVehicleHandle, 2, 1, 1000.f);
				}

				if (vehicleTyresBursted.child("_3").text().as_bool()) {
					if (!VEHICLE::GET_VEHICLE_TYRES_CAN_BURST(spoonerVehicleHandle))
						VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(spoonerVehicleHandle, true);
					VEHICLE::SET_VEHICLE_TYRE_BURST(spoonerVehicleHandle, 3, 1, 1000.f);
				}

				if (vehicleTyresBursted.child("BackLeft").text().as_bool()) {
					if (!VEHICLE::GET_VEHICLE_TYRES_CAN_BURST(spoonerVehicleHandle))
						VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(spoonerVehicleHandle, true);
					VEHICLE::SET_VEHICLE_TYRE_BURST(spoonerVehicleHandle, 4, 1, 1000.f);
				}

				if (vehicleTyresBursted.child("BackRight").text().as_bool()) {
					if (!VEHICLE::GET_VEHICLE_TYRES_CAN_BURST(spoonerVehicleHandle))
						VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(spoonerVehicleHandle, true);
					VEHICLE::SET_VEHICLE_TYRE_BURST(spoonerVehicleHandle, 5, 1, 1000.f);
				}

				if (vehicleTyresBursted.child("_6").text().as_bool()) {
					if (!VEHICLE::GET_VEHICLE_TYRES_CAN_BURST(spoonerVehicleHandle))
						VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(spoonerVehicleHandle, true);
					VEHICLE::SET_VEHICLE_TYRE_BURST(spoonerVehicleHandle, 6, 1, 1000.f);
				}

				if (vehicleTyresBursted.child("_7").text().as_bool()) {
					if (!VEHICLE::GET_VEHICLE_TYRES_CAN_BURST(spoonerVehicleHandle))
						VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(spoonerVehicleHandle, true);
					VEHICLE::SET_VEHICLE_TYRE_BURST(spoonerVehicleHandle, 7, 1, 1000.f);
				}

				if (vehicleTyresBursted.child("_8").text().as_bool()) {
					if (!VEHICLE::GET_VEHICLE_TYRES_CAN_BURST(spoonerVehicleHandle))
						VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(spoonerVehicleHandle, true);
					VEHICLE::SET_VEHICLE_TYRE_BURST(spoonerVehicleHandle, 8, 1, 1000.f);
				}
			}

			auto vehicleRpmMultiplier = vehicleProperties.child("RpmMultiplier");
			auto vehicleTorqueMultiplier = vehicleProperties.child("TorqueMultiplier");
			auto vehicleMaxSpeed = vehicleProperties.child("MaxSpeed");
			auto vehicleHeadlightIntensity = vehicleProperties.child("HeadlightIntensity");

			if (vehicleRpmMultiplier) {
				VEHICLE::MODIFY_VEHICLE_TOP_SPEED(spoonerVehicleHandle,
					vehicleRpmMultiplier.text().as_float());
			}

			if (vehicleTorqueMultiplier) {
				VEHICLE::SET_VEHICLE_CHEAT_POWER_INCREASE(
					spoonerVehicleHandle,
					vehicleTorqueMultiplier.text().as_float());
			}

			if (vehicleMaxSpeed) {
				ENTITY::SET_ENTITY_MAX_SPEED(spoonerVehicleHandle,
					vehicleMaxSpeed.text().as_float());
			}

			if (vehicleHeadlightIntensity) {
				VEHICLE::SET_VEHICLE_LIGHT_MULTIPLIER(
					spoonerVehicleHandle,
					vehicleHeadlightIntensity.text().as_float());
			}
		}
		else {
			return;
		}

		auto attachments = root.child("SpoonerAttachments");
		if (attachments) {
			std::vector<Hash> usedModels;
			std::vector<SpoonerAttachments> attachmentData;

			for (auto nodeAttachment = attachments.first_child(); nodeAttachment;
				nodeAttachment = nodeAttachment.next_sibling()) {
				g_utility.SimpleRequestModel(
					nodeAttachment.child("ModelHash").text().as_uint());
				if (nodeAttachment.child("Type").text().as_int() == 1) { // ped
					if (nodeAttachment.child("PedProperties")
						.child("AnimActive")
						.text()
						.as_bool()) {
						STREAMING::REQUEST_ANIM_DICT(
							(char*)nodeAttachment.child("PedProperties")
							.child("AnimDict")
							.text()
							.as_string());
					}
				}

				usedModels.push_back(nodeAttachment.child("ModelHash").text().as_uint());
			}

			for (auto nodeAttachment = attachments.first_child(); nodeAttachment;
				nodeAttachment = nodeAttachment.next_sibling()) {
				SpoonerAttachments e = SpawnEntityFromXmlNode(nodeAttachment);
				attachmentData.push_back(e);
			}

			if (!spoonerInitialHandle) {
				for (auto& e : attachmentData) {
					ENTITY::ATTACH_ENTITY_TO_ENTITY(e.Handle,
						spoonerVehicleHandle,
						e.Attachment.BoneIndex,
						e.Attachment.Position.x,
						e.Attachment.Position.y,
						e.Attachment.Position.z,
						e.Attachment.Rotation.x,
						e.Attachment.Rotation.y,
						e.Attachment.Rotation.z,
						1,
						0,
						spawnWithCollision,
						1,
						2,
						1,
						false);
				}
			}
			else {
				SpoonerAttachments temp;
				temp.Handle = spoonerVehicleHandle;
				temp.InitialHandle = spoonerInitialHandle; // ?
				attachmentData.push_back(temp);

				for (auto& e : attachmentData) {
					if (e.Attachment.IsAttached) {
						for (auto& b : attachmentData) {
							if (e.Handle != b.Handle && e.Attachment.AttachedTo == b.InitialHandle) {
								/*---->*/ ENTITY::ATTACH_ENTITY_TO_ENTITY(
									e.Handle,
									b.Handle,
									e.Attachment.BoneIndex,
									e.Attachment.Position.x,
									e.Attachment.Position.y,
									e.Attachment.Position.z,
									e.Attachment.Rotation.x,
									e.Attachment.Rotation.y,
									e.Attachment.Rotation.z,
									1,
									0,
									spawnWithCollision,
									1,
									2,
									1,
									false);
								break;
							}
						}
					}
				}
			}
			for (auto& e : usedModels) {
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(e);
			}
			for (auto& e : attachmentData) {
				ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&e.Handle);
			}
		}

	}
}