#pragma once
#include "detour/detour.hpp"
namespace VX {
	class hooks {
	public:
		static std::int64_t script_virtual_machine(void* stack, std::int64_t** globals, std::int64_t* program, std::int64_t* thread_context);
		static FARPROC get_proc_address(HMODULE hModule, const char* lpProcName);

    };
	class hooking {
	public:
		bool attach();
		void detach();
	public:
		void remove_script_hooks();
	public:
		detour_hook m_script_virtual_machine;
		detour_hook m_get_proc_adress;
		std::map<std::pair<const char*, uint64_t>, void**> m_hooked_natives;
	};
	hooking* GetHooking();
}