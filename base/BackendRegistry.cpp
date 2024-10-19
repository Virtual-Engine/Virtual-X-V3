#include "BackendRegistry.h"

namespace BackendRegistry
{
	BackendRegistry1 g_BackendRegistry;

	bool BackendRegistry1::isRetailKey()
	{
		hKey = HKEY_LOCAL_MACHINE;
		subKey = "SOFTWARE\\Wow6432Node\\Rockstar Games\\Grand Theft Auto V";
		long key = RegOpenKeyExA(hKey, subKey, 0, KEY_READ, &resKey);
		if (key == ERROR_SUCCESS) return true;
		else return false;
	}
	bool BackendRegistry1::isSteamKey()
	{
		hKey = HKEY_LOCAL_MACHINE;
		subKey = "SOFTWARE\\Wow6432Node\\Rockstar Games\\GTAV";
		long key = RegOpenKeyExA(hKey, subKey, 0, KEY_READ, &resKey);
		return (key == ERROR_SUCCESS);
	}
	bool BackendRegistry1::isEpicKey()
	{
		hKey = HKEY_LOCAL_MACHINE;
		subKey = "SOFTWARE\\Wow6432Node\\Rockstar Games\\GTA5";
		long key = RegOpenKeyExA(hKey, subKey, 0, KEY_READ, &resKey);
		return (key == ERROR_SUCCESS);
	}
	std::string BackendRegistry1::GetValue(bool steam)
	{

		DWORD dwType = REG_SZ;
		char value[1024];
		DWORD value_length = 1024;
		subValue = "InstallFolder";
		if (steam) subValue = "installfoldersteam";
		long key = RegQueryValueExA(resKey, subValue, NULL, &dwType, (LPBYTE)&value, &value_length);
		if (key == ERROR_FILE_NOT_FOUND) return std::string();
		else return std::string(value);
	}

	BackendRegistry1* GetBackendRegistry1() { return &g_BackendRegistry; }
}