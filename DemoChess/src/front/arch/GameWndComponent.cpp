#include "GameWndComponent.h"
#include "SysReg.h"

GameWndComponent::GameWndComponent():
	xClickLastLocal(0), yClickLastLocal(0),
	xPosParent(0), yPosParent(0),
	width(0), height(0),
	z(0)
{

}

GameWndComponent::~GameWndComponent(){

}

void GameWndComponent::Reg(
	SysReg* pReg,
	int xPosParent, int yPosParent, int width, int height,
	float z
){
	pReg->Reg(SysReg::SysName::INPUT, this);
	this->xPosParent = xPosParent;
	this->yPosParent = yPosParent;
	this->width = width;
	this->height = height;
	this->z = z;
}

void GameWndComponent::OnClick(int xClickParent, int yClickParent){
	xClickLastLocal = xClickParent - xPosParent;
	yClickLastLocal = yClickParent - yPosParent;
}

void GameWndComponent::OnClick(int xClickParent, int yClickParent, double time){
	OnClick(xClickParent, yClickParent);
}

bool GameWndComponent::IsInside(int xParent, int yParent){
	int xLocal = xParent - xPosParent;
	int yLocal = yParent - yPosParent;
	if (
		xLocal >= 0 && xLocal <= width &&
		yLocal >= 0 && yLocal <= height
		) {
		return true;
	}
	return false;
}

void GameWndComponent::MoveTo(int xNewParent, int yNewParent) {
	xPosParent = xNewParent;
	yPosParent = yNewParent;
}

float GameWndComponent::GetZ() const{
	return this->z;
}

void GameWndComponent::SetZ(float z){
	this->z = z;
}
