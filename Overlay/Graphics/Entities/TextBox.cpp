#include "pch.h"
#include "TextBox.h"
#include "Input.h"
#include "Drawing.h"
#include "Font.h"
#include "Graphics.h"


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
	TextBox::SelectedPoint = VisiblePointerEnd - TextBox::VisiblePointerStart;
	TextBox::SelectedPosition = GetTextWidth(TextBox::MainString->substr(TextBox::VisiblePointerStart, TextBox::SelectedPoint), 11, "Verdana");
	TextBox::Blocked = true;
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
void TextBox::SetState()
{
	if (IsMouseInRectangle(TextBox::Pos + TextBox::ParentPos, TextBox::Size) && IsKeyClicked(VK_LBUTTON))
	{
		TextBox::Blocked = false;
	}
	else if (IsKeyClicked(VK_LBUTTON) && !IsMouseInRectangle(TextBox::Pos + TextBox::ParentPos, TextBox::Size) && !TextBox::Blocked)
	{
		TextBox::Selecting = false;
		TextBox::Held = false;
		TextBox::Blocked = true; // prevent 2 being active at the same time unless they are somehow fucking merged
	}
	WPARAM character = Char;
	if (character == VK_RETURN)
	{
		TextBox::Blocked = true;
	}
		if (!IsKeyDown(VK_LBUTTON))
			TextBox::Held = false;
}


