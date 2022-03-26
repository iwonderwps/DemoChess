#include <Windows.h>
#include <tchar.h>

#include <string>
#include <sstream>
#include <memory>

#include "AppFront.h"

#include "Timer.h"
#include "D2DRenderer.h"
#include "Input.h"

#include "../arch/AppGameObject.h"

#include "../../util/SimpleLoader.h"
#include "../../util/SimpleRelease.h"
#include "../../util/GetIns.h"

using std::wstring;
using std::wstringstream;
using std::unique_ptr;

extern unique_ptr<AppGameObject> pAppGameObject;

AppFront::AppFront():
	clientHeight(0), clientWidth(0), wc{0}, mainWindow(0),
	pD2D(0), pTimer(0), pInput(0)
{
	//pAppGameObject = new AppGameObject();
}

AppFront::~AppFront(){
	//SimpleDelete(&pAppGameObject);
}

void AppFront::Init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	// forward init fundamental class
	pInput = GetInstanceInput();

	// load main window cfg
	wstring settingsFileName(L"cfg/MainWindow.txt");
	SimpleLoader cfgMainWindow;
	cfgMainWindow.load(settingsFileName);
	clientWidth = (long)cfgMainWindow.get<int>(L"ClientWidth");
	clientHeight = (long)cfgMainWindow.get<int>(L"ClientHeight");
	wstring strWndName = cfgMainWindow.get<wstring>(L"WindowName");

	// reg main window class
	wc.cbClsExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = 0;
	wc.hIconSm = 0;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = pInput->MAIN_WND_PROC;
	wc.lpszClassName = L"MainWndClass";
	wc.lpszMenuName = 0;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClassEx(&wc);

	// create main window
	RECT rect = { 0, 0, clientWidth, clientHeight };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);
	LONG wndStyle = WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME;
	//wndStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU);
	wndStyle &= ~(WS_THICKFRAME | WS_MAXIMIZEBOX);
	mainWindow = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW, wc.lpszClassName, strWndName.c_str(),
		wndStyle, CW_USEDEFAULT, CW_USEDEFAULT,
		rect.right - rect.left, rect.bottom - rect.top,
		NULL, NULL, hInstance, NULL);

	// init fundamental class (pInput inited)
	pD2D = GetInstanceD2DRenderer();
	pD2D->CreateWindowSizeDependentResources(mainWindow);
	pTimer = GetInstanceTimer();

	// init game
	pAppGameObject->OnInit();
}

void AppFront::Run() {
	ShowWindow(mainWindow, SW_SHOW);
	UpdateWindow(mainWindow);

	// set game loop controller
	bool continueRunning = true;
	MSG msg = { 0 };
	float accumulatedTime = 0.0;
	int nLoops = 0;
	bool bPaused = false;
	const float dt = 1 / 240.0f;
	const float maxSkipFrames = 10;

	//
	pAppGameObject->OnStartRun();

	pD2D->BeforeRenderLoop();

	// game loop
	pTimer->reset();
	while (continueRunning) {
		// peek for messages
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
			{
				continueRunning = false;
				break;
			}
		}
		pTimer->tick();
		if (!bPaused) {
			// DipsatchMessage is in the same thread with WndProc
			// therefore, simple input process can be made in WndProc instead of here.			
			float delta = (float)pTimer->getDeltaTime();
			accumulatedTime += delta;
			// now update the game logic with fixed dt as often as possible
			nLoops = 0;
			while (accumulatedTime >= dt && nLoops < maxSkipFrames) {
				pD2D->Update(dt);
				accumulatedTime -= dt;
				nLoops++;
			}
			pD2D->Render(accumulatedTime / dt);
			UpdateFPSToTitle(delta);
		}
	}

	pAppGameObject->OnEndRun();
}

void AppFront::ShutDown(){
	pAppGameObject->OnEnd();
}

void AppFront::UpdateFPSToTitle(float dt) {
	float FPS = 1 / dt;
	wstringstream s;
	s << L" - FPS: " << (int)FPS;
	SetWindowText(mainWindow, s.str().c_str());
}

