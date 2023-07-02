#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN

#include <WinSock2.h>
#include <string>
#include <iostream>
#include <Ws2tcpip.h>
#include <list>
#include <thread>
#include "json.hpp"
using json = nlohmann::json;
