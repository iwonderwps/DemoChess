#pragma once

#include <d2d1.h>

#include "Component.h"

class SysReg;

class D2DRenderer;

class GraphicsComponent:public Component {
public:
	typedef D2D1::ColorF COLOR;
	typedef ID2D1Bitmap Img;
public:
	GraphicsComponent();
	virtual ~GraphicsComponent();
public:
	virtual void Reg(SysReg* pReg) override;
public:
	virtual void Draw(D2DRenderer* pD2D);
	virtual void Init(D2DRenderer* pD2D);
public:
	virtual bool IsHidden() const;
	virtual void SetHide(bool state);
public:
	virtual float GetZ() const;
	virtual void SetZ(float z);
protected:
	bool bHiden;
protected:
	float z;
private:
	D2DRenderer* pD2D;
};

