#pragma once
#include "invoker/Natives.hpp"

namespace VX
{
	class AddOption
	{
	private:

	public:
		Texture m_hDialogBox = { "commonmenu", "gradient_bgd" };
		RGBA m_color_box = { 255,255,255,255 };
	public:
		bool BoolNumberOption(const char* option, bool* toggle, float* numeral, float min, float max, float step = 1.0f, bool action_input = false);
		bool Submenu(char const* option, void (*sub)(), char const* desc = nullptr);
		bool ColorOption(const char* option, RGBA& Color);
		bool BoolOption(const char* option, bool* toggle, const char* textDesc = "");
		void BreakOption(const char* option);
	};

	AddOption* addOption();
}