#include "pch.h"
#include "ParseServerCommandPacket.h"

namespace kx::Parsing {
    std::optional<std::string> ParseServerCommandPacket(const kx::PacketInfo& packet) {
        if (packet.direction != kx::PacketDirection::Received ||
            packet.rawHeaderId != static_cast<uint16_t>(kx::SMSG_HeaderId::SERVER_COMMAND)) {
            return std::nullopt;
        }

        const std::vector<uint8_t>& data = packet.data;
        if (data.size() < 2) {
            return "Server Command: (Too small)";
        }

        uint16_t subtype;
        std::memcpy(&subtype, data.data(), sizeof(uint16_t));

        std::stringstream ss;
        ss << "Server Command Payload:\n"
           << "  Subtype: 0x" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << subtype << std::dec;

        if (subtype == 0x0003) {
            ss << " (Performance Trigger)";
        } else if (subtype == 0x0004) {
            ss << " (Ping Response Trigger)";
            if (data.size() >= 6) {
                uint32_t value;
                std::memcpy(&value, data.data() + 2, sizeof(uint32_t));
                ss << "\n  Value: 0x" << std::hex << std::uppercase << std::setw(8) << std::setfill('0') << value << std::dec;
            }
        }

        return ss.str();
    }
}
