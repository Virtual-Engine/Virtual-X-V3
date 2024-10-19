#include "script/script.hpp"
#include "SelfMenu.h"
#include "ui/interface.hpp"
#include "BackendFiles.h"
#include "utilities/utilities.hpp"
#include "Files.h"
#include "log/log.hpp"
#include "common.hpp"
#include <shlobj.h>
#include "MemoryEdit.h"

namespace VX
{
	Files g_Files;

	void Files::MainFolder()
	{
		fs::create_directory(get_documents_path() + "\\Virtual X");
		fs::create_directory(get_documents_path() + "\\Virtual X\\Outfits");
		fs::create_directory(get_documents_path() + "\\Virtual X\\Textures");
		fs::create_directory(get_documents_path() + "\\Virtual X\\Themes");
		
	}
	std::string g_Name = ("Virtual Engine");
	std::string Files::GetLoaderPath()
	{
		std::string appdata = std::getenv("appdata");
		std::string path = appdata + ("\\") + g_Name;
		return path;
	}
	
	std::string Files::get_documents_path() {
		wchar_t Folder[1024];
		HRESULT hr = SHGetFolderPathW(0, CSIDL_MYDOCUMENTS, 0, 0, Folder);
		if (SUCCEEDED(hr))
		{
			char str[1024];
			wcstombs(str, Folder, 1023);
			return str;
		}
		else return "";
	}

	Files* GetFiles() { return &g_Files; }
}