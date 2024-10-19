#include "core.hpp"
#include "../log/log.hpp"
#include "../hooking/hooking.hpp"
#include "../invoker/invoker.hpp"
#include "../script/script.hpp"
#include "../Handler.h"
#include "../CustomText.h"
#include "../util.h"
#include "../common.hpp"
#include <memory>
#include "../pointers/pointers.hpp"
#include "../BackendRegistry.h"
#include "../dirs.h"
#include "../curl/curl.h"
#include "../Settings.hpp"
#include "../CustomInput.hpp"
#include "../input.hpp"
#include "../ScriptHookV.hpp"
#include <Psapi.h>
#include "../progressbar.hpp"
#include "../manager.hpp"
bool isRetailKey = false;
bool isSteamKey = false;
bool isEpicKey = false;
int m_try_count;
namespace VX {

	core g_core;
	void core::attach() {
		auto threadProc = [](LPVOID lpParam) -> DWORD {
			GetCore()->m_steam = (uint64_t)GetModuleHandleA("steam_api64.dll") > 0;
			g_log.attach();
			g_log.send("Service", "Service Started...");
#ifndef LOG_NO_CONSOLE

			std::srand(time(NULL));
			for (int progress = 0; progress != 100; progress += std::rand() % 10) {
				if (progress > 100) progress = 100;
				std::cout << "Scan [";
				for (int i = 0; i < 100; i++)
					if (i < progress)
						std::cout << '=';
					else if (i == progress)
						std::cout << '>';
					else
						std::cout << ' ';
				std::cout << "] " << progress << " %" << '\r';
				std::cout.flush();
				std::this_thread::sleep_for(std::chrono::milliseconds(250));
				if (progress == 100) break;
			}
			std::cout << std::endl;
#endif 
			if (!GetInput()->initialize())
			{
				g_log.send("Input", "Failed Init Input");
				return false;
			}
			g_log.send("Service", "Input Loaded");
			GetCore()->PatternBackend();
			GetPointers()->Initialize();
			g_log.send("Service", "Pattern Loaded");
			if (!GetHooking()->attach())
			{
				g_log.send("Hooking", "Failed Init Hooking");
				return false;
			}
			g_log.send("Service", "Hooking Loaded");
			if (!GetInvoker()->cache_handler())
			{
				g_log.send("Handler", "Failed Init Cache Handler");
				return false;
			}
			g_log.send("Service", "Invoker Loaded");

			Input::Initialize();

			std::filesystem::create_directory(g_utility.get_documents_path() + "\\Virtual X");
			std::filesystem::create_directory(g_utility.get_documents_path() + "\\Virtual X\\asi");
			std::filesystem::create_directory(g_utility.get_documents_path() + "\\Virtual X\\themes");
			std::filesystem::create_directory(g_utility.get_documents_path() + "\\Virtual X\\textures");
			std::filesystem::create_directory(g_utility.get_documents_path() + "\\Virtual X\\vehicle");
			std::filesystem::create_directory(g_utility.get_documents_path() + "\\Virtual X\\teleport");
			std::filesystem::create_directory(g_utility.get_documents_path() + "\\Virtual X\\map mods");
			std::filesystem::create_directory(g_utility.get_documents_path() + "\\Virtual X\\xml");

			add_fiber(new fiber("UI", &main_script));
			add_fiber(new fiber("Network Security", &network_security));
			add_fiber(new fiber("Discord", &discord));
			add_fiber(new fiber("Register Files", &register_file));
			add_fiber(new fiber("Register ScriptHookV", &register_shv));

			g_log.send("Service", "Virtual X Loaded");
			// g_log.detach();
			while (g_running) {
				if (GetAsyncKeyState(VK_F7) & 0x8000) {
					g_running = false;
				}
				std::this_thread::sleep_for(1ms);
			}
			GetCore()->detach();
			CloseHandle(GetCore()->m_main_thread);
			FreeLibraryAndExitThread(GetCore()->m_module, 0);
			};
		m_main_thread = CreateThread(NULL, 0, threadProc, this, 0, &m_main_thread_id);
	}
	void core::PatternBackend()
	{
		m_register_file = reinterpret_cast<types::file_register>(g_memory.scan("48 89 5C 24 ? 48 89 6C 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 83 EC 50 48 8B EA 4C 8B FA 48 8B D9 4D 85 C9", "RYTD"));
	}
	void core::CustomTextInit()
	{
		g_CustomText->AddText(CONSTEXPR_JOAAT("HUD_JOINING"), "Loading GTA Online with " VX_NAME "...");
		g_CustomText->AddText(CONSTEXPR_JOAAT("HUD_QUITTING"), "Leaving with " VX_NAME "...");
		g_CustomText->AddText(CONSTEXPR_JOAAT("PM_QUIT_MP"), "Exiting GTA Online with " VX_NAME);
		g_CustomText->AddText(CONSTEXPR_JOAAT("PM_ENTER_MP"), "Play GTA Online with " VX_NAME);
		g_CustomText->AddText(CONSTEXPR_JOAAT("PM_EXIT_GAME"), "Quit GTA with" VX_NAME);
		g_CustomText->AddText(CONSTEXPR_JOAAT("PM_GO"), "Freemode with " VX_NAME);
		g_CustomText->AddText(CONSTEXPR_JOAAT("HUD_MPREENTER"), "Joining a new session with " VX_NAME "...");
		g_CustomText->AddText(CONSTEXPR_JOAAT("PM_FRIEND_FM"), "Closed Friend Session with " VX_NAME "...");
		g_CustomText->AddText(CONSTEXPR_JOAAT("PM_GOTO_STORE"), "Purchase Shark Cards with " VX_NAME "...");
		g_CustomText->AddText(CONSTEXPR_JOAAT("PM_INF_EXIT"), "Quit to desktop with " VX_NAME "?");
		g_CustomText->AddText(CONSTEXPR_JOAAT("PM_CRESES"), "Joining A Crew Only Session with " VX_NAME "...");
		g_CustomText->AddText(CONSTEXPR_JOAAT("PM_INF_PGOB"), "Cut to the chase and	 head straight into the world of GTA Online with " VX_NAME "...");
		g_CustomText->AddText(CONSTEXPR_JOAAT("PM_INF_PGOT"), "Online w/ " VX_NAME "!");
		g_CustomText->AddText(CONSTEXPR_JOAAT("PM_INVO_FM"), "Join A Invite Only Session with " VX_NAME ".");
		g_CustomText->AddText(CONSTEXPR_JOAAT("LOADING_SPLAYER_L"), "Loading Story Mode with " VX_NAME "...");
		g_CustomText->AddText(CONSTEXPR_JOAAT("PM_NCREW_FM"), "Join A Crew Session with " VX_NAME ".");
		g_CustomText->AddText(CONSTEXPR_JOAAT("PM_CREW_FM"), "Join A Closed Crew Session with " VX_NAME ".");
		g_CustomText->AddText(CONSTEXPR_JOAAT("PM_SOLO_FM"), "Join A Solo Session with " VX_NAME ".");
		g_CustomText->AddText(CONSTEXPR_JOAAT("PM_FRESES"), "Join A Friends Only Session with " VX_NAME ".");
		g_CustomText->AddText(CONSTEXPR_JOAAT("MP_CHAT_ALL"), VX_NAME);
	}
	void core::GTAVersion()
	{
		HANDLE hProcess = NULL;
		if (!hProcess)
		{
			BackendRegistry::BackendRegistry1 reg;

			isSteamKey = reg.isSteamKey();

			isRetailKey = reg.isRetailKey();

			isEpicKey = reg.isEpicKey();

			if (isRetailKey)
			{
				g_log.send("Version", "Version -> Rockstar");
			}
			else if (isSteamKey)
			{
				g_log.send("Version", "Version -> Steam");
			}
			else if (isEpicKey)
			{
				g_log.send("Version", "Version -> Epic Game");
			}

		}

	}

