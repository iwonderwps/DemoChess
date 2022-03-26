#include "SysReg.h"

#include "../fundamental/D2DRenderer.h"
#include "../fundamental/Input.h"

#include "GraphicsComponent.h"
#include "GameWndComponent.h"

SysReg::SysReg(){

}

SysReg::~SysReg(){

}

void SysReg::Reg(SysName sname, Component* pComponent){
	switch (sname){
	case SysReg::SysName::D2D: {
		GraphicsComponent* p = dynamic_cast<GraphicsComponent*>(pComponent);
		if (!p)
			throw;
		GetInstanceD2DRenderer()->AddGraphicsComponent(p);
		break;
	}		
	case SysReg::SysName::INPUT: {
		GameWndComponent* p = dynamic_cast<GameWndComponent*>(pComponent);
		if (!p)
			throw;
		GetInstanceInput()->AddGameWndComponent(p);
		break;
	}		
	case SysReg::SysName::COMM: {
		// not implemented yet
		break;
	}		
	default:
		break;
	}
}

void* SysReg::GetPSys(SysName sname) const{
	switch (sname){
	case SysReg::SysName::D2D:
		return GetInstanceD2DRenderer();
	case SysReg::SysName::INPUT:
		return GetInstanceInput();
	case SysReg::SysName::COMM:
		// not implemented yet
		break;
	default:
		break;
	}
	return nullptr;
}
