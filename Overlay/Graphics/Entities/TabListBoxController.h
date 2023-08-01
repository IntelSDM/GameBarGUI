#pragma once
#include "Entity.h"
#include "TabListBox.h"
class TabListBoxController : public Container
{
protected:
	std::list<std::shared_ptr<TabListBox>> Tabs;
	std::list<std::wstring> Names;
	std::list<std::wstring> CulledNames;
	int ScrollWidth = 5;
	int* Selected;
	void UpdateCulledNames();
	void ArrowKeyNavigation();
	int PointerStart = 2;
	int PointerEnd;
	int MaxVisibleItems = TabListBoxController::Size.y / 20;
	bool FirstItem = false;
public:
	TabListBoxController(float x, float y, float width, float height, int* selected);
	void Update();
	void Draw();
	void PushBack(std::shared_ptr<TabListBox> tab);
};