#pragma once

#include <Windows.h>

class D2DRenderer;
class Timer;
class Input;

class AppGameObject;

class AppFront {
public:
	AppFront();
	virtual ~AppFront();
public:
	virtual void Init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
	virtual void Run();
	virtual void ShutDown();
private:
	void UpdateFPSToTitle(float dt);
protected:
	long clientWidth;
	long clientHeight;
	WNDCLASSEX wc;
	HWND mainWindow;
	D2DRenderer* pD2D;
	Timer* pTimer;
	Input* pInput;
	//AppGameObject* pAppGameObject;
};

