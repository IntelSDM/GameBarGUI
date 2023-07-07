#include "pch.h"
#include "Graphics.h"
#include "Drawing.h"
#include "Font.h"



void DrawText(int x, int y,std::wstring text,std::string font, int fontsize,Color colour,FontAlignment alignment)
{
	Platform::String^ platstring = ref new Platform::String(text.data());
	CanvasTextLayout^ layout = ref new CanvasTextLayout(SwapChain,platstring, GetFont(font),4096.0f,4096.0f);
	layout->SetFontSize(0,text.length(),fontsize);
	float modifier = layout->DefaultFontSize / 4.0f; // metrics isn't ever correct

    switch (alignment)
    {
    case FontAlignment::Centre:
        x -= ((layout->LayoutBounds.Width + modifier) / 2);
        break;
    case FontAlignment::Right:
        x += ((layout->LayoutBounds.Width + modifier));
        break;
    case FontAlignment::Left:
        x -= ((layout->LayoutBounds.Width + modifier));
        break;
    case FontAlignment::None:
        break;
    case FontAlignment::CentreCentre:
        x -= ((layout->LayoutBounds.Width + modifier) / 2);
        y -= ((layout->LayoutBounds.Height + modifier) / 2);
        break;
    case FontAlignment::CentreLeft:
        x -= ((layout->LayoutBounds.Width + modifier));
        y += ((layout->LayoutBounds.Height + modifier) / 2);
        break;
    case FontAlignment::CentreRight:
        x += ((layout->LayoutBounds.Width + modifier));
        y -= ((layout->LayoutBounds.Height + modifier) / 2);
        break;
    }
	SwapChain->DrawTextLayout(layout, (float)x, (float)y, colour);
}