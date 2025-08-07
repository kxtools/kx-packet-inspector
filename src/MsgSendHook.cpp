#include "MsgSendHook.h"
#include "PacketProcessor.h"
#include "AppState.h"
#include "GameStructs.h"
#include "HookManager.h"
#include <iostream>
#include <exception>
#include <cstdio>
#include <debugapi.h>

// Function pointer to the original game function. This will be populated by MinHook.
// The `jmp` in our assembly stub will jump to the address stored in this pointer.
extern "C" QueuePacketFunc originalQueuePacket = nullptr;

// Address of the target function, stored globally for cleanup.
static uintptr_t hookedQueuePacketAddress = 0;

/**
 * @brief This is the pure C++ part of our logic. It's called from the assembly stub.
 * @details This function is where all packet processing and logging should occur.
 *          It's kept separate from the hook itself to avoid compiler-generated
 *          prologues/epilogues that could corrupt the stack or registers.
 *          It must be declared `extern "C"` so that the assembler can find it by name
 *          without C++ name mangling.
 * @param pMsgConn Pointer to the game's MsgConn object.
 * @param priority Priority flag for the packet.
 * @param opcode The packet's opcode.
 * @param pPayload Pointer to the packet's data payload.
*/
extern "C" void ProcessPacketLogic(void* pMsgConn, int priority, uint32_t opcode, void* pPayload) {
    // Check if packet capture is active before processing.
    if (!kx::g_capturePaused && !kx::g_isShuttingDown.load(std::memory_order_acquire)) {
        if (pMsgConn != nullptr && pPayload != nullptr) {
            try {
                // Delegate the actual processing and logging.
                // The size is unknown at this layer, but we can pass 0 and have the
                // processor decide what to do. For many packets, the schema is needed for the true size.
                kx::PacketProcessing::ProcessDispatchedMessage(
                    kx::PacketDirection::Sent,
                    static_cast<uint16_t>(opcode), // Safely cast opcode to uint16_t
                    static_cast<const uint8_t*>(pPayload),
                    0, // Size is unknown here, but can be looked up via schema if needed
                    pMsgConn
                );
            }
            catch (const std::exception& e) {
                char msg[256];
                sprintf_s(msg, sizeof(msg), "[ProcessPacketLogic] Exception: %s\n", e.what());
                OutputDebugStringA(msg);
            }
            catch (...) {
                OutputDebugStringA("[ProcessPacketLogic] Unknown exception.\n");
            }
        }
    }
}

/**
 * @brief Initializes the MinHook detour for the packet queueing function.
 * @param targetFunctionAddress The memory address of the original game function.
 * @return true If the hook was successfully created and enabled, false otherwise.
 */
bool InitializeQueuePacketHook(uintptr_t targetFunctionAddress) {
    if (targetFunctionAddress == 0) {
        std::cerr << "[QueuePacketHook] Error: Called with null address." << std::endl;
        return false;
    }

    hookedQueuePacketAddress = targetFunctionAddress;

    // We now point the hook to our external assembly stub, `hookQueuePacket_Naked`.
    // The assembler will create the `hookQueuePacket_Naked` symbol, and the extern "C"
    // declaration in the header allows the C++ compiler to find it.
    if (!kx::Hooking::HookManager::CreateHook(reinterpret_cast<LPVOID>(targetFunctionAddress), &hookQueuePacket_Naked, reinterpret_cast<LPVOID*>(&originalQueuePacket))) {
        std::cerr << "[QueuePacketHook] Hook creation failed." << std::endl;
        hookedQueuePacketAddress = 0;
        return false;
    }

    if (!kx::Hooking::HookManager::EnableHook(reinterpret_cast<LPVOID>(targetFunctionAddress))) {
        std::cerr << "[QueuePacketHook] Hook enabling failed." << std::endl;
        hookedQueuePacketAddress = 0;
        return false;
    }

    std::cout << "[QueuePacketHook] Hook installed successfully." << std::endl;
    return true;
}

/**
 * @brief Disables and removes the MinHook detour for the packet queueing function.
 */
void CleanupQueuePacketHook() {
    if (hookedQueuePacketAddress != 0) {
        if (MH_DisableHook(reinterpret_cast<LPVOID>(hookedQueuePacketAddress)) != MH_OK) {
            std::cerr << "[QueuePacketHook] Failed to disable hook." << std::endl;
        }

        if (MH_RemoveHook(reinterpret_cast<LPVOID>(hookedQueuePacketAddress)) != MH_OK) {
            std::cerr << "[QueuePacketHook] Failed to remove hook." << std::endl;
        }

        hookedQueuePacketAddress = 0;
        originalQueuePacket = nullptr;
        std::cout << "[QueuePacketHook] Cleaned up." << std::endl;
    }
}