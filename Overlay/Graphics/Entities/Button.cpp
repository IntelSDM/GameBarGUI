#include "pch.h"
#include "Input.h"
#include "Drawing.h"
#include "Button.h"


Button::Button(float x, float y, std::wstring text, std::function<void()> click)
{
	Button::Pos = { x,y };
	Button::Size = { 70,20 };
	Button::Name = text;
	Button::Action = click;

}

void Button::Update()
{
	if (!Button::Parent)
		Button::SetVisible(false);
	if (!Button::IsVisible())
		return;


	Button::ParentPos = Button::Parent->GetParent()->GetPos();
	if (!Button::Blocked)
	{
		if (IsMouseInRectangle(Button::Pos + ParentPos, Button::Size) && IsKeyClicked(VK_LBUTTON) && Button::LastClickTime < (clock() * 0.00001f))
		{
			Button::Action();
			Button::LastClickTime = (clock() * 0.00001f) + 0.002f;
		}
	}
}

void Button::Draw()
{
	//Button::Parent->GetParent()->GetParent()->GetPos();
	if (!Button::Parent)
		Button::SetVisible(false);
	if (!Button::IsVisible())
		return;
	OutlineRectangle(ParentPos.x + Pos.x, ParentPos.y + Pos.y, Size.x + 1, Size.y + 1, 1, Colour(130, 130, 130, 255));
	FilledRectangle(ParentPos.x + Button::Pos.x, ParentPos.y + Button::Pos.y, Button::Size.x, Button::Size.y, Colour(80, 80, 80, 255));
	DrawText( ParentPos.x + Button::Pos.x + (Button::Size.x / 2), ParentPos.y + Button::Pos.y + (Button::Size.y / 2), Button::Name, "Verdana", 12,  Colour(240, 240, 240, 255), CentreCentre);

}