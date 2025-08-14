#include "pch.h"
#include "ParseSessionTickPacket.h"

namespace kx::Parsing {
    std::optional<std::string> ParseSessionTickPacket(const kx::PacketInfo& packet) {
        if (packet.rawHeaderId != static_cast<uint16_t>(kx::CMSG_HeaderId::SESSION_TICK) || packet.data.size() < 6) {
            return std::nullopt;
        }
        uint32_t timestamp;
        std::memcpy(&timestamp, packet.data.data() + 2, sizeof(uint32_t));
        std::stringstream ss;
        ss << "Session Tick Payload:\n" 
           << "  Timestamp: " << timestamp;
        return ss.str();
    }
}

