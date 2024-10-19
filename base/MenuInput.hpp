#pragma once
#include "invoker/Natives.hpp"

namespace VX
{
	class MenuInput
	{
	private:

	public:
		float fadeMenu = 0;
	public:
		void Init();
		void CheckInput();
	};

	MenuInput* GetMenuInput();
}