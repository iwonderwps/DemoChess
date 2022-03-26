#pragma once

#include "GameObject.h"

class AppGameObject :public GameObject {
public:
	AppGameObject();
	virtual ~AppGameObject();
public:
	virtual void OnInit();
	virtual void OnStartRun();
	virtual void OnEndRun();
	virtual void OnEnd();
};
