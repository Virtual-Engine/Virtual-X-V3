#pragma once
#include "invoker/Natives.hpp"

namespace VX
{
	class CustomInput
	{
	private:

		std::vector<std::function<void()>> m_functionQueue;

	public:
		bool Init(String name, std::string& output, int min, int max);
		void AddToQueue(std::function<void()> func) { m_functionQueue.push_back(func); }

		inline static HWND m_hWindow;
		static HWND GetWindow() { return m_hWindow; }
	};

	CustomInput* GetCustomInput();

	enum Justify
	{
		// justify: 0 - center, 1 - left, 2 - right (-1 = ignore)
		JustifyIgnore = -1,
		JustifyCenter,
		JustifyLeft,
		JustifyRight
	};
	struct InputCombination {
		bool m_caps;
		DWORD m_input;
		String m_output;
		String m_outputWithCaps;
	};
	static InputCombination numberCombinations[] = {
	{false, '1', "1", "!" },
	{false, '2', "2", "@" },
	{false, '3', "3", "#" },
	{false, '4', "4", "$" },
	{false, '5', "5", "%" },
	{false, '6', "6", "^" },
	{false, '7', "7", "&" },
	{false, '8', "8", "*" },
	{false, '9', "9", "(" },
	{false, '0', "0", ")" },
	{false, 'A', "a", "A" },
	{false, 'B', "b", "B" },
	{false, 'C', "c", "C" },
	{false, 'D', "d", "D" },
	{false, 'E', "e", "E" },
	{false, 'F', "f", "F" },
	{false, 'G', "g", "G" },
	{false, 'H', "h", "H" },
	{false, 'I', "i", "I" },
	{false, 'J', "j", "J" },
	{false, 'K', "k", "K" },
	{false, 'L', "l", "L" },
	{false, 'M', "m", "M" },
	{false, 'N', "n", "N" },
	{false, 'O', "o", "O" },
	{false, 'P', "p", "P" },
	{false, 'Q', "q", "Q" },
	{false, 'R', "r", "R" },
	{false, 'S', "s", "S" },
	{false, 'T', "t", "T" },
	{false, 'U', "u", "U" },
	{false, 'V', "v", "V" },
	{false, 'W', "w", "W" },
	{false, 'X', "x", "X" },
	{false, 'Y', "y", "Y" },
	{false, 'Z', "z", "Z" },
	{false, VK_OEM_7,"'", "@"},
	{false, VK_OEM_MINUS,"-", "_"},
	{false, VK_OEM_PLUS,"=", "+" },
	{false, VK_OEM_1, ";", ":" },
	{false, VK_OEM_2, "/", "?" },
	{false, VK_OEM_3, "`", "~" },
	{false, VK_OEM_4, "[", "{" },
	{false, VK_OEM_5, "\\", "|"},
	{false, VK_OEM_6, "]", "}" },
	{false, VK_OEM_7, "!", "§" },
	{false, VK_OEM_8, "]", "}" },
	{false, VK_OEM_COMMA,",", "<" },
	{false, VK_OEM_PERIOD, ".", ">" },
	{false, VK_NUMPAD1, "1", "1" },
	{false, VK_NUMPAD2, "2", "2"},
	{false, VK_NUMPAD3, "3", "3"},
	{false, VK_NUMPAD4, "4", "4"},
	{false, VK_NUMPAD5, "5", "5"},
	{false, VK_NUMPAD6, "6", "6"},
	{false, VK_NUMPAD7, "7", "7"},
	{false, VK_NUMPAD8, "8", "8"},
	{false, VK_NUMPAD9, "9", "9"},
	{false, VK_NUMPAD0, "0", "0"}
	};
	static InputCombination normalCombinations[] = {
	{false, '1', "1", "!" },
	{false, '2', "2", "@" },
	{false, '3', "3", "#" },
	{false, '4', "4", "$" },
	{false, '5', "5", "%" },
	{false, '6', "6", "^" },
	{false, '7', "7", "&" },
	{false, '8', "8", "*" },
	{false, '9', "9", "(" },
	{false, '0', "0", ")" },
	{false, 'A', "a", "A" },
	{false, 'B', "b", "B" },
	{false, 'C', "c", "C" },
	{false, 'D', "d", "D" },
	{false, 'E', "e", "E" },
	{false, 'F', "f", "F" },
	{false, 'G', "g", "G" },
	{false, 'H', "h", "H" },
	{false, 'I', "i", "I" },
	{false, 'J', "j", "J" },
	{false, 'K', "k", "K" },
	{false, 'L', "l", "L" },
	{false, 'M', "m", "M" },
	{false, 'N', "n", "N" },
	{false, 'O', "o", "O" },
	{false, 'P', "p", "P" },
	{false, 'Q', "q", "Q" },
	{false, 'R', "r", "R" },
	{false, 'S', "s", "S" },
	{false, 'T', "t", "T" },
	{false, 'U', "u", "U" },
	{false, 'V', "v", "V" },
	{false, 'W', "w", "W" },
	{false, 'X', "x", "X" },
	{false, 'Y', "y", "Y" },
	{false, 'Z', "z", "Z" },
	{false, VK_OEM_7,"'", "@"},
	{false, VK_OEM_MINUS,"-", "_"},
	{false, VK_OEM_PLUS,"=", "+" },
	{false, VK_OEM_1, ";", ":" },
	{false, VK_OEM_2, "/", "?" },
	{false, VK_OEM_3, "`", "~" },
	{false, VK_OEM_4, "[", "{" },
	{false, VK_OEM_5, "\\", "|"},
	{false, VK_OEM_6, "]", "}" },
	{false, VK_OEM_7, "!", "§" },
	{false, VK_OEM_8, "]", "}" },
	{false, VK_OEM_COMMA,",", "<" },
	{false, VK_OEM_PERIOD, ".", ">" },
	{false, VK_NUMPAD1, "1", "1" },
	{false, VK_NUMPAD2, "2", "2"},
	{false, VK_NUMPAD3, "3", "3"},
	{false, VK_NUMPAD4, "4", "4"},
	{false, VK_NUMPAD5, "5", "5"},
	{false, VK_NUMPAD6, "6", "6"},
	{false, VK_NUMPAD7, "7", "7"},
	{false, VK_NUMPAD8, "8", "8"},
	{false, VK_NUMPAD9, "9", "9"},
	{false, VK_NUMPAD0, "0", "0"}
	};
}