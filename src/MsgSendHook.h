#pragma once

/**
 * @file MsgSendHook.h
 * @brief Defines structures and functions for hooking the game's internal
 *        packet queueing function (MsgConn::QueuePacket).
 */

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <cstdint> // For uintptr_t
#include "../libs/MinHook/MinHook.h" // Adjust path as necessary

 // Link MinHook lib (consider moving linker directives to project settings)
#if _WIN64
#pragma comment(lib, "libs/MinHook/libMinHook.x64.lib")
#else
#pragma comment(lib, "libs/MinHook/libMinHook.x86.lib")
#endif

// NEW: Declare the assembly function as an external C function.
// This tells the C++ compiler that the function exists in another file.
extern "C" void hookQueuePacket_Naked();

/**
 * @brief Defines the function pointer type for the original packet queueing function.
 * @details Signature based on reverse engineering MsgConn::QueuePacket.
 *          Uses the __fastcall calling convention.
 * @param pMsgConn (RCX) Pointer to the MsgConn object.
 * @param priority (RDX) An integer, likely a priority flag (often 0).
 * @param opcode (R8) The 16-bit or 32-bit opcode of the packet.
 * @param pPayload (R9) Pointer to the serialized packet data.
 * @return bool Likely indicates if the packet was successfully queued.
 */
 // NEW: Updated function signature to match MsgConn::QueuePacket
typedef bool(__fastcall* QueuePacketFunc)(void* pMsgConn, int priority, uint32_t opcode, void* pPayload);

/**
 * @brief Initializes the MinHook detour for the packet queueing function.
 * @param targetFunctionAddress The memory address of the original game function.
 * @return true If the hook was successfully created and enabled, false otherwise.
 */
 // MODIFIED: Renamed for clarity
bool InitializeQueuePacketHook(uintptr_t targetFunctionAddress);

/**
 * @brief Disables and removes the MinHook detour for the packet queueing function.
 */
 // MODIFIED: Renamed for clarity
void CleanupQueuePacketHook();

/**
 * @brief The detour function that replaces the original packet queueing function.
 * @details Intercepts the call, delegates processing to PacketProcessor,
 *          and then calls the original function.
 *          Matches the signature defined by QueuePacketFunc.
 */
 // MODIFIED: Renamed and updated signature
bool __fastcall hookQueuePacket(void* pMsgConn, int priority, uint32_t opcode, void* pPayload);

/**
 * @brief Pointer to hold the address of the original game function.
 * @details Populated by MinHook; used by the hook to call the original code.
 */
 // MODIFIED: Changed type to match new signature
extern "C" QueuePacketFunc originalQueuePacket;

