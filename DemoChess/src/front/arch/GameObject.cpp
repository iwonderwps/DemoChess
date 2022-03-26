#include "GameObject.h"
#include "Component.h"


GameObject::GameObject(){
	// pD2D = GetInstanceD2DRenderer();
	// pInput = GetInstanceInput();
	// pComm = GetInstanceComm();
	pReg = GetInstanceSysReg();
	components.clear();
}

GameObject::~GameObject(){
	for (auto it = components.begin(); it != components.end(); ++it) {
		if (*it != 0) {
			delete (*it);
			*it = 0;
		}
	}
}

