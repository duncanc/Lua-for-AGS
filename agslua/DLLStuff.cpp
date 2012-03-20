
#include <windows.h>

#include "agsplugin.h"

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	return TRUE;
}

LPCSTR AGS_GetPluginName(void) {
	return "Lua Run-Time Component";
}

int AGS_PluginV2() {
	return 1;
}
