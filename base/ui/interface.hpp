#pragma once
#include "../common.hpp"
#include "../manager.hpp"
namespace VX {

	struct RGBAF : RGBA
	{
		int f = 0;
	};
	enum eJustify {
		JUSTIFY_LEFT,
		JUSTIFY_RIGHT,
		JUSTIFY_CENTER,
	};

	enum {
		HUD,
		HUD_WANTED_STARS,
		HUD_WEAPON_ICON,
		HUD_CASH,
		HUD_MP_CASH,
		HUD_MP_MESSAGE,
		HUD_VEHICLE_NAME,
		HUD_AREA_NAME,
		HUD_VEHICLE_CLASS,
		HUD_STREET_NAME,
		HUD_HELP_TEXT,
		HUD_FLOATING_HELP_TEXT_1,
		HUD_FLOATING_HELP_TEXT_2,
		HUD_CASH_CHANGE,
		HUD_RETICLE,
		HUD_SUBTITLE_TEXT,
		HUD_RADIO_STATIONS,
		HUD_SAVING_GAME,
		HUD_GAME_STREAM,
		HUD_WEAPON_WHEEL,
		HUD_WEAPON_WHEEL_STATS,
		HUD_END,
	};

	class interface {
	public:
		float get_text_width(char const* text, int32_t font, float scale_override);
		float get_text_height(int32_t font, float size);
		Vector2 get_spirit_scale(float size);
		void draw_left_text(char const* text, RGBA color, Vector2 position, float size, int font, bool outline);
		void draw_right_text(char const* text, RGBA color, Vector2 position, float size, int font, bool outline);
		void draw_center_text(char const* text, RGBA color, Vector2 position, float size, int font, bool outline);
		void Spriter(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a);
		void draw_sprite(char const* dict, char const* texture, Vector2 position, Vector2 size, float rotation, RGBA color);
		void DrawSpriteV2(Texture texture, float x, float y, float w, float h, float heading, RGBA color, bool renderIfNotStreamed = true);
		void DrawString(String text, float x, float y, int font, float scale, RGBA color, bool outline = false, int justify = -1, float textWrapMin = 0, float textWrapMax = 0);
		//void draw_sprite_v2(Texture, Vector2 position, Vector2 size, float rotation, RGBA color);
		void draw_rect(RGBA color, Vector2 position, Vector2 size);
		void draw_sprite_aligned(std::pair<std::string, std::string> asset, Vector2 position, Vector2 scale, float rotation, RGBA color);
		float get_normalized_font_scale(int font, float scale);
		float calculate_string_width(std::string string, int font, float scale);
		void draw_text2(std::string text, Vector2 position, float scale, int font, RGBA color, eJustify justification = JUSTIFY_LEFT, Vector2 wrap = { 0.f, 5.f });
		void forward_menu(void(*menu)(), char const* submenu);
		void back_menu();

		void draw_option_background();

		void play_frontend_sound(char const* sound_name);
		void update_hotkeys();
		// Variables 
	public:
		bool m_opened = { false };

		Vector2 m_menu_pos = { 0.8f, 0.1f };

		float m_draw_base_y = { 0.f };
		float m_last_option_base = { 0.f };
		float m_global_scale = { 1.f };
		float m_width = { 0.21f };
		float m_sub_padding = { 2.07f };
		float m_right_padding = { 7.0f };
		float m_left_padding = { 2.05f };

		//Tab
		bool FirstTabSelected = true;
		bool SecondTabSelected = false;
		int Current_Tab = 0;
		RGBA tab_color_selected{ 255,255,255,255 };
		RGBA tab_color_unselected{ 0,0,0,255 };
		bool tab_activate = false;
		float m_tab_height = { 0.035f };
		int m_tab_font = 0;
		float m_tab_font_size = { 0.3f };

		//Theme
		bool paragon = false;
		// Header
		std::string render_queue[100];
		int render_queue_index = 0;
		float m_delta = 0.f;
		RGBA m_notify_background{ 31, 30, 31, 255 };
	//	Texture m_hHeader = { "VX", "header" };
	//	SpriteAnimation* m_hAnimatedHeader;

		float m_header_height = { 0.083f };
		float m_header_font_size = { 1.f };
		int m_header_font = { 1 };
		bool HeaderText = true;

		int m_playerinfo_font = { 0 };
		RGBA m_background_playerinfo = { 0,0,0,170 };
		std::vector<std::string> m_cached_themes;
		std::size_t m_selected_theme;

		RGBA m_header_back_ground = { 107, 5, 255, 255 };
		RGBA m_header_text = { 255, 255, 255, 255 };

		// Submenu
		float m_submenu_height = { 0.035f };
		int m_submenu_font = 0;
		float m_submenu_font_size = { 0.3f };

		RGBA m_submenu_backgound = { 0, 0, 0, 255 };
		RGBA m_submenu_text = { 255, 255, 255, 255 };
		//  Option
		float m_option_height = { 0.035f };
		int m_option_font = 0;
		float m_option_font_size = { 0.3f };

