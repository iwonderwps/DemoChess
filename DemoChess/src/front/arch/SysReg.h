#pragma once

#include "../../util/GetIns.h"

class Component;

class D2DRenderer;
class Input;

class SysReg {
public:
	enum class SysName{
		D2D, INPUT, COMM,
	};
public:
	SysReg();
	~SysReg();
public:
	void Reg(SysName sname, Component* pComponent);
public:
	void* GetPSys(SysName sname) const;
};