	void core::network_security() {
		if (*GetPointers()->m_is_session_started)
		{
			g_log.send("Security", "GTA Online is not suported due to security reason go in sotry mode");
			GetHooking()->detach();
			g_log.send("Security", "Hooking Disabled");
		}
	}

	void core::detach() {
		GetHooking()->detach();
		std::this_thread::sleep_for(500ms);
		GetScript()->detach();
		g_log.detach();
		GetDiscord()->Shutdown();
	}

	void core::register_file()
	{
		auto ytd_file = g_utility.get_documents_path().append("\\Virtual X\\").append("\\textures\\").append("VX.ytd").c_str();
		g_log.send("Files", "Downloading Files...");
		download("https://nyxcheats.xyz/backend/download/VX.ytd", ytd_file);
		g_log.send("Files", "Downloaded.");
		static int tries = 0;
		if (tries > 5) {
			g_log.send("Files", "Failed to download file");
			return;
		}
		static int textureID;
		GetCore()->m_register_file(&textureID, ytd_file, true, "VX.ytd", false);
		g_log.send("Files", std::format("Register VX.ytd ID: {}", textureID).c_str());

	}
	void core::register_shv()
	{
		if (!GetModuleHandleA("ScriptHookV.dll")) {
			auto shv_file = g_utility.get_documents_path().append("\\Virtual X\\").append("ScriptHookV.dll").c_str();
			LoadLibraryA(shv_file);
		}
		else {
			if (GetModuleHandleA("dinput8.dll")) {
				while (!GetModuleHandleA("ScriptHookV.dll")) {
					std::this_thread::sleep_for(100ms);
				}
			}
		}
		GetCore()->m_script_hook_v = (uint64_t)GetModuleHandleA("ScriptHookV.dll");
		if (GetCore()->m_script_hook_v) {
			MODULEINFO shvInfo = {};
			GetModuleInformation(GetCurrentProcess(), GetModuleHandleA("ScriptHookV.dll"), &shvInfo, sizeof(shvInfo));
			script_hook_v::loaded_module_memory.emplace_back((uint64_t)shvInfo.lpBaseOfDll, (uint64_t)shvInfo.SizeOfImage, "ScriptHookV.dll", GetModuleHandleA("ScriptHookV.dll"));
			g_log.send("Files", std::format("Register ScriptHookV.dll at : {} size : {}", (uint64_t)shvInfo.lpBaseOfDll, (uint64_t)shvInfo.SizeOfImage).c_str());
		}
		else
		{
			g_log.send("Files", "Script Hook V Module Not Found");
		}
	}
	core* GetCore() { return &g_core; };
}
