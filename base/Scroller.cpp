#include "invoker/Natives.hpp"
#include "Scroller.hpp"
#include "fiber.hpp"
#include "ui/interface.hpp"
#include "textures.hpp"
namespace VX
{
	Scroller g_Scroller;

	void Scroller::Init()
	{
		if (GetRenderer()->m_current_option <= GetRenderer()->m_max_vis_options && GetRenderer()->m_option_count <= GetRenderer()->m_max_vis_options) {
			GetRenderer()->m_target = GetRenderer()->m_draw_base_y + (GetRenderer()->m_option_height / 2.f);
			Update();
			GRAPHICS::SET_SCRIPT_GFX_DRAW_ORDER(2);
			GetRenderer()->draw_rect(GetRenderer()->m_scroller_color, Vector2(GetRenderer()->m_menu_pos.x, GetRenderer()->m_current), Vector2(GetRenderer()->m_width, GetRenderer()->m_option_height));
			GRAPHICS::SET_SCRIPT_GFX_DRAW_ORDER(3);
		}
		else if (GetRenderer()->m_option_count > (GetRenderer()->m_current_option - GetRenderer()->m_max_vis_options) && GetRenderer()->m_option_count <= GetRenderer()->m_current_option) {
			GetRenderer()->m_target = GetRenderer()->m_last_option_base + (GetRenderer()->m_option_height / 2.f);
			Update();
			GetRenderer()->draw_rect(GetRenderer()->m_scroller_color, Vector2(GetRenderer()->m_menu_pos.x, GetRenderer()->m_current), Vector2(GetRenderer()->m_width, GetRenderer()->m_option_height));
			GRAPHICS::SET_SCRIPT_GFX_DRAW_ORDER(2);
			GRAPHICS::SET_SCRIPT_GFX_DRAW_ORDER(3);
		}
	}
	void Scroller::Update()
	{
		if (GetRenderer()->m_current != GetRenderer()->m_target)
			GetRenderer()->m_current = GetRenderer()->m_current * (1 - GetRenderer()->m_speed) + GetRenderer()->m_target * GetRenderer()->m_speed;
		if ((GetRenderer()->m_current > GetRenderer()->m_target - 0.0005) && (GetRenderer()->m_current < GetRenderer()->m_target + 0.0005))
			GetRenderer()->m_current = GetRenderer()->m_target;
	}

	Scroller* GetScroller() { return &g_Scroller; }
}
