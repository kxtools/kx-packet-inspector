#include "pch.h"
#include "PacketProcessor.h"

namespace kx::PacketProcessing {

    void ProcessOutgoingPacket(const GameStructs::MsgSendContext* context) {
        // Basic check (hook should ideally ensure non-null, but double-check)
        if (!context) {
            // Log::Error("ProcessOutgoingPacket called with null context."); // Future logger
            OutputDebugStringA("[PacketProcessor] Error: ProcessOutgoingPacket called with null context.\n");
            return;
        }

        try {
            // Skip processing if bufferState indicates the buffer might be invalid or getting reset (state 1).
            if (context->bufferState == 1) {
                return;
            }

            std::uint8_t* packetData = context->GetPacketBufferStart();
            std::size_t bufferSize = context->GetCurrentDataSize();

            // --- Sanity Checks ---
            bool dataIsValid = true;
            if (packetData == nullptr || context->currentBufferEndPtr == nullptr) {
                // Log::Error("Null pointer in MsgSendContext detected during processing.");
                OutputDebugStringA("[PacketProcessor] Error: Null pointer in MsgSendContext detected during processing.\n");
                dataIsValid = false;
            }
            else if (context->currentBufferEndPtr < packetData) {
                // Log::Error("Invalid packet buffer pointers (end < start) in MsgSendContext.");
                OutputDebugStringA("[PacketProcessor] Error: Invalid packet buffer pointers (end < start) in MsgSendContext.\n");
                dataIsValid = false;
            }
            else {
                // Limit size to prevent reading excessive memory.
                constexpr std::size_t MAX_REASONABLE_PACKET_SIZE = 16 * 1024;
                if (bufferSize > MAX_REASONABLE_PACKET_SIZE) {
                    // Log::Error("Outgoing packet size (%zu) exceeds sanity limit (%zu).", bufferSize, MAX_REASONABLE_PACKET_SIZE);
                    char msg[128];
                    sprintf_s(msg, sizeof(msg), "[PacketProcessor] Error: Outgoing packet size (%zu) exceeds sanity limit.\n", bufferSize);
                    OutputDebugStringA(msg);
                    dataIsValid = false;
                }
                // Check against the destination integer type limit.
                else if (bufferSize > static_cast<std::size_t>(std::numeric_limits<int>::max())) {
                    // Log::Error("Outgoing packet size (%zu) exceeds std::numeric_limits<int>::max().", bufferSize);
                    char msg[128];
                    sprintf_s(msg, sizeof(msg), "[PacketProcessor] Error: Outgoing packet size (%zu) exceeds max int.\n", bufferSize);
                    OutputDebugStringA(msg);
                    dataIsValid = false;
                }
            }
            // --- End Sanity Checks ---

            if (dataIsValid && bufferSize > 0) {
                PacketInfo info;
                info.timestamp = std::chrono::system_clock::now();
                info.size = static_cast<int>(bufferSize);
                info.direction = PacketDirection::Sent;
                info.bufferState = context->bufferState;
                info.specialType = InternalPacketType::NORMAL; // Assume normal

                // Copy packet data
                info.data.assign(packetData, packetData + bufferSize);

                // Analyze header
                if (info.data.size() >= 2) {
                    memcpy(&info.rawHeaderId, info.data.data(), sizeof(info.rawHeaderId));
                    info.name = GetPacketName(info.direction, info.rawHeaderId); // Use directional lookup
                } else {
                    info.specialType = InternalPacketType::PACKET_TOO_SMALL;
                    info.rawHeaderId = 0; // Assign a default/sentinel value
                    info.name = GetSpecialPacketTypeName(info.specialType);
                }

                // Check if the resolved name indicates an unknown header ID
                if (info.name.find("_UNKNOWN") != std::string::npos) {
                    info.specialType = InternalPacketType::UNKNOWN_HEADER; // Mark specifically as unknown ID
                }

                // Log the packet
                {
                    std::lock_guard<std::mutex> lock(g_packetLogMutex);
                    g_packetLog.push_back(std::move(info));
                }
            }
            else if (dataIsValid && bufferSize == 0) {
                PacketInfo info;
                info.timestamp = std::chrono::system_clock::now();
                info.size = 0;
                info.direction = PacketDirection::Sent;
                info.bufferState = context->bufferState;
                info.specialType = InternalPacketType::EMPTY_PACKET; // Mark as empty
                info.name = GetSpecialPacketTypeName(info.specialType);
                info.rawHeaderId = 0; // Or some default
                // Log the empty packet info
                {
                    std::lock_guard<std::mutex> lock(g_packetLogMutex);
                    g_packetLog.push_back(std::move(info));
                }
            }
        }
        catch (const std::exception& e) {
            char msg[256];
            sprintf_s(msg, sizeof(msg), "[PacketProcessor] Outgoing packet processing exception: %s\n", e.what());
            OutputDebugStringA(msg);
        }
        catch (...) {
            OutputDebugStringA("[PacketProcessor] Unknown exception during outgoing packet processing.\n");
        }
    }

    void ProcessDispatchedMessage(
        kx::PacketDirection direction,
        uint16_t messageId,
        const uint8_t* messageData,
        size_t messageSize,
        void* pMsgConn)
    {
        // Basic checks
        if (messageData == nullptr && messageSize > 0) {
            OutputDebugStringA("[PacketProcessor] Error: ProcessDispatchedMessage called with null data but non-zero size.\n");
            return;
        }
        if (messageSize > static_cast<std::size_t>(std::numeric_limits<int>::max())) {
            char msg[128];
            sprintf_s(msg, sizeof(msg), "[PacketProcessor] Error: Dispatched message size (%zu) exceeds max int.\n", messageSize);
            OutputDebugStringA(msg);
            return;
        }
        // Add MAX_REASONABLE check? Maybe less critical here as size is known?

        try {
            PacketInfo info;
            info.timestamp = std::chrono::system_clock::now();
            info.size = static_cast<int>(messageSize);
            info.direction = direction; // Should be Received
            info.rawHeaderId = messageId;
            info.specialType = InternalPacketType::NORMAL; // Assume normal

            // Copy message data payload
            if (messageSize > 0) {
                info.data.assign(messageData, messageData + messageSize);
            }
            else {
                info.specialType = InternalPacketType::EMPTY_PACKET; // Mark specific empty messages
            }

            // Get name and potentially refine type
            info.name = GetPacketName(info.direction, info.rawHeaderId);
            if (info.name.find("_UNKNOWN") != std::string::npos) {
                info.specialType = InternalPacketType::UNKNOWN_HEADER;
            }
            if (info.specialType == InternalPacketType::EMPTY_PACKET) {
                info.name = GetSpecialPacketTypeName(info.specialType); // Override name if empty
            }

            // Log the processed message info
            {
                std::lock_guard<std::mutex> lock(g_packetLogMutex);
                g_packetLog.push_back(std::move(info));
            }
        }
        catch (const std::exception& e) {
            char msg[256];
            sprintf_s(msg, sizeof(msg), "[PacketProcessor] Dispatched message processing exception: %s\n", e.what());
            OutputDebugStringA(msg);
        }
        catch (...) {
            OutputDebugStringA("[PacketProcessor] Unknown exception during dispatched message processing.\n");
        }
    }

} // namespace kx::PacketProcessing