bool TextBox::IsKeyAcceptable()
{
	WPARAM character = Char;
	if (character > 255)
		return false;
	if (character == NULL)
		return false;
	if (character == VK_BACK)
		return false;
	if (character == VK_RETURN)
		return false;
	if (IsKeyDown(VK_CONTROL))
		return false;
	if (character == VK_TAB)
		return false;
	return true;
}
void TextBox::ArrowKeyNavition()
{
	if (TextBox::Blocked)
		return;
	if (IsKeyClicked(VK_LEFT) && TextBox::LastClick < (clock() * 0.00001f))
	{
		TextBox::Selecting = false;
		TextBox::Held = false;
		// pointer isn't behind visible text
		if (SelectedPoint > TextBox::VisiblePointerStart)
		{
			TextBox::SelectedPoint--;
		}
		// pointer is going behind currently visible text
		else if (TextBox::VisiblePointerStart != 0 && SelectedPoint == TextBox::VisiblePointerStart)
		{
			TextBox::SelectedPoint--;
			TextBox::VisiblePointerStart--;
			TextBox::TextWidth = GetTextWidth(MainString->substr(TextBox::VisiblePointerStart, TextBox::VisiblePointerEnd), 11, "Verdana");
			// if the value exceeds the textbox bounds decrement the ending
			while (TextBox::TextWidth > TextBox::Size.x - 6 && TextBox::VisiblePointerStart != 0)
			{
				TextBox::VisiblePointerEnd--;
				TextBox::TextWidth = GetTextWidth(MainString->substr(TextBox::VisiblePointerStart, TextBox::VisiblePointerEnd), 11, "Verdana"); // update width so we can exit
			}
			while (TextBox::TextWidth < TextBox::Size.x - 6 && TextBox::MainString->length() > TextBox::VisiblePointerEnd && TextBox::VisiblePointerStart == 0)
			{
				TextBox::VisiblePointerEnd++; // update position
				TextBox::SelectedPoint++;
				TextBox::TextWidth = GetTextWidth(MainString->substr(TextBox::VisiblePointerStart, TextBox::VisiblePointerEnd), 11, "Verdana"); // update width so we can exit
			}
		}
		TextBox::LastClick = (clock() * 0.00001f) + 0.002f;
	}
	if (IsKeyClicked(VK_RIGHT) && TextBox::LastClick < (clock() * 0.00001f))
	{
		TextBox::Selecting = false;
		TextBox::Held = false;
		if (TextBox::SelectedPoint < TextBox::VisiblePointerEnd)
			TextBox::SelectedPoint++;
		else if (TextBox::VisiblePointerEnd != TextBox::MainString->length() && TextBox::SelectedPoint == TextBox::VisiblePointerEnd)
		{

			TextBox::SelectedPoint++;
			TextBox::VisiblePointerEnd++;
			TextBox::TextWidth = GetTextWidth(MainString->substr(TextBox::VisiblePointerStart, TextBox::VisiblePointerEnd), 11, "Verdana");
			// decrement start
			while (TextBox::TextWidth > TextBox::Size.x - 6)
			{
				TextBox::VisiblePointerStart++; // update position
				TextBox::TextWidth = GetTextWidth(MainString->substr(TextBox::VisiblePointerStart, TextBox::VisiblePointerEnd), 11, "Verdana"); // update width so we can exit
			}
		}
		TextBox::LastClick = (clock() * 0.00001f) + 0.002f;
	}
}
void TextBox::InputText()
{
	if (TextBox::Blocked)
		return;
	if (TextBox::IsKeyAcceptable())
	{
		//	(*TextBox::MainString) += Char;
		TextBox::VisiblePointerEnd++;
		TextBox::TextWidth = GetTextWidth(MainString->substr(TextBox::VisiblePointerStart, TextBox::VisiblePointerEnd), 11, "Verdana");
		MainString->insert(TextBox::SelectedPoint, 1, Char);
		TextBox::SelectedPoint++;
		while (TextBox::TextWidth > TextBox::Size.x - 6)
		{
			TextBox::VisiblePointerStart++; // update position
			TextBox::TextWidth = GetTextWidth(MainString->substr(TextBox::VisiblePointerStart, TextBox::VisiblePointerEnd), 11, "Verdana"); // update width so we can exit
		}
	}

}
void TextBox::DeleteText()
{
	if (TextBox::Blocked)
		return;
	WPARAM character = Char;
	if (character == VK_BACK && (*TextBox::MainString).length() != 0 && TextBox::VisiblePointerEnd != 0 && SelectedPoint != 0) // backspace
	{// no selection
		if (TextBox::SelectionStart == TextBox::SelectedPoint && TextBox::SelectionEnd == TextBox::SelectedPoint)
		{
			if (TextBox::SelectedPoint == TextBox::VisiblePointerEnd)
			{
				(*TextBox::MainString).erase(std::prev((*TextBox::MainString).end()));
				TextBox::VisiblePointerEnd--;
				TextBox::SelectedPoint--;
			}
			else
			{
				TextBox::MainString->erase(TextBox::SelectedPoint - 1, 1);
				TextBox::SelectedPoint--;
				TextBox::VisiblePointerEnd--;
			}

			if (TextBox::VisiblePointerStart != 0 && GetTextWidth(MainString->substr(TextBox::VisiblePointerStart, TextBox::VisiblePointerEnd), 11, "Verdana") < TextBox::Size.x - 6)
			{
				TextBox::VisiblePointerStart--;
			}
			// detect if there is any other text that we might need to add so our string doesn't randomly get cut off
			while (TextBox::TextWidth < TextBox::Size.x - 6 && TextBox::MainString->length() > TextBox::VisiblePointerEnd)
			{
				TextBox::VisiblePointerEnd++; // update position
				TextBox::SelectedPoint++;
				TextBox::TextWidth = GetTextWidth(MainString->substr(TextBox::VisiblePointerStart + 1, TextBox::VisiblePointerEnd), 11, "Verdana"); // update width so we can exit
			}
		}
		else
		{
			//selecting
			// only change selectedpoint if its going to be removed as well
			if (TextBox::SelectedPoint == TextBox::SelectionEnd)
			{
				TextBox::MainString->erase(TextBox::SelectionStart, TextBox::SelectionEnd - TextBox::SelectionStart);
				TextBox::VisiblePointerEnd -= TextBox::SelectionEnd - TextBox::SelectionStart;
				TextBox::SelectedPoint -= TextBox::SelectionEnd - TextBox::SelectionStart;
			}
			else
			{
				TextBox::MainString->erase(TextBox::SelectionStart, TextBox::SelectionEnd - TextBox::SelectionStart);
				TextBox::VisiblePointerEnd -= TextBox::SelectionEnd - TextBox::SelectionStart;
			}
			while (TextBox::TextWidth < TextBox::Size.x - 6 && TextBox::VisiblePointerStart > 0)
			{
				TextBox::VisiblePointerStart--; // Move the starting point up
				TextBox::TextWidth = GetTextWidth(MainString->substr(TextBox::VisiblePointerStart, TextBox::VisiblePointerEnd), 11, "Verdana");
			}

			// If the text still doesn't fill the TextBox, try to extend from the end
			while (TextBox::TextWidth < TextBox::Size.x - 6 && TextBox::VisiblePointerEnd < TextBox::MainString->length())
			{
				TextBox::VisiblePointerEnd++; // Extend the ending point
				TextBox::TextWidth = GetTextWidth(MainString->substr(TextBox::VisiblePointerStart, TextBox::VisiblePointerEnd), 11, "Verdana");
			}

			//reset selected points
			TextBox::SelectionStart = TextBox::SelectedPoint;
			TextBox::SelectionEnd = TextBox::SelectedPoint;
			TextBox::Held = false;
			TextBox::Selecting = false;
		}
	}
}
void TextBox::ClearText()
{
	Char = NULL;
}
void TextBox::SetSelection()
{
	if (TextBox::Blocked)
		return;
	if (TextBox::Held)
	{
		Selecting = true;
		Vector2 relativemousepos = { MousePos.x - (TextBox::Pos.x + TextBox::ParentPos.x),MousePos.y - (TextBox::Pos.y + TextBox::ParentPos.y) };
		float lastdistance = 99999; // the user shouldn't ever have a resolution/position over this value
		int instance = 0;
		for (int i = TextBox::VisiblePointerStart; i <= TextBox::VisiblePointerEnd; i++)
		{
			float width = GetTextWidth(MainString->substr(TextBox::VisiblePointerStart, i - TextBox::VisiblePointerStart), 11, "Verdana");
			float distance = std::abs(relativemousepos.x - width);
			if (distance > lastdistance)
			{
				instance = --i;
				break;
			}
			lastdistance = distance;
			instance = i;
		}
		if (instance == -1)
			instance = TextBox::TextBox::VisiblePointerEnd;
		if (TextBox::SelectedPoint > instance)
		{
			TextBox::SelectionEnd = TextBox::SelectedPoint;
			TextBox::SelectionStart = instance;
		}
		else
		{
			TextBox::SelectionEnd = instance;
			TextBox::SelectionStart = TextBox::SelectedPoint;
		}

	}

	if (IsKeyDown(VK_CONTROL) && IsKeyDown(0x41))//(A)
	{
		TextBox::SelectionStart = 0;
		TextBox::SelectionEnd = MainString->length();
	}
}
void TextBox::SetSelectionPoint()
{
	if (TextBox::Blocked)
		return;
	if (IsMouseInRectangle(TextBox::Pos + TextBox::ParentPos, TextBox::Size) && IsKeyClicked(VK_LBUTTON))
	{
		TextBox::Held = true;
		Vector2 relativemousepos = { MousePos.x - (TextBox::Pos.x + TextBox::ParentPos.x),MousePos.y - (TextBox::Pos.y + TextBox::ParentPos.y) };
		// get width
		// get last position
		// is last position closer or this one?
		// if last position is closer return last position.
		float lastdistance = 999999;
		int instance = 0;
		for (int i = TextBox::VisiblePointerStart; i <= TextBox::VisiblePointerEnd; i++)
		{
			float width = GetTextWidth(MainString->substr(TextBox::VisiblePointerStart, i - TextBox::VisiblePointerStart), 11, "Verdana");
			float distance = std::abs(relativemousepos.x - width);
			if (distance > lastdistance)
			{
				instance = --i;
				break;
			}
			lastdistance = distance;
			instance = i;
		}
		if (instance == -1)
			instance = TextBox::VisiblePointerEnd;
		TextBox::SelectedPoint = instance;

	}
}
void TextBox::SelectionDragging()
{
	if (TextBox::Blocked)
		return;
	if (TextBox::Held)
	{
		const int delay = 100; // Set the desired delay in milliseconds
		auto time = std::chrono::high_resolution_clock::now();
		// push text forwards
		while (TextBox::VisiblePointerEnd != MainString->length() && TextBox::SelectionEnd == TextBox::VisiblePointerEnd)
		{
			auto curtime = std::chrono::high_resolution_clock::now();
			auto elapsedtime = std::chrono::duration_cast<std::chrono::milliseconds>(curtime - time).count();
			if (elapsedtime >= delay)
			{
				TextBox::SelectedPoint++;
				TextBox::VisiblePointerEnd++;
				TextBox::VisiblePointerStart++;
			}

		}

		while (TextBox::VisiblePointerStart != 0 && TextBox::SelectionStart == TextBox::VisiblePointerStart)
		{

			auto curtime = std::chrono::high_resolution_clock::now();
			auto elapsedtime = std::chrono::duration_cast<std::chrono::milliseconds>(curtime - time).count();
			if (elapsedtime >= delay)
			{
				TextBox::SelectedPoint--;
				TextBox::VisiblePointerEnd--;
				TextBox::VisiblePointerStart--;
				time = std::chrono::high_resolution_clock::now();
			}

		}

	}
}
void TextBox::CopyText()
{
	if (TextBox::Blocked)
		return;
	if (TextBox::SelectedPoint == TextBox::SelectionStart && TextBox::SelectedPoint == TextBox::SelectionEnd)
		return;
	if (!(IsKeyDown(VK_CONTROL) && IsKeyDown(0x43)))
		return;
	  if (!OpenClipboard(nullptr))
        return;
	  size_t size = (SelectionEnd - SelectionStart) * sizeof(wchar_t) + sizeof(wchar_t);

	  HGLOBAL global = GlobalAlloc(GMEM_MOVEABLE, size);
	  if (!global) {
		  CloseClipboard();
		  return;
	  }

	  wchar_t* text = static_cast<wchar_t*>(GlobalLock(global));
	  if (!text) {
		  CloseClipboard();
		  GlobalFree(global);
		  return;
	  }

	  wcsncpy_s(text, size / sizeof(wchar_t), MainString->substr(SelectionStart, SelectionEnd - SelectionStart).c_str(), SelectionEnd - SelectionStart);

	  text[SelectionEnd - SelectionStart] = L'\0';
	  GlobalUnlock(global);
	  EmptyClipboard();
	  SetClipboardData(CF_UNICODETEXT, global);
	  CloseClipboard();
}
void TextBox::PasteText()
{
	if (TextBox::Blocked)
		return;
	if (!(IsKeyDown(VK_CONTROL) && IsKeyDown(0x56)))
		return;
	if (!OpenClipboard(nullptr))
		return;
	std::wstring clipboard = L"";
	HANDLE data = GetClipboardData(CF_UNICODETEXT);
	if (data != nullptr)
	{
		wchar_t* text = static_cast<wchar_t*>(GlobalLock(data));
		if (text != nullptr)
		{
			clipboard = text;
			GlobalUnlock(data);
		}
	}

	CloseClipboard();
	if (TextBox::LastClick < (clock() * 0.00001f))
	{
		if (TextBox::SelectedPoint == TextBox::SelectionStart && TextBox::SelectedPoint == TextBox::SelectionEnd)
		{
			TextBox::VisiblePointerEnd += clipboard.length();
			MainString->insert(TextBox::SelectedPoint, clipboard);
			TextBox::SelectedPoint += clipboard.length();
			TextBox::TextWidth = GetTextWidth(MainString->substr(TextBox::VisiblePointerStart, TextBox::VisiblePointerEnd), 11, "Verdana");
			while (TextBox::TextWidth > TextBox::Size.x - 6)
			{
				TextBox::VisiblePointerStart++; // update position
				TextBox::TextWidth = GetTextWidth(MainString->substr(TextBox::VisiblePointerStart, TextBox::VisiblePointerEnd), 11, "Verdana"); // update width so we can exit
			}

		}
		else
		{
			if (TextBox::SelectedPoint == TextBox::SelectionEnd)
			{
				TextBox::MainString->erase(TextBox::SelectionStart, TextBox::SelectionEnd - TextBox::SelectionStart);
				TextBox::VisiblePointerEnd -= TextBox::SelectionEnd - TextBox::SelectionStart;
				TextBox::SelectedPoint -= TextBox::SelectionEnd - TextBox::SelectionStart;
			}
			else
			{
				TextBox::MainString->erase(TextBox::SelectionStart, TextBox::SelectionEnd - TextBox::SelectionStart);
				TextBox::VisiblePointerEnd -= TextBox::SelectionEnd - TextBox::SelectionStart;
			}
			TextBox::VisiblePointerEnd += clipboard.length();
			MainString->insert(TextBox::SelectedPoint, clipboard);
			TextBox::SelectedPoint += clipboard.length();
			TextBox::TextWidth = GetTextWidth(MainString->substr(TextBox::VisiblePointerStart, TextBox::VisiblePointerEnd), 11, "Verdana");
			while (TextBox::TextWidth < TextBox::Size.x - 6 && TextBox::VisiblePointerStart > 0)
			{
				TextBox::VisiblePointerStart--; // Move the starting point up
				TextBox::TextWidth = GetTextWidth(MainString->substr(TextBox::VisiblePointerStart, TextBox::VisiblePointerEnd), 11, "Verdana");
			}

			// If the text still doesn't fill the TextBox, try to extend from the end
			while (TextBox::TextWidth < TextBox::Size.x - 6 && TextBox::VisiblePointerEnd < TextBox::MainString->length())
			{
				TextBox::VisiblePointerEnd++; // Extend the ending point
				TextBox::TextWidth = GetTextWidth(MainString->substr(TextBox::VisiblePointerStart, TextBox::VisiblePointerEnd), 11, "Verdana");
			}

			//reset selected points
			TextBox::SelectionStart = TextBox::SelectedPoint;
			TextBox::SelectionEnd = TextBox::SelectedPoint;

		}
		TextBox::LastClick = (clock() * 0.00001f) + 0.002f;
	}
}
void TextBox::Update()
{
	if (!TextBox::Parent)
		TextBox::SetVisible(false);
	if (!TextBox::IsVisible())
		return;

	TextBox::TextWidth = GetTextWidth(VisibleString, 11, "Verdana");
	TextBox::ParentPos = TextBox::Parent->GetParent()->GetPos();
	TextBox::VisibleString = MainString->substr(TextBox::VisiblePointerStart, TextBox::VisiblePointerEnd);
	TextBox::SetState();
	TextBox::ArrowKeyNavition();
	TextBox::InputText();
	TextBox::DeleteText();
	TextBox::ClearText();
	TextBox::SetSelectionPoint();
	TextBox::SetSelection();
	TextBox::SelectionDragging();
	TextBox::CopyText();
	TextBox::PasteText();
	if (!TextBox::Blocked) // take input
	{
	
		if (!TextBox::Held && !TextBox::Selecting)
		{
			TextBox::SelectionStart = TextBox::SelectedPoint;
			TextBox::SelectionEnd = TextBox::SelectedPoint;
		}

	
		// Update the selected point if it is out of bounds
		if (TextBox::SelectedPoint > TextBox::VisiblePointerEnd)
		{
			TextBox::SelectedPoint = TextBox::VisiblePointerEnd;
		}
		TextBox::SelectedPosition = GetTextWidth(MainString->substr(TextBox::VisiblePointerStart, TextBox::SelectedPoint - TextBox::VisiblePointerStart), 11, "Verdana");
		TextBox::SelectingStartPosition = GetTextWidth(MainString->substr(TextBox::VisiblePointerStart, TextBox::SelectionStart - TextBox::VisiblePointerStart), 11, "Verdana");
		TextBox::SelectingEndPosition = GetTextWidth(MainString->substr(TextBox::VisiblePointerStart, TextBox::SelectionEnd - TextBox::VisiblePointerStart), 11, "Verdana");
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
	DrawText(TextBox::ParentPos.x + TextBox::Pos.x + (TextBox::Size.x / 2), TextBox::ParentPos.y + TextBox::Pos.y - ((TextBox::Size.y / 2) - 1), TextBox::Name + L":", "Verdana", 12, Colour(255, 255, 255, 255), CentreCentre); // Title
	DrawText(TextBox::ParentPos.x + TextBox::Pos.x + 3, (TextBox::ParentPos.y + TextBox::Pos.y) + (TextBox::Size.y / 4), TextBox::VisibleString, "Verdana", 11, Colour(255, 255, 255, 255), None); // Text

	std::chrono::duration<float> elapsed = std::chrono::high_resolution_clock::now() - TextBox::AnimationStart;
	float time = std::fmodf(elapsed.count(), TextBox::AnimationInterval) / TextBox::AnimationInterval;
	float easedtime = InOutSine(time);
	if (!TextBox::Blocked && std::fmod(elapsed.count(), TextBox::AnimationInterval) < TextBox::AnimationInterval / 2)
	{
		float alpha = 255.0f * (1.0f - easedtime * 2.0f);
		FilledLine(TextBox::Pos.x + TextBox::ParentPos.x + TextBox::SelectedPosition, TextBox::Pos.y + TextBox::ParentPos.y + TextBox::Size.y - 3, TextBox::Pos.x + TextBox::ParentPos.x + TextBox::SelectedPosition, TextBox::Pos.y + TextBox::ParentPos.y + 3, 1, Colour(255, 255, 255, static_cast<unsigned int>(alpha)));
	}
	if (TextBox::SelectingStartPosition >=0 || TextBox::SelectingEndPosition>=0 && TextBox::Selecting)
	{
		float selectionwidth = std::abs(TextBox::SelectingEndPosition - TextBox::SelectingStartPosition); // bandage fix for negative value
		FilledRectangle(TextBox::Pos.x + TextBox::ParentPos.x + SelectingStartPosition, TextBox::Pos.y +TextBox::ParentPos.y, selectionwidth, TextBox::Size.y, Colour(0, 150, 255, 100));
	}
}