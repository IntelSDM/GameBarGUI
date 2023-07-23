#include "pch.h"
#include "KeyBind.h"

KeyBind::KeyBind(float x, float y, std::wstring text, int key)
{

}
void KeyBind::Update()
{
	if (!KeyBind::Parent)
		KeyBind::SetVisible(false);
	if (!KeyBind::IsVisible())
		return;


	KeyBind::ParentPos = KeyBind::Parent->GetParent()->GetPos();
	
}

void KeyBind::Draw()
{
	if (!KeyBind::Parent)
		KeyBind::SetVisible(false);
	if (!KeyBind::IsVisible())
		return;
	
}