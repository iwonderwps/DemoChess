#pragma once

#include "Component.h"

class SysReg;

class GameWndComponent :public Component {
public:
	GameWndComponent();
	virtual ~GameWndComponent();
public:
	virtual void Reg(
		SysReg* pReg,
		int xPosParent, int yPosParent, int width, int height, 
		float z = 0
		);
public:
	// not in use or implemented
	// virtual void AddChild(GameWndComponent* pChildWnd);
public:
	virtual void OnClick(int xClickParent, int yClickParent);
	virtual void OnClick(int xClickParent, int yClickParent, double time);
	virtual bool IsInside(int xParent, int yParent);
public:
	virtual void MoveTo(int xNewParent, int yNewParent);
public:
	virtual float GetZ() const;
	virtual void SetZ(float z);
protected:
	// last x and y coord of the local wnd in pixel.
	int xClickLastLocal, yClickLastLocal;
	// the x and y coord in pixel of the wnd in its parent.
	int xPosParent, yPosParent;
	// width and height of the wnd.
	int width, height;
	// not in use or implemented
	float z;
};
