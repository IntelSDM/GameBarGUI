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
	if (!Label::Parent)
		Label::SetVisible(false);
	if (!Label::IsVisible())
		return;
	Label::ParentPos = Label::Parent->GetParent()->GetPos();
}
void Label::Draw()
{
	if (!Label::Parent)
		Label::SetVisible(false);
	if (!Label::IsVisible())
		return;
	DrawText( Label::ParentPos.x + Label::Pos.x, Label::ParentPos.y + Label::Pos.y, Label::Name, "Verdana", 12,  Colour(255, 255, 255, 255), None);
}