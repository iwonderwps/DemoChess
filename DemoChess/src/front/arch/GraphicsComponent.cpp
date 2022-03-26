#include "GraphicsComponent.h"
#include "SysReg.h"
#include "../fundamental/D2DRenderer.h"


GraphicsComponent::GraphicsComponent():
	bHiden(false), z(0), pD2D(0)
{

}

GraphicsComponent::~GraphicsComponent() {

}

void GraphicsComponent::Reg(SysReg* pReg) {
	pReg->Reg(SysReg::SysName::D2D, this);
	this->pD2D = static_cast<D2DRenderer*>(pReg->GetPSys(SysReg::SysName::D2D));
}

void GraphicsComponent::Draw(D2DRenderer* pD2D) {

}

void GraphicsComponent::Init(D2DRenderer* pD2D){
	
}

bool GraphicsComponent::IsHidden() const{
	return bHiden;
}

void GraphicsComponent::SetHide(bool state){
	bHiden = state;
}

float GraphicsComponent::GetZ() const{
	return z;
}

void GraphicsComponent::SetZ(float z){
	this->z = z;
	pD2D->OnReSort();
}
