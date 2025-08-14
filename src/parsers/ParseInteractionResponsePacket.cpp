#include "pch.h"
#include "ParseInteractionResponsePacket.h"

namespace kx::Parsing {
    std::optional<std::string> ParseInteractionResponsePacket(const kx::PacketInfo& packet) {
        if (packet.rawHeaderId != static_cast<uint16_t>(kx::CMSG_HeaderId::INTERACTION_RESPONSE) || packet.data.size() < 3) {
            return std::nullopt;
        }
        if (packet.data[2] == 0x01) {
            return "Interaction Response: OK";
        }
        return "Interaction Response: (Malformed)";
    }
}
