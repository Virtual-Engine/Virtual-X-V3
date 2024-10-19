#include "ui/interface.hpp"

namespace VX
{
	void Selfloop();
	inline bool GodMod = false;
	inline bool Invisible = false;
	inline bool Offradar = false;
	inline float alpha = 255;
	inline bool Spin = false;
	inline bool Neverwanted = false;
	inline float LevelWanted = 0;
	inline float LevelFakeWanted = 0;
	inline bool NoRagDoll = false;
	inline bool Alwaysragdoll = false;
	inline bool DieonRagdoll = false;
	inline bool thermal = false;
	inline bool night = false;
	inline bool FireBreath = false;
	inline bool DeadEyeMotion = false;
	inline bool g_SlowMotion = false;
	inline float handred{ 255.f };
	inline float handgreen{ 0.f };
	inline float handblue{ 0.f };
	inline float handalpha{ 255.f };
	inline float handscale{ 0.5f };
	inline bool m_Handtrails{ false };
	inline const char* m_Particle[]{ "Lines", "Alien", "Alien2", "Clown", "Lightning", "Ghost", "Electric" };
	inline const char* m_ParticleCalls0[]{ "scr_rcpaparazzo1", "scr_rcbarry1", "scr_rcbarry1", "scr_rcbarry2", "scr_rcbarry2", "scr_agencyheist", "scr_agencyheistb" };
	inline const char* m_ParticleCalls1[]{ "scr_mich4_firework_sparkle_spawn", "scr_alien_disintegrate", "scr_alien_teleport", "scr_clown_appears", "scr_clown_death", "scr_fbi_dd_breach_smoke", "scr_agency3b_elec_box" };
	inline int m_ParticleIterator{ 0 };
	inline bool m_Head{ false };
	inline bool m_RightHand{ false };
	inline bool m_LeftHand{ false };
	inline bool m_RightFood{ false };
	inline bool m_LeftFood{ false };
	inline float m_GlowScale{ 0.1f };
	inline bool glowmanager = false;
	inline bool WalkunderWater = false;
	inline bool WalkonWater = false;
	inline bool ModiffyWater = false;
	inline float handred1{ 0.f };
	inline float handgreen2{ 0.f };
	inline float handblue3{ 0.f };
	inline float handred4{ 0.f };
	inline float handgreen5{ 0.f };
	inline float handblue6{ 0.f };
	inline RGBA neon;
	inline bool neonleft = false;
	inline bool neonright = false;
	inline bool neonfront = false;
	inline bool neonback = false;
	inline const char* RampTypes[]{ "Ramp", "Halfpipe" };
	inline bool m_front_ramp = false;
	inline bool m_rear_ramp = false;
	inline bool m_left_ramp = false;
	inline bool m_right_ramp = false;
	inline bool m_transparency = false;
	void attach();
	void detach();
	void PlayerLis_giveweapon();
	void PlayerList_giveweaponMK1();
	void PlayerList_giveweaponMK2();
	inline float g_NoClipSpeed{ 2.f };
	inline bool g_NoClip{ false };
	void NoClip(std::size_t type, float speed, bool toggle);
	inline const char* NoclipTypes[]{ "Classic", "Walking" };
	inline int NoclipIterator = 0;
	inline float AlphaNoclip = 170;
	inline bool AlphaNoclipBool = false;
	inline bool SpinNoclip = false;
	inline bool Superjump = false;
	inline bool Beastjump = false;
	inline bool NinjaJump = false;
	inline float FastRunSpeed = 1.49f;
	inline bool Fastrun = false;
	inline RGBA m_color = { 255, 255, 255, 255 };
	inline float m_range = 0.25;
	inline float m_intensity = 100;
	inline bool Paintgun = false;
	void giveallweapon();
	inline std::size_t m_EntityPropellantIterator;
	inline float m_ObjectPropellantSpeed{ 500.f };
	inline float m_PropellantSpawnDistance{ 10.f };
	inline bool BulletSwap = false;
	inline bool g_YoinkGun = false;
	inline float magnetGunR = 107;
	inline float magnetGunG = 5;
	inline float magnetGunB = 255;
	inline float magnetGunA = 170;
	inline bool m_Magnet = false;
	inline bool m_RapidFire = false;
	inline bool Teleportgun = false;
	inline const char* GravityGunStyle[]{ "Static", "Dynamic" };
	inline int GravityGunSize{ 0 };
	inline bool LockOnEntity{ false };
	inline std::vector<std::int32_t> GravityGunDatabase{};
	inline float g_PullPushStrength{ 1.5f };
	inline float g_Velocity{ 1.5f };
	inline int m_GravityGunEntityCount{ 1 };
	inline float g_Force{ 5.f };
	inline bool GravityGun = false;
	inline bool EntityVehicleGun = false;
	inline bool MoneyGun = false;
	inline float moneyNumber = 0;
	inline bool WaterShoot = false;
	inline bool Flame = false;
	inline bool DeadEyegun = false;
	inline bool RainBowCamo = false;
	inline bool Forcegun = false;
	inline const char* m_Entity[] = { "Vehicle", "Object", "Pickup", "Propellant" };
	inline const char* m_EntityVehicle[] = { "Adder", "Oppressor", "Rhino", "Insurgent", "Scramjet",  "T20", "Taipan", "Tempesta", "Tezeract", "Turismor", };
	inline const char* m_EntityObject[] = { "p_spinning_anus_s", "prop_pipes_conc_02", "prop_barier_conc_03a", "prop_logpile_07b", "prop_asteroid_01",  "prop_tool_shovel2", "prop_prop_tree_01", "prop_conslift_cage", "prop_bush_lrg_01e_cr", "prop_aircon_t_03", };
	inline const char* m_Pickup[] = { "Vehicle", "Object", "Pickup", "Propellant" };
	inline const char* m_PickupType[] = { "Money", "Armour", "Health" };
	inline const char* m_PickupModel[] = { "Bag", "Alien Egg", "X-Mas Tree","Dildo", "Safe","Med Bag", "Gun Case", "Guitar" "Bag", "Golfbag" };
	inline const char* m_PropellantText[] = { "Firework", "Railgun", "RPG", "Up-n-Atomizer" };
	inline int m_HashModels[] = { -1666779307, 1803116220, 238789712, -422877666, -1251197000, 1368637848, 1213275131, -708789241, 886428669 };
	inline std::uint32_t m_HashPickups[] = { 0x1E9A99F8, 0x4BFB42D1, 0x8F707C18 };
	inline std::uint32_t m_PropellantHashes[] = { 0x7F7497E5, 0x6D544C99, 0xB1CA77B1, 0xAF3696A1 };
	inline std::size_t m_EntityVehicleIterator;
	inline float m_VehicleSpawnDistance{ 10.f };
	inline float m_VehicleLaunchSpeed{ 500.f };
	inline float laserR = 107;
	inline float laserG = 5;
	inline float laserB = 255;
	inline bool Laserlight = false;
	inline bool Deletegun = false;
	inline bool Airstrikegun = false;
	inline int m_EntityObjectIterator;
	inline float m_ObjectSpawnDistance{ 10.f };
	inline float m_ObjectLaunchSpeed{ 500.f };
	inline bool EntityObjectGun = false;
	inline bool Explosivebullet = false;
	void DriveToWaypoint();
	void StopAutoDrive();
	inline bool AutoFix = false;
	inline bool Autoflip = false;
	inline bool InvisibleVehicle = false;
	inline bool DriftMode = false;
	inline bool DriveonWater = false;
	inline bool DriveunderWater = false;
	inline bool ForceVehicletoGround = false;
	inline bool ThreeSixty = false;
	inline bool EngineAlwayson = false;
	inline bool Glitch = false;
	inline bool m_EnableGlowVehicle{ false };
	inline bool m_RightFrontWheel{ false };
	inline bool m_LeftFrontWheel{ false };
	inline bool m_RightBackWheel{ false };
	inline bool m_LeftBackWheel{ false };
	inline float m_GlowScale0{ 0.2f };
	inline const char* m_Particle0[] = { "Alien", "Alien2", "Clown", "Lightning", "Ghost", "Electric" };
	inline const char* m_ParticleCalls00[] = { "scr_rcbarry1", "scr_rcbarry1", "scr_rcbarry2", "scr_rcbarry2", "scr_agencyheist", "scr_agencyheistb" };
	inline const char* m_ParticleCalls10[] = { "scr_alien_disintegrate", "scr_alien_teleport", "scr_clown_appears", "scr_clown_death", "scr_fbi_dd_breach_smoke", "scr_agency3b_elec_box" };
	inline int m_ParticleIterator0{ 0 };
	inline bool ParticleVehicle = false;
	inline std::array<const char*, 3> VehicleWeapons = { "Rocket", "Explosive", "Red Light" };
	inline std::array<std::uint32_t, 3> VehicleWeaponHashes = { -1090665087, 0xE2822A29, 0x5D6660AB };
	inline std::size_t VehicleWeaponIterator{ 0 };
	inline int g_WeaponDelay{ 1000 };
	inline bool g_VehicleWeapons{ false };
	inline bool g_Lasersight{ false };
	inline float g_WeaponSpeed{ 250.f };
	inline bool g_VehicleFly{ false };
	inline float g_FlySpeed{ 130.f };
	inline bool g_Collision{ true };
	inline bool g_BypassSpeed{ true };
	inline bool m_AudioBoost{ false };
	inline float m_SpeedBoost{ 2.f };
	inline bool m_BoostEffect{ false };
	inline bool m_Hornboost{ false };
	inline const char* Ability[]{ "Off", "Boost", "Jump" };
	inline std::size_t AbilityIterator{ 0 };
	inline const char* g_Jump[] = { "Off", "Tap", "Hold" };
	inline std::size_t g_JumpIterator{ 0 };
	inline std::size_t RainbowIterator{ 0 };
	inline const char* g_RainbowText[] = { "Off", "Smooth", "Rapid" };
	inline bool g_Seatbelt = false;
	inline bool g_InvincibleVehicle = false;
	inline bool g_Scorched = false;
	inline bool Hornboost2 = false;
	void VehicleRamp(bool front, bool back, bool left, bool right);
	void vehicle_acrobatics(int type);
	void SetClouds(const char* cloudtexture);
	inline int g_LightRed{ 255 };
	inline int g_LightBlue{ 0 };
	inline int g_LightGreen{ 0 };
	inline int g_LigtIntensity{ 20 };
	inline bool g_EnableLight = false;
	inline bool g_PauseTime{ false };
	inline bool g_TimeEnable{ false };
	inline int g_Hour{ 23 };
	inline int g_Minute{ 59 };
	inline int g_Second{ 59 };
	void SPMoney(bool add, int value, bool reset);
	inline bool m_ExplodeNearVehs = false;
	inline bool m_DeleteNearVehs = false;
	inline bool m_RainbowNearVehs = false;
	inline bool m_BoostNearVehs = false;
	void Ramp();
	void DeleteRamp();
	inline std::vector<std::int32_t> g_Ramp{};
	inline int RampIndex{ 0 };
	inline int g_RampCount{ 10 };
	void TeleportFunction(Vector3 coords);
	Vector3 GetBlipIcon();
	void teleport_direction(int direction);
	bool get_objective_location(Vector3& location);
	void SetRank(int rpvalue);
	bool IsKeyPressed(std::uint16_t key);
	inline int levelrp = 0;
	inline bool p_PROTECTION_BOUNTY{ true };
	inline bool p_PROTECTION_CLAIM_BOUNTY{ true };
	inline bool p_PROTECTION_CEO_BAN{ true };
	inline bool p_PROTECTION_CEO_KICK{ true };
	inline bool p_PROTECTION_CEO_MONEY{ true };
	inline bool p_PROTECTION_CLEAR_WANTED{ true };
	inline bool p_PROTECTION_FAKE_DEPOSIT{ true };
	inline bool p_PROTECTION_FORCE_MISSION{ true };
	inline bool p_PROTECTION_GTA_BANNER{ false };
	inline bool p_PROTECTION_PERSONAL_VEHICLE{ true };
	inline bool p_PROTECTION_OFF_RADAR{ true };
	inline bool p_PROTECTION_ROTATE_CAM{ false };
	inline bool p_PROTECTION_FORCE_CUTSCENE{ true };
	inline bool p_PROTECTION_FORCE_ISLAND{ true };
	inline bool p_PROTECTION_SOUND_SPAM{ true };
	inline bool p_PROTECTION_SPECTATE{ true };
	inline bool p_PROTECTION_FORCE_APARTMENT{ true };
	inline bool p_PROTECTION_TRANSACTION_ERROR{ true };
	inline bool p_PROTECTION_VEHICLE_KICK{ true };
	inline bool p_PROTECTION_NETWORK_BAIL{ true };
	inline bool p_PROTECTION_FREEZE{ true };
	inline bool p_PROTECTION_BRIBE{ true };
	inline bool p_PROTECTION_BLOCK_PASSIVE{ true };
	inline bool p_PROTECTION_KICK{ true };
	inline bool p_PROTECTION_CRASH{ true };
	inline bool p_PROTECTION_NOTIFY{ true };
	inline bool p_NOTIFY_EVENTS{ true };
	inline bool Player_Specate = false;
	inline bool moneydrop = false;
	void DiscordInstruct();
	enum class eSessionType {
		JOIN_PUBLIC,
		NEW_PUBLIC,
		CLOSED_CREW,
		CREW,
		CLOSED_FRIENDS = 6,
		FIND_FRIEND = 9,
		SOLO,
		INVITE_ONLY,
		JOIN_CREW,
		SC_TV,
		LEAVE_ONLINE = -1
	};

	struct SessionType {
		eSessionType id;
		const char name[29];
	};

	const SessionType sessions[11] = {
		{ eSessionType::JOIN_PUBLIC, "Find Public Session"},
		{ eSessionType::NEW_PUBLIC, "Find New Public Session"},
		{ eSessionType::CLOSED_CREW, "Create Closed Crew Session"},
		{ eSessionType::CREW, "Create Crew Session"},
		{ eSessionType::CLOSED_FRIENDS, "Create Closed Friend Session"},
		{ eSessionType::FIND_FRIEND, "Find Friend Session"},
		{ eSessionType::SOLO, "Create Solo Session"},
		{ eSessionType::INVITE_ONLY, "Create Invite Only Session"},
		{ eSessionType::JOIN_CREW, "Find Crew Session"},
		{ eSessionType::SC_TV, "Social Club TV"},
		{ eSessionType::LEAVE_ONLINE, "Leave GTA Online"},
	};
	void join_type(eSessionType session);
	inline bool Logger_activate = false;
	void SpawnVehicle(uint32_t model);
	void giveweapon(Hash hash);
	inline bool spectator = false;
}