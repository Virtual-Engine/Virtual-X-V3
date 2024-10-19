#pragma once
#include "invoker/Natives.hpp"

namespace VX
{
	class Scroller
	{
	private:

	public:
		void Init();
		void Update();
	};

	Scroller* GetScroller();
}