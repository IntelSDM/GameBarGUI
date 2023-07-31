#include "Pch.h"
#include "TabListBoxController.h"
#include "GUI.h"
#include "Input.h"
#include "Drawing.h"
#include "Font.h"
#include "Graphics.h"
#include "TabListBox.h"
TabListBoxController::TabListBoxController(float x, float y, float width, float height,int* selected)
{
	TabListBoxController::Pos = { x,y };
	TabListBoxController::Size = { width,height };
	TabListBoxController::Selected = selected;
}
void TabListBoxController::Update()
{
	TabListBoxController::ParentPos = TabListBoxController::Parent->GetParentPos();
}
void TabListBoxController::Draw()
{
	FilledRectangle(TabListBoxController::ParentPos.x + TabListBoxController::Pos.x, TabListBoxController::ParentPos.y + TabListBoxController::Pos.y, TabListBoxController::Size.x, TabListBoxController::Size.y, Colour(80, 80, 80, 255));
	OutlineRectangle(TabListBoxController::ParentPos.x + TabListBoxController::Pos.x-1, TabListBoxController::ParentPos.y + TabListBoxController::Pos.y-1, TabListBoxController::Size.x+1, TabListBoxController::Size.y+1,1,Colour(150, 150, 150, 255));
	FilledRectangle(TabListBoxController::ParentPos.x + TabListBoxController::Pos.x, TabListBoxController::ParentPos.y + TabListBoxController::Pos.y, 5, TabListBoxController::Size.y, Colour(130, 130, 130, 255));

	for each (std::shared_ptr<TabListBox> tab in TabListBoxController::Tabs)
	{
		if (tab->Index == *Selected)
		{

			tab->Draw();
			tab->Update();
		}
	}

}
void TabListBoxController::PushBack(std::shared_ptr<TabListBox> tab)
{
	TabListBoxController::Tabs.push_back(tab);
}