#include "common.hpp"


namespace VX
{
	std::string m_name = "Virtual X";
	int m_color1;
	int m_style;
	int m_icon;
	const char* textSettingsLabels[] = {
	"Normal",
	"Bold",
	"Italic"
	};

	const char* textSettingsValues[] = {
		"",
		"~h~",
		"~italic~"
	}; int textSettingsId = 0;

	const char* textColorsLabels[] = {
		"Default",
		"Black",
		"Blue",
		"Gold",
		"Green",
		"Grey",
		"Light Blue",
		"Orange",
		"Purple",
		"Red"
	};

	const char* textColorsValues[] = {
		"",
		"~v~",
		"~b~",
		"~y~",
		"~g~",
		"~c~",
		"~f~",
		"~o~",
		"~p~",
		"~r~"
	}; int textColorsId = 0;

	const char* textIconsLabels[] = {
		"None",
		"Wanted Star",
		"Rockstar Verified",
		"Rockstar"
	};

	const char* textIconsValues[] = {
		"",
		"~ws~",
		"~¦~",
		"~÷~"
	}; int textIconsId = 0;
}