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
	DropDown::Size = { 80,20 };
	DropDown::CalculateBuffer();
	DropDown::ConvertSelectedName();
}
void DropDown::CalculateBuffer()
{
	if (!DropDown::Active)
		DropDown::CutOffBuffer = 15;
	else
		DropDown::CutOffBuffer = 0;
}
void DropDown::Update()
{
	if (!DropDown::Parent)
		DropDown::SetVisible(false);
	if (!DropDown::IsVisible())
		return;
	
	DropDown::ParentPos = DropDown::Parent->GetParent()->GetPos();
	DropDown::CalculateBuffer();
	if (!DropDown::Blocked)
	{
		if (IsMouseInRectangle(DropDown::Pos + ParentPos, DropDown::Size) && IsKeyClicked(VK_LBUTTON) && DropDown::LastClick < (clock() * 0.00001f))
		{
			DropDown::Active = true;
			DropDown::SetBlockedSiblings(true);
			DropDown::LastClick = (clock() * 0.00001f) + 0.002f;
			DropDown::CalculateBuffer();
			DropDown::ConvertSelectedName();
		}
	}
	if (!IsMouseInRectangle(DropDown::Pos + ParentPos, DropDown::Size) && IsKeyClicked(VK_LBUTTON) && DropDown::Active )
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
void DropDown::Draw()
{
	if (!DropDown::Parent)
		DropDown::SetVisible(false);
	if (!DropDown::IsVisible())
		return;

	FilledRectangle(DropDown::ParentPos.x + DropDown::Pos.x, DropDown::ParentPos.y +DropDown::Pos.y, DropDown::Size.x, DropDown::Size.y, Colour(80, 80, 80, 255));
	float trianglex1 = DropDown::ParentPos.x + DropDown::Pos.x + DropDown::Size.x - 12;
	float triangley1 = DropDown::ParentPos.y + DropDown::Pos.y +3;
	float trianglex2 = DropDown::ParentPos.x + DropDown::Pos.x + DropDown::Size.x - 3;
	float triangley2 = DropDown::Pos.y + DropDown::ParentPos.y + 3;
	float trianglex3 = DropDown::ParentPos.x + DropDown::Pos.x + DropDown::Size.x - 7;
	float triangley3 = DropDown::ParentPos.y + DropDown::Pos.y + DropDown::Size.y - 3;
	if(!DropDown::Active)
	FilledTriangle(trianglex1, triangley1, trianglex2, triangley2, trianglex3, triangley3, Colour(255, 0, 0, 255));
	DrawText(DropDown::ParentPos.x + DropDown::Pos.x + 5, ParentPos.y + DropDown::Pos.y + (DropDown::Size.y /8), DropDown::SelectedName, "Verdana", 11, Colour(240, 240, 240, 255), None);
}