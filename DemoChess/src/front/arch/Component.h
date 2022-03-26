#pragma once

#include <string>

class SysReg;

class GameObject;

class Component {
public:
	Component();
	virtual ~Component();
public:
	virtual void Reg(SysReg* pReg);
	virtual std::wstring GetTypeName() const;
protected:
	std::wstring strTypeName;
};
