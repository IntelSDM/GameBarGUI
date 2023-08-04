#include "pch.h"
#include "TabController.h"
TabController::TabController()
{
	TabController::SetVisible(true);
}

void TabController::Update()
{
	if (!TabController::Parent)
		TabController::SetVisible(false);

	// The tab control is NOT valid, or disabled.
	if (!TabController::IsVisible())
		return;
	TabController::ParentPos = TabController::Parent->GetParentPos();
	TabController::Pos.x = TabController::Parent->GetPos().x;
	TabController::Pos.y = TabController::Parent->GetPos().y;
	TabController::Size = TabController::Parent->GetSize();
	TabController::Container::Update();
}

void TabController::Draw()
{
	if (!TabController::IsVisible())
		return;
	int size = TabController::Size.x / 12;
	//  FilledRectangle(TabController::Pos.x, TabController::Pos.y + TabController::Size.y - size, TabController::Size.x, size, Colour(25, 25, 25, 255));

	TabController::Container::Draw();
}