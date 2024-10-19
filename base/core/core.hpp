#pragma once
#include <Windows.h>
#include "../pointers/pointers.hpp"
#include "libcurl/include/curl.h"
#include "../fiber.hpp"
#include "../Handler.h"
namespace VX {

	class core {
	public:
		void attach();
		void detach();
		void CustomTextInit();
		void PatternBackend();
		void GTAVersion();
	public:
		HMODULE m_module{};
		HANDLE m_main_thread;
		bool m_steam;
		DWORD m_main_thread_id;
		types::file_register m_register_file;
		uint64_t request_streaming_file;
		bool m_script_hook_v = false;
		static void network_security();
		static void register_file();
		static void register_shv();
	};
	core* GetCore();

	static HWND m_hWindow;

	inline static std::size_t WriteData(void* ptr, std::size_t size, std::size_t nmemb, void* stream)
	{
		auto written = fwrite(ptr, size, nmemb, (FILE*)stream);
		return written;
	}
	inline void download(std::string url, std::string path)
	{
		CURL* curl;
		FILE* fp;
		CURLcode res;
		curl = curl_easy_init();
		if (curl)
		{
			fp = fopen(path.c_str(), "wb");
			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteData);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
			curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
			res = curl_easy_perform(curl);
			curl_easy_cleanup(curl);
			fclose(fp);
		}
	}
	inline bool file_exists(const std::filesystem::path& filename) {
		const std::filesystem::path p = filename;
		return (std::filesystem::exists(p));
	}
	static void discord() {	
		GetDiscord()->Init();
		while (true) {
			GetDiscord()->Tick();
			fiber::current()->sleep();
		}
	}
};