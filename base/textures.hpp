#pragma once
#include "invoker/Natives.hpp"

namespace VX
{
	class Textures
	{
	private:

	public:
		std::string m_YTDName{ "VX" };
		std::string FullHeaderName{ "VX" };
	public:
		bool FileExists(const std::string& fileName);
	};

	Textures* GetTextures();
}