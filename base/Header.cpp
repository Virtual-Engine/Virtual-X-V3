#include "invoker/Natives.hpp"
#include "Header.hpp"
#include "fiber.hpp"
#include "ui/interface.hpp"
#include "textures.hpp"
#include "animatedYTD.h"
namespace VX
{
	Header g_Header;

	void Header::Init()
	{
		GRAPHICS::SET_SCRIPT_GFX_DRAW_ORDER(1);
		PAD::DISABLE_CONTROL_ACTION(2, 27, TRUE);
		//if (m_hAnimatedHeader) m_hAnimatedHeader->Draw(m_menu_pos.x, m_menu_pos.y, m_width, m_header_height);
		//m_hAnimatedHeader->Draw(GetRenderer()->m_menu_pos.x, GetRenderer()->m_draw_base_y + (GetRenderer()->m_header_height / 2.f), GetRenderer()->m_width, GetRenderer()->m_header_height);
		GetRenderer()->draw_rect(GetRenderer()->m_header_back_ground, Vector2(GetRenderer()->m_menu_pos.x, GetRenderer()->m_draw_base_y + (GetRenderer()->m_header_height / 2.f)), Vector2(GetRenderer()->m_width, GetRenderer()->m_header_height));
		if (GetRenderer()->HeaderText)
		{
			GetRenderer()->draw_center_text(m_menu_name, GetRenderer()->m_header_text, Vector2(GetRenderer()->m_menu_pos.x, GetRenderer()->m_draw_base_y + (GetRenderer()->m_header_height / 2.f) - (GetRenderer()->get_text_height(GetRenderer()->m_header_font, GetRenderer()->m_header_font_size) / 2.f)), GetRenderer()->m_header_font_size, GetRenderer()->m_header_font, true);
		}
		DrawGlare();
		GetRenderer()->m_draw_base_y += GetRenderer()->m_header_height;
	}
	void Header::DrawGlare()
	{
		if (m_render_glare) {
			m_glare_handle = GRAPHICS::REQUEST_SCALEFORM_MOVIE("MP_MENU_GLARE");
			Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
			float dir = g_math.convert_360(rot.z, 0, 360);
			if ((m_glare_direction == 0 || m_glare_direction - dir > 0.5) || m_glare_direction - dir < -0.5)
			{
				m_glare_direction = dir;
				GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(m_glare_handle, "SET_DATA_SLOT");
				GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(m_glare_direction);
				GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
			}
			GRAPHICS::DRAW_SCALEFORM_MOVIE(m_glare_handle, (GetRenderer()->m_menu_pos.x + 0.339f) * GetRenderer()->m_global_scale, (GetRenderer()->m_draw_base_y + (GetRenderer()->m_header_height / 2.f) + 0.38f) * GetRenderer()->m_global_scale, (GetRenderer()->m_width + 0.82700f) * GetRenderer()->m_global_scale, (GetRenderer()->m_header_height + 0.852f) * GetRenderer()->m_global_scale, 255, 255, 255, 255, 0);
		}
	}

	Header* GetHeader() { return &g_Header; }
}
