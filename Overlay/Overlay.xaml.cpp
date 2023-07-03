#include "pch.h"
#include "Overlay.xaml.h"
#include <TlHelp32.h>
#include <thread>
#include <string>
#include "Input.h"


using namespace Cheat;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI;
using namespace Microsoft::Graphics::Canvas::UI::Xaml;
using namespace Microsoft::Graphics::Canvas;

using namespace Microsoft::Graphics::Canvas;
using namespace Microsoft::Graphics::Canvas::Text;
using namespace Microsoft::Graphics::Canvas::UI::Xaml;
using namespace Microsoft::Gaming::XboxGameBar;

using namespace Windows::Foundation;
using namespace Windows::UI::Core;
using namespace Windows::System;
using namespace Windows::UI::ViewManagement;
using namespace Windows::ApplicationModel::Core;

Microsoft::Graphics::Canvas::UI::Xaml::CanvasSwapChainPanel^ CanvasObject;

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
POINT mousePosition;
void Overlay::PointerMoved(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	// Get the current mouse position
	Windows::Foundation::Point mp = e->GetCurrentPoint(nullptr)->Position;
	mousePosition = {(long) mp.X,(long)mp.Y };
	// Use the mouse position as needed
	// For example, you can display it in a TextBlock
}
bool test123 = false;


//You can just pass the CanvasObject directly into this but I used it in other places also
void RenderingThread()
{
	static auto ds = CanvasObject->SwapChain->CreateDrawingSession(Colors::Transparent);

	while (true) 
	{
		
		ds->Clear(Colors::Transparent);
		/* RENDER*/

		std::string test = std::to_string(mousePosition.x) + "x" + std::to_string(mousePosition.y);
		std::wstring wideText(test.begin(), test.end());
		Platform::String^ text = ref new Platform::String(wideText.c_str());
	
		ds->DrawText(text, 0, 0, Colors::Red);

		/*END OF RENDERING*/
	//	ds->FillRectangle(0,0, sdk::WindowWidth, sdk::WindowHeight,Colors::White);

		ds->Flush();
	
	CanvasObject->SwapChain->Present();
	
	
	// Unhook the mouse hook
	
	}
}




void Overlay::SwapChainPanel_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	canvasSwapChainPanel->SwapChain = ref new CanvasSwapChain(CanvasDevice::GetSharedDevice(), (float)Window::Current->CoreWindow->Bounds.Width, 
		(float)Window::Current->CoreWindow->Bounds.Height, 96);

	CanvasObject = canvasSwapChainPanel;

	//lets use this it is way better for what we want
	sdk::WindowWidth = (float)Window::Current->CoreWindow->Bounds.Width;
	sdk::WindowHeight = (float)Window::Current->CoreWindow->Bounds.Height;

	

	std::thread renderthread(RenderingThread);
	renderthread.detach();

}
