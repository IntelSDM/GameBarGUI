#include "Pch.h"
#include "TabListBox.h"
#include "GUI.h"
#include "Input.h"
#include "Drawing.h"
#include "Font.h"
#include "Graphics.h"

TabListBox::TabListBox(std::wstring name)
{
	TabListBox::Name = name;
	TabListBox::Index = TabCount;
	TabCount++;
}

void TabListBox::Update()
{
	TabListBox::ParentPos = TabListBox::Parent->GetParentPos();
	Container::Update();
}
void TabListBox::Draw()
{
	Container::Draw();
}