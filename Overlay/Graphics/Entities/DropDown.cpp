#include "pch.h"
#include "Input.h"
#include "Drawing.h"
#include "DropDown.h"
#include "Font.h"
DropDown::DropDown(float x, float y, std::wstring text, int* index, std::list<std::wstring>names)
{
	DropDown::Pos = { x,y };
	DropDown::Name = text;
	DropDown::Index = index;
	DropDown::Names = names;
	DropDown::Size = { 120,20 };
	DropDown::CalculateBuffer();
	DropDown::ConvertSelectedName();
	if (DropDown::MaxVisibleItems > DropDown::Names.size())
	{
		DropDown::MaxVisibleItems = DropDown::Names.size();
	}
	DropDown::PointerStart = 0;
	DropDown::PointerEnd = DropDown::MaxVisibleItems;
}
void DropDown::CalculateBuffer()
{
	if (!DropDown::Active)
		DropDown::CutOffBuffer = 15;
	else
		DropDown::CutOffBuffer = 0;
}
void DropDown::SetDropDownWidth()
{
	float width = 0;
	for (std::wstring str : DropDown::Names)
	{
		float wdth = GetTextWidth(str, 11, "Verdana");
		if (wdth > width)
			width = wdth;
	}
	DropDown::DropWidth = width;
}
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
void DropDown::ArrowNavigation()
{
	if (!DropDown::Active)
		return;
	if (IsKeyClicked(VK_DOWN) && DropDown::LastClick < (clock() * 0.00001f))
	{
		if (DropDown::Names.size()-1> DropDown::PointerEnd)
		{
			DropDown::PointerEnd++;
			DropDown::PointerStart++;
			DropDown::LastClick = (clock() * 0.00001f) + 0.002f;
		}
	}
	if (IsKeyClicked(VK_UP) && DropDown::LastClick < (clock() * 0.00001f))
	{
		if (DropDown::PointerStart > 0)
		{
			DropDown::PointerEnd--;
			DropDown::PointerStart--;
			DropDown::LastClick = (clock() * 0.00001f) + 0.002f;
		}
	}
}
void DropDown::Update()
{
	if (!DropDown::Parent)
		DropDown::SetVisible(false);
	if (!DropDown::IsVisible())
		return;
	DropDown::ArrowNavigation();
	DropDown::ParentPos = DropDown::Parent->GetParentPos();
	DropDown::CalculateBuffer();
	DropDown::UpdateScrollBar();
	if (!DropDown::Blocked)
	{
		if (IsMouseInRectangle(DropDown::Pos + ParentPos, DropDown::Size) && IsKeyClicked(VK_LBUTTON) && DropDown::LastClick < (clock() * 0.00001f))
		{
			if (!DropDown::Active)
			{
				DropDown::Active = true;
				DropDown::SetBlockedSiblings(true);
				DropDown::LastClick = (clock() * 0.00001f) + 0.002f;
				DropDown::CalculateBuffer();
				DropDown::ConvertSelectedName();
			}
			else
			{
				DropDown::Active = false;
				DropDown::SetBlockedSiblings(false);
				DropDown::CalculateBuffer();
				DropDown::ConvertSelectedName();
				DropDown::LastClick = (clock() * 0.00001f) + 0.002f;
			}
		}
	}
	if ( IsKeyClicked(VK_LBUTTON) && DropDown::Active && !(IsMouseInRectangle(DropDown::Pos + ParentPos, DropDown::Size) || IsMouseInRectangle(DropDown::ParentPos.x + DropDown::Pos.x - (DropDown::SizeDifference / 2), DropDown::ParentPos.y + DropDown::Pos.y + DropDown::Size.y +5, DropDown::DropWidth, DropDown::Names.size() * DropDown::Size.y) || IsMouseInRectangle(DropDown::ParentPos.x + DropDown::Pos.x + DropDown::Size.x + (DropDown::SizeDifference / 2), DropDown::ParentPos.y + DropDown::Pos.y + DropDown::Size.y + 4, 6, (DropDown::PointerEnd - DropDown::PointerStart) * DropDown::Size.y)))
	{
		DropDown::Active = false;
		DropDown::SetBlockedSiblings(false);
		DropDown::CalculateBuffer();
		DropDown::ConvertSelectedName();
	}
	if ((IsKeyClicked(VK_RETURN) || IsKeyClicked(VK_ESCAPE)) && DropDown::Active)
	{
		DropDown::Active = false;
		DropDown::SetBlockedSiblings(false);
		DropDown::CalculateBuffer();
		DropDown::ConvertSelectedName();
	}
	if (DropDown::Active)
	{
		DropDown::SizeDifference = DropDown::DropWidth - DropDown::TextWidth;
		DropDown::SetDropDownWidth();
		int i = 0;
		for (const std::wstring& name : DropDown::Names)
		{
			if (i < DropDown::PointerStart)
			{
				i++;
				continue;
			}
			if (i > DropDown::PointerEnd-1)
			{
				i++;
				continue;
			}
			float itemposy = DropDown::ParentPos.y + DropDown::Pos.y + DropDown::Size.y + 5 + ((i - DropDown::PointerStart) * DropDown::Size.y);
			
			if (IsMouseInRectangle(DropDown::ParentPos.x + DropDown::Pos.x , itemposy, DropDown::DropWidth + (DropDown::SizeDifference/2), DropDown::Size.y) && IsKeyClicked(VK_LBUTTON))
			{
				*DropDown::Index = i;
				DropDown::Active = false;
				DropDown::SetBlockedSiblings(false);
				DropDown::CalculateBuffer();
				DropDown::ConvertSelectedName();

			}
			i++;
		}
	}
}
void DropDown::UpdateScrollBar()
{
	if (!IsKeyDown(VK_LBUTTON))
		DropDown::ScrollBar = false;
	if (IsMouseInRectangle(DropDown::ParentPos.x + DropDown::Pos.x + DropDown::Size.x + (DropDown::SizeDifference / 2), DropDown::ParentPos.y + DropDown::Pos.y + DropDown::Size.y + 4, 6, (DropDown::PointerEnd - DropDown::PointerStart) * DropDown::Size.y) && IsKeyClicked(VK_LBUTTON))
		DropDown::ScrollBar = true;
	if (DropDown::ScrollBar)
	{
		float ratio = (MousePos.y - (float)(DropDown::ParentPos.y + DropDown::Pos.y + DropDown::Size.y + 4)) / (float)((DropDown::MaxVisibleItems - 1) * DropDown::Size.y);
		ratio = std::clamp(ratio, 0.0f, 1.0f);
		DropDown::PointerEnd = (int)(DropDown::MaxVisibleItems + (DropDown::Names.size() - DropDown::MaxVisibleItems) * ratio);
	
	}
	DropDown::PointerStart = DropDown::PointerEnd - DropDown::MaxVisibleItems;
}

