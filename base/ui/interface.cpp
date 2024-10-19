#include "interface.hpp"
#include "../invoker/Natives.hpp"
#include "../script/script.hpp"
#include "../MemoryEdit.h"
#include "../scaleform.h"
#include "../Settings.hpp"
#include "../animatedYTD.h"
#include "../ControlUtil.h"
#include "../keyboard.hpp"
#include "../Translation.hpp"
#include "../Header.hpp"
#include "../Tab.hpp"
#include "../sub.hpp"
#include "../Background.hpp"
#include "../Footer.hpp"
#include "../Scroller.hpp"
#include "../Mousse.hpp"
#include "../MenuInput.hpp"
#include "../description.hpp"
namespace VX {

	interface g_interface;

	float interface::get_text_width(char const* text, int32_t font, float scaleOverride) {
		HUD::BEGIN_TEXT_COMMAND_GET_WIDTH_("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_WEBSITE(text);
		float scale = m_option_height;
		HUD::SET_TEXT_FONT(0);
		if (font != -1) {
			scale = scaleOverride * m_global_scale;
			HUD::SET_TEXT_FONT(font);
		}
		HUD::SET_TEXT_SCALE(0.0f, scale);
		return HUD::END_TEXT_COMMAND_GET_WIDTH_(TRUE);
	}
	void interface::Spriter(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a)
	{
		if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED((char*)Streamedtexture.c_str()))
		{
			GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT((char*)Streamedtexture.c_str(), false);
		}
		else
		{
			GRAPHICS::DRAW_SPRITE((char*)Streamedtexture.c_str(), (char*)textureName.c_str(), x, y, width, height, rotation, r, g, b, a);
		}
	}
	float interface::get_text_height(int32_t font, float size) {
		return HUD::GET_RENDERED_CHARACTER_HEIGHT(size, font);
	}
	void interface::draw_sprite_aligned(std::pair<std::string, std::string> asset, Vector2 position, Vector2 scale, float rotation, RGBA color) {

		if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(asset.first.c_str()) && asset.first != "aethertextures") {
			GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(asset.first.c_str(), true);
		}

