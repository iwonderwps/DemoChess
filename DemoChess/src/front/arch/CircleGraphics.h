#pragma once

#include <d2d1.h>

#include "GraphicsComponent.h"

class CircleGraphics :public GraphicsComponent {
public:
	CircleGraphics();
	virtual ~CircleGraphics();
public:
	virtual void Reg(SysReg* pReg, int x, int y, int radius, COLOR ctype);
	virtual void Draw(D2DRenderer* pD2D) override;
	virtual void Init(D2DRenderer* pD2D) override;
protected:
	int radius;
	int x, y;
	COLOR color;
	ID2D1SolidColorBrush* pBrush;
};
