#include "common.hpp"
#include "JSON/json.hpp"
#include "dirs.h"
#include "invoker/Natives.hpp"
#include "ui/interface.hpp"
#include "Header.hpp"

namespace VX
{
	void SaveProfil(std::string name) {
		std::string MenuFolderPath = util::dirs::get_directories()->get_theme();

		nlohmann::json jsonData;

		jsonData["Profils"]["Header R"] = GetRenderer()->m_header_back_ground.r;
		jsonData["Profils"]["Header G"] = GetRenderer()->m_header_back_ground.g;
		jsonData["Profils"]["Header B"] = GetRenderer()->m_header_back_ground.b;
		jsonData["Profils"]["Header A"] = GetRenderer()->m_header_back_ground.a;

		jsonData["Profils"]["Header Text R"] = GetRenderer()->m_header_text.r;
		jsonData["Profils"]["Header Text G"] = GetRenderer()->m_header_text.g;
		jsonData["Profils"]["Header Text B"] = GetRenderer()->m_header_text.b;
		jsonData["Profils"]["Header Text A"] = GetRenderer()->m_header_text.a;

		jsonData["Profils"]["Sub R"] = GetRenderer()->m_submenu_backgound.r;
		jsonData["Profils"]["Sub G"] = GetRenderer()->m_submenu_backgound.g;
		jsonData["Profils"]["Sub B"] = GetRenderer()->m_submenu_backgound.b;
		jsonData["Profils"]["Sub A"] = GetRenderer()->m_submenu_backgound.a;

		jsonData["Profils"]["Sub Text R"] = GetRenderer()->m_submenu_text.r;
		jsonData["Profils"]["Sub Text G"] = GetRenderer()->m_submenu_text.g;
		jsonData["Profils"]["Sub Text B"] = GetRenderer()->m_submenu_text.b;
		jsonData["Profils"]["Sub Text A"] = GetRenderer()->m_submenu_text.a;

		jsonData["Profils"]["Scroller R"] = GetRenderer()->m_scroller_color.r;
		jsonData["Profils"]["Scroller G"] = GetRenderer()->m_scroller_color.g;
		jsonData["Profils"]["Scroller B"] = GetRenderer()->m_scroller_color.b;
		jsonData["Profils"]["Scroller A"] = GetRenderer()->m_scroller_color.a;

		jsonData["Profils"]["Scroller Text R"] = GetRenderer()->m_option_text_selected.r;
		jsonData["Profils"]["Scroller Text G"] = GetRenderer()->m_option_text_selected.g;
		jsonData["Profils"]["Scroller Text B"] = GetRenderer()->m_option_text_selected.b;
		jsonData["Profils"]["Scroller Text A"] = GetRenderer()->m_option_text_selected.a;

		jsonData["Profils"]["Background R"] = GetRenderer()->m_option_backgound.r;
		jsonData["Profils"]["Background G"] = GetRenderer()->m_option_backgound.g;
		jsonData["Profils"]["Background B"] = GetRenderer()->m_option_backgound.b;
		jsonData["Profils"]["Background A"] = GetRenderer()->m_option_backgound.a;

		jsonData["Profils"]["Background Text R"] = GetRenderer()->m_option_text.r;
		jsonData["Profils"]["Background Text G"] = GetRenderer()->m_option_text.g;
		jsonData["Profils"]["Background Text B"] = GetRenderer()->m_option_text.b;
		jsonData["Profils"]["Background Text A"] = GetRenderer()->m_option_text.a;

		jsonData["Profils"]["Footer R"] = GetRenderer()->m_footer_background.r;
		jsonData["Profils"]["Footer G"] = GetRenderer()->m_footer_background.g;
		jsonData["Profils"]["Footer B"] = GetRenderer()->m_footer_background.b;
		jsonData["Profils"]["Footer A"] = GetRenderer()->m_footer_background.a;

		jsonData["Profils"]["Sprite Footer R"] = GetRenderer()->m_sprite_color.r;
		jsonData["Profils"]["Sprite Footer G"] = GetRenderer()->m_sprite_color.g;
		jsonData["Profils"]["Sprite Footer B"] = GetRenderer()->m_sprite_color.b;
		jsonData["Profils"]["Sprite Footer A"] = GetRenderer()->m_sprite_color.a;

		jsonData["Profils"]["Toggle On R"] = GetRenderer()->m_toggle_color_on.r;
		jsonData["Profils"]["Toggle On G"] = GetRenderer()->m_toggle_color_on.g;
		jsonData["Profils"]["Toggle On B"] = GetRenderer()->m_toggle_color_on.b;
		jsonData["Profils"]["Toggle On A"] = GetRenderer()->m_toggle_color_on.a;

		jsonData["Profils"]["Toggle Off R"] = GetRenderer()->m_toggle_color_off.r;
		jsonData["Profils"]["Toggle Off G"] = GetRenderer()->m_toggle_color_off.g;
		jsonData["Profils"]["Toggle Off B"] = GetRenderer()->m_toggle_color_off.b;
		jsonData["Profils"]["Toggle Off A"] = GetRenderer()->m_toggle_color_off.a;

		jsonData["Profils"]["Break R"] = GetRenderer()->m_break_text.r;
		jsonData["Profils"]["Break G"] = GetRenderer()->m_break_text.g;
		jsonData["Profils"]["Break B"] = GetRenderer()->m_break_text.b;
		jsonData["Profils"]["Break A"] = GetRenderer()->m_break_text.a;

		jsonData["Profils"]["Player Info R"] = GetRenderer()->m_background_playerinfo.r;
		jsonData["Profils"]["Player Info G"] = GetRenderer()->m_background_playerinfo.g;
		jsonData["Profils"]["Player Info B"] = GetRenderer()->m_background_playerinfo.b;
		jsonData["Profils"]["Player Info A"] = GetRenderer()->m_background_playerinfo.a;

		jsonData["Profils"]["Tab selected R"] = GetRenderer()->tab_color_selected.r;
		jsonData["Profils"]["Tab selected G"] = GetRenderer()->tab_color_selected.g;
		jsonData["Profils"]["Tab selected B"] = GetRenderer()->tab_color_selected.b;
		jsonData["Profils"]["Tab selected A"] = GetRenderer()->tab_color_selected.a;

		jsonData["Profils"]["Tab unselected R"] = GetRenderer()->tab_color_unselected.r;
		jsonData["Profils"]["Tab unselected G"] = GetRenderer()->tab_color_unselected.g;
		jsonData["Profils"]["Tab unselected B"] = GetRenderer()->tab_color_unselected.b;
		jsonData["Profils"]["Tab unselected A"] = GetRenderer()->tab_color_unselected.a;

		jsonData["Profils"]["Tab Activate"] = GetRenderer()->tab_activate;
		jsonData["Profils"]["Glare"] = GetHeader()->m_render_glare;
		jsonData["Profils"]["Header Text"] = GetRenderer()->HeaderText;

		jsonData["Profils"]["Instructional"] = GetRenderer()->drawinstructional;

		jsonData["Profils"]["Header Font"] = GetRenderer()->m_header_font;
		jsonData["Profils"]["Sub Font"] = GetRenderer()->m_submenu_font;
		jsonData["Profils"]["Option Font"] = GetRenderer()->m_option_font;
		jsonData["Profils"]["Break Font"] = GetRenderer()->m_break_font;
		jsonData["Profils"]["Player Info Font"] = GetRenderer()->m_playerinfo_font;
		jsonData["Profils"]["Max Option visible"] = GetRenderer()->m_max_vis_options;

		jsonData["Profils"]["Tab Size"] = GetRenderer()->m_tab_font_size;
		jsonData["Profils"]["Tab Height"] = GetRenderer()->m_tab_height;
		jsonData["Profils"]["Tab Font"] = GetRenderer()->m_tab_font;

		jsonData["Profils"]["Header Size"] = GetRenderer()->m_header_height;
		jsonData["Profils"]["Header Height"] = GetRenderer()->m_header_font_size;

		jsonData["Profils"]["Sub Size"] = GetRenderer()->m_submenu_height;
		jsonData["Profils"]["Sub Height"] = GetRenderer()->m_submenu_font_size;

		jsonData["Profils"]["Option Size"] = GetRenderer()->m_option_height;
		jsonData["Profils"]["Option Height"] = GetRenderer()->m_option_font_size;

		jsonData["Profils"]["Toggle Size"] = GetRenderer()->m_toggle_size;

		jsonData["Profils"]["Break Size"] = GetRenderer()->m_break_font_size;

		jsonData["Profils"]["Footer Sprite Size"] = GetRenderer()->m_footer_arrow_size;
		jsonData["Profils"]["Footer Height"] = GetRenderer()->m_footer_height;

		jsonData["Profils"]["Scroller Speed"] = GetRenderer()->m_speed;

		jsonData["Profils"]["X"] = GetRenderer()->m_menu_pos.x;
		jsonData["Profils"]["Y"] = GetRenderer()->m_menu_pos.y;
		jsonData["Profils"]["Width"] = GetRenderer()->m_width;

		std::ofstream outputFile(MenuFolderPath + name + ".json");
		outputFile << jsonData.dump(4);
		outputFile.close();
	}
	void LoadProfil(std::string name) {
		int modifiedItems{ 0 };
		try {
			std::string MenuFolderPath = util::dirs::get_directories()->get_theme();
			std::ifstream inputFile(MenuFolderPath + name + ".json");
			if (inputFile.is_open()) {
				nlohmann::json jsonData;
				inputFile >> jsonData;
				inputFile.close();


				nlohmann::json& json = jsonData["Profils"];


				GetRenderer()->m_header_back_ground.r = jsonData["Profils"]["Header R"];
				GetRenderer()->m_header_back_ground.g = jsonData["Profils"]["Header G"];
				GetRenderer()->m_header_back_ground.b = jsonData["Profils"]["Header B"];
				GetRenderer()->m_header_back_ground.a = jsonData["Profils"]["Header A"];
				
				GetRenderer()->m_header_text.r = jsonData["Profils"]["Header Text R"];
				GetRenderer()->m_header_text.g = jsonData["Profils"]["Header Text G"];
				GetRenderer()->m_header_text.b = jsonData["Profils"]["Header Text B"];
				GetRenderer()->m_header_text.a = jsonData["Profils"]["Header Text A"];

				GetRenderer()->m_submenu_backgound.r = jsonData["Profils"]["Sub R"];
				GetRenderer()->m_submenu_backgound.g = jsonData["Profils"]["Sub G"];
				GetRenderer()->m_submenu_backgound.b = jsonData["Profils"]["Sub B"];
				GetRenderer()->m_submenu_backgound.a = jsonData["Profils"]["Sub A"];

				GetRenderer()->m_submenu_text.r = jsonData["Profils"]["Sub Text R"];
				GetRenderer()->m_submenu_text.g = jsonData["Profils"]["Sub Text G"];
				GetRenderer()->m_submenu_text.b = jsonData["Profils"]["Sub Text B"];
				GetRenderer()->m_submenu_text.a = jsonData["Profils"]["Sub Text A"];

				GetRenderer()->m_scroller_color.r = jsonData["Profils"]["Scroller R"];
				GetRenderer()->m_scroller_color.g = jsonData["Profils"]["Scroller G"];
				GetRenderer()->m_scroller_color.b = jsonData["Profils"]["Scroller B"];
				GetRenderer()->m_scroller_color.a = jsonData["Profils"]["Scroller A"];

				GetRenderer()->m_option_text_selected.r = jsonData["Profils"]["Scroller Text R"];
				GetRenderer()->m_option_text_selected.g = jsonData["Profils"]["Scroller Text G"];
				GetRenderer()->m_option_text_selected.b = jsonData["Profils"]["Scroller Text B"];
				GetRenderer()->m_option_text_selected.a = jsonData["Profils"]["Scroller Text A"];

				GetRenderer()->m_option_backgound.r = jsonData["Profils"]["Background R"];
				GetRenderer()->m_option_backgound.g = jsonData["Profils"]["Background G"];
				GetRenderer()->m_option_backgound.b = jsonData["Profils"]["Background B"];
				GetRenderer()->m_option_backgound.a = jsonData["Profils"]["Background A"];

				GetRenderer()->m_option_text.r = jsonData["Profils"]["Background Text R"];
				GetRenderer()->m_option_text.g = jsonData["Profils"]["Background Text G"];
				GetRenderer()->m_option_text.b = jsonData["Profils"]["Background Text B"];
				GetRenderer()->m_option_text.a = jsonData["Profils"]["Background Text A"];

				GetRenderer()->m_footer_background.r = jsonData["Profils"]["Footer R"];
				GetRenderer()->m_footer_background.g = jsonData["Profils"]["Footer G"];
				GetRenderer()->m_footer_background.b = jsonData["Profils"]["Footer B"];
				GetRenderer()->m_footer_background.a = jsonData["Profils"]["Footer A"];

				GetRenderer()->m_sprite_color.r = jsonData["Profils"]["Sprite Footer R"];
				GetRenderer()->m_sprite_color.g = jsonData["Profils"]["Sprite Footer G"];
				GetRenderer()->m_sprite_color.b = jsonData["Profils"]["Sprite Footer B"];
				GetRenderer()->m_sprite_color.a = jsonData["Profils"]["Sprite Footer A"];

				GetRenderer()->m_toggle_color_on.r = jsonData["Profils"]["Toggle On R"];
				GetRenderer()->m_toggle_color_on.g = jsonData["Profils"]["Toggle On G"];
				GetRenderer()->m_toggle_color_on.b = jsonData["Profils"]["Toggle On B"];
				GetRenderer()->m_toggle_color_on.a = jsonData["Profils"]["Toggle On A"];

				GetRenderer()->m_toggle_color_off.r = jsonData["Profils"]["Toggle Off R"];
				GetRenderer()->m_toggle_color_off.g = jsonData["Profils"]["Toggle Off G"];
				GetRenderer()->m_toggle_color_off.b = jsonData["Profils"]["Toggle Off B"];
				GetRenderer()->m_toggle_color_off.a = jsonData["Profils"]["Toggle Off A"];

				GetRenderer()->m_break_text.r = jsonData["Profils"]["Break R"];
				GetRenderer()->m_break_text.g = jsonData["Profils"]["Break G"];
				GetRenderer()->m_break_text.b = jsonData["Profils"]["Break B"];
				GetRenderer()->m_break_text.a = jsonData["Profils"]["Break A"];

				GetRenderer()->m_background_playerinfo.r = jsonData["Profils"]["Player Info R"];
				GetRenderer()->m_background_playerinfo.g = jsonData["Profils"]["Player Info G"];
				GetRenderer()->m_background_playerinfo.b = jsonData["Profils"]["Player Info B"];
				GetRenderer()->m_background_playerinfo.a = jsonData["Profils"]["Player Info A"];

				GetRenderer()->tab_color_selected.r = jsonData["Profils"]["Tab selected R"];
				GetRenderer()->tab_color_selected.g = jsonData["Profils"]["Tab selected G"];
				GetRenderer()->tab_color_selected.b = jsonData["Profils"]["Tab selected B"];
				GetRenderer()->tab_color_selected.a = jsonData["Profils"]["Tab selected A"];

				GetRenderer()->tab_color_unselected.r = jsonData["Profils"]["Tab unselected R"];
				GetRenderer()->tab_color_unselected.g = jsonData["Profils"]["Tab unselected G"];
				GetRenderer()->tab_color_unselected.b = jsonData["Profils"]["Tab unselected B"];
				GetRenderer()->tab_color_unselected.a = jsonData["Profils"]["Tab unselected A"];

				GetRenderer()->tab_activate = jsonData["Profils"]["Tab Activate"];
				GetHeader()->m_render_glare = jsonData["Profils"]["Glare"];
				GetRenderer()->HeaderText = jsonData["Profils"]["Header Text"];

				GetRenderer()->drawinstructional = jsonData["Profils"]["Instructional"];

				GetRenderer()->m_header_font = jsonData["Profils"]["Header Font"];
				GetRenderer()->m_submenu_font = jsonData["Profils"]["Sub Font"];
				GetRenderer()->m_option_font = jsonData["Profils"]["Option Font"];
				GetRenderer()->m_break_font = jsonData["Profils"]["Break Font"];
				GetRenderer()->m_playerinfo_font = jsonData["Profils"]["Player Info Font"];
				GetRenderer()->m_max_vis_options = jsonData["Profils"]["Max Option visible"];

				GetRenderer()->m_tab_font_size = jsonData["Profils"]["Tab Size"];
				GetRenderer()->m_tab_height = jsonData["Profils"]["Tab Height"];
				GetRenderer()->m_tab_font = jsonData["Profils"]["Tab Font"];

				GetRenderer()->m_header_height = jsonData["Profils"]["Header Size"];
				GetRenderer()->m_header_font_size = jsonData["Profils"]["Header Height"];

				GetRenderer()->m_submenu_height = jsonData["Profils"]["Sub Size"];
				GetRenderer()->m_submenu_font_size = jsonData["Profils"]["Sub Height"];

				GetRenderer()->m_option_height = jsonData["Profils"]["Option Size"];
				GetRenderer()->m_option_font_size = jsonData["Profils"]["Option Height"];

				GetRenderer()->m_toggle_size = jsonData["Profils"]["Toggle Size"];

				GetRenderer()->m_break_font_size = jsonData["Profils"]["Break Size"];

				GetRenderer()->m_footer_arrow_size = jsonData["Profils"]["Footer Sprite Size"];
				GetRenderer()->m_footer_height = jsonData["Profils"]["Footer Height"];

				GetRenderer()->m_speed = jsonData["Profils"]["Scroller Speed"];

				GetRenderer()->m_menu_pos.x = jsonData["Profils"]["X"];
				GetRenderer()->m_menu_pos.y = jsonData["Profils"]["Y"];
				GetRenderer()->m_width = jsonData["Profils"]["Width"];
			}
		}
		catch (const std::exception& e) {
			g_log.send("Json", e.what());
		}
	}
}