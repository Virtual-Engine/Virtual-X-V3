#include "common.hpp"
#include "ui/interface.hpp"

namespace VX
{

	Vector2 m_positionWeaponPV;
	void Scaleform_Weapon(Hash hash)
	{

	}
	void DisplayWeapon(std::string texture1, std::string texture2)
	{
		float VehBannerWidth = 0.13f;
		float VehBannerHeight = 0.045f;
		RGBA line{ 255, 255, 255, 255 };
		float lineX = { GetRenderer()->m_menu_pos.x - 0.19f };
		float lineY = 0.2451f;

		GetRenderer()->draw_rect({ 0, 0, 0, 255 }, Vector2(m_positionWeaponPV.x + 0.60f, 0.1870f), Vector2(0.180f, 0.165f));
		GetRenderer()->Spriter(texture1, texture2, m_positionWeaponPV.x + 0.60f, 0.1870f, 0.180f, 0.165f, 0, 255, 255, 255, 255);
	}
	struct WeaponPreview {
		Hash hashWeapon;
		const char* WeaponPreviewDict;
		const char* WeaponName;
		const char* name;
	};
	WeaponPreview WeaponPreviews[]{
	{ 0x92A27487, "mpkillquota", "weapon_dagger", "dagger"},
	{ 0x958A4A8F, "mpkillquota", "weapon_bat" , "bat"},
	{ 0xF9E6AA4B, "mpkillquota", "weapon_bottle", "bottle"},
	{ 0x84BD7BFD, "mpkillquota", "weapon_crowbar", "crowbar"},
	{ 0x8BB05FD7, "mpkillquota", "weapon_flashlight", "flashlight"},
	{ 0x440E4788, "mpkillquota", "weapon_golfclub", "golfclub"},
	{ 0x4E875F73, "mpkillquota", "weapon_Hammer", "Hammer"},
	{ 0xF9DCBF2D, "mpkillquota", "weapon_hatchet","Hatchet"},
	{ 0xD8DF3C3C, "mpkillquota", "weapon_knuckles","Knuckles"},
	{ 0x99B507EA, "mpkillquota", "weapon_knife","knife"},
	{ 0xDD5DF8D9, "mpkillquota", "weapon_machete","machete"},
	{ 0xDFE37640, "mpkillquota", "weapon_switchbaled","switchblade"},
	{ 0x678B81B1, "mpkillquota", "weapon_nightstick","nightstick"},
	{ 0x19044EE0, "mpkillquota", "weapon_wrench","wrench"},
	{ 0xCD274149, "mpkillquota", "weapon_battleaxe","battleaxe"},
	{ 0x94117305, "mpkillquota", "weapon_poolcue","poolcue"},
	{ 0x3813FC08, "mpkillquota", "weapon_stone_hatchet","stone hatchet"},
	{ 0x6589186A, "mpkillquota", "weapon_candycane", "candycane"},

	//Pistol	
	{ 0x1B06D571,"mpkillquota", "weapon_pistol", "Pistol"},
	{ 0xBFE256D4,"mpkillquota", "weapon_pistol_mk2", "Pistol MK2"},
	{ 0x5EF9FEC4,"mpkillquota", "weapon_combatpistol", "Combat Pistol"},
	{ 0x22D8FE39,"mpkillquota", "weapon_appistol", "AP Pistol"},
	{ 0x3656C8C1,"mpkillquota", "weapon_stungun", "Stun Gun"},
	{ 0x99AEEB3B,"mpkillquota", "weapon_pistol50", "Pistol 50"},
	{ 0xBFD21232,"mpkillquota", "weapon_snspistol", "SNS Pistol"},
	{ 0x88374054,"mpkillquota", "weapon_snspistol_mk2", "SNS Pistol MK2"},
	{ 0xD205520E,"mpkillquota", "weapon_heavypistol", "Heavy Pistol"},
	{ 0x83839C4,"mpkillquota",  "weapon_vintagepistol", "Vintage Pistol"},
	{ 0x47757124,"mpkillquota", "weapon_flaregun", "Flare Gun"},
	{ 0xDC4DB296,"mpkillquota", "weapon_marksmanpistol", "Marksman Pistol"},
	{ 0xC1B3C3D1,"mpkillquota", "weapon_revolver", "Heavy Revolver"},
	{ 0xCB96392F,"mpkillquota", "weapon_revolver_mk2", "Heavy Revolver MK2"},
	{ 0x97EA20B8,"mpkillquota", "weapon_doubleaction", "Double Action Revolver"},
	{ 0xAF3696A1,"mpkillquota", "weapon_raypistol", "Up-n-Atomizer"},
	{ 0x2B5EF5EC,"mpkillquota", "weapon_ceramicpistol", "Ceramic Pistol"},
	{ 0x917F6C8C,"mpkillquota", "weapon_navyrevolver", "Navy Revolver"},
	{ 0x57A4368C,"mpkillquota", "weapon_gadgetpistol", "Perico Pistol"},
	{ 0x1BC4FDB9,"mpkillquota", "weapon_pistolxm3", "WM 29 Pistol"},

	//SMG
	{ 0x13532244,"mpkillquota", "weapon_miscrosmg", "Micro SMG"},
	{ 0x2BE6766B, "mpkillquota", "weapon_smg","SMG"},
	{ 0x78A97CD0, "mpkillquota", "weapon_smg_mk2","SMG MK2"},
	{ 0xEFE7E2DF, "mpkillquota", "weapon_assaultsmg","Assault SMG"},
	{ 0x0A3D4D34, "mpkillquota", "weapon_combatpdw","Combat PDW"},
	{ 0xDB1AA450, "mpkillquota", "weapon_machinepistol","Machine Pistol"},
	{ 0xBD248B55, "mpkillquota", "weapon_minismg","Mini SMG"},
	{ 0x476BF155, "mpkillquota", "weapon_raycarbine","Unholy Hellbringer"},
	{ 0x14E5AFD5, "mpkillquota", "weapon_tecpistol","Tactical SMG"},

	//Shotguns
	{ 0x1D073A89, "mpkillquota", "weapon_pumpshotgun","Pump"},
	{ 0x555AF99A, "mpkillquota", "weapon_pumpshotgun_mk2","Pump MK2"},
	{ 0x7846A318, "mpkillquota", "weapon_sawnoffshotgun","Sawed-Off"},
	{ 0xE284C527, "mpkillquota", "weapon_assaultshotgun","Assault"},
	{ 0x9D61E50F, "mpkillquota", "weapon_bullpupshotgun","Bullpup"},
	{ 0xA89CB99E, "mpkillquota", "weapon_musket","Musket"},
	{ 0x3AABBBAA, "mpkillquota", "weapon_heavyshotgun","Heavy Shotguns"},
	{ 0xEF951FBB, "mpkillquota", "weapon_dbshotgun","Double Barrel"},
	{ 0x12E82D3D, "mpkillquota", "weapon_autoshotgun","Sweeper"},
	{ 0x5A96BA4,  "mpkillquota", "weapon_combatshotgun","Combat"},

	//Assault Rifles
	{ 0xBFEFFF6D, "mpkillquota", "weapon_assaultrifle", "Assault Rifle"},
	{ 0x394F415C, "mpkillquota", "weapon_assaultrifle_mk2", "Assault Rifle MK2"},
	{ 0x83BF0278, "mpkillquota", "weapon_carbinerifle", "Carbine Rifle"},
	{ 0xFAD1F1C9, "mpkillquota", "weapon_carbinerifle_mk2", "Carbine Rifle MK2"},
	{ 0xAF113F99, "mpkillquota", "weapon_advancedrifle", "Advanced Rifle"},
	{ 0xC0A3098D, "mpkillquota", "weapon_specialcarbine", "Special Carbine"},
	{ 0x969C3D67, "mpkillquota", "weapon_specialcarbine_mk2", "Special Carbine MK2"},
	{ 0x7F229F94, "mpkillquota", "weapon_bullpuprifle", "Bullpup Rifle"},
	{ 0x84D6FAFD, "mpkillquota", "weapon_bullpuprifle_mk2", "Bullpup Rifle MK2"},
	{ 0x624FE830, "mpkillquota", "weapon_compactrifle", "Compact Rifle"},
	{ 0x9D1F17E6, "mpkillquota", "weapon_militaryrifle", "Military Rifle"},
	{ 0xC78D71B4, "mpkillquota", "weapon_heavyrifle", "Heavy Rifle"},
	{ 0xD1D5F52B, "mpkillquota", "weapon_tacticalrifle", "Tactical Rifle"},

	//Machine guns
	{ 0x9D07F764, "mpkillquota", "weapon_mg","MG"},
	{ 0x7FD62962, "mpkillquota", "weapon_combatmg","Combat MG"},
	{ 0xDBBD7280, "mpkillquota", "weapon_combatmg_mk2","Combat MG MK2"},
	{ 0x61012683, "mpkillquota", "weapon_gusenberg","Gusenberg Sweeper"},

	//Sniper Rifles
	{ 0x05FC3C11, "mpkillquota", "weapon_sniperrifle","Sniper Rifle"},
	{ 0x0C472FE2, "mpkillquota", "weapon_heavysniper","Heavy Sniper"},
	{ 0xA914799, "mpkillquota", "weapon_heavysniper_mk2","Heavy Sniper MK2"},
	{ 0xC734385A, "mpkillquota", "weapon_marksmanrifle","Marksman Rifle"},
	{ 0x6A6C02E0, "mpkillquota", "weapon_marksmanrifle_mk2","Marksman Rifle MK2"},
	{ 0x6E7DDDEC, "mpkillquota", "weapon_precisionrifle","Precision Rifle"},

	//Heavy
	{ 0xB1CA77B1, "mpkillquota", "weapon_rpg","RPG"},
	{ 0xA284510B, "mpkillquota", "weapon_grenadelauncher","Grenade Launcher"},
	{ 0x4DD2DC56, "mpkillquota", "weapon_grenadelauncher_smoke","Grenade Launcher Smoke"},
	{ 0x42BF8A85, "mpkillquota", "weapon_minigun","Minigun"},
	{ 0x7F7497E5, "mpkillquota", "weapon_firework","Firework Launcher"},
	{ 0x6D544C99, "mpkillquota", "weapon_railgun","Railgun"},
	{ 0x63AB0442, "mpkillquota", "weapon_hominglauncher","Homing Launcher"},
	{ 0x0781FE4A, "mpkillquota", "weapon_compactlauncher","Compact Grenade Launcher"},
	{ 0xB62D1F67, "mpkillquota", "weapon_rayminigun","Widowmaker"},
	{ 0xDB26713A, "mpkillquota", "weapon_emplauncher","Compact EMP Launcher"},
	{ 0xFEA23564, "mpkillquota", "weapon_railgunxm3","Railgun"},

	//Throwables
	{ 0x93E220BD, "mpkillquota", "weapon_grenade","Grenade" },
	{ 0xA0973D5E, "mpkillquota", "weapon_bzgas","BZ Gas" },
	{ 0xFDBC8A50, "mpkillquota", "weapon_smokegrenade","Smoke grenade" },
	{ 0x497FACC3, "mpkillquota", "weapon_flare","Flare" },
	{ 0x24B17070, "mpkillquota", "weapon_molotov","Molotov" },
	{ 0x2C3731D9, "mpkillquota", "weapon_stickybomb","Sticky Bomb" },
	{ 0xAB564B93, "mpkillquota", "weapon_proximine","Proximine" },
	{ 0x787F0BB, "mpkillquota", "weapon_snowball","Snowball" },
	{ 0xBA45E8B8, "mpkillquota", "weapon_pipebomb","PipeBomb" },
	{ 0x23C9F95C, "mpkillquota", "weapon_ball","Ball" },

	//Miscellaneous
	{ 0x34A67B97, "mpkillquota", "weapon_petrolcan","Jerry Can" },
	{ 0xFBAB5776, "mpkillquota", "gadget_parachute","Parachute" },
	{ 0x060EC506, "mpkillquota", "weapon_fireextinguisher","Fire Extinguisher" },
	{ 0xBA536372, "mpkillquota", "weapon_hazardcan","Hazardous Jerry Can" },
	{ 0x184140A1, "mpkillquota", "weapon_fertilizercan","Fertilizer Can" },
	};
	struct Weapon {
		Hash hashWeapon;
		const char* m_name;
	};
	Weapon WeaponV2[]{
	{ 0x92A27487, "dagger"},
	{ 0x958A4A8F, "bat"},
	{ 0xF9E6AA4B, "bottle"},
	{ 0x84BD7BFD, "crowbar"},
	{ 0x8BB05FD7, "flashlight"},
	{ 0x440E4788, "golfclub"},
	{ 0x4E875F73, "Hammer"},
	{ 0xF9DCBF2D, "Hatchet"},
	{ 0xD8DF3C3C, "Knuckles"},
	{ 0x99B507EA, "knife"},
	{ 0xDD5DF8D9, "machete"},
	{ 0xDFE37640, "switchblade"},
	{ 0x678B81B1, "nightstick"},
	{ 0x19044EE0, "wrench"},
	{ 0xCD274149, "battleaxe"},
	{ 0x94117305, "poolcue"},
	{ 0x3813FC08, "stone hatchet"},
	{ 0x6589186A, "candycane"},


	};
	struct WeaponPS {
		Hash hashWeaponV2P;
		const char* m_nameV2P;
	};
	WeaponPS WeaponV2PS[] =
	{
		//Pistol
		{ 0x1B06D571, "Pistol"},
		{ 0xBFE256D4, "Pistol MK2"},
		{ 0x5EF9FEC4, "Combat Pistol"},
		{ 0x22D8FE39, "AP Pistol"},
		{ 0x3656C8C1, "Stun Gun"},
		{ 0x99AEEB3B, "Pistol 50"},
		{ 0xBFD21232, "SNS Pistol"},
		{ 0x88374054, "SNS Pistol MK2"},
		{ 0xD205520E, "Heavy Pistol"},
		{ 0x83839C4, "Vintage Pistol"},
		{ 0x47757124, "Flare Gun"},
		{ 0xDC4DB296, "Marksman Pistol"},
		{ 0xC1B3C3D1, "Heavy Revolver"},
		{ 0xCB96392F, "Heavy Revolver MK2"},
		{ 0x97EA20B8, "Double Action Revolver"},
		{ 0xAF3696A1, "Up-n-Atomizer"},
		{ 0x2B5EF5EC, "Ceramic Pistol"},
		{ 0x917F6C8C, "Navy Revolver"},
		{ 0x57A4368C, "Perico Pistol"},
		{ 0x1BC4FDB9, "WM 29 Pistol"},
	};
	struct WeaponSMG {
		Hash hashWeaponV2SMG;
		const char* m_nameV2SMG;
	};
	WeaponSMG WeaponV2SMG[] = {
		{ 0x13532244, "Micro SMG"},
		{ 0x2BE6766B, "SMG"},
		{ 0x78A97CD0, "SMG MK2"},
		{ 0xEFE7E2DF, "Assault SMG"},
		{ 0x0A3D4D34, "Combat PDW"},
		{ 0xDB1AA450, "Machine Pistol"},
		{ 0xBD248B55, "Mini SMG"},
		{ 0x476BF155, "Unholy Hellbringer"},
		{ 0x14E5AFD5, "Tactical SMG"},
	};
	struct WeaponSHG {
		Hash hashWeaponV2SHG;
		const char* m_nameV2SHG;
	};
	WeaponSHG WeaponV2SHG[] = {
		{ 0x1D073A89, "Pump"},
		{ 0x555AF99A, "Pump MK2"},
		{ 0x7846A318, "Sawed-Off"},
		{ 0xE284C527, "Assault"},
		{ 0x9D61E50F, "Bullpup"},
		{ 0xA89CB99E, "Musket"},
		{ 0x3AABBBAA, "Heavy Shotguns"},
		{ 0xEF951FBB, "Double Barrel"},
		{ 0x12E82D3D, "Sweeper"},
		{ 0x5A96BA4,  "Combat"},
	};
	struct WeaponAR {
		Hash hashWeaponV2AR;
		const char* m_nameV2AR;
	};
	WeaponAR WeaponV2AR[] = {
		{ 0xBFEFFF6D, "Assault Rifle"},
		{ 0x394F415C, "Assault Rifle MK2"},
		{ 0x83BF0278, "Carbine Rifle"},
		{ 0xFAD1F1C9, "Carbine Rifle MK2"},
		{ 0xAF113F99, "Advanced Rifle"},
		{ 0xC0A3098D, "Special Carbine"},
		{ 0x969C3D67, "Special Carbine MK2"},
		{ 0x7F229F94, "Bullpup Rifle"},
		{ 0x84D6FAFD, "Bullpup Rifle MK2"},
		{ 0x624FE830, "Compact Rifle"},
		{ 0x9D1F17E6, "Military Rifle"},
		{ 0xC78D71B4, "Heavy Rifle"},
		{ 0xD1D5F52B, "Tactical Rifle"},
	};
	struct WeaponMG {
		Hash hashWeaponV2MG;
		const char* m_nameV2MG;
	};
	WeaponMG WeaponV2MG[] = {
		{ 0x9D07F764, "MG"},
		{ 0x7FD62962, "Combat MG"},
		{ 0xDBBD7280, "Combat MG MK2"},
		{ 0x61012683, "Gusenberg Sweeper"},
	};
	struct WeaponSP {
		Hash hashWeaponV2SP;
		const char* m_nameV2SP;
	};
	WeaponSP WeaponV2SP[] = {
		{ 0x05FC3C11, "Sniper Rifle"},
		{ 0x0C472FE2, "Heavy Sniper"},
		{ 0xA914799, "Heavy Sniper MK2"},
		{ 0xC734385A, "Marksman Rifle"},
		{ 0x6A6C02E0, "Marksman Rifle MK2"},
		{ 0x6E7DDDEC, "Precision Rifle"},
	};
	struct WeaponHV {
		Hash hashWeaponV2HV;
		const char* m_nameV2HV;
	};
	WeaponHV WeaponV2HV[] = {
		{ 0xB1CA77B1, "RPG"},
		{ 0xA284510B, "Grenade Launcher"},
		{ 0x4DD2DC56, "Grenade Launcher Smoke"},
		{ 0x42BF8A85, "Minigun"},
		{ 0x7F7497E5, "Firework Launcher"},
		{ 0x6D544C99, "Railgun"},
		{ 0x63AB0442, "Homing Launcher"},
		{ 0x0781FE4A, "Compact Grenade Launcher"},
		{ 0xB62D1F67, "Widowmaker"},
		{ 0xDB26713A, "Compact EMP Launcher"},
		{ 0xFEA23564, "Railgun"},
	};
	struct WeaponTH {
		Hash hashWeaponV2TH;
		const char* m_nameV2TH;
	};
	WeaponTH WeaponV2TH[] = {
		{ 0x93E220BD, "Grenade"},
		{ 0xA0973D5E, "BZ Gas"},
		{ 0xFDBC8A50, "Smoke grenade"},
		{ 0x497FACC3, "Flare"},
		{ 0x24B17070, "Molotov"},
		{ 0x2C3731D9, "Sticky Bomb"},
		{ 0xAB564B93, "Proximine"},
		{ 0x787F0BB, "Snowball"},
		{ 0xBA45E8B8, "PipeBomb"},
		{ 0x23C9F95C, "Ball"},
	};
	struct WeaponMisc {
		Hash hashWeaponV2MC;
		const char* m_nameV2MC;
	};
	WeaponMisc WeaponV2Misc[] = {
		{ 0x34A67B97, "Jerry Can"},
		{ 0xFBAB5776, "Parachute"},
		{ 0x060EC506, "Fire Extinguisher"},
		{ 0xBA536372, "Hazardous Jerry Can"},
		{ 0x184140A1, "Fertilizer Can"},
	};

