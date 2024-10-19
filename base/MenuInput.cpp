#include "invoker/Natives.hpp"
#include "MenuInput.hpp"
#include "fiber.hpp"
#include "ui/interface.hpp"
#include "Mousse.hpp"
#include "script/script.hpp"
#include "Settings.hpp"
#include "VehicleInfo.hpp"
namespace VX
{
	MenuInput g_MenuInput;

	void MenuInput::Init()
	{
		if (GetTickCount64() - GetRenderer()->m_previous_tick > GetRenderer()->m_delay) {
			if (GetRenderer()->m_OpenKeyPressed || PAD::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_RB) && PAD::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_RIGHT)) {
				if (GetRenderer()->m_menu_level == 0)
					GetRenderer()->forward_menu(home_submenu, "Home");
				GetRenderer()->play_frontend_sound(GetRenderer()->m_opened ? "SELECT" : "BACK");
				GetRenderer()->m_opened = !GetRenderer()->m_opened;
				GetRenderer()->m_previous_tick = GetTickCount64();
			}
			else if (GetRenderer()->m_BackKeyPressed || PAD::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_CANCEL)) {
				if (GetRenderer()->m_opened && GetRenderer()->m_menu_level != 0) {
					GetRenderer()->play_frontend_sound("BACK");
					if (GetRenderer()->m_menu_level == 1)
						GetRenderer()->m_opened = false;
					else if (GetRenderer()->m_menu_level != 1)
						GetRenderer()->back_menu();
				}
				GetRenderer()->m_previous_tick = GetTickCount64();
			}
			else if (GetRenderer()->m_BackKeyPressed || PAD::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_CANCEL)) {
				if (GetRenderer()->m_opened && GetRenderer()->m_menu_level != 0) {
					GetRenderer()->play_frontend_sound("BACK");
					if (GetRenderer()->m_menu_level == 1)
						GetRenderer()->m_opened = false;
					else if (GetRenderer()->m_menu_level != 1)
						GetRenderer()->back_menu();
				}
				GetRenderer()->m_previous_tick = GetTickCount64();
			}
			else if (GetRenderer()->m_UpKeyPressed || PAD::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_UP)) {
				if (GetRenderer()->m_opened && GetRenderer()->m_menu_level != 0) {
					GetRenderer()->play_frontend_sound("NAV_UP_DOWN");
					if (GetRenderer()->m_current_option > 1)
						GetRenderer()->m_current_option--;
					else
						GetRenderer()->m_current_option = GetRenderer()->m_option_count;
				}
				GetRenderer()->m_up_pressed = true;
				GetRenderer()->m_previous_tick = GetTickCount64();
			}
			else if (GetRenderer()->m_DownKeyPressed || PAD::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_DOWN)) {
				if (GetRenderer()->m_opened && GetRenderer()->m_menu_level != 0) {
					GetRenderer()->play_frontend_sound("NAV_UP_DOWN");
					if (GetRenderer()->m_current_option < GetRenderer()->m_option_count)
						GetRenderer()->m_current_option++;
					else
						GetRenderer()->m_current_option = 1;
				}
				GetRenderer()->m_down_pressed = true;
				GetRenderer()->m_previous_tick = GetTickCount64();
			}
			else if (GetRenderer()->m_LeftKeyPressed || PAD::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_LEFT)) {
				if (GetRenderer()->m_opened && GetRenderer()->m_menu_level != 0) {
					GetRenderer()->play_frontend_sound("NAV_LEFT_RIGHT");
					GetRenderer()->m_left_pressed = true;
				}
				GetRenderer()->m_previous_tick = GetTickCount64();
			}
			else if (GetRenderer()->m_RightKeyPressed || PAD::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_RIGHT)) {
				if (GetRenderer()->m_opened && GetRenderer()->m_menu_level != 0) {
					GetRenderer()->play_frontend_sound("NAV_LEFT_RIGHT");
					GetRenderer()->m_right_pressed = true;
				}
				GetRenderer()->m_previous_tick = GetTickCount64();
			}
			else if (GetRenderer()->m_EnterKeyPressed || PAD::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_ACCEPT)) {
				if (GetRenderer()->m_opened && GetRenderer()->m_menu_level != 0) {
					GetRenderer()->play_frontend_sound("SELECT");
					GetRenderer()->m_select_pressed = true;
				}
				GetRenderer()->m_previous_tick = GetTickCount64();
			}
			else if (GetAsyncKeyState(VK_F8)) // h key
			{
				if (GetRenderer()->m_opened) {
					GetRenderer()->m_hotkey_pressed = true;
				}
				GetRenderer()->m_previous_tick = GetTickCount64();
			}
			else if (GetAsyncKeyState(VK_END) || PAD::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_LB))
			{
				GetRenderer()->m_previous_tick = GetTickCount64();
				GetRenderer()->Current_Tab++;
				if (GetRenderer()->Current_Tab == 2)
					GetRenderer()->Current_Tab = 0;

			}
			else if (GetAsyncKeyState(VK_DELETE) || PAD::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_RB))
			{
				GetRenderer()->m_previous_tick = GetTickCount64();
				GetRenderer()->Current_Tab--;
				if (GetRenderer()->Current_Tab == -1)
					GetRenderer()->Current_Tab = 1;
			}
			else if (GetRenderer()->m_MouseKeyPressed)
			{
				GetMousse()->mouse_activate = true;
				GetRenderer()->m_previous_tick = GetTickCount64();
			}
		}
	}
	void MenuInput::CheckInput()
	{
		GetRenderer()->m_OpenKeyPressed = GetInput()->is_key_pressed(VK_F5);
		GetRenderer()->m_BackKeyPressed = GetInput()->is_key_pressed(VK_BACK);
		GetRenderer()->m_EnterKeyPressed = GetInput()->is_key_pressed(VK_RETURN);
		GetRenderer()->m_UpKeyPressed = GetInput()->is_key_pressed(VK_UP);
		GetRenderer()->m_DownKeyPressed = GetInput()->is_key_pressed(VK_DOWN);
		GetRenderer()->m_LeftKeyPressed = GetInput()->is_key_pressed(VK_LEFT);
		GetRenderer()->m_RightKeyPressed = GetInput()->is_key_pressed(VK_RIGHT);
		GetRenderer()->m_MouseKeyPressed = GetInput()->is_key_pressed(VK_F4);
	}
	MenuInput* GetMenuInput() { return &g_MenuInput; }
}
