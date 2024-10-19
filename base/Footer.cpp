#include "invoker/Natives.hpp"
#include "Footer.hpp"
#include "fiber.hpp"
#include "ui/interface.hpp"
namespace VX
{
	Footer g_Footer;

	void Footer::Init()
	{
		float size = GetRenderer()->m_footer_arrow_size;
		float rotation = 0.f;
		const char* texture = "shop_arrows_upanddown";
		if (GetRenderer()->m_current_option == 1) {
			rotation = 90.f;
			texture = "arrowright";
			size *= 0.7f;
		}
		else if (GetRenderer()->m_current_option == GetRenderer()->m_option_count) {
			rotation = 270.f;
			texture = "arrowright";
			size *= 0.7f;
		}
		Vector2 sizee = GetRenderer()->get_spirit_scale(size);
		GetRenderer()->draw_rect(GetRenderer()->m_footer_background, Vector2(GetRenderer()->m_menu_pos.x, GetRenderer()->m_draw_base_y + (GetRenderer()->m_footer_height / 2.f)), Vector2(GetRenderer()->m_width, GetRenderer()->m_footer_height));
		GetRenderer()->draw_sprite("commonmenu", texture, Vector2(GetRenderer()->m_menu_pos.x, GetRenderer()->m_draw_base_y + (GetRenderer()->m_footer_height / 2.f)), sizee, rotation, { GetRenderer()->m_sprite_color });
		GetRenderer()->m_draw_base_y += GetRenderer()->m_footer_height;
	}

	Footer* GetFooter() { return &g_Footer; }
}
