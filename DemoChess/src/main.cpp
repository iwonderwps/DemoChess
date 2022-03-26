#include <Windows.h>

#include "front/fundamental/AppFront.h"
#include "./util/GetIns.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	AppFront* pAppFront = GetInstanceAppFront();
	pAppFront->Init(hInstance, hPrevInstance, lpCmdLine, nShowCmd);
	pAppFront->Run();
	pAppFront->ShutDown();
	return 0x679;
}

