#include "Hooks.h"
#include "AppState.h"        // For setting status flags
#include "Config.h"          // For patterns/process name
#include "PatternScanner.h"  // For finding game functions
#include "MessageHandlerHook.h"

#include <iostream>          // Replace with logging

namespace kx {

    // --- GameHooks Implementation ---
    // (Could be in its own GameHooks.cpp if it grows more complex)
    namespace GameHooks {

        bool InitializeMsgSendHook() {
            g_msgSendHookStatus = HookStatus::Unknown; // Start as unknown
            g_msgSendAddress = 0;

            std::cout << "Scanning for MsgSend pattern..." << std::endl;
            std::optional<uintptr_t> msgSendAddrOpt = kx::PatternScanner::FindPattern(
                std::string(kx::MSG_CONN_QUEUE_PACKET_PATTERN),
                std::string(kx::TARGET_PROCESS_NAME)
            );

            if (!msgSendAddrOpt) {
                std::cerr << "[GameHooks] MsgSend pattern not found. Hook skipped." << std::endl;
                g_msgSendHookStatus = HookStatus::Failed; // Or a specific "NotFound" status
                return true; // Non-fatal if pattern isn't found
            }

            g_msgSendAddress = *msgSendAddrOpt;
            std::cout << "[GameHooks] MsgSend pattern found at: 0x" << std::hex << g_msgSendAddress << std::dec << std::endl;

            // Now use the existing MsgSendHook.h logic, but it should internally use HookManager
            if (::InitializeQueuePacketHook(g_msgSendAddress)) { // Call the global function from MsgSendHook.h
                g_msgSendHookStatus = HookStatus::OK;
                std::cout << "[GameHooks] MsgSend hook initialized." << std::endl;
                return true;
            }
            else {
                std::cerr << "[GameHooks] Failed to initialize MsgSend hook." << std::endl;
                g_msgSendHookStatus = HookStatus::Failed;
                return false; // Indicate failure if hooking itself failed
            }
        }

        bool InitializeMessageHandlerHook() {
            g_msgRecvHookStatus = HookStatus::Unknown; // Use Recv status flag
            g_msgRecvAddress = 0; // Base address of dispatcher

            std::cout << "Scanning for MsgDispatch pattern..." << std::endl;
            std::optional<uintptr_t> msgDispatchAddrOpt = kx::PatternScanner::FindPattern(
                std::string(kx::MSG_DISPATCH_STREAM_PATTERN), // Use dispatcher pattern
                std::string(kx::TARGET_PROCESS_NAME)
            );

            if (!msgDispatchAddrOpt) {
                std::cerr << "[GameHooks] MsgDispatch pattern not found. Hook skipped." << std::endl;
                g_msgRecvHookStatus = HookStatus::Failed;
                return true;
            }

            g_msgRecvAddress = *msgDispatchAddrOpt; // Store dispatcher base address
            std::cout << "[GameHooks] MsgDispatch pattern found at: 0x" << std::hex << g_msgRecvAddress << std::dec << std::endl;

            // Call the new initializer, passing the dispatcher base address
            if (::InitializeMessageHandlerHooks(g_msgRecvAddress)) { // <<< CHANGED
                g_msgRecvHookStatus = HookStatus::OK;
                std::cout << "[GameHooks] Message Handler hooks initialized." << std::endl;
                return true;
            }
            else {
                std::cerr << "[GameHooks] Failed to initialize Message Handler hooks." << std::endl;
                g_msgRecvHookStatus = HookStatus::Failed;
                return false;
            }
        }

        void Shutdown() {
            // Call specific cleanup if needed (e.g., freeing resources specific to the hook)
            // These functions might become empty if all cleanup is handled by HookManager::Shutdown
            ::CleanupQueuePacketHook();
            ::CleanupMessageHandlerHooks();
            std::cout << "[GameHooks] Shutdown complete." << std::endl;
        }

    } // namespace GameHooks


    // --- Global Hook Orchestration ---

    bool InitializeHooks() {
        // Reset status flags
        g_presentHookStatus = HookStatus::Unknown;
        g_msgSendHookStatus = HookStatus::Unknown;
        g_msgRecvHookStatus = HookStatus::Unknown;
        g_msgSendAddress = 0;
        g_msgRecvAddress = 0;

        // 1. Initialize Hook Manager (MinHook)
        if (!kx::Hooking::HookManager::Initialize()) {
            return false; // Fatal if MinHook fails
        }

        // 2. Initialize D3D Render Hook (Present, WndProc, ImGui)
        if (!kx::Hooking::D3DRenderHook::Initialize()) {
            // D3DRenderHook::Initialize already logs errors
            kx::Hooking::HookManager::Shutdown(); // Cleanup MinHook if Present hook fails
            g_presentHookStatus = HookStatus::Failed;
            return false; // Present hook is essential
        }
        // Status g_presentHookStatus is set inside D3DRenderHook::Initialize

        // 3. Initialize Game-Specific Hooks (MsgSend, MsgRecv)
        // We consider these non-fatal for now if they fail (e.g., pattern not found)
        GameHooks::InitializeMsgSendHook();
        GameHooks::InitializeMessageHandlerHook();

        std::cout << "[Hooks] Overall initialization finished." << std::endl;
        return true; // Return true even if game hooks failed, as Present hook is OK
    }

    void CleanupHooks() {
        std::cout << "[Hooks] Starting cleanup..." << std::endl;

        // 1. Shutdown game-specific hooks (if they have specific cleanup)
        GameHooks::Shutdown();

        // 2. Shutdown D3D Render Hook (Restores WndProc, cleans ImGui/D3D resources)
        kx::Hooking::D3DRenderHook::Shutdown();

        // 3. Shutdown Hook Manager (Disables/Removes all hooks via MinHook)
        kx::Hooking::HookManager::Shutdown();

        std::cout << "[Hooks] Cleanup finished." << std::endl;
    }

} // namespace kx