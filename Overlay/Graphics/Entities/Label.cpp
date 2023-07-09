#include "pch.h"
#include "Drawing.h"
#include "label.h"

Label::Label(std::wstring text, float posx, float posy)
{
	Label::Pos = { posx,posy };
	Label::Name = text;
}
void Label::Update()
{
	Label::ParentPos = Label::Parent->GetParent()->GetPos();
}
void Label::Draw()
{
	DrawText( Label::ParentPos.x + Label::Pos.x, Label::ParentPos.y + Label::Pos.y, Label::Name, "Verdana", 12,  Colour(255, 255, 255, 255), None);
}