#include "pch.h"
#include "Tab.h"
#include "Input.h"
#include "Gui.h"
#include "Drawing.h"

Tab::Tab(std::wstring name, float x, float y, float width, float height, int* selectedtab = nullptr)
{
	Tab::Size = { width,height };
	Tab::SetVisible(true);
	Tab::Index = TabCount; // this doesn't need to be changed for a different set of tabs or whatever, you dont need to import a value here you just need a nonce value so you never get a repeated one
	Tab::Pos = { x,y };
	Tab::Selected = selectedtab;
	Tab::Name = name;
	//	Tab::Size.x += 1;
	TabCount++;
}
void Tab::Update()
{
	if (!Tab::Parent)
		Tab::SetVisible(false);

	if (!Tab::IsVisible())
		return;
	Tab::ParentPos = Tab::GetParent()->GetPos();
	Tab::ParentSize = Tab::GetParent()->GetSize();
	// Bandaid fix
	size_t ignore_count = 0;

	for (child& it : Tab::Parent->Container())
	{
		if (it == shared_from_this())
			break;

		if (!it->IsVisible())
			++ignore_count;
	}
	bool selected = Index == *Selected;
	if (!selected && !Tab::Blocked)
	{
		if (IsMouseInRectangle(Tab::ParentPos.x + Tab::Pos.x, (Tab::ParentPos.y + Tab::ParentSize.y) - Tab::Pos.y, Tab::Size.x, Tab::Size.y) && IsKeyClicked(VK_LBUTTON) && !selected)
		{
			*Selected = Index;
			// ideally you just want to make a timer and use that but since this is just poc we do this
			Sleep(50); // allows us to smooth into tabs as we don't want inputs to go straight through tabs
		}
	}

}
void Tab::Draw()
{
	if (!Tab::IsVisible())
		return;

	Color textcolour = Colour(0, 0, 255, 255);
	bool selected = Index == *Selected;

	textcolour = Colour(255, 0, 0, 255);
	FilledRectangle(Tab::ParentPos.x + Tab::Pos.x, (Tab::ParentPos.y + Tab::ParentSize.y) - Tab::Pos.y, Tab::Size.x, Tab::Size.y, Colour(80, 80, 80, 255));
	DrawText(Tab::ParentPos.x + Tab::Pos.x + (Tab::Size.x / 2), ((Tab::ParentPos.y + Tab::ParentSize.y) - Tab::Pos.y) + (Tab::Size.y / 2), Tab::Name, "Verdana", 12,  Colour(255, 255, 255, 255), CentreCentre);

	if (selected)
	{
		Container::Draw();
		Container::Update();
	}
}