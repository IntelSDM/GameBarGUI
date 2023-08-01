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
	TabListBoxController::PointerEnd = TabListBoxController::Size.y / 20;
	TabListBoxController::PointerStart = 0;
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
void TabListBoxController::ArrowKeyNavigation()
{
	if (TabListBoxController::Tabs.size() < TabListBoxController::Size.y / 20)
		return;
	if (IsKeyClicked(VK_DOWN) && TabListBoxController::LastClick < (clock() * 0.00001f))
	{
		if (TabListBoxController::Tabs.size() > TabListBoxController::PointerEnd)
		{
			TabListBoxController::PointerEnd++;
			TabListBoxController::PointerStart++;
			TabListBoxController::LastClick = (clock() * 0.00001f) + 0.002f;
		}
	}
	if (IsKeyClicked(VK_UP) && TabListBoxController::LastClick < (clock() * 0.00001f))
	{
		if (TabListBoxController::PointerStart > 0)
		{
			TabListBoxController::PointerEnd--;
			TabListBoxController::PointerStart--;
			TabListBoxController::LastClick = (clock() * 0.00001f) + 0.002f;
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
	TabListBoxController::ArrowKeyNavigation();
	TabListBoxController::ScrollBarAction();

	int i = 0;
	for (auto tab : TabListBoxController::Tabs)
	{
		if (i < TabListBoxController::PointerStart)
		{
			i++;
			continue;
		}
		if (i > TabListBoxController::PointerEnd - 1)
		{
			i++;
			continue;
		}
		float itemposy = TabListBoxController::ParentPos.y + TabListBoxController::Pos.y + ((i - TabListBoxController::PointerStart) * 20);
		if (IsMouseInRectangle(TabListBoxController::ParentPos.x + TabListBoxController::Pos.x + TabListBoxController::ScrollWidth + 2, (itemposy), TabListBoxController::Size.x - (TabListBoxController::ScrollWidth + 2), 20) && TabListBoxController::LastClick < (clock() * 0.00001f) && IsKeyClicked(VK_LBUTTON))
		{
			
			*Selected = tab->Index;
			TabListBoxController::LastClick = (clock() * 0.00001f) + 0.002f;
		}
		i++;
	}
}
void TabListBoxController::ScrollBarAction()
{
	if (!IsKeyDown(VK_LBUTTON))
		TabListBoxController::ScrollBarHeld = false;
	if (IsMouseInRectangle(TabListBoxController::ParentPos.x + TabListBoxController::Pos.x, TabListBoxController::ParentPos.y + TabListBoxController::Pos.y, 5, TabListBoxController::Size.y) && IsKeyClicked(VK_LBUTTON))
		TabListBoxController::ScrollBarHeld = true;
	if (TabListBoxController::ScrollBarHeld)
	{
		float ratio = (MousePos.y - (float)(TabListBoxController::ParentPos.y + TabListBoxController::Pos.y)) / (float)((TabListBoxController::MaxVisibleItems - 1) * 20);
		ratio = std::clamp(ratio, 0.0f, 1.0f);
		TabListBoxController::PointerEnd = (int)(TabListBoxController::MaxVisibleItems + (TabListBoxController::Names.size() - TabListBoxController::MaxVisibleItems) * ratio);

	}
	TabListBoxController::PointerStart = TabListBoxController::PointerEnd - TabListBoxController::MaxVisibleItems;
}
void TabListBoxController::Draw()
{
	if (!TabListBoxController::IsVisible())
		return;
	for (std::shared_ptr<TabListBox> tab : TabListBoxController::Tabs)
	{
		if (tab->Index == *Selected)
		{
			tab->Draw();
			tab->Update();
		}
	}
	FilledRectangle(TabListBoxController::ParentPos.x + TabListBoxController::Pos.x, TabListBoxController::ParentPos.y + TabListBoxController::Pos.y, TabListBoxController::Size.x, TabListBoxController::Size.y, Colour(80, 80, 80, 255));
	OutlineRectangle(TabListBoxController::ParentPos.x + TabListBoxController::Pos.x-1, TabListBoxController::ParentPos.y + TabListBoxController::Pos.y-1, TabListBoxController::Size.x+1, TabListBoxController::Size.y+1,1,Colour(150, 150, 150, 255));

	int i = 0;
	for (std::wstring culledname : TabListBoxController::CulledNames)
	{
		if (i < TabListBoxController::PointerStart)
		{
			i++;
			continue;
		}
		if (i > TabListBoxController::PointerEnd-1)
		{
			i++;
			continue;
		}
		float itemposy = TabListBoxController::ParentPos.y + TabListBoxController::Pos.y + ((i - TabListBoxController::PointerStart) * 20);
		if (!IsMouseInRectangle(TabListBoxController::ParentPos.x + TabListBoxController::Pos.x + TabListBoxController::ScrollWidth + 2, (itemposy), TabListBoxController::Size.x - (TabListBoxController::ScrollWidth + 2), 20))
		{
			DrawText(TabListBoxController::ParentPos.x + TabListBoxController::Pos.x + TabListBoxController::ScrollWidth + 2,(itemposy), culledname, "Verdana", 11, Colour(240, 240, 240, 255), None);
		}
		i++;
	}
	// do this in a seperate loop so we can draw over all culled names
	i = 0;
	for (std::wstring name : TabListBoxController::Names)
	{
		if (i < TabListBoxController::PointerStart)
		{
			i++;
			continue;
		}
		if (i > TabListBoxController::PointerEnd - 1)
		{
			i++;
			continue;
		}
		float itemposy = TabListBoxController::ParentPos.y + TabListBoxController::Pos.y + ((i - TabListBoxController::PointerStart) * 20);
		if (IsMouseInRectangle(TabListBoxController::ParentPos.x + TabListBoxController::Pos.x + TabListBoxController::ScrollWidth + 2, (itemposy), TabListBoxController::Size.x - (TabListBoxController::ScrollWidth + 2), 20))
		{
			int width = GetTextWidth(name, 11, "Verdana");
			if(width + TabListBoxController::ScrollWidth + 2 + 5 < TabListBoxController::Size.x)
			DrawText(TabListBoxController::ParentPos.x + TabListBoxController::Pos.x + TabListBoxController::ScrollWidth + 2 + 5, (itemposy), name, "Verdana", 11, Colour(255, 0, 0, 255), None);
			else
			{
				FilledRectangle(TabListBoxController::ParentPos.x + TabListBoxController::Pos.x + TabListBoxController::ScrollWidth + 2 + 5, (itemposy), width, 20, Colour(120,120,120,255));
				DrawText(TabListBoxController::ParentPos.x + TabListBoxController::Pos.x + TabListBoxController::ScrollWidth + 2 + 5, (itemposy) + 5, name, "Verdana", 11, Colour(255, 0, 0, 255), None);
			}
		}
	
		i++;
	}
	if (TabListBoxController::Tabs.size() > TabListBoxController::Size.y / 20)
	{
		int unselectedelements = Names.size() - MaxVisibleItems;
		float unselectedclamp = std::clamp(unselectedelements, 1, (int)Names.size());
		float scrollheight = TabListBoxController::Size.y / unselectedclamp;
		float scrolly = TabListBoxController::ParentPos.y + TabListBoxController::Pos.y + (((PointerEnd - MaxVisibleItems) * 20));
		float scrollyclamp = std::clamp(scrolly, TabListBoxController::ParentPos.y + TabListBoxController::Pos.y, TabListBoxController::ParentPos.y + TabListBoxController::Pos.y + 5 + ((TabListBoxController::PointerEnd - TabListBoxController::PointerStart) * 20) - scrollheight);

		FilledRectangle(TabListBoxController::ParentPos.x + TabListBoxController::Pos.x, TabListBoxController::ParentPos.y + TabListBoxController::Pos.y, TabListBoxController::ScrollWidth, TabListBoxController::Size.y, Colour(130, 130, 130, 255));
		FilledRectangle(TabListBoxController::ParentPos.x + TabListBoxController::Pos.x, scrollyclamp, 5, scrollheight, Colour(255, 0, 0, 255));
	}
}
void TabListBoxController::PushBack(std::shared_ptr<TabListBox> tab)
{
	TabListBoxController::Tabs.push_back(tab);
	TabListBoxController::Names.push_back(tab->GetName());
	if (!FirstItem)
	{
		*TabListBoxController::Selected = tab->Index;
		FirstItem = true;
	}
	TabListBoxController::Push(tab);
	TabListBoxController::UpdateCulledNames();
	TabListBoxController::PointerEnd = TabListBoxController::Tabs.size();
		TabListBoxController::MaxVisibleItems = TabListBoxController::Tabs.size();
	if (TabListBoxController::Tabs.size() > TabListBoxController::Size.y / 20)
		TabListBoxController::MaxVisibleItems = TabListBoxController::Size.y / 20;
	if (TabListBoxController::PointerEnd > TabListBoxController::Size.y / 20)
		TabListBoxController::PointerEnd = TabListBoxController::Size.y / 20;
	
}