	inline Entity m_current_ent_w{};
	inline float m_heading_w{};
	inline Hash m_weapon_model_hash{};
	inline bool m_running_w = false;
	inline bool m_shutdown_preview_w = false;
	inline std::chrono::time_point<std::chrono::steady_clock> m_rotation_start_time_w;

	bool request_model_w(Hash hash) {
		if (STREAMING::HAS_MODEL_LOADED(hash)) {
			return true;
		}

		bool has_loaded;

		if (STREAMING::IS_MODEL_VALID(hash) && STREAMING::IS_MODEL_IN_CDIMAGE(hash)) {
			do {
				has_loaded = STREAMING::HAS_MODEL_LOADED(hash);
				if (has_loaded)
					break;

				STREAMING::REQUEST_MODEL(hash);

				fiber::current()->sleep();
			} while (!has_loaded);

			return true;
		}

		return false;
	}

	Vehicle spawn_w(Hash hash, Vector3 location, float heading, bool is_networked, bool script_veh) {
		if (request_model(hash)) {
			auto veh =
				WEAPON::CREATE_WEAPON_OBJECT(hash, 999,  location.x, location.y, location.z, true, 5.f, 0, 0 ,0);

			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);

			return veh;
		}
		return 0;
	}

	inline void preview_weapon(Hash hash) {
		if (m_running_w && m_weapon_model_hash != hash) {
			if (m_running_w)
				m_shutdown_preview_w = true;
			return;
		}

		if (!m_running_w) {
			m_weapon_model_hash = hash;
		}

		if (m_running_w) {
			return;
		}

		m_running_w = true;
			m_heading_w = 0.f;
			m_rotation_start_time_w = std::chrono::steady_clock::now();

			while (!m_shutdown_preview_w && g_running && GetRenderer()->m_opened
				&& GetRenderer()->m_current_sub_menu
				&& !GetRenderer()->m_UpKeyPressed && !GetRenderer()->m_down_pressed && !GetRenderer()->m_BackKeyPressed) {
				Vector3 location{};

				if (m_current_ent_w == 0) {
					m_current_ent_w = spawn_w(m_weapon_model_hash, location, 0.f, false, false);
					if (m_current_ent_w) {
						ENTITY::FREEZE_ENTITY_POSITION(m_current_ent, true);
						ENTITY::SET_ENTITY_ALPHA(m_current_ent_w, 170, false);
						ENTITY::SET_ENTITY_COLLISION(m_current_ent_w, false, false);
						ENTITY::SET_ENTITY_COMPLETELY_DISABLE_COLLISION(m_current_ent_w, false, false);
						ENTITY::SET_ENTITY_CAN_BE_DAMAGED(m_current_ent_w, false);
						ENTITY::SET_ENTITY_PROOFS(m_current_ent_w, true, true, true, true, true, true, true, true);
						ENTITY::SET_CAN_CLIMB_ON_ENTITY(m_current_ent_w, false);
						OBJECT::SET_OBJECT_ALLOW_LOW_LOD_BUOYANCY(m_current_ent_w, false);
					}
				}

				ENTITY::SET_ENTITY_HEADING(m_current_ent_w, m_heading_w);
				Vector3 minimum, maximum;
				MISC::GET_MODEL_DIMENSIONS(m_current_ent_w, &minimum, &maximum);
				Vector3 camera_rotation = CAM::GET_FINAL_RENDERED_CAM_ROT(0);
				Vector3 gameplay_camera_direction = rotation_to_direction(camera_rotation);
				Vector3 size = subtract(maximum, minimum); // Remplace 'maximum - minimum'
				Vector3 gameplay_camera_position = add(CAM::GET_FINAL_RENDERED_CAM_COORD(), multiply(gameplay_camera_direction, 5.f));
				Vector3 vehicle_spawn_position = add(gameplay_camera_position, multiply(gameplay_camera_direction, size.y));

				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(m_current_ent_w,
					vehicle_spawn_position.x,
					vehicle_spawn_position.y,
					vehicle_spawn_position.z,
					FALSE,
					FALSE,
					FALSE);

				GetRenderer()->DrawInWorldBox(m_current_ent_w, { 255, 255, 255, 255 });

				auto now = std::chrono::steady_clock::now();
				auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_rotation_start_time_w)
					.count()
					/ 1000.0;

				m_heading_w = (elapsed_time / 10.0) * 360.0;
				m_heading_w = fmod(m_heading_w, 360.0);

				fiber::current()->sleep();
			}

			ENTITY::DELETE_ENTITY(&m_current_ent_w);

			m_weapon_model_hash = {};
			m_shutdown_preview_w = false;
			m_running_w = false;
			m_current_ent_w = NULL;
	}
}