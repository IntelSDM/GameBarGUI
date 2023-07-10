#include "pch.h"
#include "Overlay.xaml.h"
#include "Graphics.h"
#include "Input.h"
#include "Font.h"
#include "Drawing.h"
#include "GUI.h"
#include "TabController.h"
using namespace Cheat;
using namespace Platform;
using namespace Windows::UI::Core;
Microsoft::Graphics::Canvas::UI::Xaml::CanvasSwapChainPanel^ CanvasObject;
CanvasDrawingSession^ SwapChain;
namespace sdk
{
	float WindowWidth;
	float WindowHeight;
}


Overlay::Overlay()
{
	InitializeComponent();

	// Hide Title Bar
	auto  coretitlebar = CoreApplication::GetCurrentView()->TitleBar;
	coretitlebar->ExtendViewIntoTitleBar = true;
	auto titlebar = ApplicationView::GetForCurrentView()->TitleBar;
	titlebar->ButtonBackgroundColor = Colors::Transparent;
	titlebar->ButtonInactiveBackgroundColor = Colors::Transparent;
	titlebar->ButtonPressedBackgroundColor = Colors::Transparent;
	titlebar->ButtonHoverBackgroundColor = Colors::Transparent;
}


//You can just pass the CanvasObject directly into this but I used it in other places also
void RenderingThread()
{
	SwapChain = CanvasObject->SwapChain->CreateDrawingSession(Colors::Transparent);
	CreateFont("Verdana", L"Verdana", 20, Weight::Normal);
	CreateGUI();
	while (true) 
	{
		
		SwapChain->Clear(Colors::Transparent);
		/* RENDER*/
		SwapChain->Clear(Colors::Black);
		std::string test = std::to_string(MousePos.x) + "x" + std::to_string(MousePos.y) +"|" + std::to_string(IsKeyClicked(VK_SHIFT));
		std::wstring wideText(test.begin(), test.end());
		Platform::String^ text = ref new Platform::String(wideText.c_str());
		SwapChain->DrawText(text, 0, 0, Colour(255,0,0,255));
		/*DrawText(10, 50, L"text0", "verdana", 16, Colour(255, 0, 0, 255), FontAlignment::None);
		FilledRectangle(80, 80, 50, 50, Colour(0, 255, 0, 255));
		OutlineRoundedRectangle(150, 150, 50, 50, 5, 5, Colour(255, 0, 255, 255));
		OutlineCircle(300, 300, 100, 1, Colour(0, 0, 0, 255));
		ColourPicker(400, 400, 200, 200,Colour(255,0,0,255));
		FilledTriangle(600, 150, 900, 150, 750, 300, Colour(0, 0, 255, 255));*/
		RenderGUI();
		/*END OF RENDERING*/
		SwapChain->Flush();
		CanvasObject->SwapChain->Present();
	

	
	}
}

void Overlay::CharacterReceived(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::CharacterReceivedEventArgs^ e)
{
	// Get the character that was received
	wchar_t character = e->KeyCode;
	Char = character;
}

