#include "pch.h"
#include "ColourPicker.h"
#include "Input.h"
#include "Drawing.h"

ColourPicker::ColourPicker(float x, float y, std::wstring text, Color* colour)
{
	ColourPicker::MainColour = colour;
	ColourPicker::Size = {20,10};
	ColourPicker::Pos = { x,y };
}
void ColourPicker::Update()
{
	ColourPicker::ParentPos = ColourPicker::Parent->GetParent()->GetPos();
}
void ColourPicker::Draw()
{
	FilledRectangle(ColourPicker::ParentPos.x + ColourPicker::Pos.x, ColourPicker::ParentPos.y + ColourPicker::Pos.y, ColourPicker::Size.x, ColourPicker::Size.y, *ColourPicker::MainColour);
	OutlineRectangle(ColourPicker::ParentPos.x + ColourPicker::Pos.x, ColourPicker::ParentPos.y + ColourPicker::Pos.y, ColourPicker::Size.x, ColourPicker::Size.y, 1, Colour(85, 85, 85, 255));
}