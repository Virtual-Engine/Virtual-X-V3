#include "core/core.hpp"

BOOL DllMain(HINSTANCE hInstance, DWORD reason, LPVOID) {
	using namespace VX;
	DisableThreadLibraryCalls(hInstance);
	GetCore()->m_module = hInstance;
	switch (reason) {
	case DLL_PROCESS_ATTACH: {
		GetCore()->attach();
	} break;
	case DLL_PROCESS_DETACH: {
		GetCore()->detach();
	} break;
	}
	return TRUE;
}
