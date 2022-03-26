#pragma once

#include <d2d1.h>

#include <string>

#include "GraphicsComponent.h"

class ImgGraphics :public GraphicsComponent {
public:
	ImgGraphics();
	virtual ~ImgGraphics();
public:
	virtual void Reg(SysReg* pReg, const wchar_t* strPath, int x, int y, int width, int height);
	virtual void Draw(D2DRenderer* pD2D) override;
	virtual void Init(D2DRenderer* pD2D) override;
public:
	virtual void MoveTo(int xNewPos, int yNewPos);
protected:
	int x, y;
	int width, height;
	std::wstring rscPath;
	Img* pImg;
};
