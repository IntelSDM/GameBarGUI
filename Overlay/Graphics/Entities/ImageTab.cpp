#include "pch.h"
#include "Input.h"
#include "Drawing.h"
#include "ImageTab.h"

ImageTab::ImageTab(float x, float y, std::wstring image)
{

}
void ImageTab::Update()
{
	if (!ImageTab::Parent)
		ImageTab::SetVisible(false);
	if (!ImageTab::IsVisible())
		return;


	ImageTab::ParentPos = ImageTab::Parent->GetParent()->GetPos();
}
void ImageTab::Draw()
{
	if (!ImageTab::Parent)
		ImageTab::SetVisible(false);
	if (!ImageTab::IsVisible())
		return;
}