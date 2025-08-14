#include "pch.h"
#include "ParseInteractWithAgentPacket.h"

namespace kx::Parsing {
    std::optional<std::string> ParseInteractWithAgentPacket(const kx::PacketInfo& packet) {
        if (packet.direction != kx::PacketDirection::Sent ||
            packet.rawHeaderId != static_cast<uint16_t>(kx::CMSG_HeaderId::INTERACT_WITH_AGENT)) {
            return std::nullopt;
        }

        const std::vector<uint8_t>& data = packet.data;
        constexpr size_t required_size = 4;

        if (data.size() < required_size) {
            return std::nullopt;
        }

        uint16_t commandId;
        std::memcpy(&commandId, data.data() + 2, sizeof(uint16_t));

        std::string command_desc = "Unknown";
        switch (commandId) {
            case 0x0001: command_desc = "Continue/Next"; break;
            case 0x0002: command_desc = "Select Option"; break;
            case 0x0004: command_desc = "Exit Dialogue"; break;
        }

        std::stringstream ss;
        ss << "Interact With Agent Payload:\n" 
           << "  Command ID: 0x" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << commandId 
           << " (" << command_desc << ")";

        return ss.str();
    }
}
