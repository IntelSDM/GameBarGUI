#pragma once
#include "Entity.h"
class TabListBoxController : public Container
{
protected:
public:
	TabListBoxController(float x, float y, float width, float height);
	void Update();
	void Draw();
};