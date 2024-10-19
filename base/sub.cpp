#include "invoker/Natives.hpp"
#include "sub.hpp"
#include "fiber.hpp"
#include "ui/interface.hpp"
namespace VX
{
	SubBar g_SubBar;

	void SubBar::Init(const char* title)
	{
		GRAPHICS::SET_SCRIPT_GFX_DRAW_ORDER(1);
		//draw_rect(m_submenu_backgound, Vector2(m_menu_pos.x, m_draw_base_y - 0.0001f), Vector2(m_width + 0.0005f, 0.0026f));
		GetRenderer()->draw_rect(GetRenderer()->m_submenu_backgound, Vector2(GetRenderer()->m_menu_pos.x, GetRenderer()->m_draw_base_y + (GetRenderer()->m_submenu_height / 2.f)), Vector2(GetRenderer()->m_width, GetRenderer()->m_submenu_height));
		GetRenderer()->draw_left_text(title, GetRenderer()->m_submenu_text, Vector2(GetRenderer()->m_menu_pos.x - (GetRenderer()->m_width / 2.06f), GetRenderer()->m_draw_base_y + (GetRenderer()->m_submenu_height / 2.f) - (GetRenderer()->get_text_height(GetRenderer()->m_submenu_font, GetRenderer()->m_submenu_font_size) / 1.5f)), GetRenderer()->m_submenu_font_size, GetRenderer()->m_submenu_font, false);
		GetRenderer()->draw_right_text(std::format("{}/{}", GetRenderer()->m_current_option, GetRenderer()->m_option_count).c_str(), GetRenderer()->m_submenu_text, Vector2(GetRenderer()->m_menu_pos.x + (GetRenderer()->m_width / GetRenderer()->m_sub_padding), GetRenderer()->m_draw_base_y + (GetRenderer()->m_submenu_height / 2.f) - (GetRenderer()->get_text_height(GetRenderer()->m_submenu_font, GetRenderer()->m_submenu_font_size) / 1.5f)), GetRenderer()->m_submenu_font_size, GetRenderer()->m_submenu_font, false);
		GetRenderer()->m_draw_base_y += GetRenderer()->m_submenu_height;
	}

	SubBar* GetSubBar() { return &g_SubBar; }
}
