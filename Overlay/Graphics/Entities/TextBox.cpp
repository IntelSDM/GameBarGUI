#include "pch.h"
#include "TextBox.h"
#include "Input.h"
#include "Drawing.h"
#include "Font.h"
/*
bool for input which is set to true when clicked.
take each key clicked and then translate it into the char
display char, if char exceeds the width of the textbox, remove characters until it doesn't

needs to pass through a string ptr for what it is editting
*/

TextBox::TextBox(float x, float y, std::wstring text, std::wstring* data = nullptr)
{
	TextBox::Pos = { x,y };
	TextBox::Size = { 277,25 };
	TextBox::Name = text;
	TextBox::Blocked = false;
	TextBox::MainString = data;
	TextBox::VisiblePointerEnd = MainString->length();
	TextBox::SetStartIndex(); // this sets start value
	TextBox::VisibleString = MainString->substr(TextBox::VisiblePointerStart,TextBox::VisiblePointerEnd);
	TextBox::SelectedPoint = VisiblePointerEnd;
	TextBox::SelectedPosition = GetTextWidth(TextBox::VisibleString.substr(TextBox::VisiblePointerStart, TextBox::SelectedPoint), 11, "Verdana");
}
void TextBox::SetStartIndex()
{
	// Sets the value to be the right most character at the end.
	TextBox::VisiblePointerStart = 0;
	TextBox::TextWidth = GetTextWidth(MainString->substr(TextBox::VisiblePointerStart, TextBox::VisiblePointerEnd), 11, "Verdana");
	while (TextBox::TextWidth > TextBox::Size.x - 6)
	{
		TextBox::VisiblePointerStart++; // update position
		TextBox::TextWidth = GetTextWidth(MainString->substr(TextBox::VisiblePointerStart, TextBox::VisiblePointerEnd), 11, "Verdana"); // update width so we can exit

	}

}


void TextBox::Update()
{
	if (!TextBox::Parent)
		TextBox::SetVisible(false);
	if (!TextBox::IsVisible())
		return;

	TextBox::TextWidth = GetTextWidth(VisibleString, 11, "Verdana");
	TextBox::TextHeight = GetTextHeight(VisibleString, 11, "Verdana");
	TextBox::ParentPos = TextBox::Parent->GetParent()->GetPos();
	TextBox::VisibleString = MainString->substr(TextBox::VisiblePointerStart, TextBox::VisiblePointerEnd);
	if (IsMouseInRectangle(TextBox::Pos + TextBox::ParentPos, TextBox::Size) && IsKeyClicked(VK_LBUTTON))
	{
		TextBox::Blocked = false;
	}
	else if (IsKeyClicked(VK_LBUTTON) && !IsMouseInRectangle(TextBox::Pos + TextBox::ParentPos, TextBox::Size) && !TextBox::Blocked)
	{
		TextBox::Blocked = true; // prevent 2 being active at the same time unless they are somehow fucking merged
	}
	if (IsKeyClicked(VK_RIGHT))
	{
		if (TextBox::SelectedPoint != TextBox::VisiblePointerEnd)
		{
		
			TextBox::SelectedPoint++;
		}
		TextBox::SelectedPosition = GetTextWidth(TextBox::VisibleString.substr(TextBox::VisiblePointerStart, TextBox::SelectedPoint), 11, "Verdana");
		
	}
	if (IsKeyClicked(VK_LEFT))
	{

		if (TextBox::SelectedPoint != TextBox::VisiblePointerStart) 
		{
			TextBox::SelectedPoint--;
		}
		TextBox::SelectedPosition = GetTextWidth(TextBox::VisibleString.substr(TextBox::VisiblePointerStart, TextBox::SelectedPoint), 11, "Verdana");
	}
	if (!TextBox::Blocked) // take input
	{
		WPARAM character = Char;
		if (character == VK_BACK && (*TextBox::MainString).length() != 0 && TextBox::VisiblePointerEnd !=0) // backspace, wndproc doesn't seem to like us using iskeyclicked for backspace right now
		{
			(*TextBox::MainString).erase(std::prev((*TextBox::MainString).end()));
			TextBox::VisiblePointerEnd--;
			/*
			if the pointer end != start??
			*/
			if (TextBox::VisiblePointerStart != 0 && GetTextWidth(MainString->substr(--TextBox::VisiblePointerStart, TextBox::VisiblePointerEnd), 11, "Verdana") < TextBox::Size.x - 6)
			{
				TextBox::VisiblePointerStart--;
				
			}
			TextBox::SelectedPosition = GetTextWidth(TextBox::VisibleString.substr(TextBox::VisiblePointerStart, TextBox::SelectedPoint), 11, "Verdana");
		}
		if (character == VK_RETURN)
		{
			TextBox::Blocked = true;
		}
		if (Char < 255 && Char != NULL && Char != VK_BACK && Char != VK_RETURN)
		{
			(*TextBox::MainString) += Char;
			TextBox::VisiblePointerEnd++;
			TextBox::TextWidth = GetTextWidth(MainString->substr(TextBox::VisiblePointerStart, TextBox::VisiblePointerEnd), 11, "Verdana");
		
			while (TextBox::TextWidth > TextBox::Size.x - 6)
			{
				TextBox::VisiblePointerStart++; // update position
				TextBox::TextWidth = GetTextWidth(MainString->substr(TextBox::VisiblePointerStart, TextBox::VisiblePointerEnd), 11, "Verdana"); // update width so we can exit

			}
			TextBox::SelectedPosition = GetTextWidth(TextBox::VisibleString.substr(TextBox::VisiblePointerStart, TextBox::SelectedPoint), 11, "Verdana");
		}
		Char = NULL;


		// make a system so if it is clicked and held that it will keep inputting the char
		// control + A should select the entire field
	}


}

