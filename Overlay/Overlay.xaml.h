//
// Overlay.xaml.h
// Declaration of the Overlay class.
//

#pragma once

#include "Overlay.g.h"

namespace Cheat
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public ref class Overlay sealed
    {
    public:
        Overlay();
        void canvasSwapChainPanel_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
    };
}

