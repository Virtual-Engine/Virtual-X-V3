#pragma once
#include "common.hpp"
#include "JSON/json.hpp"
#include "log/log.hpp"
namespace VX
{
	class settings
	{
	public:
		explicit settings() = default;
		~settings() = default;

		nlohmann::json options;
		nlohmann::json default_options =
			R"({

			"key_classic": true,
			"key_numpad" : false,
			"Draw_Instructional" : true
		

		})"_json;
		//g_settings.options["Self_Invincible"].get<bool>()
		bool save()
		{
			
			std::string settings_file = (g_utility.get_documents_path() + "\\Virtual X\\Config\\Settings.json");

			std::ofstream file(settings_file, std::ios::out | std::ios::trunc);
			file << options.dump(4);
			file.close();
			return true;
		}

		bool load()
		{
			std::string settings_file = (g_utility.get_documents_path() + "\\Virtual X\\Config\\Settings.json");

			std::ifstream file(settings_file);

			if (!file.is_open())
			{
				write_default_config();
				file.open(settings_file);
			}

			file >> options;

			bool should_save = false;
			for (auto& e : default_options.items())
			{
				if (options.count(e.key()) == 0)
				{
					should_save = true;
					options[e.key()] = e.value();
				}
			}

			if (should_save)
			{
				g_log.send("Config", "Save config sucessfuly");
				save();
			}

			return true;
		}

	private:
		bool write_default_config()
		{
			std::string settings_file = (g_utility.get_documents_path() + "\\Virtual X\\Config\\Settings.json");

			std::ofstream file(settings_file, std::ios::out);
			file << default_options.dump(4);
			file.close();

			options.clear();
			options = default_options;

			return true;
		}
	};

	inline settings g_settings;
}
