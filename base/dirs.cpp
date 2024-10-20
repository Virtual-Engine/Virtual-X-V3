#include "common.hpp"
#include "dirs.h"
#include <ShlObj.h>
#include <filesystem>
#include "curl/curl.h"

namespace util::dirs {
	bool create_directories(std::vector<std::string> directories) {
		for (std::string dir : directories) {
			std::error_code error;
			std::filesystem::create_directories(dir, error);

			if (error.value()) {
				printf("[Dirs] Failed creating dir \"%s\" -> %s\n", dir.c_str(), error.message().c_str());
				return false;
			}
		}

		return true;
	}

	std::vector<std::string> directories::get_files_in_directory(std::string dir, std::string extension) {
		std::vector<std::string> buffer;

		WIN32_FIND_DATAA fd;
		HANDLE vit = FindFirstFileA((dir + "*" + extension).c_str(), &fd);

		if (vit != INVALID_HANDLE_VALUE) {
			do {
				if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
					std::string original = fd.cFileName;
					buffer.push_back(original.substr(0, original.length() - extension.length()));
				}
			} while (FindNextFileA(vit, &fd));

			FindClose(vit);
		}

		return buffer;
	}

	std::string directories::create_string(std::string base, std::string folder) {
		return base + "\\" + folder;
	}
	bool directories::load() {
		if (SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, m_paths[PATH_DOCUMENTS]) != S_OK) {
			printf("[Dirs] Failed to get documents folder\n");
			return false;
		}

		char tmp[MAX_PATH];
		SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, SHGFP_TYPE_CURRENT, tmp);

		sprintf_s(m_paths[PATH_TMP], ("%s\\"), tmp);
		sprintf_s(m_paths[PATH_VX], ("%s\\Virtual X"), m_paths[PATH_DOCUMENTS]);
		sprintf_s(m_paths[PATH_VX], ("%s\\Asi"), m_paths[PATH_ASI]);
		sprintf_s(m_paths[PATH_GFX], ("%s\\fonts\\"), m_paths[PATH_VX]);
		sprintf_s(m_paths[PATH_TEXTURES], ("%s\\textures\\"), m_paths[PATH_VX]);
		sprintf_s(m_paths[PATH_THEME], ("%s\\themes\\"), m_paths[PATH_VX]);
		sprintf_s(m_paths[PATH_LOG], create_string(m_paths[PATH_VX], ("log.txt")).c_str());
		sprintf_s(m_paths[PATH_GFX], ("%s\\fonts\\"), m_paths[PATH_VX]);
		sprintf_s(m_paths[PATH_OUTFITS], ("%s\\Outfits\\"), m_paths[PATH_VX]);
		sprintf_s(m_paths[PATH_VEHICLE], ("%s\\vehicle\\"), m_paths[PATH_VX]);
		sprintf_s(m_paths[PATH_TELEPORT], ("%s\\teleport\\"), m_paths[PATH_VX]);
		sprintf_s(m_paths[PATH_PLAYER], ("%s\\Player\\"), m_paths[PATH_VX]);
		sprintf_s(m_paths[PATH_CONFIGV2], ("%s\\Config\\"), m_paths[PATH_VX]);
		sprintf_s(m_paths[PATH_MAPMODS], ("%s\\map mods\\"), m_paths[PATH_VX]);
		sprintf_s(m_paths[PATH_SHV], ("%s\\xml\\"), m_paths[PATH_VX]);


		bool success = create_directories({
			m_paths[PATH_VX],
			create_string(m_paths[PATH_VX], ("textures")),
			create_string(m_paths[PATH_VX], ("fonts")),
			create_string(m_paths[PATH_VX], ("translations")),
			create_string(m_paths[PATH_VX], ("themes")),
			create_string(m_paths[PATH_VX], ("Outfits")),
			create_string(m_paths[PATH_VX], ("vehicle")),
			create_string(m_paths[PATH_VX], ("teleport")),
			create_string(m_paths[PATH_VX], ("Player")),
			create_string(m_paths[PATH_VX], ("Config")),
			create_string(m_paths[PATH_VX], ("map mods")),
			create_string(m_paths[PATH_VX], ("xml")),
			create_string(m_paths[PATH_VX], ("asi"))
			});

		if (success == false) return success;

		return true;
	}
	bool directories::DoesFileExist(String file) {
		std::ifstream i(file);
		return i.good();
	}
	directories* get_directories() {
		static directories instance;
		return &instance;
	}
}