#include "pch.h"
#include "KeyBind.h"
#include "Drawing.h"
#include "Input.h"
KeyBind::KeyBind(float x, float y, std::wstring text, int* key)
{
	KeyBind::Pos = {x,y};
	KeyBind::Name = text;
	KeyBind::Key = key;
	KeyBind::Size = { 80,20 };
	KeyBind::ConvertKeyToName();
}
void KeyBind::ConvertKeyToName()
{
	if (KeyBind::Active)
	{
		KeyBind::KeyName = L"[Click A Key]";
		return;
	}
	if (*KeyBind::Key == NULL && !KeyBind::Active)
	{
		KeyBind::KeyName = L"[Unbound]";
		return;
	}

	int keycode = *KeyBind::Key;
	int scancode = MapVirtualKey(keycode, MAPVK_VK_TO_VSC);
	WCHAR keyname[256] = { 0 }; 
	if (SymbolKeys[keycode] != L"")
	{
		KeyBind::KeyName = SymbolKeys[keycode];
		return;
	}
	if (GetKeyNameTextW((scancode << 16), keyname, sizeof(keyname) / sizeof(keyname[0])) == 0 && KeyBind::Key != NULL)
	{
		KeyBind::KeyName = L"[Unknown Key]";
	}
	else
	{
		KeyBind::KeyName = keyname;
	}

}
void KeyBind::Update()
{
	if (!KeyBind::Parent)
		KeyBind::SetVisible(false);
	if (!KeyBind::IsVisible())
		return;


	KeyBind::ParentPos = KeyBind::Parent->GetParentPos();
	if (!KeyBind::Blocked)
	{
		if (IsMouseInRectangle(KeyBind::Pos + ParentPos, KeyBind::Size) && IsKeyClicked(VK_LBUTTON) && KeyBind::LastClick < (clock() * 0.00001f) && !KeyBind::Blocked && !KeyBind::Active)
		{
		//	KeyBind::SetBlockedSiblings(true);
			KeyBind::Blocked = true;
			KeyBind::LastClick = (clock() * 0.00001f) + 0.002f;
			KeyBind::Active = true;
			KeyBind::Blocked = false;
		}
	}
	if (Active)
	{
		*KeyBind::Key = 0;
		KeyBind::KeyName = L"[Click A Key]";
		KeyBind::CollectInput();
		KeyBind::ConvertKeyToName();
	}
	
}
void KeyBind::CollectInput()
{
	for (int i=0; i <= 255; i++)
	{
		if (IsKeyClicked(VK_RETURN) || IsKeyClicked(VK_ESCAPE))
		{
			KeyBind::Active = false;
			return;
		}
		if (IsKeyClicked(i) && KeyBind::LastClick < (clock() * 0.00001f))
		{
			KeyBind::Key = new int(i);
			KeyBind::Active = false;
			KeyBind::LastClick = (clock() * 0.00001f) + 0.002f;
			return;

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
	DrawText(ParentPos.x + KeyBind::Pos.x, ParentPos.y + KeyBind::Pos.y -KeyBind::Size.y, KeyBind::Name, "Verdana", 12, Colour(240, 240, 240, 255), None);
	DrawText(ParentPos.x + KeyBind::Pos.x + (KeyBind::Size.x / 2), ParentPos.y + KeyBind::Pos.y + (KeyBind::Size.y / 2),KeyName, "Verdana", 10, Colour(240, 240, 240, 255), CentreCentre);

}