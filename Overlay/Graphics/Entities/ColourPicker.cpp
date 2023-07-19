#include "pch.h"
#include "ColourPicker.h"
#include "Input.h"
#include "Drawing.h"

ColourPicker::ColourPicker(float x, float y, Color* colour)
{
	ColourPicker::MainColour = colour;
	ColourPicker::Size = {20,10};
	ColourPicker::Pos = { x,y };
	ColourPicker::Blocked = true;
}
void ColourPicker::Update()
{
	ColourPicker::ParentPos = ColourPicker::Parent->GetParent()->GetPos();
	if (IsMouseInRectangle(ColourPicker::ParentPos.x + ColourPicker::Pos.x, ColourPicker::ParentPos.y + ColourPicker::Pos.y, ColourPicker::Size.x, ColourPicker::Size.y) && IsKeyClicked(VK_LBUTTON) && ColourPicker::LastClick < (clock() * 0.00001f))
	{
		ClickedPos = MousePos;
		ColourPicker::Blocked = !ColourPicker::Blocked;
		ColourPicker::LastClick = (clock() * 0.00001f) + 0.002f;
	}
	if (!(IsMouseInRectangle(ColourPicker::ParentPos.x + ColourPicker::Pos.x, ColourPicker::ParentPos.y + ColourPicker::Pos.y, ColourPicker::Size.x, ColourPicker::Size.y) || IsMouseInRectangle(ClickedPos.x, ClickedPos.y, 150, 150)) && IsKeyClicked(VK_LBUTTON))
	{
		ColourPicker::Blocked = true;
	}
}
void ColourPicker::Draw()
{
	FilledRectangle(ColourPicker::ParentPos.x + ColourPicker::Pos.x, ColourPicker::ParentPos.y + ColourPicker::Pos.y, ColourPicker::Size.x, ColourPicker::Size.y, *ColourPicker::MainColour);
	OutlineRectangle(ColourPicker::ParentPos.x + ColourPicker::Pos.x, ColourPicker::ParentPos.y + ColourPicker::Pos.y, ColourPicker::Size.x, ColourPicker::Size.y, 1, Colour(85, 85, 85, 255));
	
	if (!ColourPicker::Blocked)
	{
		FilledRectangle(ClickedPos.x - 5, ClickedPos.y - 5, 185, 175, Colour(85, 85, 85, 255));
		OutlineRectangle(ClickedPos.x - 5, ClickedPos.y - 5, 185, 175,1, Colour(180, 180, 180, 255));
		DrawColourPicker(ClickedPos.x, ClickedPos.y, 150, 150, *ColourPicker::MainColour);
		DrawColourPickerSlider(ClickedPos.x, ClickedPos.y + 155, 150, 10);
		OutlineRectangle(ClickedPos.x +155, ClickedPos.y, 20, 165,1, Colour(180, 180, 180, 255));
		DrawColourPickerAlphaSlider(ClickedPos.x + 155, ClickedPos.y, 20, 165, *ColourPicker::MainColour);
	}
}