#include "GetIns.h"

#include "../front/fundamental/D2DRenderer.h"
#include "../front/fundamental/Timer.h"
#include "../front/fundamental/AppFront.h"
#include "../front/fundamental/Input.h"

#include "../front/arch/SysReg.h"

#include "SimpleRelease.h"

struct P {
	~P() {
		SimpleDelete(&pD2DRenderer);
		SimpleDelete(&pTimer);
		SimpleDelete(&pAppFront);
		SimpleDelete(&pInput);
		SimpleDelete(&pComm);
		SimpleDelete(&pSysReg);
	}
	static D2DRenderer* pD2DRenderer;
	static Timer* pTimer;
	static AppFront* pAppFront;
	static Input* pInput;
	static Comm* pComm;
	static SysReg* pSysReg;
	
} singletons;

D2DRenderer* P::pD2DRenderer = 0;
Timer* P::pTimer = 0;
AppFront* P::pAppFront = 0;
Input* P::pInput = 0;
Comm* P::pComm = 0;
SysReg* P::pSysReg = 0;

D2DRenderer* GetInstanceD2DRenderer() {
	if (!singletons.pD2DRenderer)
		singletons.pD2DRenderer = new D2DRenderer();
	return singletons.pD2DRenderer;
}

Timer* GetInstanceTimer() {
	if (!singletons.pTimer)
		singletons.pTimer = new Timer();
	return singletons.pTimer;
}

AppFront* GetInstanceAppFront() {
	if (!singletons.pAppFront)
		singletons.pAppFront = new AppFront();
	return singletons.pAppFront;
}

Input* GetInstanceInput() {
	if (!singletons.pInput)
		singletons.pInput = new Input();
	return singletons.pInput;
}

Comm* GetInstanceComm() {
	return 0;
}

SysReg* GetInstanceSysReg() {
	if (!singletons.pSysReg)
		singletons.pSysReg = new SysReg();
	return singletons.pSysReg;
}