void TextBox::Draw()
{
	if (!TextBox::Parent)
		TextBox::SetVisible(false);
	if (!TextBox::IsVisible())
		return;
	

	FilledRoundedRectangle(TextBox::Pos.x + TextBox::ParentPos.x - 1, TextBox::Pos.y + +TextBox::ParentPos.y - 1, TextBox::Size.x + 2, TextBox::Size.y + 2, 4, 4, Colour(200, 200, 200, 255));
	FilledRoundedRectangle(TextBox::Pos.x + TextBox::ParentPos.x, TextBox::Pos.y + +TextBox::ParentPos.y, TextBox::Size.x, TextBox::Size.y, 4, 4, Colour(80, 80, 80, 255));
	DrawText(TextBox::ParentPos.x + TextBox::Pos.x + (TextBox::Size.x / 2), TextBox::ParentPos.y + TextBox::Pos.y - ((TextBox::Size.y / 2) - 1), TextBox::Name, "Verdana", 12, Colour(255, 255, 255, 255), CentreCentre); // Title
	DrawText(TextBox::ParentPos.x + TextBox::Pos.x + 3, (TextBox::ParentPos.y + TextBox::Pos.y) + (TextBox::Size.y / 4), TextBox::VisibleString, "Verdana", 11, Colour(255, 255, 255, 255), None); // Text

	std::chrono::duration<float> elapsed = std::chrono::high_resolution_clock::now() - TextBox::AnimationStart;
	float time = std::fmodf(elapsed.count(), TextBox::AnimationInterval) / TextBox::AnimationInterval;
	float easedtime = InOutSine(time);
	if (!TextBox::Blocked && std::fmod(elapsed.count(), TextBox::AnimationInterval) < TextBox::AnimationInterval / 2)
	{
		float alpha = 180.0f * (1.0f - easedtime * 2.0f);
		FilledLine(TextBox::Pos.x + TextBox::ParentPos.x + TextBox::SelectedPosition, TextBox::Pos.y + TextBox::ParentPos.y + TextBox::Size.y - 3, TextBox::Pos.x + TextBox::ParentPos.x + TextBox::SelectedPosition, TextBox::Pos.y + TextBox::ParentPos.y + 3, 1, Colour(255, 255, 255, static_cast<unsigned int>(alpha)));
	}
}