//
// App.xaml.cpp
// Implementation of the App class.
//

#include "pch.h"
#include "Overlay.xaml.h"
#pragma comment(lib, "user32.lib")

using namespace Cheat;

using namespace Platform;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Microsoft::Gaming::XboxGameBar;

using namespace Windows::Foundation;
using namespace Windows::UI::Core;
using namespace Windows::System;
using namespace Windows::UI::ViewManagement;

App::App()
{
    InitializeComponent();
    Suspending += ref new SuspendingEventHandler(this, &App::OnSuspending);

}

// Get the horizontal and vertical screen sizes in pixel
void GetDesktopResolution(int& horizontal, int& vertical)
{
    RECT desktop;
    // Get a handle to the desktop window
    const HWND hDesktop = GetDesktopWindow();
    // Get the size of screen to the variable desktop
    GetWindowRect(hDesktop, &desktop);
    // The top left corner will have coordinates (0,0)
    // and the bottom right corner will have coordinates
    // (horizontal, vertical)
    horizontal = desktop.right;
    vertical = desktop.bottom;
}

void App::OnActivated(Windows::ApplicationModel::Activation::IActivatedEventArgs^ e)
{
    XboxGameBarWidgetActivatedEventArgs^ widgetArgs = nullptr;

    if (e->Kind == ActivationKind::Protocol)
    {
        auto protocolArgs = dynamic_cast<IProtocolActivatedEventArgs^>(e);
        if (protocolArgs)
        {
            // If scheme name is ms-gamebarwidget, Xbox Game Bar is activating us.
            const wchar_t* scheme = protocolArgs->Uri->SchemeName->Data();
            if (0 == wcscmp(scheme, L"ms-gamebarwidget"))
            {
                widgetArgs = dynamic_cast<XboxGameBarWidgetActivatedEventArgs^>(e);
            }
        }
    }

    if (widgetArgs)
    {
        if (widgetArgs->IsLaunchActivation)
        {
            auto rootFrame = ref new Frame();
            rootFrame->NavigationFailed += ref new Windows::UI::Xaml::Navigation::NavigationFailedEventHandler(this, &App::OnNavigationFailed);
            Window::Current->Content = rootFrame;

            // Create Game Bar widget object which bootstraps the connection with Game Bar
            m_Overlay = ref new XboxGameBarWidget(widgetArgs, Window::Current->CoreWindow, rootFrame);
           
            m_Overlay->VerticalResizeSupported = true;
            m_Overlay->HorizontalResizeSupported = true;

            float width = GetSystemMetrics(SM_CXSCREEN);
            float height = GetSystemMetrics(SM_CYSCREEN);

            m_Overlay->MinWindowSize = Windows::Foundation::Size(width, height - 40);
            m_Overlay->MaxWindowSize = Windows::Foundation::Size(7680, 4320);

            m_Overlay->CenterWindowAsync();
            m_Overlay->TryResizeWindowAsync(Windows::Foundation::Size(width, height - 40));

            rootFrame->Navigate(TypeName(Overlay::typeid), nullptr);

            m_OverlayWindowClosedHandlerToken = Window::Current->Closed += ref new WindowClosedEventHandler(this, &Cheat::App::OverlayWindowClosedHandler);

			Window::Current->Activate();
        }
    }
}

void App::OverlayWindowClosedHandler(Platform::Object^ /*sender*/, Windows::UI::Core::CoreWindowEventArgs^ /*e*/)
{
    m_Overlay = nullptr;
    Window::Current->Closed -= m_OverlayWindowClosedHandlerToken;
}

void App::OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ e)
{
    auto rootFrame = dynamic_cast<Frame^>(Window::Current->Content);

    if (rootFrame)
    {
        if (e->PrelaunchActivated == false)
        {
            if (rootFrame->Content == nullptr)
            {
                // When the navigation stack isn't restored navigate to the first page,
                // configuring the new page by passing required information as a navigation
                // parameter
                rootFrame->Navigate(TypeName(Overlay::typeid), e->Arguments);
            }

            // Ensure the current window is active
            Window::Current->Activate();
        }
    }
    else
    {
        //assume this is 'startup' when a user is logged into the hack we launch this, then this gives them the xbox live store option
        if (!rootFrame) 
        {
            auto rootFrame = ref new Frame();
            Window::Current->Content = rootFrame;
            rootFrame->Navigate(TypeName(Overlay::typeid), e->Arguments);
            Window::Current->Activate();
	    }
    }
}

void App::OnSuspending(Object^ sender, SuspendingEventArgs^ e)
{
    (void) sender;  // Unused parameter 
    (void) e;   // Unused parameter

    m_Overlay = nullptr;
}

void App::OnNavigationFailed(Platform::Object ^sender, Windows::UI::Xaml::Navigation::NavigationFailedEventArgs ^e)
{
    throw ref new FailureException("Failed to load Page " + e->SourcePageType.Name);
}