void Overlay::PointerMoved(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::PointerEventArgs^ e)
{
	// Get the current mouse position
	Windows::Foundation::Point mp = e->CurrentPoint->Position;
	MousePos = {(float) mp.X,(float)mp.Y };
	if(CanCollectInput())
	SetClassLongPtr(GetForegroundWindow() ,GCLP_HCURSOR,(LONG_PTR)GetCurrentCursor()); // set cursor
}
void Overlay::PointerPressed(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::PointerEventArgs^ e)
{
	// Check the state of the mouse buttons
	Windows::UI::Input::PointerPoint^ pointer = e->CurrentPoint;
	auto button = pointer->Properties->PointerUpdateKind;
	if (button == Windows::UI::Input::PointerUpdateKind::LeftButtonPressed)
	{
		UpdateKeyState(VK_LBUTTON, true);
	}
	if (button == Windows::UI::Input::PointerUpdateKind::RightButtonPressed)
	{
		UpdateKeyState(VK_RBUTTON, true);
	}
	if (button == Windows::UI::Input::PointerUpdateKind::MiddleButtonPressed)
	{
		UpdateKeyState(VK_MBUTTON, true);
	}
	if (button == Windows::UI::Input::PointerUpdateKind::XButton1Pressed)
	{
		UpdateKeyState(VK_XBUTTON1, true);
	}
	if (button == Windows::UI::Input::PointerUpdateKind::XButton2Pressed)
	{
		UpdateKeyState(VK_XBUTTON2, true);
	}
}
void Overlay::PointerReleased(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::PointerEventArgs^ e)
{
	// Check the state of the mouse buttons
	
	Windows::UI::Input::PointerPoint^ pointer = e->CurrentPoint;
	auto button = pointer->Properties->PointerUpdateKind;
	if (button == Windows::UI::Input::PointerUpdateKind::LeftButtonReleased)
	{
		UpdateKeyState(VK_LBUTTON, false);
	}
	if (button == Windows::UI::Input::PointerUpdateKind::RightButtonReleased)
	{
		UpdateKeyState(VK_RBUTTON, false);
	}
	if (button == Windows::UI::Input::PointerUpdateKind::MiddleButtonReleased)
	{
		UpdateKeyState(VK_MBUTTON, false);
	}
	if (button == Windows::UI::Input::PointerUpdateKind::XButton1Released)
	{
		UpdateKeyState(VK_XBUTTON1, false);
	}
	if (button == Windows::UI::Input::PointerUpdateKind::XButton2Released)
	{
		UpdateKeyState(VK_XBUTTON2, false);
	}
}
void Overlay::KeyDown(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::KeyEventArgs^ e)
{
	// Get the key that was pressed down
	Windows::System::VirtualKey key = e->VirtualKey;
	int keyvalue = static_cast<int>(key);
	UpdateKeyState(keyvalue, true);
	
}
void Overlay::KeyUp(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::KeyEventArgs^ e)
{
	// Get the key that was released
	Windows::System::VirtualKey key = e->VirtualKey;
	int keyvalue = static_cast<int>(key);
	UpdateKeyState(keyvalue, false);
}
void Overlay::SwapChainPanel_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	canvasSwapChainPanel->SwapChain = ref new CanvasSwapChain(CanvasDevice::GetSharedDevice(), (float)Window::Current->CoreWindow->Bounds.Width, 
		(float)Window::Current->CoreWindow->Bounds.Height, 96);

	CanvasObject = canvasSwapChainPanel;
	CanvasObject->AllowFocusWhenDisabled = true;
	//lets use this it is way better for what we want
	sdk::WindowWidth = (float)Window::Current->CoreWindow->Bounds.Width;
	sdk::WindowHeight = (float)Window::Current->CoreWindow->Bounds.Height;

	Windows::UI::Core::CoreWindow::GetForCurrentThread()->CharacterReceived += ref new Windows::Foundation::TypedEventHandler<Windows::UI::Core::CoreWindow^, Windows::UI::Core::CharacterReceivedEventArgs^>(this, &Overlay::CharacterReceived);
	Windows::UI::Core::CoreWindow::GetForCurrentThread()->PointerMoved +=ref new Windows::Foundation::TypedEventHandler<Windows::UI::Core::CoreWindow^, Windows::UI::Core::PointerEventArgs^>(this, &Overlay::PointerMoved);
	Windows::UI::Core::CoreWindow::GetForCurrentThread()->PointerPressed += ref new Windows::Foundation::TypedEventHandler<Windows::UI::Core::CoreWindow^, Windows::UI::Core::PointerEventArgs^>(this, &Overlay::PointerPressed);
	Windows::UI::Core::CoreWindow::GetForCurrentThread()->PointerReleased += ref new Windows::Foundation::TypedEventHandler<Windows::UI::Core::CoreWindow^, Windows::UI::Core::PointerEventArgs^>(this, &Overlay::PointerReleased);
	Windows::UI::Core::CoreWindow::GetForCurrentThread()->KeyDown += ref new Windows::Foundation::TypedEventHandler<Windows::UI::Core::CoreWindow^, Windows::UI::Core::KeyEventArgs^>(this, &Overlay::KeyDown);
	Windows::UI::Core::CoreWindow::GetForCurrentThread()->KeyUp += ref new Windows::Foundation::TypedEventHandler<Windows::UI::Core::CoreWindow^, Windows::UI::Core::KeyEventArgs^>(this, &Overlay::KeyUp);
	SetInput();

	std::thread renderthread(RenderingThread);
	renderthread.detach();

}
