#include "Input.h"
#include "Timer.h"

#include "../arch/GameWndComponent.h"

#include "../../util/GetIns.h"


Input::Input(){
	pTimer = GetInstanceTimer();
}

Input* Input::_this = GetInstanceInput();

Input::~Input(){

}

void Input::AddGameWndComponent(GameWndComponent* p) {
	for (auto it = gameWndComponents.begin(); it != gameWndComponents.end(); ++it) {
		if (*it == p)
			throw;
	}
	gameWndComponents.push_back(p);
}

void Input::AddControllerComponent(ControllerComponent* p){
	for (auto it = controllerComponents.begin(); it != controllerComponents.end(); ++it) {
		if (*it == p)
			throw;
	}
	controllerComponents.push_back(p);
}

void Input::OnLButtonDown(HWND hWnd, unsigned int msg, WPARAM wParam, LPARAM lParam){
	int xPos = GET_X_LPARAM(lParam);
	int yPos = GET_Y_LPARAM(lParam);
	double time = pTimer->getTotalTime();
	for (auto it = gameWndComponents.begin(); it != gameWndComponents.end(); ++it) {
		if ((*it)->IsInside(xPos, yPos)) {
			(*it)->OnClick(xPos, yPos, time);
		}
	}
}

LRESULT Input::MAIN_WND_PROC(HWND hWnd, unsigned int msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_LBUTTONDOWN:
		if (wParam & MK_LBUTTON) {
			_this->OnLButtonDown(hWnd, msg, wParam, lParam);
		}
		return 0;
	default:
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}