#include "invoker/Natives.hpp"
#include "description.hpp"
#include "fiber.hpp"
#include "ui/interface.hpp"
namespace VX
{
	Description g_Description;

	void Description::Init(const char* text)
	{
		if (GetRenderer()->m_current_option == GetRenderer()->m_option_count)
		{
			if (GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(GetRenderer()->iToolTipScaleform)) {
				GRAPHICS::DRAW_SCALEFORM_MOVIE(GetRenderer()->iToolTipScaleform, GetRenderer()->m_menu_pos.x - 0.203f, GetRenderer()->m_menu_pos.y + 0.5f, 0.20500f, 1.0f, 255, 255, 255, 255, 0);
				GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(GetRenderer()->iToolTipScaleform, "SET_TEXT");
				GRAPHICS::BEGIN_TEXT_COMMAND_SCALEFORM_STRING("STRING");
				HUD::SET_TEXT_SCALE(.39f, .39f);
				HUD::SET_TEXT_COLOUR(255, 255, 255, 255);
				HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
				GRAPHICS::END_TEXT_COMMAND_SCALEFORM_STRING();
			}
			else {
				GetRenderer()->iToolTipScaleform = GRAPHICS::REQUEST_SCALEFORM_MOVIE("TEXTFIELD");
			}
		}
	}

	Description* GetDescription() { return &g_Description; }
}
