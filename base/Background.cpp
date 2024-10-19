#include "invoker/Natives.hpp"
#include "Background.hpp"
#include "fiber.hpp"
#include "ui/interface.hpp"
namespace VX
{
	Background g_Background;

	void Background::Init()
	{
		GRAPHICS::SET_SCRIPT_GFX_DRAW_ORDER(1);
		int visible_options = GetRenderer()->m_option_count > GetRenderer()->m_max_vis_options ? GetRenderer()->m_max_vis_options : GetRenderer()->m_option_count;
		// draw_sprite("commonmenu", "gradient_bgd", Vector2(m_menu_pos.x, m_header_height + m_submenu_height + m_menu_pos.y + ((m_option_height * visible_options) / 2.f)), Vector2(m_width, m_option_height * visible_options), 0.f, {255, 255, 255, 255}); // if u want a fade effect 
		GetRenderer()->draw_rect(GetRenderer()->m_option_backgound, Vector2(GetRenderer()->m_menu_pos.x, GetRenderer()->m_header_height + GetRenderer()->m_submenu_height + GetRenderer()->m_menu_pos.y + ((GetRenderer()->m_option_height * visible_options) / 2.f)), Vector2(GetRenderer()->m_width, GetRenderer()->m_option_height * visible_options));
		GetRenderer()->m_option_count = 0;
		GRAPHICS::SET_SCRIPT_GFX_DRAW_ORDER(3);
	}

	Background* GetBackground() { return &g_Background; }
}
