#include "Pch.h"
#include "ListBoxTab.h"
#include "GUI.h"
#include "Input.h"
#include "Drawing.h"
#include "Font.h"
#include "Graphics.h"

ListBoxTab::ListBoxTab(std::wstring name, int* selectedtab)
{
	ListBoxTab::Name = name;
	ListBoxTab::Selected = selectedtab;
	ListBoxTab::Index = TabCount;
	TabCount++;
}

void ListBoxTab::Update()
{
}
void ListBoxTab::Draw()
{
}