		RGBA m_option_backgound = { 0 , 0 , 0,  170 };
		RGBA m_option_scroll = { 255, 255, 255, 255 };
		RGBA m_option_text = { 255, 255, 255, 255 };
		RGBA m_option_text_selected = { 0, 0, 0, 255 };
		// Toggle
		std::map<int, bool*> m_toggle_hot_keys;
		float m_toggle_size = { 0.028f };
		RGBA m_toggle_color_on = { 0, 255, 0, 255 };
		RGBA m_toggle_color_off = { 255, 0, 0, 255 };
		float m_arrow_rotated_size = { 0.035f };
		// Break
		int m_break_font = 1;
		float m_break_font_size = { 0.4f };

		RGBA m_break_text = { 255, 255, 255, 255 };
		// Footer 
		bool m_dynamic_footer = { true };
		RGBA m_sprite_color = { 255, 255, 255, 255 };

		float m_footer_height = { 0.030f };
		float m_footer_arrow_size = { 0.035f };

		RGBA m_footer_background = { 0, 0, 0, 255 };
		// Option Desc 
		int m_desc_font = 0;

		RGBA m_desc_background = { 0, 0, 0, 200 };
		RGBA m_desc_line = { 255, 255, 255, 255 };
		// Scroller
		float m_target = { 0.f };
		float m_current = { 0.f };
		float m_speed = { 0.1281f };

		RGBA m_scroller_color = { 255, 255, 255, 255 };
		// Options
		int m_max_vis_options = 13;
		int m_option_count;
		int m_current_option;
		int m_previous_option;

		float m_opacity = 0;

		// Menu
		int m_menu_level;
		int m_option_array[1000];

		void(*m_current_menu)();
		void(*m_menu_array[1000])();

		bool drawinstructional = true;

		char const* m_current_sub_menu;
		char const* m_sub_menu_array[1000];
		char const* m_current_desc;
		// Input 
		bool m_hotkey_pressed = false;
		bool m_select_pressed = false;
		bool m_up_pressed = false;
		bool m_down_pressed = false;
		bool m_left_pressed = false;
		bool m_right_pressed = false;
		//Handle Key
		bool m_OpenKeyPressed = false;
		bool m_BackKeyPressed = false;
		bool m_EnterKeyPressed = false;
		bool m_UpKeyPressed = false;
		bool m_DownKeyPressed = false;
		bool m_LeftKeyPressed = false;
		bool m_RightKeyPressed = false;
		bool m_MouseKeyPressed = false;

		std::int32_t m_OpenDelay = 200;
		std::int32_t m_BackDelay = 300;
		std::int32_t m_EnterDelay = 300;
		std::int32_t m_VerticalDelay = 120;
		std::int32_t m_HorizontalDelay = 120;

		int m_delay = 150;
		int m_previous_tick = 0;

		float X_InfoFloat{};
		float Y_InfoFloat{};

		//Line
		RGBA m_line_background = { 255, 255, 255, 255 };

		RGBA m_line_unselected_background = { 0, 0, 0, 255 };

		int iToolTipScaleform;

		bool g_is_mouse_enabled;
		bool g_is_moving_menu;

		std::vector<int> m_disabled_mouse_keys = {
		0, 1, 2, 3, 4, 5, 6, 14, 15, 16, 17, 24, 69, 70, 84, 85, 92, 99, 100, 106, 114, 115, 121, 142, 241, 257, 261, 262, 329, 330, 331
		};
		void move_menu_with_mouse(Vector2 mousePos, Vector2 initialMenuPosition);
		bool is_point_in_rect(Vector2 point, Vector2 rectPos, Vector2 rectSize);
		Vector2 get_mouse_pos();

		int m_mouseKey = 'X';
		void MouseInput();

		float m_bgOpacity = 45;
		float m_lineWidth = 0.0009f;
		RGBA m_cOutline = { 15,23,42,255 };
		RGBA m_cPrimary = { 0, 0, 0, 190 };
		RGBA m_cOption = { 255, 255, 255, 255 };
		float m_dialogHeaderHeight = 0.0415f;
		float m_dialogFooterHeight = 0.01725f;

	public:
		// Ticks
		void draw_mouse_tick();
		void draw_tick();

		void disbale_controls();
		// Drawing 
	public:
		void add_option(const char* option);
		bool draw_regular(const char* option);
		bool draw_number(const char* option, float* numeral, float min, float max, float step = 1.0f, bool action_input = false);
		bool draw_number(const char* option, int* numeral, int min, int max, int step = 1, bool action_input = false);
		bool draw_array(const char* option, const char** array, int* position, bool action_input = false);
		bool draw_bool_number(const char* option, bool* toggle, float* numeral, int min, int max, int step = 1, bool action_input = false);
		bool draw_bool_array(const char* option, const char* textDesc, bool* toggle, const char** array, int* position, bool action_input);
		bool draw_link(const char* option);
		void PlayerInfoText(std::string text, RGBAF rgbaf, Vector2 position, Vector2 size, bool center, bool right);
		void DrawRect(float x, float y, float width, float height, RGBA color);
		void DrawBox(float x, float y, float width, float height, String title = "", bool gradients = false, Texture texture = { "", "" }, bool customColor = false, RGBA color = { 255, 255, 255, 255 });
		void DrawInWorldBox(Entity entity, RGBA color);
		//hotkey saver
		void save_key_toggles(const std::string& filename);
		void load_key_toggles(const std::string& filename);
		int get_assigned_key(bool* toggle);
	};
	interface* GetRenderer();
}