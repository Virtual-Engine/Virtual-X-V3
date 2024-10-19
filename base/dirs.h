#pragma once
#include "common.hpp"
#include <unordered_map>

#undef GetTempPath
namespace util::dirs {
	class directories {
	public:
		bool load();
		std::string create_string(std::string base, std::string folder);
		std::vector<std::string> get_files_in_directory(std::string dir, std::string extension);

		const char* get_log() { return get_path(PATH_LOG); }
		const char* get_gfx() { return get_path(PATH_GFX); }
		const char* get_config() { return get_path(PATH_CONFIGV2); }
		const char* get_vx() { return get_path(PATH_VX); }
		const char* get_tmp() { return get_path(PATH_TMP); }
		const char* get_theme() { return get_path(PATH_THEME); }
		const char* get_outfits() { return get_path(PATH_OUTFITS); }
		const char* get_vehicle() { return get_path(PATH_VEHICLE); }
		const char* get_teleport() { return get_path(PATH_TELEPORT); }
		const char* get_player() { return get_path(PATH_PLAYER); }
		const char* get_mapmods() { return get_path(PATH_MAPMODS); }
		const char* get_textures() { return get_path(PATH_TEXTURES); }
		const char* get_xml() { return get_path(PATH_SHV); }
		const char* get_asi() { return get_path(PATH_ASI); }

		bool DoesFileExist(String file);



		enum Paths {
			PATH_DOCUMENTS,
			PATH_VX,
			PATH_ASI,
			PATH_LOG,
			PATH_GFX,
			PATH_CONFIGV2,
			PATH_TMP,
			PATH_TEXTURES,
			PATH_THEME,
			PATH_OUTFITS,
			PATH_VEHICLE,
			PATH_TELEPORT,
			PATH_PLAYER,
			PATH_MAPMODS,
			PATH_SHV
		};
	private:
		std::unordered_map<Paths, char[MAX_PATH]> m_paths;

		const char* get_path(Paths path) {
			return m_paths[path];
		}
	};

	directories* get_directories();

	inline std::vector<std::string> get_files_in_directory(std::string dir, std::string extension = ".txt") {
		return get_directories()->get_files_in_directory(dir, extension);
	}

	inline bool load() {
		return get_directories()->load();
	}

	inline std::string create_string(std::string base, std::string folder) {
		return get_directories()->create_string(base, folder);
	}
#define get_path(name) get_directories()->get_##name##()
}