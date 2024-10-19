#include "invoker/Natives.hpp"
#include "textures.hpp"
#include "fiber.hpp"
#include "ui/interface.hpp"
#include "MemoryEdit.h"
namespace VX
{
	Textures g_Textures;

	bool Textures::FileExists(const std::string& fileName)
	{
		struct stat buffer;
		return (stat(fileName.c_str(), &buffer) == 0);
	}

	Textures* GetTextures() { return &g_Textures; }
}
