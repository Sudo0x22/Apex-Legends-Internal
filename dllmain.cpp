#include"source/core/core.hpp"
BOOL APIENTRY DllMain(HMODULE hModule, DWORD hReasons, LPVOID hBuffer) {
	if (hReasons != DLL_PROCESS_ATTACH)
		return FALSE;
	pCore.Initialize();
	return TRUE;
}