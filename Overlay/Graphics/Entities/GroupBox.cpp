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
	SetVisible(true);
}
void GroupBox::Update()
{
	if (!GroupBox::Parent)	
		GroupBox::SetVisible(false);

	if (!GroupBox::IsVisible())
		return;
	GroupBox::TextStartPos = GroupBox::Parent->GetParent()->GetPos().x + GroupBox::Pos.x + GroupBox::TextStartOffset;
	GroupBox::ParentPos = { GroupBox::Parent->GetParent()->GetPos().x + GroupBox::Pos.x + 5, GroupBox::Parent->GetParent()->GetPos().y + GroupBox::Pos.y + 10};
	GroupBox::ParentSize = { GroupBox::Size };
	
	for (child& it : GroupBox::GetContainer())
	{
		// if it exceeds the position/size of this then dont draw it.
		bool inbox = (
			GroupBox::ParentPos.x + it->Pos.x >  GroupBox::Pos.x &&
			GroupBox::ParentPos.y + it->Pos.y >  GroupBox::Pos.y &&
			GroupBox::ParentPos.x + it->Pos.x + it->Size.x < GroupBox::ParentPos.x + GroupBox::Pos.x + GroupBox::Size.x &&
			GroupBox::ParentPos.y + it->Pos.y + it->Size.y < GroupBox::ParentPos.y+ GroupBox::Pos.y + GroupBox::Size.y
			);
		it->SetVisible(inbox);

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