		GRAPHICS::DRAW_SPRITE(asset.first.c_str(), asset.second.c_str(), position.x + (scale.x * 0.5f), position.y + (scale.y * 0.5f), scale.x, scale.y, rotation, color.r, color.g, color.b, color.a);
	}
	void interface::draw_text2(std::string text, Vector2 position, float scale, int font, RGBA color, eJustify justification, Vector2 wrap) {
		HUD::SET_TEXT_WRAP(wrap.x, wrap.y);

		if (justification != JUSTIFY_LEFT) {
			//  HUD::SET_TEXT_JUSTIFICATION(justification = JUSTIFY_CENTER ? 0 : 2);
		}

		HUD::SET_TEXT_CENTRE(justification == JUSTIFY_CENTER);
		HUD::SET_TEXT_SCALE(0.f, scale);
		HUD::SET_TEXT_COLOUR(color.r, color.g, color.b, color.a);
		HUD::SET_TEXT_FONT(font);

		if (text.length() >= 98) {
			render_queue[render_queue_index] = text;
			render_queue_index++;
			render_queue_index %= 100;
		}

		HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
		HUD::END_TEXT_COMMAND_DISPLAY_TEXT(position.x, position.y, 0);
	}
	float interface::get_normalized_font_scale(int font, float scale) {
		switch (font) {
		case 0: return (scale * 1.0f);
		case 1: return (scale * 1.3f);
		case 2: return (scale * 1.11f);
		case 4: return (scale * 1.11f);
		case 7: return (scale * 1.29f);
		}

		return scale;
	}
	Vector2 interface::get_spirit_scale(float size) {
		int x;
		int y;
		GRAPHICS::GET_ACTIVE_SCREEN_RESOLUTION_(&x, &y);
		return Vector2(((float)y / (float)x) * size, size);
	}

	void interface::draw_left_text(char const* text, RGBA color, Vector2 position, float size, int font, bool outline) {
		HUD::SET_TEXT_SCALE(size * m_global_scale, size * m_global_scale);
		HUD::SET_TEXT_FONT(font);
		HUD::SET_TEXT_COLOUR(color.r, color.g, color.b, color.a);
		if (outline)
			HUD::SET_TEXT_OUTLINE();
		HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
		HUD::END_TEXT_COMMAND_DISPLAY_TEXT(position.x * m_global_scale, position.y * m_global_scale, 0);
	}

	void interface::draw_right_text(char const* text, RGBA color, Vector2 position, float size, int font, bool outline) {
		HUD::SET_TEXT_WRAP(0.f, position.x * m_global_scale);
		HUD::SET_TEXT_RIGHT_JUSTIFY(true);
		draw_left_text(text, color, position, size, font, outline);
	}

	void interface::draw_center_text(char const* text, RGBA color, Vector2 position, float size, int font, bool outline) {
		HUD::SET_TEXT_CENTRE(true);
		draw_left_text(text, color, position, size, font, outline);
	}

	void interface::draw_sprite(char const* dict, char const* texture, Vector2 position, Vector2 size, float rotation, RGBA color) {
		if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(dict))
			GRAPHICS::DRAW_SPRITE(dict, texture, position.x * m_global_scale, position.y * m_global_scale, size.x * m_global_scale, size.y * m_global_scale, rotation, color.r, color.g, color.b, color.a);
		else
			GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(dict, false);
	}
	void interface::DrawSpriteV2(Texture texture, float x, float y, float w, float h, float heading, RGBA color, bool renderIfNotStreamed) {
		bool streamed = GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(texture.dict);
		if (streamed || renderIfNotStreamed) GRAPHICS::DRAW_SPRITE(texture.dict, texture.id, x, y, w, h, heading, color.r, color.g, color.b, color.a);
		if (!streamed) GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(texture.dict, 0);
	}
	void interface::DrawString(String text, float x, float y, int font, float scale, RGBA color, bool outline, int justify, float textWrapMin, float textWrapMax) {
		HUD::SET_TEXT_FONT(font);

		// justify: 0 - center, 1 - left, 2 - right (-1 = ignore)
		if (justify != -1) {
			if (justify == 2)
				HUD::SET_TEXT_WRAP(m_menu_pos.x - m_width / 2, m_menu_pos.x + m_width / 2 - 0.015f / 2.0f);
			HUD::SET_TEXT_JUSTIFICATION(justify);
		}

		// fix for Chalet London sizing 
		if (font == 0) {
			scale *= 0.75f;
			y += 0.003f;
		}
		if (font == 0) {
			y += 0.003f;
		}

		HUD::SET_TEXT_SCALE(0.0f, scale);
		HUD::SET_TEXT_COLOUR(color.r, color.g, color.b, color.a);

		if (textWrapMin != 0 || textWrapMax != 0) HUD::SET_TEXT_WRAP(textWrapMin, textWrapMax);

		HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
		HUD::END_TEXT_COMMAND_DISPLAY_TEXT(x, y, 0);
	}
	void interface::draw_rect(RGBA color, Vector2 position, Vector2 size) {
		GRAPHICS::DRAW_RECT(position.x * m_global_scale, position.y * m_global_scale, size.x * m_global_scale, size.y * m_global_scale, color.r, color.g, color.b, color.a, 0);
	}

	void interface::play_frontend_sound(char const* sound_name) {
		AUDIO::PLAY_SOUND_FRONTEND(-1, sound_name, "HUD_FRONTEND_DEFAULT_SOUNDSET", false);
	}

	void interface::forward_menu(void(*menu)(), char const* sub_menu) {
		m_menu_array[m_menu_level] = m_current_menu;
		m_sub_menu_array[m_menu_level] = m_current_sub_menu;
		m_option_array[m_menu_level] = m_current_option;
		m_menu_level++;
		m_current_menu = menu;
		m_current_sub_menu = sub_menu;
		m_current_option = 1;
	}

	void interface::back_menu() {
		m_menu_level--;
		m_current_menu = m_menu_array[m_menu_level];
		m_current_sub_menu = m_sub_menu_array[m_menu_level];
		m_current_option = m_option_array[m_menu_level];
	}
	void interface::draw_tick() {

		HUD::DISPLAY_HUD_WHEN_PAUSED_THIS_FRAME();
		GRAPHICS::FORCE_RENDER_IN_GAME_UI(true);
		GRAPHICS::SET_SCRIPT_GFX_DRAW_BEHIND_PAUSEMENU(true);
		GetScaleform()->PrepareInstructionalButtons();
		GetScaleform()->DrawInstructional("Open Virtual X", "F5");
		//GetMousse()->MousseInput();
		GetScaleform()->FinishInstructionalButtons();
		GetMenuInput()->CheckInput();
		//GetMousse()->Init();
		if (m_menu_level != 0 && m_opened) {
			m_draw_base_y = m_menu_pos.y;
			GetHeader()->Init();
			if (tab_activate)
			{
				GetTab()->Init(m_current_sub_menu);
			}
			else
			{
				GetSubBar()->Init(m_current_sub_menu);
			}
			GetBackground()->Init();
			m_current_menu();
			GetFooter()->Init();
		}
		update_hotkeys();
		m_hotkey_pressed = false;
		m_select_pressed = false;
		m_up_pressed = false;
		m_down_pressed = false;
		m_left_pressed = false;
		m_right_pressed = false;
		if (Current_Tab == 0)
		{
			FirstTabSelected = true;
			SecondTabSelected = false;
		}
		else if (Current_Tab == 1)
		{
			FirstTabSelected = false;
			SecondTabSelected = true;
		}
	}

	void interface::add_option(const char* option) {
		m_last_option_base = (m_header_height + (m_menu_pos.y) + m_submenu_height + ((m_option_count - (m_current_option - m_max_vis_options)) * m_option_height));
		m_option_count++;
		bool selected = m_current_option == m_option_count ? true : false;
		if (m_current_option <= m_max_vis_options && m_option_count <= m_max_vis_options) {
			draw_left_text(option, selected ? m_option_text_selected : m_option_text, Vector2(m_menu_pos.x - (m_width / m_left_padding), m_draw_base_y + (m_option_height / 2.f) - (get_text_height(m_option_font, m_option_font_size) / 1.5f)), m_option_font_size, m_option_font, false);
			if (selected)
				GetScroller()->Init();
		}
		else if ((m_option_count > (m_current_option - m_max_vis_options)) && m_option_count <= m_current_option) {
			draw_left_text(option, selected ? m_option_text_selected : m_option_text, Vector2(m_menu_pos.x - (m_width / m_left_padding), m_last_option_base + (m_option_height / 2.f) - (get_text_height(m_option_font, m_option_font_size) / 1.5f)), m_option_font_size, m_option_font, false);
			if (selected)
				GetScroller()->Init();
		}
	}

	bool interface::draw_regular(const char* option) {
		add_option(option);
		if (m_option_count <= m_max_vis_options)
			m_draw_base_y += m_option_height;
		if (m_option_count == m_current_option)
			if (m_select_pressed)
				return true;
		return false;
	}
	bool interface::draw_link(const char* option) {
		add_option(option);
		draw_sprite("VX", "link", Vector2(m_menu_pos.x + (m_width / m_right_padding + 0.06f), m_draw_base_y + (m_option_height / 2.f)), Vector2(0.0150f, 0.030f), 0, m_line_background);
		if (m_option_count <= m_max_vis_options)
			m_draw_base_y += m_option_height;
		if (m_option_count == m_current_option)
			if (m_select_pressed)
				return true;
		return false;
	}

	Vector2 interface::get_mouse_pos() {
		return Vector2{
			PAD::GET_DISABLED_CONTROL_NORMAL(2, static_cast<int>(eControllerInputs::INPUT_CURSOR_X)),
				PAD::GET_DISABLED_CONTROL_NORMAL(2, static_cast<int>(eControllerInputs::INPUT_CURSOR_Y))
		};
	}
	void interface::move_menu_with_mouse(Vector2 mousePos, Vector2 initialMenuPosition) {
		auto offsets = mousePos;
		auto currentMousePos = get_mouse_pos();

		GetRenderer()->m_menu_pos = currentMousePos;
	}
	bool interface::is_point_in_rect(Vector2 point, Vector2 rectPos, Vector2 rectSize) {
		auto left = rectPos.x - (rectSize.x / 2.f);
		auto right = rectPos.x + (rectSize.x / 2.f);
		auto top = rectPos.y + (rectSize.y / 2.f);
		auto bottom = rectPos.y - (rectSize.y / 2.f);

		return point.x <= right && point.x >= left && point.y <= top && point.y >= bottom;
	}
	void interface::update_hotkeys() {
		for (const auto& pair : m_toggle_hot_keys) {
			int key = pair.first;
			bool* toggle = pair.second;
			if (GetTickCount64() - m_previous_tick > m_delay) {
				if (GetAsyncKeyState(key) & 0x8000) {
					*toggle = !*toggle;
					m_previous_tick = GetTickCount64();

				}
			}
		}
	}
	void interface::save_key_toggles(const std::string& filename) {
		std::ofstream file(filename);
		if (file.is_open()) {
			for (const auto& pair : m_toggle_hot_keys) {
				int key = pair.first;
				bool toggle = *pair.second;

				file << key << " " << (toggle ? "1" : "0") << std::endl;
			}

			file.close();
			g_log.send("hotkeys", "Hotkeys saved.");
		}
		else {
			g_log.send("hotkeys", "Failed to save hotkeys.");
		}
	}

	void interface::load_key_toggles(const std::string& filename) {
		std::ifstream file(filename);
		if (file.is_open()) {
			m_toggle_hot_keys.clear();

			int key;
			int toggleValue;
			while (file >> key >> toggleValue) {
				bool toggle = (toggleValue != 0);
				m_toggle_hot_keys[key] = new bool(toggle);
			}

			file.close();
			g_log.send("hotkeys", "Hotkeys loaded.");
		}
		else {
			g_log.send("hotkeys", "Failed to load hotkeys.");
		}
	}

	int interface::get_assigned_key(bool* toggle) {
		for (const auto& pair : m_toggle_hot_keys) {
			int key = pair.first;
			bool* assignedToggle = pair.second;
			if (assignedToggle == toggle) {
				return key;
			}
		}
		return -1;
	}
	

	bool interface::draw_number(const char* option, float* numeral, float min, float max, float step, bool action_input) {
		add_option(option);
		bool selected = m_current_option == m_option_count ? true : false;
		if (m_current_option <= m_max_vis_options && m_option_count <= m_max_vis_options) {
			if (selected) {
				draw_sprite("commonmenu", "shop_arrows_upanddown", Vector2(m_menu_pos.x + (m_width / m_right_padding + 0.07f) - (get_spirit_scale(m_arrow_rotated_size).x / 2.f), m_draw_base_y + (m_option_height / 2.f)), get_spirit_scale(m_arrow_rotated_size), 90.f, selected ? m_option_text_selected : m_option_text);
				draw_right_text(g_utility.fixed_decimel(*numeral), selected ? m_option_text_selected : m_option_text, Vector2(m_menu_pos.x + (m_width / m_right_padding + 0.07f) - 0.0165f, m_draw_base_y + (m_option_height / 2.f) - (get_text_height(m_option_font, m_option_font_size) / 1.5f)), m_option_font_size, m_option_font, false);
			}
			else {
				draw_right_text(g_utility.fixed_decimel(*numeral), selected ? m_option_text_selected : m_option_text, Vector2(m_menu_pos.x + (m_width / m_right_padding + 0.07f) - 0.0015f, m_draw_base_y + (m_option_height / 2.f) - (get_text_height(m_option_font, m_option_font_size) / 1.5f)), m_option_font_size, m_option_font, false);
			}
		}
		else if (m_option_count > (m_current_option - m_max_vis_options) && m_option_count <= m_current_option) {
			if (selected) {
				draw_sprite("commonmenu", "shop_arrows_upanddown", Vector2(m_menu_pos.x + (m_width / m_right_padding + 0.07f) - (get_spirit_scale(m_arrow_rotated_size).x / 2.f), m_last_option_base + (m_option_height / 2.f)), get_spirit_scale(m_arrow_rotated_size), 90.f, selected ? m_option_text_selected : m_option_text);
				draw_right_text(g_utility.fixed_decimel(*numeral), selected ? m_option_text_selected : m_option_text, Vector2(m_menu_pos.x + (m_width / m_right_padding + 0.07f) - 0.0165f, m_last_option_base + (m_option_height / 2.f) - (get_text_height(m_option_font, m_option_font_size) / 1.5f)), m_option_font_size, m_option_font, false);
			}
			else {
				draw_right_text(g_utility.fixed_decimel(*numeral), selected ? m_option_text_selected : m_option_text, Vector2(m_menu_pos.x + (m_width / m_right_padding + 0.07f) - 0.0015f, m_last_option_base + (m_option_height / 2.f) - (get_text_height(m_option_font, m_option_font_size) / 1.5f)), m_option_font_size, m_option_font, false);
			}
		}
		if (m_option_count <= m_max_vis_options) {
			m_draw_base_y += m_option_height;
		}
		if (m_option_count == m_current_option) {
			if (m_left_pressed) {
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
			if (m_right_pressed) {
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
			if (m_select_pressed) {
				const char* keyboard = g_gta_utility.draw_keyboard();
				if (keyboard) {
					*numeral = std::atof(keyboard);
				}
				return true;
			}
		}
		return false;
	}

	bool interface::draw_number(const char* option, int* numeral, int min, int max, int step, bool action_input) {
		add_option(option);
		bool selected = m_current_option == m_option_count ? true : false;
		std::string right_text = std::format("{}", *numeral);
		if (m_current_option <= m_max_vis_options && m_option_count <= m_max_vis_options) {
			if (selected) {
				draw_sprite("commonmenu", "shop_arrows_upanddown", Vector2(m_menu_pos.x + (m_width / m_right_padding + 0.07f) - (get_spirit_scale(m_arrow_rotated_size).x / 2.f), m_draw_base_y + (m_option_height / 2.f)), get_spirit_scale(m_arrow_rotated_size), 90.f, selected ? m_option_text_selected : m_option_text);
				draw_right_text(right_text.c_str(), selected ? m_option_text_selected : m_option_text, Vector2(m_menu_pos.x + (m_width / m_right_padding + 0.07f) - 0.0165f, m_draw_base_y + (m_option_height / 2.f) - (get_text_height(m_option_font, m_option_font_size) / 1.5f)), m_option_font_size, m_option_font, false);
			}
			else {
				draw_right_text(right_text.c_str(), selected ? m_option_text_selected : m_option_text, Vector2(m_menu_pos.x + (m_width / m_right_padding + 0.07f) - 0.0015f, m_draw_base_y + (m_option_height / 2.f) - (get_text_height(m_option_font, m_option_font_size) / 1.5f)), m_option_font_size, m_option_font, false);
			}
		}
		else if (m_option_count > (m_current_option - m_max_vis_options) && m_option_count <= m_current_option) {
			if (selected) {
				draw_sprite("commonmenu", "shop_arrows_upanddown", Vector2(m_menu_pos.x + (m_width / m_right_padding + 0.07f) - (get_spirit_scale(m_arrow_rotated_size).x / 2.f), m_last_option_base + (m_option_height / 2.f)), get_spirit_scale(m_arrow_rotated_size), 90.f, selected ? m_option_text_selected : m_option_text);
				draw_right_text(g_utility.fixed_decimel(*numeral), selected ? m_option_text_selected : m_option_text, Vector2(m_menu_pos.x + (m_width / m_right_padding + 0.07f) - 0.0165f, m_last_option_base + (m_option_height / 2.f) - (get_text_height(m_option_font, m_option_font_size) / 1.5f)), m_option_font_size, m_option_font, false);
			}
			else {
				draw_right_text(g_utility.fixed_decimel(*numeral), selected ? m_option_text_selected : m_option_text, Vector2(m_menu_pos.x + (m_width / m_right_padding + 0.07f) - 0.0015f, m_last_option_base + (m_option_height / 2.f) - (get_text_height(m_option_font, m_option_font_size) / 1.5f)), m_option_font_size, m_option_font, false);
			}
		}
		if (m_option_count <= m_max_vis_options) {
			m_draw_base_y += m_option_height;
		}
		if (selected) {
			if (m_left_pressed) {
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
			if (m_right_pressed) {
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
			if (m_select_pressed) {
				const char* keyboard = g_gta_utility.draw_keyboard();
				if (keyboard) {
					*numeral = std::atoi(keyboard);
				}
				return true;
			}
		}
		return false;
	}

	bool interface::draw_array(const char* option, const char** array, int* position, bool action_input) {
		add_option(option);
		bool selected = m_current_option == m_option_count ? true : false;
		int max = sizeof(array) / sizeof(array[0]) + 1;
		std::string right_text = std::format("{}", array[*position]);
		if (m_current_option <= m_max_vis_options && m_option_count <= m_max_vis_options) {
			if (selected) {
				draw_sprite("commonmenu", "shop_arrows_upanddown", Vector2(m_menu_pos.x + (m_width / m_right_padding + 0.07f) - (get_spirit_scale(m_arrow_rotated_size).x / 2.f), m_draw_base_y + (m_option_height / 2.f)), get_spirit_scale(m_arrow_rotated_size), 90.f, selected ? m_option_text_selected : m_option_text);
				draw_right_text(right_text.c_str(), selected ? m_option_text_selected : m_option_text, Vector2(m_menu_pos.x + (m_width / m_right_padding + 0.07f) - 0.0165f, m_draw_base_y + (m_option_height / 2.f) - (get_text_height(m_option_font, m_option_font_size) / 1.5f)), m_option_font_size, m_option_font, false);
			}
			else {
				draw_right_text(right_text.c_str(), selected ? m_option_text_selected : m_option_text, Vector2(m_menu_pos.x + (m_width / m_right_padding + 0.07f) - 0.0015f, m_draw_base_y + (m_option_height / 2.f) - (get_text_height(m_option_font, m_option_font_size) / 1.5f)), m_option_font_size, m_option_font, false);
			}
		}
		else if (m_option_count > (m_current_option - m_max_vis_options) && m_option_count <= m_current_option) {
			if (selected) {
				draw_sprite("commonmenu", "shop_arrows_upanddown", Vector2(m_menu_pos.x + (m_width / m_right_padding + 0.07f) - (get_spirit_scale(m_arrow_rotated_size).x / 2.f), m_last_option_base + (m_option_height / 2.f)), get_spirit_scale(m_arrow_rotated_size), 90.f, selected ? m_option_text_selected : m_option_text);
				draw_right_text(right_text.c_str(), selected ? m_option_text_selected : m_option_text, Vector2(m_menu_pos.x + (m_width / m_right_padding + 0.07f) - 0.0165f, m_last_option_base + (m_option_height / 2.f) - (get_text_height(m_option_font, m_option_font_size) / 1.5f)), m_option_font_size, m_option_font, false);
			}
			else {
				draw_right_text(right_text.c_str(), selected ? m_option_text_selected : m_option_text, Vector2(m_menu_pos.x + (m_width / m_right_padding + 0.07f), m_last_option_base + (m_option_height / 2.f) - (get_text_height(m_option_font, m_option_font_size) / 1.5f)), m_option_font_size, m_option_font, false);
			}
		}
		if (m_option_count <= m_max_vis_options) {
			m_draw_base_y += m_option_height;
		}
		if (m_current_option == m_option_count) {
			if (m_left_pressed) {
				if (*position > 0) {
					*position -= 1;
				}
				else {
					*position = max;
				}
				if (action_input) {
					return true;
				}
			}
			if (m_right_pressed) {
				if (*position < max) {
					*position += 1;
				}
				else {
					*position = 0;
				}
				if (action_input) {
					return true;
				}
			}
			if (m_select_pressed) {
				return true;
			}
		}
		return false;
	}

	bool interface::draw_bool_array(const char* option, const char* textDesc, bool* toggle, const char** array, int* position, bool action_input) {
		add_option(option);
		GetDescription()->Init(textDesc);
		bool selected = m_current_option == m_option_count ? true : false;
		int max = sizeof(array) / sizeof(array[0]) + 1;
		std::string right_text = std::format("{}", array[*position]);
		if (m_current_option <= m_max_vis_options && m_option_count <= m_max_vis_options) {
			if (selected) {
				draw_sprite("commonmenu", "common_medal", Vector2(m_menu_pos.x + (m_width / m_right_padding) - (get_spirit_scale(m_toggle_size).x / 3.f), m_draw_base_y + (m_option_height / 2.f)), get_spirit_scale(m_toggle_size), 0.f, *toggle ? m_toggle_color_on : m_toggle_color_off);
				draw_sprite("commonmenu", "shop_arrows_upanddown", Vector2(m_menu_pos.x + (m_width / m_right_padding) - (get_spirit_scale(m_arrow_rotated_size).x / 2.f) - (get_spirit_scale(m_toggle_size).x / 2.8f), m_draw_base_y + (m_option_height / 2.f)), get_spirit_scale(m_arrow_rotated_size), 90.f, selected ? m_option_text_selected : m_option_text);
				draw_right_text(right_text.c_str(), selected ? m_option_text_selected : m_option_text, Vector2(m_menu_pos.x + (m_width / m_right_padding) - 0.016f - (get_spirit_scale(m_toggle_size).x / 2.8f), m_draw_base_y + (m_option_height / 2.f) - (get_text_height(m_option_font, m_option_font_size) / 1.5f)), m_option_font_size, m_option_font, false);
			}
			else {
				draw_sprite("commonmenu", "common_medal", Vector2(m_menu_pos.x + (m_width / m_right_padding) - (get_spirit_scale(m_toggle_size).x / 3.f), m_draw_base_y + (m_option_height / 2.f)), get_spirit_scale(m_toggle_size), 0.f, *toggle ? m_toggle_color_on : m_toggle_color_off);
				draw_right_text(right_text.c_str(), selected ? m_option_text_selected : m_option_text, Vector2(m_menu_pos.x + (m_width / m_right_padding) - 0.014f, m_draw_base_y + (m_option_height / 2.f) - (get_text_height(m_option_font, m_option_font_size) / 1.5f)), m_option_font_size, m_option_font, false);
			}
		}
		else if (m_option_count > (m_current_option - m_max_vis_options) && m_option_count <= m_current_option) {
			if (selected) {
				draw_sprite("commonmenu", "common_medal", Vector2(m_menu_pos.x + (m_width / m_right_padding) - (get_spirit_scale(m_toggle_size).x / 3.f), m_last_option_base + (m_option_height / 2.f)), get_spirit_scale(m_toggle_size), 0.f, *toggle ? m_toggle_color_on : m_toggle_color_off);
				draw_sprite("commonmenu", "shop_arrows_upanddown", Vector2(m_menu_pos.x + (m_width / m_right_padding) - (get_spirit_scale(m_arrow_rotated_size).x / 2.f) - (get_spirit_scale(m_toggle_size).x / 2.8f), m_last_option_base + (m_option_height / 2.f)), get_spirit_scale(m_arrow_rotated_size), 90.f, selected ? m_option_text_selected : m_option_text);
				draw_right_text(right_text.c_str(), selected ? m_option_text_selected : m_option_text, Vector2(m_menu_pos.x + (m_width / m_right_padding) - 0.016f - (get_spirit_scale(m_toggle_size).x / 1.8f), m_last_option_base + (m_option_height / 2.f) - (get_text_height(m_option_font, m_option_font_size) / 1.5f)), m_option_font_size, m_option_font, false);
			}
			else {
				draw_sprite("commonmenu", "common_medal", Vector2(m_menu_pos.x + (m_width / m_right_padding) - (get_spirit_scale(m_toggle_size).x / 3.f), m_last_option_base + (m_option_height / 2.f)), get_spirit_scale(m_toggle_size), 0.f, *toggle ? m_toggle_color_on : m_toggle_color_off);
				draw_right_text(right_text.c_str(), selected ? m_option_text_selected : m_option_text, Vector2(m_menu_pos.x + (m_width / m_right_padding) - 0.014f, m_last_option_base + (m_option_height / 2.f) - (get_text_height(m_option_font, m_option_font_size) / 1.5f)), m_option_font_size, m_option_font, false);
			}
		}
		if (m_option_count <= m_max_vis_options) {
			m_draw_base_y += m_option_height;
		}
		if (m_current_option == m_option_count) {
			if (m_left_pressed) {
				if (*position > 0) {
					*position -= 1;
				}
				else {
					*position = max;
				}
				if (action_input) {
					return true;
				}
			}
			if (m_right_pressed) {
				if (*position < max) {
					*position += 1;
				}
				else {
					*position = 0;
				}
				if (action_input) {
					return true;
				}
			}
			if (m_select_pressed) {
				*toggle = !*toggle;
				return true;
			}
		}
		return false;
	}

	void interface::DrawRect(float x, float y, float width, float height, RGBA color)
	{
		GRAPHICS::DRAW_RECT(x, y, width, height, color.r, color.g, color.b, color.a, 0);
	}
	void interface::PlayerInfoText(std::string text, RGBAF rgbaf, Vector2 position, Vector2 size, bool center, bool right)
	{
		HUD::SET_TEXT_RIGHT_JUSTIFY(right);
		HUD::SET_TEXT_CENTRE(center);
		HUD::SET_TEXT_COLOUR(rgbaf.r, rgbaf.g, rgbaf.b, rgbaf.a);
		HUD::SET_TEXT_FONT(m_playerinfo_font);
		HUD::SET_TEXT_SCALE(size.x, size.y);
		HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT((char*)"STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.data());
		HUD::END_TEXT_COMMAND_DISPLAY_TEXT(position.x, position.y, NULL);
	}
	void interface::DrawBox(float x, float y, float width, float height, String title, bool gradients, Texture texture, bool customColor, RGBA color) {
		if (gradients && m_cPrimary.r == 0 && m_cPrimary.g == 0 && m_cPrimary.b == 0 && m_cPrimary.a == 255) {
			DrawSpriteV2(texture, x, y - height / 2 + m_dialogHeaderHeight / 2, width, m_dialogHeaderHeight, 0.0f, { m_cPrimary.r, m_cPrimary.g, m_cPrimary.b, m_cPrimary.a });
			DrawSpriteV2(texture, x, y + height / 2 - m_dialogFooterHeight / 2, width, m_dialogFooterHeight, 180, { m_cPrimary.r, m_cPrimary.g, m_cPrimary.b, m_cPrimary.a });
			//DrawRect(x, y, width, height, { customColor ? color.m_r : m_cPrimary.m_r, customColor ? color.m_g : m_cPrimary.m_g, customColor ? color.m_b : m_cPrimary.m_b, customColor ? color.m_a : (int)m_bgOpacity * 255 / 100 });
			DrawRect(x, y + m_dialogHeaderHeight / 2 - m_dialogFooterHeight / 2, width, height - m_dialogHeaderHeight - m_dialogFooterHeight, { m_cPrimary.r, m_cPrimary.g, m_cPrimary.b, (int)m_bgOpacity * 255 / 100 });
		}
		else DrawRect(x, y, width, height, { customColor ? color.r : m_cPrimary.r, customColor ? color.g : m_cPrimary.g, customColor ? color.b : m_cPrimary.b, customColor ? color.a : (int)m_bgOpacity * 255 / 100 });


		DrawString(title, x - width / 2 + 0.01f, y - height / 2 + 0.005f, 7, 0.5f, m_cOption, true);

		DrawRect(x, y - height / 2, width + m_lineWidth * 2, m_lineWidth, m_cPrimary); //Top
		DrawRect(x, y + height / 2, width + m_lineWidth * 2, m_lineWidth, m_cPrimary); //Bottom
		DrawRect(x - width / 2, y, m_lineWidth, height + m_lineWidth * 2, m_cPrimary); //Left
		DrawRect(x + width / 2, y, m_lineWidth, height + m_lineWidth * 2, m_cPrimary); //Right

		DrawRect(x, y - height / 2 - m_lineWidth, width + m_lineWidth * 2, m_lineWidth, m_cOutline); //Top
		DrawRect(x, y + height / 2 + m_lineWidth, width + m_lineWidth * 2, m_lineWidth, m_cOutline); //Bottom
		DrawRect(x - width / 2 - m_lineWidth, y, m_lineWidth, height + m_lineWidth * 3, m_cOutline); //Left
		DrawRect(x + width / 2 + m_lineWidth, y, m_lineWidth, height + m_lineWidth * 3, m_cOutline); //Right
	}

	void interface::DrawInWorldBox(Entity entity, RGBA color) {
		Vector3 Min;
		Vector3 Max;
		MISC::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(entity), &Min, &Max);
		float BoxWidth = Max.x * 2;
		float BoxLength = Max.y * 2;
		float BoxHeight = Max.z * 2;

		Vector3 P1 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(entity, (BoxWidth / 2) * -1, (BoxLength / 2), BoxHeight / 2);
		Vector3 P4 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(entity, BoxWidth / 2, (BoxLength / 2), BoxHeight / 2);
		Vector3 P5 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(entity, (BoxWidth / 2) * -1, (BoxLength / 2), (BoxHeight / 2) * -1);
		Vector3 P7 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(entity, BoxWidth / 2, (BoxLength / 2), (BoxHeight / 2) * -1);
		Vector3 P2 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(entity, (BoxWidth / 2) * -1, (BoxLength / 2) * -1, BoxHeight / 2);
		Vector3 P3 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(entity, BoxWidth / 2, (BoxLength / 2) * -1, BoxHeight / 2);
		Vector3 P6 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(entity, (BoxWidth / 2) * -1, (BoxLength / 2) * -1, (BoxHeight / 2) * -1);
		Vector3 P8 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(entity, BoxWidth / 2, (BoxLength / 2) * -1, (BoxHeight / 2) * -1);

		GRAPHICS::DRAW_LINE(P1.x, P1.y, P1.z, P4.x, P4.y, P4.z, color.r, color.g, color.b, color.a);
		GRAPHICS::DRAW_LINE(P1.x, P1.y, P1.z, P2.x, P2.y, P2.z, color.r, color.g, color.b, color.a);
		GRAPHICS::DRAW_LINE(P1.x, P1.y, P1.z, P5.x, P5.y, P5.z, color.r, color.g, color.b, color.a);
		GRAPHICS::DRAW_LINE(P2.x, P2.y, P2.z, P3.x, P3.y, P3.z, color.r, color.g, color.b, color.a);
		GRAPHICS::DRAW_LINE(P3.x, P3.y, P3.z, P8.x, P8.y, P8.z, color.r, color.g, color.b, color.a);
		GRAPHICS::DRAW_LINE(P4.x, P4.y, P4.z, P7.x, P7.y, P7.z, color.r, color.g, color.b, color.a);
		GRAPHICS::DRAW_LINE(P4.x, P4.y, P4.z, P3.x, P3.y, P3.z, color.r, color.g, color.b, color.a);
		GRAPHICS::DRAW_LINE(P5.x, P5.y, P5.z, P7.x, P7.y, P7.z, color.r, color.g, color.b, color.a);
		GRAPHICS::DRAW_LINE(P6.x, P6.y, P6.z, P2.x, P2.y, P2.z, color.r, color.g, color.b, color.a);
		GRAPHICS::DRAW_LINE(P6.x, P6.y, P6.z, P8.x, P8.y, P8.z, color.r, color.g, color.b, color.a);
		GRAPHICS::DRAW_LINE(P5.x, P5.y, P5.z, P6.x, P6.y, P6.z, color.r, color.g, color.b, color.a);
		GRAPHICS::DRAW_LINE(P7.x, P7.y, P7.z, P8.x, P8.y, P8.z, color.r, color.g, color.b, color.a);
	}

	void interface::disbale_controls()
	{
		HUD::HIDE_HELP_TEXT_THIS_FRAME();
		CAM::SET_CINEMATIC_BUTTON_ACTIVE(1);

		HUD::HIDE_HUD_COMPONENT_THIS_FRAME(HUD_HELP_TEXT);
		HUD::HIDE_HUD_COMPONENT_THIS_FRAME(HUD_VEHICLE_NAME);
		HUD::HIDE_HUD_COMPONENT_THIS_FRAME(HUD_AREA_NAME);
		HUD::HIDE_HUD_COMPONENT_THIS_FRAME(HUD_STREET_NAME);
		HUD::HIDE_HUD_COMPONENT_THIS_FRAME(HUD_VEHICLE_CLASS);

		PAD::SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_ACCEPT);
		PAD::SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_CANCEL);
		PAD::SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_DOWN);
		PAD::SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_UP);
		PAD::SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_LEFT);
		PAD::SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_RIGHT);
		PAD::DISABLE_CONTROL_ACTION(0, INPUT_FRONTEND_RIGHT, true);
		PAD::DISABLE_CONTROL_ACTION(0, INPUT_FRONTEND_DOWN, true);
		PAD::DISABLE_CONTROL_ACTION(0, INPUT_FRONTEND_LEFT, true);
		PAD::DISABLE_CONTROL_ACTION(0, INPUT_FRONTEND_UP, true);
		PAD::DISABLE_CONTROL_ACTION(0, INPUT_ARREST, true);
		PAD::DISABLE_CONTROL_ACTION(0, INPUT_CONTEXT, true);
		PAD::DISABLE_CONTROL_ACTION(0, INPUT_MELEE_BLOCK, true);
		PAD::DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_UP, true);
		PAD::DISABLE_CONTROL_ACTION(0, INPUT_HUD_SPECIAL, true);
		PAD::DISABLE_CONTROL_ACTION(0, INPUT_VEH_CIN_CAM, true);
		PAD::DISABLE_CONTROL_ACTION(0, INPUT_VEH_CIN_CAM, true);
		PAD::DISABLE_CONTROL_ACTION(0, INPUT_VEH_HEADLIGHT, true);
		PAD::DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_LEFT, true);
		PAD::DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_DOWN, true);
		PAD::DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_RDOWN, true);
		PAD::DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_RIGHT, true);
		PAD::DISABLE_CONTROL_ACTION(0, INPUT_CHARACTER_WHEEL, true);
		PAD::DISABLE_CONTROL_ACTION(0, INPUT_VEH_RADIO_WHEEL, true);
		PAD::DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_CANCEL, true);
		PAD::DISABLE_CONTROL_ACTION(0, INPUT_MELEE_ATTACK_LIGHT, true);
		PAD::DISABLE_CONTROL_ACTION(0, INPUT_MELEE_ATTACK_HEAVY, true);
		PAD::DISABLE_CONTROL_ACTION(0, INPUT_SELECT_CHARACTER_TREVOR, true);
		PAD::DISABLE_CONTROL_ACTION(0, INPUT_SELECT_CHARACTER_MICHAEL, true);
		PAD::DISABLE_CONTROL_ACTION(0, INPUT_SELECT_CHARACTER_FRANKLIN, true);
		PAD::DISABLE_CONTROL_ACTION(0, INPUT_SELECT_CHARACTER_MULTIPLAYER, true);
	}

	interface* GetRenderer() { return &g_interface; }
}


