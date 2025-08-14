#include "pch.h"
#include "MsgSendHook.h"
#include "PacketProcessor.h" // Include the new processor header
#include "HookManager.h"

// Function pointer to the original game function. Set by MinHook.
MsgSendFunc originalMsgSend = nullptr;
// Address of the target function, used for cleanup.
static uintptr_t hookedMsgSendAddress = 0;

// Detour function for the game's internal message sending logic.
// This function now primarily captures the context and delegates processing.
void __fastcall hookMsgSend(void* param_1) {

    // Check if packet capture is active before processing.
    // This check happens *before* calling the original function.
    if (!kx::g_capturePaused && !kx::g_isShuttingDown.load(std::memory_order_acquire)) {
        if (param_1 != nullptr) {
            try {
                // Cast the context pointer.
                auto* context = reinterpret_cast<kx::GameStructs::MsgSendContext*>(param_1);
                // Delegate the actual processing and logging.
                kx::PacketProcessing::ProcessOutgoingPacket(context);
            }
            catch (const std::exception& e) {
                // Log::Error("[hookMsgSend] Exception during packet processing delegation: %s", e.what());
                char msg[256];
                sprintf_s(msg, sizeof(msg), "[hookMsgSend] Exception during outgoing processing call: %s\n", e.what());
                OutputDebugStringA(msg);
            }
            catch (...) {
                // Log::Error("[hookMsgSend] Unknown exception during packet processing delegation.");
                OutputDebugStringA("[hookMsgSend] Unknown exception during outgoing processing call.\n");
            }
        }
        else {
            // Log::Warn("[hookMsgSend] Called with null context pointer.");
            OutputDebugStringA("[hookMsgSend] Warning: Called with null context pointer.\n");
        }
    }

    // CRITICAL: Always call the original function, regardless of capture state or errors.
    if (originalMsgSend) {
        originalMsgSend(param_1);
    }
    else {
        // Log::Critical("[hookMsgSend] Original MsgSend function pointer is NULL!");
        OutputDebugStringA("[hookMsgSend] CRITICAL ERROR: Original MsgSend function pointer is NULL!\n");
        // Avoid crashing, but logging indicates a severe setup issue.
    }
}

// Initializes the MinHook detour for the message sending function.
bool InitializeMsgSendHook(uintptr_t targetFunctionAddress) {
    if (targetFunctionAddress == 0) {
        // Log::Error("InitializeMsgSendHook called with null address.");
        std::cerr << "[Error] InitializeMsgSendHook called with null address." << std::endl;
        return false;
    }

    // Create the hook.
    hookedMsgSendAddress = targetFunctionAddress; // Keep track for potential specific cleanup
    if (!kx::Hooking::HookManager::CreateHook(reinterpret_cast<LPVOID>(targetFunctionAddress), &hookMsgSend, reinterpret_cast<LPVOID*>(&originalMsgSend))) {
        std::cerr << "[MsgSendHook] Hook creation failed via HookManager." << std::endl;
        hookedMsgSendAddress = 0;
        return false;
    }

    if (!kx::Hooking::HookManager::EnableHook(reinterpret_cast<LPVOID>(targetFunctionAddress))) {
        std::cerr << "[MsgSendHook] Hook enabling failed via HookManager." << std::endl;
        hookedMsgSendAddress = 0;
        return false;
    }

    return true;
}

// The explicit disable-remove sequence is employed to avoid potential disconnects or packet loss,
// ensuring the hook is cleanly removed before the shutdown process completes.
void CleanupMsgSendHook() {
    if (hookedMsgSendAddress != 0) {
        // Disable the hook to immediately halt message interception.
        if (MH_DisableHook(reinterpret_cast<LPVOID>(hookedMsgSendAddress)) != MH_OK) {
            std::cerr << "[MsgSendHook] Failed to disable hook." << std::endl;
        }

        // Remove the hook to finalize cleanup and restore original function behavior.
        if (MH_RemoveHook(reinterpret_cast<LPVOID>(hookedMsgSendAddress)) != MH_OK) {
            std::cerr << "[MsgSendHook] Failed to remove hook." << std::endl;
        }

        // Reset local state variables.
        hookedMsgSendAddress = 0;
        originalMsgSend = nullptr;
        std::cout << "[MsgSendHook] Cleaned up." << std::endl;
    }
}
