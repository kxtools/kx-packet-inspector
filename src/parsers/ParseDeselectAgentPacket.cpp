#include "pch.h"
#include "ParseDeselectAgentPacket.h"

namespace kx::Parsing {
    std::optional<std::string> ParseDeselectAgentPacket(const kx::PacketInfo& packet) {
        if (packet.direction != kx::PacketDirection::Sent ||
            packet.rawHeaderId != static_cast<uint16_t>(kx::CMSG_HeaderId::DESELECT_AGENT)) {
            return std::nullopt;
        }
        if (packet.data.size() == 3 && packet.data[2] == 0x00) {
            return "Deselect Agent: OK";
        }
        return "Deselect Agent: (Malformed)";
    }
}
