#include "invoker/Natives.hpp"
#include "Mousse.hpp"
#include "fiber.hpp"
#include "ui/interface.hpp"
#include "scaleform.h"
namespace VX
{
	Mousse g_Mousse;

	void Mousse::Init()
	{
		if (mouse_activate)
		{
			// Handle menu GUI navigation - only when the menu is actually open/visible
			HUD::SET_MOUSE_CURSOR_THIS_FRAME();
			HUD::SET_MOUSE_CURSOR_STYLE(CursorType::Normal);

			if (GetTickCount64() - GetRenderer()->m_previous_tick > GetRenderer()->m_delay)
			{
				if (cursor_at_pos({ GetRenderer()->m_menu_pos.x, GetRenderer()->m_menu_pos.y + (GetRenderer()->m_header_height / 2.f) }, { GetRenderer()->m_width, GetRenderer()->m_header_height }))
				{
					HUD::SET_MOUSE_CURSOR_STYLE(CursorType::PreGrab);
					if (PAD::IS_DISABLED_CONTROL_PRESSED(0, INPUT_CURSOR_ACCEPT))
					{
						GetRenderer()->m_menu_pos = get_cursor_location();
					}
				}
				// Menu GUI Close/Back Button
				if (PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, INPUT_CURSOR_CANCEL))
				{
					GetRenderer()->back_menu();
					GetRenderer()->m_previous_tick = GetTickCount64();
				}
				// Scroll Up
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, INPUT_CURSOR_SCROLL_UP))
				{
					if (GetRenderer()->m_current_option > 1)
					{
						GetRenderer()->m_current_option -= 1;
					}
					else
					{
						GetRenderer()->m_current_option = GetRenderer()->m_option_count;					}
					AUDIO::PLAY_SOUND_FRONTEND(-1, (char*)"NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);
				}
				// Scroll Down
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, INPUT_CURSOR_SCROLL_DOWN))
				{
					if (GetRenderer()->m_option_count > GetRenderer()->m_current_option)
					{
						GetRenderer()->m_current_option += 1;
					}
					else
					{
						GetRenderer()->m_current_option = 1;
					}
					AUDIO::PLAY_SOUND_FRONTEND(-1, (char*)"NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);
				}
				else if (PAD::IS_DISABLED_CONTROL_PRESSED(0, INPUT_CURSOR_ACCEPT))
				{
					GetRenderer()->m_select_pressed = true;
					if (GetRenderer()->m_menu_level > 0)
					{
						AUDIO::PLAY_SOUND_FRONTEND(-1, (char*)"SELECT", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);
					}

					GetRenderer()->m_previous_tick = GetTickCount64();
				}
			}
		}
	}
	bool Mousse::cursor_at_pos(Vector2 const& boxCentre, Vector2 const& boxSize)
	{
		return (get_cursor_location().x >= boxCentre.x - boxSize.x / 2 && get_cursor_location().x <= boxCentre.x + boxSize.x / 2)
			&& (get_cursor_location().y > boxCentre.y - boxSize.y / 2 && get_cursor_location().y < boxCentre.y + boxSize.y / 2);
	}
	Vector2 Mousse::get_cursor_location()
	{
		return { PAD::GET_DISABLED_CONTROL_NORMAL(2, INPUT_CURSOR_X), PAD::GET_DISABLED_CONTROL_NORMAL(2, INPUT_CURSOR_Y) };
	}
	void Mousse::MousseInput() {
		GetScaleform()->DrawInstructional(mouse_activate ? ToggleMousseOn : ToggleMousseOff, "F4");

	}

	Mousse* GetMousse() { return &g_Mousse; }
}
