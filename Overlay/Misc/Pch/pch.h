#pragma once

#undef WINAPI_FAMILY
#define WINAPI_FAMILY WINAPI_FAMILY_DESKTOP_APP
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#ifdef DrawText
#undef DrawText
#endif
#ifdef GetCurrentTime
#undef GetCurrentTime
#endif
#ifdef GetObject
#undef GetObject
#endif
#ifdef SendMessage
#undef SendMessage
#endif
#ifdef GetUserName
#undef GetUserName
#endif

#include <collection.h>
#include <ppltasks.h>
#include <windowsx.h>
#include <psapi.h>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <list>
#include "Vector.h"
#include "App.xaml.h"
