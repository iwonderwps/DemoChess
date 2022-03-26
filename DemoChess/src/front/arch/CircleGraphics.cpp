#include "CircleGraphics.h"
#include "../fundamental/D2DRenderer.h"
#include "../../util/SimpleRelease.h"

CircleGraphics::CircleGraphics():
	x(0), y(0), radius(0), pBrush(0),color(COLOR::White)
{

}

CircleGraphics::~CircleGraphics() {
	SimpleRelease(&pBrush);
}

void CircleGraphics::Reg(SysReg* pReg, int x, int y, int radius, COLOR ctype) {
	GraphicsComponent::Reg(pReg);
	this->x = x;
	this->y = y;
	this->radius = radius;
	color = ctype;
}

void CircleGraphics::Draw(D2DRenderer* pD2D) {
	pD2D->DrawEllipse(x, y, radius, radius, pBrush);
}

void CircleGraphics::Init(D2DRenderer* pD2D) {
	ID2D1RenderTarget* pRT = pD2D->GetRenderTarget();
	pRT->CreateSolidColorBrush(color, &pBrush);
}

