#include "pch.h"
#include "Graphics.h"
#include "Drawing.h"
#include "Font.h"
#include <WindowsNumerics.h>


void DrawText(int x, int y,std::wstring text,std::string font, int fontsize,Color colour,FontAlignment alignment)
{
	Platform::String^ platstring = ref new Platform::String(text.data());
	CanvasTextLayout^ layout = ref new CanvasTextLayout(SwapChain,platstring, GetFont(font),4096.0f,4096.0f);
	layout->SetFontSize(0,text.length(),fontsize);
	float modifier = layout->DefaultFontSize / 4.0f; // metrics isn't ever correct

    switch (alignment)
    {
    case FontAlignment::Centre:
        x -= ((layout->LayoutBounds.Width) / 2);
        break;
    case FontAlignment::Right:
        x += ((layout->LayoutBounds.Width));
        break;
    case FontAlignment::Left:
        x -= ((layout->LayoutBounds.Width));
        break;
    case FontAlignment::None:
        break;
    case FontAlignment::CentreCentre:
        x -= ((layout->LayoutBounds.Width) / 2);
        y -= ((layout->LayoutBounds.Height) / 2);
        break;
    case FontAlignment::CentreLeft:
        x += ((layout->LayoutBounds.Width));
        y -= ((layout->LayoutBounds.Height) / 2);
        break;
    case FontAlignment::CentreRight:
        x += (layout->LayoutBounds.Width);
        y -= ((layout->LayoutBounds.Height) / 2);
        break;
    }

	SwapChain->DrawTextLayout(layout, (float)x, (float)y, colour);
}

void DrawTextClipped(int x, int y,int width,int height, std::wstring text, std::string font, int fontsize, Color colour, FontAlignment alignment)
{
    Platform::String^ platstring = ref new Platform::String(text.data());
    CanvasTextLayout^ layout = ref new CanvasTextLayout(SwapChain, platstring, GetFont(font), width, height);
    layout->SetFontSize(0, text.length(), fontsize);
    float modifier = layout->DefaultFontSize / 4.0f; // metrics isn't ever correct

    switch (alignment)
    {
    case FontAlignment::Centre:
        x -= ((layout->LayoutBounds.Height + modifier) / 2);
        break;
    case FontAlignment::Right:
        x += ((layout->LayoutBounds.Height + modifier));
        break;
    case FontAlignment::Left:
        x -= ((layout->LayoutBounds.Height + modifier));
        break;
    case FontAlignment::None:
        break;
    case FontAlignment::CentreCentre:
        x -= ((layout->LayoutBounds.Height + modifier) / 2);
        y -= ((layout->LayoutBounds.Width + modifier) / 2);
        break;
    case FontAlignment::CentreLeft:
        x += ((layout->LayoutBounds.Height + modifier));
        y -= ((layout->LayoutBounds.Width + modifier) / 2);
        break;
    case FontAlignment::CentreRight:
        x += ((layout->LayoutBounds.Height + modifier));
        y -= ((layout->LayoutBounds.Width + modifier) / 2);
        break;
    }

    SwapChain->DrawTextLayout(layout, (float)x, (float)y, colour);
}

void FilledRectangle(int x, int y, int width, int height, Color colour)
{
    Rect rect(x, y, width,height);
    SwapChain->FillRectangle(rect, colour);
}
void ColourPicker(int x, int y, int width, int height, Color colour)
{
    auto stops = ref new Platform::Array<CanvasGradientStop>(2);
    stops[0] = { 0.00f, colour };
    stops[1] = { 1.0f, Colors::Black };


    auto brush = ref new CanvasLinearGradientBrush(SwapChain, stops);
    brush->StartPoint =  float2(x + width, y);
    brush->EndPoint =  float2(x, y + height);

    SwapChain->FillRectangle(Rect(x, y, width, height), brush);

}
void ColourPickerSlider(int x, int y, int width, int height)
{
    auto stops = ref new Platform::Array<CanvasGradientStop>(7);
    stops[0] = { 0.00f, Colour(255,0,0,255) };
    stops[1] = { 0.16f, Colour(255,255,0,255) };
    stops[2] = { 0.32f,  Colour(0,255,0,255) };
    stops[3] = { 0.48f,  Colour(0,255,255,255) };
    stops[4] = { 0.64f,  Colour(0,0,255,255) };
    stops[5] = { 0.80f,  Colour(255,0,255,255) };
    stops[6] = { 0.96f,  Colour(255,0,0,255) };

    auto brush = ref new CanvasLinearGradientBrush(SwapChain, stops);
    brush->StartPoint = float2((float)x, (float)y);
    brush->EndPoint = float2((float)(x + width), (float)y);

    SwapChain->FillRectangle(Rect(x, y, width, height), brush);

}
void OutlineRectangle(int x, int y, int width, int height, int thickness, Color colour)
{
    Rect rect(x, y, width, height);
    SwapChain->DrawRectangle(rect,colour, thickness);
}
void FilledRoundedRectangle(int x, int y, int width, int height,int aax, int aay,Color colour)
{
    Rect rect(x, y, width, height);
    SwapChain->FillRoundedRectangle(rect,aax,aay, colour);
}

void OutlineRoundedRectangle(int x, int y, int width, int height, int aax, int aay,Color colour)
{
    Rect rect(x, y,width,height);
    SwapChain->DrawRoundedRectangle(rect,aax,aay, colour);
}

void OutlineCircle(int x, int y, int radius,int thickness, Color colour)
{
    SwapChain->DrawCircle(x,y,(float)radius,colour, thickness);
}
void FilledCircle(int x, int y, int radius, int thickness, Color colour)
{
    SwapChain->FillCircle(x, y, (float)radius, colour);
}
void FilledLine(int x1,int y1,int x2, int y2, int thickness, Color colour)
{
    SwapChain->DrawLine(x1,y1,x2,y2,colour,thickness);
}
void FilledTriangle(int x1, int y1, int x2, int y2, int x3, int y3, Color colour)
{
    Point p1(x1,y1);
    Point p2(x2, y2);
    Point p3(x3, y3);
    
    auto path = ref new CanvasPathBuilder(SwapChain->Device);

    path->BeginFigure(p1);
    path->AddLine(p2);
    path->AddLine(p3);
    path->EndFigure(CanvasFigureLoop::Closed);
    auto geometry = CanvasGeometry::CreatePath(path);
    SwapChain->FillGeometry(geometry, colour);
}