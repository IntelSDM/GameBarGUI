﻿#pragma once

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
#ifdef CreateFont
#undef CreateFont
#endif
#include <collection.h>
#include <ppltasks.h>
#include <windowsx.h>
#include <psapi.h>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <list>
#include <string>
#include <map>
#include <TlHelp32.h>
#include <thread>


#include "Vector.h"
#include "App.xaml.h"
#include "Colour.h"