#pragma once

#include <list>
#include <string>

#include "../../util/GetIns.h"


class Component;
class SysReg;

class GameObject {
public:
	GameObject();
	virtual ~GameObject();
public:
	template<class ComponentType, typename... ParamType>
	Component* AddNewComponent(ParamType&&... params) {
		ComponentType* pc = new ComponentType();
		Component* p = dynamic_cast<Component*>(pc);
		if (!p)
			throw;
		components.push_back(p);
		// pc->Reg(pD2D, pInput, pComm, params...);
		pc->Reg(pReg, params...);
		return p;
	}
private:
	// D2DRenderer* pD2D;
	// Input* pInput;
	// Comm* pComm;
	SysReg* pReg;
private:
	// own and see
	std::list<Component*> components;
};
