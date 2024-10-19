#include "hooking.hpp"
#include "../pointers/pointers.hpp"
#include "hooks/script_virtual_machine.hpp"
#include "../rage/classes.hpp"
#include "../invoker/invoker.hpp"
namespace VX {

	hooking g_hooking;

	bool hooking::attach() {
		MH_Initialize();

		m_script_virtual_machine.create("SVM", GetPointers()->m_script_virtual_machine, &hooks::script_virtual_machine);
		m_get_proc_adress.create("SHV", GetProcAddress, &hooks::get_proc_address);

		MH_EnableHook(MH_ALL_HOOKS);
		return true;
	}

	void hooking::detach() {
		remove_script_hooks();

		m_script_virtual_machine.remove();
		m_get_proc_adress.remove();

		MH_DisableHook(MH_ALL_HOOKS);
		
		MH_Uninitialize();
	}
	void hooking::remove_script_hooks() {
		// Credits vali
		for (auto& hooked_native : m_hooked_natives) {
			if (auto val = GetInvoker()->m_cache.find(hooked_native.first.second); val != GetInvoker()->m_cache.end()) {
				void* handler = (void*)val->second;
				*hooked_native.second = handler;
			}
		}
		m_hooked_natives.clear();
	}
	hooking* GetHooking() { return &g_hooking; }
}