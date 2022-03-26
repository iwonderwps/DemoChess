#pragma once

#include "../arch/GameObject.h"

class CircleGraphics;

class TestObj :public GameObject {
public:
	TestObj();
	~TestObj();
public:
	void Init();
private:
	int x, y;
	int r;
	CircleGraphics* circleGraphics;
};
