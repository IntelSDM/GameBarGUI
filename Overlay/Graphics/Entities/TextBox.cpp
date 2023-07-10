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
	TextBox::VisibleString = *MainString;

}


void TextBox::Update()
{
	if (!TextBox::Parent)
		TextBox::SetVisible(false);
	if (!TextBox::IsVisible())
		return;

	TextBox::ParentPos = TextBox::Parent->GetParent()->GetPos();
	if (IsMouseInRectangle(TextBox::Pos + TextBox::ParentPos, TextBox::Size) && IsKeyClicked(VK_LBUTTON))
	{
	//	Char = NULL;
		TextBox::Blocked = false;
	}
	else if (IsKeyClicked(VK_LBUTTON) && !IsMouseInRectangle(TextBox::Pos + TextBox::ParentPos, TextBox::Size) && !TextBox::Blocked)
	{
		TextBox::Blocked = true; // prevent 2 being active at the same time unless they are somehow fucking merged
	}
	if (!TextBox::Blocked) // take input
	{
		WPARAM character = Char;
		if (character == VK_BACK && (*TextBox::MainString).length() != 0) // backspace, wndproc doesn't seem to like us using iskeyclicked for backspace right now
		{
			(*TextBox::MainString).erase(std::prev((*TextBox::MainString).end()));
			TextBox::VisibleString.erase(std::prev(TextBox::VisibleString.end()));
		}
		if (character == VK_RETURN)
		{
			TextBox::Blocked = true;
		}
		if (Char < 255 && Char != NULL && Char != VK_BACK && Char != VK_RETURN)
		{
			(*TextBox::MainString) += Char;
			TextBox::VisibleString += Char;
		}
		Char = NULL;

		
		// make a system so if it is clicked and held that it will keep inputting the char
		// control + A should select the entire field
	}
	// probably shouldn't be here for optimization reasons but this is a small project, you don't want to keep making templates each frame for each textbox. i will fix this in the actual gui. 
	GetTextSize(VisibleString, 11, &TextWidth, &TextHeight, "Verdana");
	if (TextBox::TextWidth > TextBox::Size.x - 3) // textsize isn't too accurate
	{
		// trim visible text
		TextBox::VisibleString.erase(TextBox::VisibleString.begin());
	}
	if (TextBox::VisibleString.length() == 0 && (*TextBox::MainString).length() != 0) // this is a temporary fix so when you delete all of the visible string it lets you go back through the main string
		TextBox::VisibleString = *TextBox::MainString;
}

void TextBox::Draw()
{
	if (!TextBox::Parent)
		TextBox::SetVisible(false);
	if (!TextBox::IsVisible())
		return;


	FilledRoundedRectangle(TextBox::Pos.x + TextBox::ParentPos.x - 1, TextBox::Pos.y + +TextBox::ParentPos.y - 1, TextBox::Size.x + 2, TextBox::Size.y + 2, 4,4, Colour(200, 200, 200, 255));
	FilledRoundedRectangle(TextBox::Pos.x + TextBox::ParentPos.x, TextBox::Pos.y + +TextBox::ParentPos.y, TextBox::Size.x, TextBox::Size.y, 4,4, Colour(80, 80, 80, 255));
	DrawText( TextBox::ParentPos.x + TextBox::Pos.x + (TextBox::Size.x / 2), TextBox::ParentPos.y + TextBox::Pos.y - ((TextBox::Size.y / 2) - 1), TextBox::Name, "Verdana", 12,  Colour(255, 255, 255, 255), CentreCentre); // Title
	DrawTextClipped( TextBox::ParentPos.x + TextBox::Pos.x + 3, (TextBox::ParentPos.y + TextBox::Pos.y) + (TextBox::Size.y / 4), TextBox::Size.x, TextBox::Size.y, TextBox::VisibleString, "Verdana", 11,  Colour(255, 255, 255, 255), None); // Text

	if (!TextBox::Blocked)
	{
		FilledLine(TextBox::Pos.x + TextBox::ParentPos.x + TextBox::TextWidth + 3, TextBox::Pos.y + TextBox::ParentPos.y + TextBox::Size.y - 3, TextBox::Pos.x + TextBox::ParentPos.x + TextBox::TextWidth + 3, TextBox::Pos.y + TextBox::ParentPos.y + 3, 1, Colour(135, 135, 135, 180));
	}
}