#pragma once

// --- Windows & System ---
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <psapi.h> // For PatternScanner
#include <ShlObj.h> // For GuiStyle font loading
#include <shellapi.h> // For ShellExecuteA

// --- Standard Library ---
#include <string>
#include <string_view>
#include <vector>
#include <deque>
#include <map>
#include <mutex>
#include <chrono>
#include <optional>
#include <cstdint>
#include <sstream>
#include <iomanip>
#include <exception>
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cstring> // For memcpy
#include <ctime>   // For formatting time

// --- Third-Party Libraries ---
#include "../libs/ImGui/imgui.h"
#include "../libs/ImGui/imgui_impl_win32.h"
#include "../libs/ImGui/imgui_impl_dx11.h"
#include "../libs/MinHook/MinHook.h"
#include "../libs/safetyhook/safetyhook.hpp"

// --- Project Headers (stable and widely used) ---
#include "PacketData.h"
#include "PacketHeaders.h"
#include "GameStructs.h"
#include "AppState.h"
