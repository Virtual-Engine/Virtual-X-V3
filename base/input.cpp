#include "common.hpp"
#include "input.hpp"
#include "keyboardKey.hpp"
#include "CustomInput.hpp"
#include <set>
using namespace VX;
WNDPROC Input::m_windowProc;
std::set<Input::KeyboardFunction> g_keyboardFunctions;

bool Input::Initialize() {
	m_windowProc = (WNDPROC)SetWindowLongPtrA(GetInput()->m_hwnd, GWLP_WNDPROC, (__int3264)(LONG_PTR)WindowProcess);

	if (m_windowProc == nullptr) return false;
	g_log.send("Hooking", "IH initialized");
	return true;
}

LRESULT APIENTRY Input::WindowProcess(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg) {
	case WM_SIZE: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP: {
		GetKeyboard()->OnKeyboardMessage((DWORD)wParam, lParam & 0xFFFF, (lParam >> 16) & 0xFF, (lParam >> 24) & 1, (uMsg == WM_SYSKEYDOWN || uMsg == WM_SYSKEYUP), (lParam >> 30) & 1, (uMsg == WM_SYSKEYUP || uMsg == WM_KEYUP));
		auto functions = g_keyboardFunctions; for (auto& function : functions) function((DWORD)wParam, lParam & 0xFFFF, (lParam >> 16) & 0xFF, (lParam >> 24) & 1, (uMsg == WM_SYSKEYDOWN || uMsg == WM_SYSKEYUP), (lParam >> 30) & 1, (uMsg == WM_SYSKEYUP || uMsg == WM_KEYUP));
		break;
	}
	}
	return CallWindowProc(m_windowProc, hwnd, uMsg, wParam, lParam);
}

void Input::Cleanup() {
	SetWindowLongPtrA(GetInput()->m_hwnd, GWLP_WNDPROC, (LONG_PTR)m_windowProc);
	g_log.send("[Hooking]", "Disabled IH");
}