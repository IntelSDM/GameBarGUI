#pragma once
#include "Entity.h"
#include "TabListBox.h"
class TabListBoxController : public Container
{
protected:
	std::list<std::shared_ptr<TabListBox>> Tabs;
	int* Selected;
public:
	TabListBoxController(float x, float y, float width, float height, int* selected);
	void Update();
	void Draw();
	void PushBack(std::shared_ptr<TabListBox> tab);
};