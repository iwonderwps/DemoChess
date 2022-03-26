#include "ImgGraphics.h"
#include "../fundamental/D2DRenderer.h"
#include "../../util/SimpleRelease.h"

ImgGraphics::ImgGraphics():
	pImg(0), x(0), y(0), width(0), height(0)
{

}

ImgGraphics::~ImgGraphics(){
	SimpleRelease(&pImg);
}

void ImgGraphics::Reg(SysReg* pReg, const wchar_t* strPath, int x, int y, int width, int height){
	GraphicsComponent::Reg(pReg);
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->rscPath = strPath;
}

void ImgGraphics::Draw(D2DRenderer* pD2D){
	if (this->IsHidden())
		return;
	pD2D->DrawImg(pImg, x, y, width, height);
}

void ImgGraphics::Init(D2DRenderer* pD2D) {
	pD2D->LoadImgFromFile(rscPath.c_str(), width, height, &pImg);
}

void ImgGraphics::MoveTo(int xNewPos, int yNewPos) {
	x = xNewPos;
	y = yNewPos;
}

