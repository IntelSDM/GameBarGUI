#include "pch.h"
#include "GUI.h"
#include "entity.h"
#include "Form.h"
#include "Tab.h"
#include "Toggle.h"
#include "Label.h"
#include "Button.h"
#include "TextBox.h"
#include "Slider.h"
#include "TabController.h"
#include "ColourPicker.h"
#include "KeyBind.h"
#include "DropDown.h"
#include "ComboBox.h"
#include "TabListBoxController.h"
Color ColourPickerClipBoard = Colors::Red;
EntityVector MenuEntity;
int SelectedTab = 1;
int SelectedSubTab = 0;
int TabCount=0;
bool ToggleTest;
bool ToggleTest1 = true;
std::wstring TextBoxText = L"txtboxdsgdsdshchgkhdsgsdgsdgWWWWAAAA";
int intvalue = 3;
float floatvalue = 8.5f;
Color Col = Colour(255, 255, 255, 255);
int Key = 0;
int Down = 1;
bool Combo1 = true;
bool Combo2 = false;
bool Combo3 = false;
bool Combo4 = true;
bool Combo5 = false;
void CreateGUI()
{
	MenuEntity = std::make_shared< Container >();
	// We use the makeshared function instead of declaring new variables because they are automatically disposed
	auto form = std::make_shared<Form >(100, 100.0f, 480, 300, 2, 30, L"FORM", true);
	{
		auto tabcontroller = std::make_shared<TabController>();
			form->Push(tabcontroller);
		//std::string name, float x, float y, float width, float height, int* selectedtab = nullptr
		auto tab = std::make_shared<Tab>(L"Tab1", 5, 25, 50, 20, &SelectedTab);
		{			
			auto colourpicker = std::make_shared<ColourPicker>(200, 40, &Col);
			tab->Push(colourpicker);
			auto toggle = std::make_shared<Toggle>(10, 40, L"Toggle", &ToggleTest);
			tab->Push(toggle);
			auto toggle1 = std::make_shared<Toggle>(10, 60, L"Toggle", &ToggleTest1);
			tab->Push(toggle1);
			auto label = std::make_shared<Label>(L"Label", 10, 80);
			tab->Push(label);
			auto button = std::make_shared<Button>(10, 100, L"Button", []()
				{
					Beep(100, 100);
				});
			tab->Push(button);
			auto textbox = std::make_shared<TextBox>(10, 150, L"Textbox", &TextBoxText);
			tab->Push(textbox);
			auto floatslider = std::make_shared<Slider<float>>(10, 190, L"Slider Float", L"", 0.0f, 10.0f, &floatvalue);
			tab->Push(floatslider);
			auto intslider = std::make_shared<Slider<int>>(10, 220, L"Slider Int", L"%", 0, 100, &intvalue);
			tab->Push(intslider);
			auto keybind = std::make_shared<KeyBind>(150, 80, L"KeyBind", &Key);
			tab->Push(keybind);
			std::list<std::wstring> downvalues = {L"Value 12345", L"Value 2", L"Value 3", L"Value 4" , L"Value 5", L"Value 6", L"Value 7" , L"Value 8" , L"Value 9" , L"Value 9" };
			auto dropdown = std::make_shared<DropDown>(290, 80, L"DropDown", &Down,downvalues);
			tab->Push(dropdown);
			std::list<std::wstring> combovalues = { L"Value 12345", L"Value 2", L"Value 3", L"Value 4" , L"Value 5", L"Value 6", L"Value 7" , L"Value 8" };
			std::list<bool*> bools = { &Combo1 ,&Combo2 ,&Combo3 ,&Combo4 ,&Combo5,&Combo5 ,&Combo5 ,&Combo5 };
			auto combo = std::make_shared<ComboBox>(290, 110, L"DropDown", bools, combovalues);
			tab->Push(combo);
		
		}
		tabcontroller->Push(tab);
		auto tab1 = std::make_shared<Tab>(L"Tab2", 60, 25, 50, 20, &SelectedTab);
		{
		//	auto label = std::make_shared<Label>(L"Label", 10, 80);
		//	tab1->Push(label);
			auto tablist = std::make_shared<TabListBoxController>(10, 40, 160, 160, &SelectedSubTab);
			auto listtab1 = std::make_shared<TabListBox>(L"Tab1");
			{
				std::list<std::wstring> downvalues = { L"Value 12345", L"Value 2", L"Value 3", L"Value 4" , L"Value 5", L"Value 6", L"Value 7" , L"Value 8" , L"Value 9" , L"Value 9" };
				auto dropdown = std::make_shared<DropDown>(290, 80, L"DropDown", &Down, downvalues);
				listtab1->Push(dropdown);
				auto label = std::make_shared<Label>(L"Label", 290, 150);
				listtab1->Push(label);
			}
			auto listtab2 = std::make_shared<TabListBox>(L"Tab2");
			{
				auto label = std::make_shared<Label>(L"Label", 290, 150);
				listtab2->Push(label);
			}
			auto listtab3 = std::make_shared<TabListBox>(L"Tab3");
			auto listtab4 = std::make_shared<TabListBox>(L"Tab4fdhdfhdhfdfhdfhdfhdhfdfhdfhdfhdfhdfhdfdfhdfhdfh");
			auto listtab5 = std::make_shared<TabListBox>(L"Tab5");
			auto listtab6 = std::make_shared<TabListBox>(L"Tab6");
			auto listtab7 = std::make_shared<TabListBox>(L"Tab7");
			auto listtab8 = std::make_shared<TabListBox>(L"Tab8");
			auto listtab9 = std::make_shared<TabListBox>(L"Tab9");
			auto listtab10 = std::make_shared<TabListBox>(L"Tab10");
			tablist->PushBack(listtab1);
			tablist->PushBack(listtab2);
			tablist->PushBack(listtab3);
			tablist->PushBack(listtab4);
			tablist->PushBack(listtab5);
			tablist->PushBack(listtab6);
			tablist->PushBack(listtab7);
			tablist->PushBack(listtab8);
			tablist->PushBack(listtab9);
			tablist->PushBack(listtab10);
			tablist->PushBack(listtab7);
			tablist->PushBack(listtab8);
			tablist->PushBack(listtab9);
			tablist->PushBack(listtab10);
			tab1->Push(tablist);
		}
		tabcontroller->Push(tab1);
		auto tab2 = std::make_shared<Tab>(L"Tab3", 115, 25, 50, 20, &SelectedTab);
		tabcontroller->Push(tab2);
		auto tab3 = std::make_shared<Tab>(L"Tab4", 170, 25, 50, 20, &SelectedTab);
		tabcontroller->Push(tab3);
		
	}
	MenuEntity->Push(form);
	MenuEntity->Draw();
	MenuEntity->Update();
}
void SetFormPriority()
{
	// This sorts the host container (containerptr) which contains forms, as long as a form isn't parented to another form then this will allow it to draw over when clicked.
	// I swear to god if i need to make this work for forms inside forms for some odd reason in the future then i am going to throw a monitor out the window.
	std::sort(MenuEntity->GetContainer().begin(), MenuEntity->GetContainer().end(),
		[](child a, child b) {return b->GetLastClick() < a->GetLastClick(); }
	);
}
void RenderGUI()
{
	MenuEntity->Draw();
	MenuEntity->GetContainer()[0]->Update(); // only allow stretching,dragging and other update stuff if it is the main form, prevents dragging and sizing the wrong forms.
	SetFormPriority();
};