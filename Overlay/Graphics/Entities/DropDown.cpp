#include "pch.h"
#include "Input.h"
#include "Drawing.h"
#include "DropDown.h"

DropDown::DropDown(float x, float y, std::wstring text, int* items, std::list<std::wstring>names)
{
	DropDown::Pos = { x,y };
	DropDown::Name = text;
	DropDown::Items = items;
	DropDown::Names = names;
	DropDown::Size = { 80,20 };
}

void DropDown::Update()
{
	if (!DropDown::Parent)
		DropDown::SetVisible(false);
	if (!DropDown::IsVisible())
		return;
	DropDown::ParentPos = DropDown::Parent->GetParent()->GetPos();
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
	FilledTriangle(trianglex1, triangley1, trianglex2, triangley2, trianglex3, triangley3, Colour(255, 0, 0, 255));
	
}