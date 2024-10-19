#include "common.hpp"

namespace BackendRegistry
{
	class BackendRegistry1
	{
		HKEY hKey;
		LPCSTR subKey;
		LPCSTR subValue;
		HKEY resKey;
		DWORD dataLen;

	public:

		bool isRetailKey();
		bool isSteamKey();
		bool isEpicKey();
		std::string GetValue(bool steam = false);

	private:

	};
	BackendRegistry1* GetBackendRegistry1();
}