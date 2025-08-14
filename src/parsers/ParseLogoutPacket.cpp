#include "pch.h"
#include "ParseLogoutPacket.h"

namespace kx::Parsing {
    std::optional<std::string> ParseLogoutPacket(const kx::PacketInfo& packet) {
        if (packet.direction != kx::PacketDirection::Sent ||
            packet.rawHeaderId != static_cast<uint16_t>(kx::CMSG_HeaderId::LOGOUT_TO_CHAR_SELECT)) {
            return std::nullopt;
        }
        if (packet.data.size() == 2) {
            return "Logout to Character Select";
        }
        return "Logout to Character Select: (Malformed)";
    }
}
