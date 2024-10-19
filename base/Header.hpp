#pragma once
#include "invoker/Natives.hpp"
#include "animatedYTD.h"
namespace VX
{
	class Header
	{
	private:

	public:
		void Init();
		void DrawGlare();
		bool m_render_glare = true;
		int m_glare_handle;
		float m_glare_direction;
		SpriteAnimation* m_hAnimatedHeader;
	};

	Header* GetHeader();
}