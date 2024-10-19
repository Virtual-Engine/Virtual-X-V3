#include "invoker/Natives.hpp"
#include "CustomInput.hpp"
#include "fiber.hpp"
#include "ui/interface.hpp"
#include "scaleform.h"
#include "keyboardKey.hpp"
#include "option.hpp"
namespace VX
{
	CustomInput g_CustomInput;
	template <typename T, size_t N>
	constexpr size_t NUMOF(T(&)[N]) { return N; }
	void DoTimedFunctionV24(int* timer, int timeMS, std::function<void()> function) {
		if (*timer < MISC::GET_GAME_TIMER()) {
			*timer = MISC::GET_GAME_TIMER() + timeMS;
			function();
		}
	}
	void GetInputText(std::string& inputtxt, InputCombination keys[], int size, int maxLength) {
		static int timer;
		if (GetInput()->is_key_pressed(17/*LCTRL*/) && KeyJustUp('V')) {
			if (OpenClipboard(GetCustomInput()->GetWindow()));
			CloseClipboard();
			return;
		}
		if (GetInput()->is_key_pressed(VK_SPACE)) inputtxt += " ";
		if (GetInput()->is_key_pressed(VK_BACK)) timer = 0;
		if (GetInput()->is_key_pressed(VK_BACK) && inputtxt.length() > 0) DoTimedFunctionV24(&timer, 10, [&] {inputtxt.pop_back(); });
		for (int i = 0; i < 200; i++) {
			const InputCombination& comb = keys[i];
			if (GetInput()->is_key_pressed(comb.m_input)) inputtxt += KeyDown(VK_SHIFT) || KeyDown(VK_CAPITAL) ? comb.m_outputWithCaps : comb.m_output;
		}
		//if (inputtxt.length() > maxLength) inputtxt.pop_back();
	}
	bool CustomInput::Init(String name, std::string& output, int min, int max)
	{
		const static float x = 0.5f, y = 0.4f, width = 0.2f, height = 0.1f;
		bool accepted = false;
		bool exit = false;
		std::string inputText;
		while (!exit) {
			fiber::current()->sleep();
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
			PAD::ENABLE_ALL_CONTROL_ACTIONS(2);
			GetRenderer()->DrawBox(x, y, width, height, name, true, addOption()->m_hDialogBox);
			GetRenderer()->DrawRect(0.5, y + 0.02f, width - 0.04f, 0.03f, { 80, 80, 80, 160 });
			GetRenderer()->DrawString(inputText.c_str(), x, y - 0.02f + 0.02f, 0, 0.5f, { 255, 255, 255, 255 }, false, JustifyCenter, x - width / 2, x + width / 2);

			GetInputText(inputText, normalCombinations, NUMOF(numberCombinations), max);

			if (GetInput()->is_key_pressed(VK_SHIFT)) {
				exit = 1;
				accepted = 1;
			}
			else if (KeyJustUp(VK_ESCAPE)) {
				exit = 1;
				accepted = 0;
			}
		}
		if (inputText.length() < min) {
			return false;
		}
		if (accepted) output = inputText;
		return accepted;
	}

	CustomInput* GetCustomInput() { return &g_CustomInput; }
}
