#include "invoker/Natives.hpp"
#include "option.hpp"
#include "fiber.hpp"
#include "ui/interface.hpp"
#include "Scroller.hpp"
#include "VehicleInfo.hpp"
#include "ControlUtil.h"
#include "description.hpp"
#include "Mousse.hpp"
namespace VX
{
	AddOption g_addOption;
	bool AddOption::Submenu(char const* option, void (*sub)(), char const* desc)
	{
		GetRenderer()->add_option(option);
		GetDescription()->Init(desc);
		if (GetRenderer()->m_current_option <= GetRenderer()->m_max_vis_options && GetRenderer()->m_option_count <= GetRenderer()->m_max_vis_options) {
			//draw_rect(m_line_background, Vector2(m_menu_pos.x + (m_width / m_right_padding) - (0.0035f / 2.f), m_draw_base_y + (m_option_height / 2.f)), Vector2(0.0030f, m_option_height));
			GetRenderer()->draw_sprite("commonmenu", "arrowright", Vector2(GetRenderer()->m_menu_pos.x + (GetRenderer()->m_width / GetRenderer()->m_right_padding + 0.06f), GetRenderer()->m_draw_base_y + (GetRenderer()->m_option_height / 2.f)), Vector2(0.0200f, 0.030f), 0, GetRenderer()->m_line_background);
			//draw_right_text(">>", m_header_back_ground, Vector2(m_menu_pos.x + (m_width / m_right_padding)), 0.30f, m_header_font, 0);
		}
		else if (GetRenderer()->m_option_count > (GetRenderer()->m_current_option - GetRenderer()->m_max_vis_options) && GetRenderer()->m_option_count <= GetRenderer()->m_current_option) {
			//GetRenderer()->draw_right_text(">>", GetRenderer()->m_line_background, Vector2(GetRenderer()->m_menu_pos.x + (GetRenderer()->m_width / GetRenderer()->m_right_padding + 0.06f), GetRenderer()->m_draw_base_y + (GetRenderer()->m_option_height / 2.f)), 0.0200f, 0, 0);
			GetRenderer()->draw_sprite("commonmenu", "arrowright", Vector2(GetRenderer()->m_menu_pos.x + (GetRenderer()->m_width / GetRenderer()->m_right_padding + 0.06f), GetRenderer()->m_draw_base_y + (GetRenderer()->m_option_height / 2.f)), Vector2(0.0200f, 0.030f), 0, GetRenderer()->m_line_background);

		}
		if (GetRenderer()->m_option_count <= GetRenderer()->m_max_vis_options) {
			GetRenderer()->m_draw_base_y += GetRenderer()->m_option_height;
		}
		if (GetRenderer()->m_current_option == GetRenderer()->m_option_count) {
			if (GetRenderer()->m_select_pressed) {
				GetRenderer()->forward_menu(sub, option);
				return true;
			}
		}
		return false;
	}
	bool AddOption::ColorOption(const char* option, RGBA& Color)
	{
		GetRenderer()->add_option(option);
		if (GetRenderer()->m_current_option <= GetRenderer()->m_max_vis_options && GetRenderer()->m_option_count <= GetRenderer()->m_max_vis_options) {
			GetRenderer()->draw_rect(Color, Vector2(GetRenderer()->m_menu_pos.x + (GetRenderer()->m_width / GetRenderer()->m_right_padding + 0.07f) - (GetRenderer()->get_spirit_scale(GetRenderer()->m_toggle_size).x / 3.f), GetRenderer()->m_draw_base_y + (GetRenderer()->m_option_height / 2.f)), GetRenderer()->get_spirit_scale(GetRenderer()->m_toggle_size));
		}
		else if (GetRenderer()->m_option_count > (GetRenderer()->m_current_option - GetRenderer()->m_max_vis_options) && GetRenderer()->m_option_count <= GetRenderer()->m_current_option) {
			GetRenderer()->draw_rect(Color, Vector2(GetRenderer()->m_menu_pos.x + (GetRenderer()->m_width / GetRenderer()->m_right_padding + 0.07f) - (GetRenderer()->get_spirit_scale(GetRenderer()->m_toggle_size).x / 3.f), GetRenderer()->m_draw_base_y + (GetRenderer()->m_option_height / 2.f)), GetRenderer()->get_spirit_scale(GetRenderer()->m_toggle_size));
		}
		if (GetRenderer()->m_option_count <= GetRenderer()->m_max_vis_options)
			GetRenderer()->m_draw_base_y += GetRenderer()->m_option_height;
		if (GetRenderer()->m_option_count == GetRenderer()->m_current_option)
			if (GetRenderer()->m_select_pressed)
			{
				float x = 0.5f, y = 0.5f, width = 0.24f, height = 0.375f;
				bool accepted = false;
				bool exit = false;
				static int sX = 5, sY = 5;
				static int hueSlider = 0;
				static bool sliderSelected = false;
				RGBA originalCol = { Color.r, Color.g, Color.b, Color.a };
				bool mouseDragging = false;
				while (!exit) {
					fiber::current()->sleep();
					PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
					GetRenderer()->DrawBox(x, y, width, height, option, true, m_hDialogBox);
					GetRenderer()->DrawRect(0.5, 0.55f, width - 0.04f, 0.034f, { 50, 50, 50, 160 });


					for (int xx = 0; xx <= 18; xx++) {
						GetRenderer()->DrawRect(x + xx * 0.011f - 0.099f, y - 2 * 0.022f - 0.055f, 0.011f, 0.02f, g_utility.HSVToRGB(xx * 20, 1, 1));
					}
					for (int xx = 0; xx <= 9; xx++) {
						for (int yy = 0; yy <= 9; yy++) {
							if (!(xx == sX && yy == sY && !sliderSelected)) {
								GetRenderer()->DrawRect(x + xx * 0.022f - 0.099f, y + yy * 0.022f - 0.055f, 0.02f, 0.02f, g_utility.HSVToRGB(hueSlider, xx * (1.0f / 9), yy * (1.0f / 9)));
							}
			
						}
					}
					if (sliderSelected) {
						GetRenderer()->DrawBox(x - 0.099f + (hueSlider * 0.00055f), y - 2 * 0.022f - 0.055f, 0.015f, 0.03f, "", false, { "", "" }, true, g_utility.HSVToRGB(hueSlider, 1, 1));
					}
					else {
						GetRenderer()->DrawBox(x - 0.099f + (hueSlider * 0.00055f), y - 2 * 0.022f - 0.055f, 0.01f, 0.02f);
						GetRenderer()->DrawBox(x + sX * 0.022f - 0.099f, y + sY * 0.022f - 0.055f, 0.026f, 0.026f, "");
						GetRenderer()->DrawRect(x + sX * 0.022f - 0.099f, y + sY * 0.022f - 0.055f, 0.026f, 0.026f, g_utility.HSVToRGB(hueSlider, sX * (1.0f / 9), sY * (1.0f / 9)));
					}
					static bool downDisabled = false;
					static bool leftDisabled = false;
					static bool rightDisabled = false;
					static int downTimer = 0;
					static int leftTimer = 0;
					static int rightTimer = 0;
					static int TIMER;

					static bool upDisabled = false;
					static int upTimer = 0;
					Color = g_utility.HSVToRGB(hueSlider, sX * (1.0f / 9), sY * (1.0f / 9));
					//Scroll up
					if (GetInput()->is_key_pressed(VK_UP) || PAD::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_UP)) {
						if (!upDisabled) {
							if (sY > 0) sY--;
							else sliderSelected = true;
						}
						upDisabled = false;
						upTimer = 0;
					}
					// Hold up
				/*	if (GetInput()->is_key_pressed(true)) {
						if (++upTimer > 20) {
							upDisabled = true;
							g_utility.DoTimedFunction(&TIMER, 50);
						}
					}*/
					// Scroll down
					if (GetInput()->is_key_pressed(VK_DOWN) || PAD::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_DOWN)) {
						if (!downDisabled) {
							if (sliderSelected) {
								sliderSelected = false;
							}
							else if (sY < 9) sY++;
						}
						downDisabled = false;
						downTimer = 0;
					}

					/*// Hold down
					if (GetInput()->is_key_pressed(true)) {
						if (++downTimer > 20) {
							downDisabled = true;
							g_utility.DoTimedFunction(&TIMER, 50);
						}
					}*/

					//Scroll left
					if (GetInput()->is_key_pressed(VK_LEFT) || PAD::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_LEFT)) {
						if (!leftDisabled) {
							if (!sliderSelected) {
								if (sX > 0) sX--;
							}
							else {
								hueSlider -= 2;
								if (hueSlider < 0) hueSlider = 360;
							}

						}
						leftDisabled = false;
						leftTimer = 0;
					}
					// Scroll right
					if (GetInput()->is_key_pressed(VK_RIGHT) || PAD::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_RIGHT)) {
						if (!rightDisabled) {
							if (!sliderSelected) {
								if (sX < 9) sX++;
							}
							else {
								hueSlider += 2;
								if (hueSlider > 360) hueSlider = 0;
							}
						}
						rightDisabled = false;
						rightTimer = 0;
					}
					// Hold left
					/*if (GetInput()->is_key_pressed(true)) {
						if (++leftTimer > 20) {
							leftDisabled = true;
							if (!sliderSelected) {
								g_utility.DoTimedFunction(&TIMER, 50);
							}
							else {
								hueSlider -= 2;
								if (hueSlider < 0) hueSlider = 360;
							}
						}
					}
					// Hold right
					if (GetInput()->is_key_pressed(true)) {
						if (++rightTimer > 20) {
							rightDisabled = true;
							if (!sliderSelected) {
								g_utility.DoTimedFunction(&TIMER, 50);
							}
							else {
								hueSlider += 2;
								if (hueSlider > 360) hueSlider = 0;
							}
						}
					}*/

					if (GetInput()->is_key_pressed(VK_SHIFT) || PAD::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_RB)) {
						accepted = true;
						exit = 1;
					}
					else if (GetInput()->is_key_pressed(VK_ESCAPE) || PAD::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_RT)) {
						exit = 1;
						accepted = 0;
					}
				}
				if (accepted) Color = g_utility.HSVToRGB(hueSlider, sX * (1.0f / 9), sY * (1.0f / 9));
				else Color = originalCol;
				return accepted;
			}
				return true;
		return false;
		
	}
	bool AddOption::BoolOption(const char* option, bool* toggle, const char* textDesc) {
		GetRenderer()->add_option(option);
		GetDescription()->Init(textDesc);
		if (GetRenderer()->m_current_option <= GetRenderer()->m_max_vis_options && GetRenderer()->m_option_count <= GetRenderer()->m_max_vis_options) {
			GetRenderer()->draw_sprite("commonmenu", "common_medal", Vector2(GetRenderer()->m_menu_pos.x + (GetRenderer()->m_width / GetRenderer()->m_right_padding + 0.07f) - (GetRenderer()->get_spirit_scale(GetRenderer()->m_toggle_size).x / 3.f), GetRenderer()->m_draw_base_y + (GetRenderer()->m_option_height / 2.f)), GetRenderer()->get_spirit_scale(GetRenderer()->m_toggle_size), 0.f, *toggle ? GetRenderer()->m_toggle_color_on : GetRenderer()->m_toggle_color_off);
		}
		else if (GetRenderer()->m_option_count > (GetRenderer()->m_current_option - GetRenderer()->m_max_vis_options) && GetRenderer()->m_option_count <= GetRenderer()->m_current_option) {
			GetRenderer()->draw_sprite("commonmenu", "common_medal", Vector2(GetRenderer()->m_menu_pos.x + (GetRenderer()->m_width / GetRenderer()->m_right_padding + 0.07f) - (GetRenderer()->get_spirit_scale(GetRenderer()->m_toggle_size).x / 3.f), GetRenderer()->m_last_option_base + (GetRenderer()->m_option_height / 2.f)), GetRenderer()->get_spirit_scale(GetRenderer()->m_toggle_size), 0.f, *toggle ? GetRenderer()->m_toggle_color_on : GetRenderer()->m_toggle_color_off);
		}
		int assignedKey = GetRenderer()->get_assigned_key(toggle);
		if (assignedKey != -1)
		{
			// add text to right or whatever..
		}
		if (GetRenderer()->m_option_count <= GetRenderer()->m_max_vis_options) {
			GetRenderer()->m_draw_base_y += GetRenderer()->m_option_height;
		}
		if (GetRenderer()->m_current_option == GetRenderer()->m_option_count) {
			if (GetRenderer()->m_hotkey_pressed) {
				for (int key = 0; key < 256; key++) {
					if (GetAsyncKeyState(key) & 0x8000 && key != 72) {
						bool keyAlreadyUsed = false;
						for (const auto& pair : GetRenderer()->m_toggle_hot_keys) {
							if (pair.first == key) {
								keyAlreadyUsed = true;
								break;
							}
						}
						if (!keyAlreadyUsed) {
							GetRenderer()->m_toggle_hot_keys[key] = toggle;
						}

						break;
					}
				}
			}
			if (GetRenderer()->m_select_pressed) {
				*toggle = !*toggle;
				return true;
			}
		}
		return false;
	}
	void AddOption::BreakOption(const char* option)
	{
		GetRenderer()->m_last_option_base = (GetRenderer()->m_header_height + (GetRenderer()->m_menu_pos.y) + GetRenderer()->m_submenu_height + (GetRenderer()->m_max_vis_options - 1) * GetRenderer()->m_option_height);
		GetRenderer()->m_option_count++;
		if (GetRenderer()->m_up_pressed && GetRenderer()->m_option_count == GetRenderer()->m_current_option) {
			GetRenderer()->m_current_option--;
		}
		if (GetRenderer()->m_down_pressed && GetRenderer()->m_option_count == GetRenderer()->m_current_option) {
			GetRenderer()->m_current_option++;
		}
		bool selected = GetRenderer()->m_current_option == GetRenderer()->m_option_count ? true : false;
		if (GetRenderer()->m_current_option <= GetRenderer()->m_max_vis_options && GetRenderer()->m_option_count <= GetRenderer()->m_max_vis_options) {
			GetRenderer()->draw_center_text(option, GetRenderer()->m_break_text, Vector2(GetRenderer()->m_menu_pos.x, GetRenderer()->m_draw_base_y + (GetRenderer()->m_option_height / 2.f) - (GetRenderer()->get_text_height(GetRenderer()->m_break_font, GetRenderer()->m_break_font_size) / 1.5f)), GetRenderer()->m_break_font_size, GetRenderer()->m_break_font, false);
			if (selected)
				GetScroller()->Init();
		}
		else if (GetRenderer()->m_option_count > (GetRenderer()->m_current_option - GetRenderer()->m_max_vis_options) && GetRenderer()->m_option_count <= GetRenderer()->m_current_option) {
			GetRenderer()->draw_center_text(option, GetRenderer()->m_break_text, Vector2(GetRenderer()->m_menu_pos.x, GetRenderer()->m_last_option_base + (GetRenderer()->m_option_height / 2.f) - (GetRenderer()->get_text_height(GetRenderer()->m_break_font, GetRenderer()->m_break_font_size) / 1.5f)), GetRenderer()->m_break_font_size, GetRenderer()->m_break_font, false);
			if (selected)
				GetScroller()->Init();
		}
		if (GetRenderer()->m_option_count <= GetRenderer()->m_max_vis_options)
			GetRenderer()->m_draw_base_y += GetRenderer()->m_option_height;
	}
	bool AddOption::BoolNumberOption(const char* option, bool* toggle, float* numeral, float min, float max, float step, bool action_input)
	{ 
			GetRenderer()->add_option(option);
			bool selected = GetRenderer()->m_current_option == GetRenderer()->m_option_count ? true : false;
			if (GetRenderer()->m_current_option <= GetRenderer()->m_max_vis_options && GetRenderer()->m_option_count <= GetRenderer()->m_max_vis_options) {
				if (selected) {
					GetRenderer()->draw_sprite("commonmenu", "common_medal", Vector2(GetRenderer()->m_menu_pos.x + (GetRenderer()->m_width / GetRenderer()->m_right_padding + 0.07f) - (GetRenderer()->get_spirit_scale(GetRenderer()->m_toggle_size).x / 3.f), GetRenderer()->m_draw_base_y + (GetRenderer()->m_option_height / 2.f)), GetRenderer()->get_spirit_scale(GetRenderer()->m_toggle_size), 0.f, *toggle ? GetRenderer()->m_toggle_color_on : GetRenderer()->m_toggle_color_off);
					GetRenderer()->draw_sprite("commonmenu", "shop_arrows_upanddown", Vector2(GetRenderer()->m_menu_pos.x + (GetRenderer()->m_width / GetRenderer()->m_right_padding + 0.07f) - (GetRenderer()->get_spirit_scale(GetRenderer()->m_arrow_rotated_size).x / 2.f) - (GetRenderer()->get_spirit_scale(GetRenderer()->m_toggle_size).x / 2.8f), GetRenderer()->m_draw_base_y + (GetRenderer()->m_option_height / 2.f)), GetRenderer()->get_spirit_scale(GetRenderer()->m_arrow_rotated_size), 90.f, selected ? GetRenderer()->m_option_text_selected : GetRenderer()->m_option_text);
					GetRenderer()->draw_right_text(g_utility.fixed_decimel(*numeral), selected ? GetRenderer()->m_option_text_selected : GetRenderer()->m_option_text, Vector2(GetRenderer()->m_menu_pos.x + (GetRenderer()->m_width / GetRenderer()->m_right_padding + 0.07f) - 0.016f - (GetRenderer()->get_spirit_scale(GetRenderer()->m_toggle_size).x / 2.8f), GetRenderer()->m_draw_base_y + (GetRenderer()->m_option_height / 2.f) - (GetRenderer()->get_text_height(GetRenderer()->m_option_font, GetRenderer()->m_option_font_size) / 1.5f)), GetRenderer()->m_option_font_size, GetRenderer()->m_option_font, false);
				}
				else {
					GetRenderer()->draw_sprite("commonmenu", "common_medal", Vector2(GetRenderer()->m_menu_pos.x + (GetRenderer()->m_width / GetRenderer()->m_right_padding + 0.07f) - (GetRenderer()->get_spirit_scale(GetRenderer()->m_toggle_size).x / 3.f), GetRenderer()->m_draw_base_y + (GetRenderer()->m_option_height / 2.f)), GetRenderer()->get_spirit_scale(GetRenderer()->m_toggle_size), 0.f, *toggle ? GetRenderer()->m_toggle_color_on : GetRenderer()->m_toggle_color_off);
					GetRenderer()->draw_right_text(g_utility.fixed_decimel(*numeral), selected ? GetRenderer()->m_option_text_selected : GetRenderer()->m_option_text, Vector2(GetRenderer()->m_menu_pos.x + (GetRenderer()->m_width / GetRenderer()->m_right_padding + 0.07f) - 0.014f, GetRenderer()->m_draw_base_y + (GetRenderer()->m_option_height / 2.f) - (GetRenderer()->get_text_height(GetRenderer()->m_option_font, GetRenderer()->m_option_font_size) / 1.5f)), GetRenderer()->m_option_font_size, GetRenderer()->m_option_font, false);
				}
			}
			else if (GetRenderer()->m_option_count > (GetRenderer()->m_current_option - GetRenderer()->m_max_vis_options) && GetRenderer()->m_option_count <= GetRenderer()->m_current_option) {
				if (selected) {
					GetRenderer()->draw_sprite("commonmenu", "common_medal", Vector2(GetRenderer()->m_menu_pos.x + (GetRenderer()->m_width / GetRenderer()->m_right_padding + 0.07f) - (GetRenderer()->get_spirit_scale(GetRenderer()->m_toggle_size).x / 3.f), GetRenderer()->m_last_option_base + (GetRenderer()->m_option_height / 2.f)), GetRenderer()->get_spirit_scale(GetRenderer()->m_toggle_size), 0.f, *toggle ? GetRenderer()->m_toggle_color_on : GetRenderer()->m_toggle_color_off);
					GetRenderer()->draw_sprite("commonmenu", "shop_arrows_upanddown", Vector2(GetRenderer()->m_menu_pos.x + (GetRenderer()->m_width / GetRenderer()->m_right_padding + 0.07f) - (GetRenderer()->get_spirit_scale(GetRenderer()->m_arrow_rotated_size).x / 2.f) - (GetRenderer()->get_spirit_scale(GetRenderer()->m_toggle_size).x / 2.8f), GetRenderer()->m_last_option_base + (GetRenderer()->m_option_height / 2.f)), GetRenderer()->get_spirit_scale(GetRenderer()->m_arrow_rotated_size), 90.f, selected ? GetRenderer()->m_option_text_selected : GetRenderer()->m_option_text);
					GetRenderer()->draw_right_text(g_utility.fixed_decimel(*numeral), selected ? GetRenderer()->m_option_text_selected : GetRenderer()->m_option_text, Vector2(GetRenderer()->m_menu_pos.x + (GetRenderer()->m_width / GetRenderer()->m_right_padding + 0.07f) - 0.016f - (GetRenderer()->get_spirit_scale(GetRenderer()->m_toggle_size).x / 1.8f), GetRenderer()->m_last_option_base + (GetRenderer()->m_option_height / 2.f) - (GetRenderer()->get_text_height(GetRenderer()->m_option_font, GetRenderer()->m_option_font_size) / 1.5f)), GetRenderer()->m_option_font_size, GetRenderer()->m_option_font, false);
				}
				else {
					GetRenderer()->draw_sprite("commonmenu", "common_medal", Vector2(GetRenderer()->m_menu_pos.x + (GetRenderer()->m_width / GetRenderer()->m_right_padding + 0.07f) - (GetRenderer()->get_spirit_scale(GetRenderer()->m_toggle_size).x / 3.f), GetRenderer()->m_last_option_base + (GetRenderer()->m_option_height / 2.f)), GetRenderer()->get_spirit_scale(GetRenderer()->m_toggle_size), 0.f, *toggle ? GetRenderer()->m_toggle_color_on : GetRenderer()->m_toggle_color_off);
					GetRenderer()->draw_right_text(g_utility.fixed_decimel(*numeral), selected ? GetRenderer()->m_option_text_selected : GetRenderer()->m_option_text, Vector2(GetRenderer()->m_menu_pos.x + (GetRenderer()->m_width / GetRenderer()->m_right_padding + 0.07f) - 0.014f, GetRenderer()->m_last_option_base + (GetRenderer()->m_option_height / 2.f) - (GetRenderer()->get_text_height(GetRenderer()->m_option_font, GetRenderer()->m_option_font_size) / 1.5f)), GetRenderer()->m_option_font_size, GetRenderer()->m_option_font, false);
				}
			}
			if (GetRenderer()->m_option_count <= GetRenderer()->m_max_vis_options) {
				GetRenderer()->m_draw_base_y += GetRenderer()->m_option_height;
			}
			if (selected) {
				if (GetRenderer()->m_left_pressed) {
					if (*numeral >= min) {
						*numeral -= step;
					}
					else {
						*numeral = max;
					}
					if (action_input) {
						return true;
					}
				}
				if (GetRenderer()->m_right_pressed) {
					if (*numeral < max) {
						*numeral += step;
					}
					else {
						*numeral = min;
					}
					if (action_input) {
						return true;
					}
				}
				if (GetRenderer()->m_select_pressed) {
					*toggle = !*toggle;
					if (GetInput()->is_key_pressed(VK_LSHIFT)) {
						const char* keyboard = g_gta_utility.draw_keyboard();
						if (keyboard) {
							*numeral = std::atof(keyboard);
						}
					}
					return true;
				}

				return false;
			}
	}

	AddOption* addOption() { return &g_addOption; }
}
