#pragma once
#include "invoker/Natives.hpp"

namespace VX
{
	class Description
	{
	private:

	public:
		void Init(const char* text);
	};

	Description* GetDescription();
}