void DropDown::Draw()
{
	if (!DropDown::Parent)
		DropDown::SetVisible(false);
	if (!DropDown::IsVisible())
		return;
	OutlineRectangle(DropDown::ParentPos.x + DropDown::Pos.x - 1, DropDown::ParentPos.y + DropDown::Pos.y - 1, DropDown::Size.x + 1, DropDown::Size.y + 1, 1, Colour(130, 130, 130, 255));
	FilledRectangle(DropDown::ParentPos.x + DropDown::Pos.x, DropDown::ParentPos.y +DropDown::Pos.y, DropDown::Size.x, DropDown::Size.y, Colour(80, 80, 80, 255));
	float trianglex1 = DropDown::ParentPos.x + DropDown::Pos.x + DropDown::Size.x - 12;
	float triangley1 = DropDown::ParentPos.y + DropDown::Pos.y +3;
	float trianglex2 = DropDown::ParentPos.x + DropDown::Pos.x + DropDown::Size.x - 3;
	float triangley2 = DropDown::Pos.y + DropDown::ParentPos.y + 3;
	float trianglex3 = DropDown::ParentPos.x + DropDown::Pos.x + DropDown::Size.x - 7;
	float triangley3 = DropDown::ParentPos.y + DropDown::Pos.y + DropDown::Size.y - 3;
	if(!DropDown::Active)
	FilledTriangle(trianglex1, triangley1, trianglex2, triangley2, trianglex3, triangley3, Colour(255, 0, 0, 255));
	DrawText(DropDown::ParentPos.x + DropDown::Pos.x + 5, DropDown::ParentPos.y + DropDown::Pos.y + (DropDown::Size.y /8),DropDown::SelectedName, "Verdana", 11, Colour(240, 240, 240, 255), None);

	if (DropDown::DropWidth < DropDown::Size.x)
	{
		DropDown::DropWidth = DropDown::Size.x;
		DropDown::SizeDifference = 0;
	}
	if (DropDown::Active)
	{
		OutlineRectangle(DropDown::ParentPos.x + DropDown::Pos.x - (DropDown::SizeDifference / 2) - 1, DropDown::ParentPos.y + DropDown::Pos.y + DropDown::Size.y +4, DropDown::DropWidth + 1, (DropDown::PointerEnd - DropDown::PointerStart) * DropDown::Size.y + 1, 1, Colour(130, 130, 130, 255));
		FilledRectangle(DropDown::ParentPos.x + DropDown::Pos.x - (DropDown::SizeDifference / 2), DropDown::ParentPos.y + DropDown::Pos.y + DropDown::Size.y +5, DropDown::DropWidth, (DropDown::PointerEnd - DropDown::PointerStart) * DropDown::Size.y,Colour(80,80,80,255));

		int i = 0;
		for (const std::wstring& name : DropDown::Names)
		{
			if (i < DropDown::PointerStart)
			{
				i++;
				continue;
			}
			if (i > DropDown::PointerEnd-1)
			{
				i++;
				continue;
			}
			float itemposy = DropDown::ParentPos.y + DropDown::Pos.y + DropDown::Size.y + 5 + ((i- DropDown::PointerStart) * DropDown::Size.y);
			if (IsMouseInRectangle(DropDown::ParentPos.x + DropDown::Pos.x - (DropDown::SizeDifference / 2), itemposy, DropDown::DropWidth, DropDown::Size.y))
			{
				FilledRectangle(DropDown::ParentPos.x + DropDown::Pos.x - (DropDown::SizeDifference / 2), itemposy, DropDown::DropWidth, DropDown::Size.y, Colour(150, 150, 150, 120));
				
			}
			if(i == *DropDown::Index)
				DrawText(DropDown::ParentPos.x + DropDown::Pos.x + 5 - (DropDown::SizeDifference / 2), itemposy + (DropDown::Size.y / 8), name, "Verdana", 11, Colour(255, 0, 0, 255), None);
			else
				DrawText(DropDown::ParentPos.x + DropDown::Pos.x + 5 - (DropDown::SizeDifference / 2), itemposy + (DropDown::Size.y / 8), name, "Verdana", 11, Colour(240, 240, 240, 255), None);
			i++;
		}
		OutlineRectangle(DropDown::ParentPos.x + DropDown::Pos.x + DropDown::Size.x + (DropDown::SizeDifference / 2), DropDown::ParentPos.y + DropDown::Pos.y + DropDown::Size.y + 4, 6, (DropDown::PointerEnd - DropDown::PointerStart) * DropDown::Size.y + 1, 1, Colour(130, 130, 130, 255));
		int unselectedelements = Names.size() - MaxVisibleItems;
		float unselectedclamp = std::clamp(unselectedelements, 1, (int)Names.size());
		float scrollheight = ((DropDown::PointerEnd - DropDown::PointerStart) * DropDown::Size.y) / (unselectedclamp);
		float scrolly = DropDown::ParentPos.y + DropDown::Pos.y + DropDown::Size.y + 5 + (((PointerEnd - MaxVisibleItems) * Size.y));
		float scrollyclamp = std::clamp(scrolly, DropDown::ParentPos.y + DropDown::Pos.y + DropDown::Size.y + 5, DropDown::ParentPos.y + DropDown::Pos.y + DropDown::Size.y + 5 + ((DropDown::PointerEnd - DropDown::PointerStart) * DropDown::Size.y) - scrollheight);


		FilledRectangle(DropDown::ParentPos.x + DropDown::Pos.x + DropDown::Size.x + (DropDown::SizeDifference / 2), scrollyclamp, 6, scrollheight, Colour(255, 0, 0, 255));
	}
}