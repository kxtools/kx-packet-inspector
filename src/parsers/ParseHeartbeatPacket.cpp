#include "pch.h"
#include "ParseHeartbeatPacket.h"

namespace kx::Parsing {
    std::optional<std::string> ParseHeartbeatPacket(const kx::PacketInfo& packet) {
        if (packet.direction != kx::PacketDirection::Sent ||
            packet.rawHeaderId != static_cast<uint16_t>(kx::CMSG_HeaderId::HEARTBEAT)) {
            return std::nullopt;
        }

        if (packet.data.size() < 4) {
            return "Heartbeat: (Malformed, too small)";
        }

        uint16_t value;
        std::memcpy(&value, packet.data.data() + 2, sizeof(uint16_t));

        std::stringstream ss;
        ss << "Heartbeat Payload:\n" 
           << "  Value: 0x" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << value;

        return ss.str();
    }
}
