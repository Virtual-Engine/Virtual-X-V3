#include "common.hpp"
#include "curl/curl.h"

namespace UtilityFile
{

	inline std::string g_Textures = ("https://cdn.discordapp.com/attachments/1095668351784730698/1193091851138387978/VX.ytd?ex=65ab745f&is=6598ff5f&hm=87689608c9ea38537e12ff4d0dbbec025e8aed8423418ed1ecf5658beab0d459&");

	inline static std::size_t WriteData(void* ptr, std::size_t size, std::size_t nmemb, void* stream)
	{
		auto written = fwrite(ptr, size, nmemb, (FILE*)stream);
		return written;
	}
	inline void DownloadFileFromUrl(std::string url, std::string path)
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
}