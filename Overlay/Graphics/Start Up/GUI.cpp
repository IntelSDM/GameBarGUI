#include "pch.h"
#include "GUI.h"
#include "Entity.h"
#include "Form.h"
EntityVector MenuEntity;
int TabCount;
void CreateGUI()
{
	MenuEntity = std::make_shared< Container >();
	auto form = std::make_shared<Form >(300, 100, 600, 500, 2, 30, L"FORM", true);
	{	
	
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