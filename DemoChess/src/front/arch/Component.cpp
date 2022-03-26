#include "Component.h"
#include "GameObject.h"


Component::Component(){
	//strTypeName = L"Component";
}

Component::~Component() {

}

void Component::Reg(SysReg* pReg) {
	return;
}

std::wstring Component::GetTypeName() const {
	return strTypeName;
}
