﻿//#include "pch.h"
#include "pch.h"
#include "Overlay.xaml.h"
#include <TlHelp32.h>
#include <thread>
#include <string>
#include "Input.h"
#include "Sockets.h"

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

bool test123 = false;
//You can just pass the CanvasObject directly into this but I used it in other places also
void RenderingThread()
{
	static auto ds = CanvasObject->SwapChain->CreateDrawingSession(Colors::Transparent);

	while (true) 
	{
		
		ds->Clear(Colors::Transparent);
		/* RENDER*/

		std::string test = std::to_string(sdk::WindowWidth) + "x" + std::to_string(sdk::WindowHeight);
		std::wstring wideText(test.begin(), test.end());
		Platform::String^ text = ref new Platform::String(wideText.c_str());
	
		ds->DrawText(text, 0, 0, Colors::Red);

		/*END OF RENDERING*/
	//	ds->FillRectangle(0,0, sdk::WindowWidth, sdk::WindowHeight,Colors::White);

		ds->Flush();
	
	CanvasObject->SwapChain->Present();
	if ((GetKeyState(VK_RBUTTON) & 0x01) != 0)
		test123 = true;
	
	}
}

void GetKey()
{
	// we will need to implement sending key states back to the client here
	while (true)
	{

		if ((GetKeyState(VK_RBUTTON) & 0x01) != 0)
			test123 = true;
	}

}

void ListeningThread()
{

	/*
	So we have a listening thread incase lets say the client disconnects and restarts.
	In websockets you cant just see if a thread is closed
	Also the while true is basically exitted, so accept clients is called and then its stuck there until a client connects
	So no additional load is put on the cpu. Optimized stuff microsoft.
	*/
	
	
}

void Overlay::canvasSwapChainPanel_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	canvasSwapChainPanel->SwapChain = ref new CanvasSwapChain(CanvasDevice::GetSharedDevice(), (float)Window::Current->CoreWindow->Bounds.Width, 
		(float)Window::Current->CoreWindow->Bounds.Height, 96);

	CanvasObject = canvasSwapChainPanel;

	//lets use this it is way better for what we want
	sdk::WindowWidth = (float)Window::Current->CoreWindow->Bounds.Width;
	sdk::WindowHeight = (float)Window::Current->CoreWindow->Bounds.Height;
	CreateSockets();


	std::thread renderthread(RenderingThread);
	renderthread.detach();
	std::thread listernerthread(ListeningThread);
	listernerthread.detach();
	//std::thread keytest(GetKey);
	//keytest.detach();
}
