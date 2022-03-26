#include "TestObj.h"

#include "../arch/CircleGraphics.h"

TestObj::TestObj(){
	x = 50;
	y = 50;
	r = 50;
}

TestObj::~TestObj(){

}

void TestObj::Init(){
	Component* temp = AddNewComponent<CircleGraphics>(x, y, r, CircleGraphics::COLOR::Green);
	circleGraphics = dynamic_cast<CircleGraphics*>(temp);
}
