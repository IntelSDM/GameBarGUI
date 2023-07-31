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
void TabListBoxController::UpdateCulledNames()
{
	CulledNames.clear();
	auto it = TabListBoxController::Names.begin();
	float originalwidth = GetTextWidth(*it, 11, "Verdana");
	/*
	void DropDown::ConvertSelectedName()
{
	auto it = DropDown::Names.begin();
	std::advance(it, *Index);
	float originalwidth = GetTextWidth(*it, 11, "Verdana");

	if (originalwidth < DropDown::Size.x - DropDown::CutOffBuffer)
	{
		DropDown::SelectedName = *it;
		TextWidth = originalwidth;
		return;
	}
	else
	{
		std::wstring str = *it;
		for (int i = str.length(); i > 0; i--)
		{
			str.erase(std::prev((str).end()));
			float width = GetTextWidth(str + L"..", 11, "Verdana");
			if (width < DropDown::Size.x - DropDown::CutOffBuffer)
			{
				DropDown::SelectedName = str + L"..";
				TextWidth = width;
				return;
			}
		}
		DropDown::SelectedName = str + L"..";
		TextWidth = GetTextWidth(str + L"..", 11, "Verdana");
	}

}
	*/
}
void TabListBoxController::Update()
{
	if (!TabListBoxController::Parent)
		TabListBoxController::SetVisible(false);
	if (!TabListBoxController::IsVisible())
		return;
	TabListBoxController::ParentPos = TabListBoxController::Parent->GetParentPos();
}
void TabListBoxController::Draw()
{
	if (!TabListBoxController::IsVisible())
		return;
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
	TabListBoxController::Names.push_back(tab->GetName());
}