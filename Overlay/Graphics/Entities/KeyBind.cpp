#include "pch.h"
#include "KeyBind.h"
#include "Drawing.h"
#include "Input.h"
KeyBind::KeyBind(float x, float y, std::wstring text, int* key)
{
	KeyBind::Pos = {x,y};
	KeyBind::Name = text;
	KeyBind::Key = key;
}
void KeyBind::Update()
{
	if (!KeyBind::Parent)
		KeyBind::SetVisible(false);
	if (!KeyBind::IsVisible())
		return;


	KeyBind::ParentPos = KeyBind::Parent->GetParent()->GetPos();
	if (!KeyBind::Blocked)
	{
		if (IsMouseInRectangle(KeyBind::Pos + ParentPos, KeyBind::Size) && IsKeyClicked(VK_LBUTTON) && KeyBind::LastClick < (clock() * 0.00001f))
		{
			KeyBind::CollectInput();
			KeyBind::LastClick = (clock() * 0.00001f) + 0.002f;
		}
	}
}
void KeyBind::CollectInput()
{
	while (true)
	{
		if (KeyBind::LastClick < (clock() * 0.00001f))
		{
			for (int i = 0; i <= 255; i++)
			{
				if (IsKeyDown(i))
					*KeyBind::Key = i;
			}
		}
	}
}
void KeyBind::Draw()
{
	if (!KeyBind::Parent)
		KeyBind::SetVisible(false);
	if (!KeyBind::IsVisible())
		return;
	OutlineRectangle(ParentPos.x + Pos.x-1, ParentPos.y + Pos.y-1, Size.x + 1, Size.y + 1, 1, Colour(130, 130, 130, 255));
	FilledRectangle(ParentPos.x + KeyBind::Pos.x, ParentPos.y + KeyBind::Pos.y, KeyBind::Size.x, KeyBind::Size.y, Colour(80, 80, 80, 255));
	DrawText(ParentPos.x + KeyBind::Pos.x + (KeyBind::Size.x / 2), ParentPos.y + KeyBind::Pos.y + (KeyBind::Size.y / 2), KeyBind::Name, "Verdana", 12, Colour(240, 240, 240, 255), CentreCentre);

}