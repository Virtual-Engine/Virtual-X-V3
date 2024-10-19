#include "invoker/Natives.hpp"
#include "Tab.hpp"
#include "fiber.hpp"
#include "ui/interface.hpp"
namespace VX
{
	Tab g_Tab;

	void Tab::Init(const char* title)
	{
		GRAPHICS::SET_SCRIPT_GFX_DRAW_ORDER(1);
		if (GetRenderer()->FirstTabSelected) {
			GetRenderer()->draw_rect(GetRenderer()->tab_color_selected, Vector2(GetRenderer()->m_menu_pos.x - 0.055f, 0.1175f + GetRenderer()->m_menu_pos.y - 0.0165f), { 0.10f, GetRenderer()->m_tab_height });
			GetRenderer()->draw_center_text("Local", {0,0,0,255}, Vector2(GetRenderer()->m_menu_pos.x - 0.055f, 0.1175f + GetRenderer()->m_menu_pos.y - 0.0270f), GetRenderer()->m_tab_font_size, GetRenderer()->m_tab_font, false);
		}
		else {
			GetRenderer()->draw_rect(GetRenderer()->tab_color_unselected, Vector2(GetRenderer()->m_menu_pos.x - 0.055f, 0.1175f + GetRenderer()->m_menu_pos.y - 0.0165f), { 0.10f, GetRenderer()->m_tab_height });
			GetRenderer()->draw_center_text("Local", {255,255,255,255}, Vector2(GetRenderer()->m_menu_pos.x - 0.055f, 0.1175f + GetRenderer()->m_menu_pos.y - 0.0270f), GetRenderer()->m_tab_font_size, GetRenderer()->m_tab_font, false);
		}

		if (GetRenderer()->SecondTabSelected) {
			GetRenderer()->draw_rect(GetRenderer()->tab_color_selected, Vector2(GetRenderer()->m_menu_pos.x + 0.050f, 0.1175f + GetRenderer()->m_menu_pos.y - 0.0165f), { 0.11f, GetRenderer()->m_tab_height });
			GetRenderer()->draw_center_text("Spawner", { 0,0,0,255 }, Vector2(GetRenderer()->m_menu_pos.x + 0.045f, 0.1175f + GetRenderer()->m_menu_pos.y - 0.0270f), GetRenderer()->m_tab_font_size, GetRenderer()->m_tab_font, false);
		}
		else {
			GetRenderer()->draw_rect(GetRenderer()->tab_color_unselected, Vector2(GetRenderer()->m_menu_pos.x + 0.050f, 0.1175f + GetRenderer()->m_menu_pos.y - 0.0165f), { 0.11f, GetRenderer()->m_tab_height });
			GetRenderer()->draw_center_text("Spawner", { 255,255,255,255 }, Vector2(GetRenderer()->m_menu_pos.x + 0.045f, 0.1175f + GetRenderer()->m_menu_pos.y - 0.0270f), GetRenderer()->m_tab_font_size, GetRenderer()->m_tab_font, false);
		}
		GetRenderer()->m_draw_base_y += GetRenderer()->m_submenu_height;
	}

	Tab* GetTab() { return &g_Tab; }
}
