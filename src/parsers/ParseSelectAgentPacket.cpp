#include "pch.h"
#include "ParseSelectAgentPacket.h"
#include "../PacketStructures.h"

namespace kx::Parsing {
    std::optional<std::string> ParseSelectAgentPacket(const kx::PacketInfo& packet) {
        if (packet.direction != kx::PacketDirection::Sent ||
            packet.rawHeaderId != static_cast<uint16_t>(kx::CMSG_HeaderId::SELECT_AGENT)) {
            return std::nullopt;
        }

        const std::vector<uint8_t>& data = packet.data;
        constexpr size_t required_size = sizeof(kx::Packets::CMSG_SelectAgentPayload);

        if (data.size() < required_size) {
            return std::nullopt;
        }

        kx::Packets::CMSG_SelectAgentPayload payload;
        std::memcpy(&payload, data.data(), required_size);

        std::stringstream ss;
        ss << "Select Agent Payload:\n"
           << "  Agent ID: 0x" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << payload.agentId << std::dec;
        if (payload.agentId != payload.agentId_repeat) {
            ss << " (Mismatch: 0x" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << payload.agentId_repeat << std::dec << ")";
        }
        ss << "\n  Unknown: 0x" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << payload.unknown << std::dec;

        return ss.str();
    }
}
