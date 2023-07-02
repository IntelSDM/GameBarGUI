﻿//
// App.xaml.h
// Declaration of the App class.
//

#pragma once

#include "App.g.h"

namespace Cheat
{
    /// <summary>
    /// Provides application-specific behavior to supplement the default Application class.
    /// </summary>
    ref class App sealed
    {
    protected:
        virtual void OnActivated(Windows::ApplicationModel::Activation::IActivatedEventArgs^ e) override;
        virtual void OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ e) override;

    internal:
        App();

    private:
        void OnSuspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ e);
        void OnNavigationFailed(Platform::Object ^sender, Windows::UI::Xaml::Navigation::NavigationFailedEventArgs ^e);
        void OverlayWindowClosedHandler(Platform::Object^ sender, Windows::UI::Core::CoreWindowEventArgs^ e);

        Windows::Foundation::EventRegistrationToken m_OverlayWindowClosedHandlerToken{};
        Microsoft::Gaming::XboxGameBar::XboxGameBarWidget^ m_Overlay{ nullptr };
    };
}
