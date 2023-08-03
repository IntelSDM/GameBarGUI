#include "pch.h"
#include "GroupBox.h"
#include "Input.h"
#include "Gui.h"
#include "Drawing.h"
#include "Font.h"
GroupBox::GroupBox(std::wstring name, float x, float y, float width, float height)
{
	GroupBox::Size = { width,height };
	GroupBox::SetVisible(true);
	GroupBox::Pos = { x,y };
	GroupBox::Name = name;
	GroupBox::TextHeight = GetTextHeight(GroupBox::Name, 12, "Verdana");
	GroupBox::TextWidth = GetTextWidth(GroupBox::Name, 12, "Verdana");
	GroupBox::TextStartOffset = 5;
}
void GroupBox::Update()
{
	if (!GroupBox::Parent)
		GroupBox::SetVisible(false);

	if (!GroupBox::IsVisible())
		return;
	GroupBox::TextStartPos = GroupBox::Parent->GetParent()->GetPos().x + GroupBox::Pos.x + GroupBox::TextStartOffset;
	GroupBox::ParentPos = GroupBox::GetParent()->GetPos();
	GroupBox::ParentSize = GroupBox::GetParent()->GetSize();

	size_t ignorecount = 0;

	for (child& it : GroupBox::Parent->GetContainer())
	{
		if (it == shared_from_this())
			break;

		if (!it->IsVisible())
			++ignorecount;
	}
	

}
void GroupBox::Draw()
{
	if (!GroupBox::IsVisible())
		return;
	FilledLine(GroupBox::Parent->GetParent()->GetPos().x + GroupBox::Pos.x, GroupBox::Parent->GetParent()->GetPos().y + GroupBox::Pos.y, TextStartPos, GroupBox::Parent->GetParent()->GetPos().y + GroupBox::Pos.y, 2, Colour(0, 0, 0, 255)); // draw up to text
	FilledLine(TextStartPos + GroupBox::TextWidth, GroupBox::Parent->GetParent()->GetPos().y + GroupBox::Pos.y, GroupBox::Parent->GetParent()->GetPos().x + GroupBox::Pos.x + GroupBox::Size.x, GroupBox::Parent->GetParent()->GetPos().y + GroupBox::Pos.y, 2, Colour(0, 0, 0, 255)); // draw past
	OutlineRectangle(GroupBox::Parent->GetParent()->GetPos().x + GroupBox::Pos.x, GroupBox::Parent->GetParent()->GetPos().y + GroupBox::Pos.y +1, GroupBox::Size.x, GroupBox::Size.y-1, 2, Colour(0, 0, 0, 255));
	FilledRectangle(GroupBox::Parent->GetParent()->GetPos().x + GroupBox::Pos.x, GroupBox::Parent->GetParent()->GetPos().y + GroupBox::Pos.y, GroupBox::Size.x, GroupBox::Size.y, Colour(30, 30, 30, 255));
	
	DrawText(TextStartPos + 1, GroupBox::Parent->GetParent()->GetPos().y + GroupBox::Pos.y - (TextHeight / 2), GroupBox::Name, "Verdana", 12, Colour(255, 255, 255, 255), None);
	Container::Draw();
	Container::Update();
	
}

