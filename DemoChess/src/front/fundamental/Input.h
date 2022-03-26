#pragma once

#include <Windows.h>
#include <windowsx.h>
#include <tchar.h>

#include <vector>

class Timer;

class GameWndComponent;
class ControllerComponent;

class Input {
public:
	static LRESULT CALLBACK MAIN_WND_PROC(HWND hWnd, unsigned int msg, WPARAM wParam, LPARAM lParam);
	static Input* _this;
public:
	Input();
	~Input();
public:
	void AddGameWndComponent(GameWndComponent* p);
	void AddControllerComponent(ControllerComponent* p);
private:
	void OnLButtonDown(HWND hWnd, unsigned int msg, WPARAM wParam, LPARAM lParam);
private:
	// see but not own
	std::vector<GameWndComponent*> gameWndComponents;
	// see but not own
	std::vector<ControllerComponent*> controllerComponents;
private:
	Timer* pTimer;
};
