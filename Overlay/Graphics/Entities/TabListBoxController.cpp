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
	for (std::wstring str : TabListBoxController::Names)
	{
		std::wstring culledname = L"";
		float width = GetTextWidth(str, 11, "Verdana");
		if (width < TabListBoxController::Size.x - TabListBoxController::ScrollWidth + 2)
		{
			CulledNames.push_back(str);
			
		}
		else
		{
			culledname = str;
			for (int i = culledname.length(); i > 0; i--)
			{
				culledname.erase(std::prev((culledname).end()));
				float width = GetTextWidth(culledname + L"..", 11, "Verdana");
				if (width < TabListBoxController::Size.x - TabListBoxController::ScrollWidth + 2)
				{
					CulledNames.push_back(culledname + L"..");
					break;
				}
			}
			
		}
	}
	
	
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
	FilledRectangle(TabListBoxController::ParentPos.x + TabListBoxController::Pos.x, TabListBoxController::ParentPos.y + TabListBoxController::Pos.y, TabListBoxController::ScrollWidth, TabListBoxController::Size.y, Colour(130, 130, 130, 255));
	int i = 0;
	for (std::wstring culledname : TabListBoxController::CulledNames)
	{
		if (!IsMouseInRectangle(TabListBoxController::ParentPos.x + TabListBoxController::Pos.x + TabListBoxController::ScrollWidth + 2, TabListBoxController::ParentPos.y + TabListBoxController::Pos.y + (i * 20), TabListBoxController::Size.x, 20))
		{
			DrawText(TabListBoxController::ParentPos.x + TabListBoxController::Pos.x + TabListBoxController::ScrollWidth + 2, TabListBoxController::ParentPos.y + TabListBoxController::Pos.y + (i * 20), culledname, "Verdana", 11, Colour(240, 240, 240, 255), None);
		}
		i++;
	}
	// do this in a seperate loop so we can draw over all culled names
	i = 0;
	for (std::wstring name : TabListBoxController::Names)
	{
		
		if (IsMouseInRectangle(TabListBoxController::ParentPos.x + TabListBoxController::Pos.x + TabListBoxController::ScrollWidth + 2, TabListBoxController::ParentPos.y + TabListBoxController::Pos.y + (i * 20), TabListBoxController::Size.x, 20))
		{
			int width = GetTextWidth(name, 11, "Verdana");
			if(width + TabListBoxController::ScrollWidth + 2 + 5 < TabListBoxController::Size.x)
			DrawText(TabListBoxController::ParentPos.x + TabListBoxController::Pos.x + TabListBoxController::ScrollWidth + 2 + 5, TabListBoxController::ParentPos.y + TabListBoxController::Pos.y + (i * 20), name, "Verdana", 11, Colour(255, 0, 0, 255), None);
			else
			{
				FilledRectangle(TabListBoxController::ParentPos.x + TabListBoxController::Pos.x + TabListBoxController::ScrollWidth + 2 + 5, TabListBoxController::ParentPos.y + TabListBoxController::Pos.y + (i * 20), width, 20, Colour(150,150,150,255));
				DrawText(TabListBoxController::ParentPos.x + TabListBoxController::Pos.x + TabListBoxController::ScrollWidth + 2 + 5, TabListBoxController::ParentPos.y + TabListBoxController::Pos.y + (i * 20), name, "Verdana", 11, Colour(255, 0, 0, 255), None);
			}
		}
	
		i++;
	}
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
	TabListBoxController::UpdateCulledNames();
}