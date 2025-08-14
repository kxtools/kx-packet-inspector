#include "pch.h"
#include "ParsePlayerStateUpdatePacket.h"
#include "../PacketStructures.h"

namespace kx::Parsing {
    std::optional<std::string> ParsePlayerStateUpdatePacket(const kx::PacketInfo& packet) {
        if (packet.direction != kx::PacketDirection::Received ||
            packet.rawHeaderId != static_cast<uint16_t>(kx::SMSG_HeaderId::PLAYER_STATE_UPDATE)) {
            return std::nullopt;
        }

        const std::vector<uint8_t>& data = packet.data;
        constexpr size_t required_size = sizeof(kx::Packets::SMSG_PlayerStateUpdatePayload);

        if (data.size() < required_size) {
            return std::nullopt;
        }

        kx::Packets::SMSG_PlayerStateUpdatePayload payload;
        std::memcpy(&payload, data.data(), required_size);

        std::stringstream ss;
        ss << "Player State Update Payload:\n"
           << "  Hdr: 0x" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << payload.hdr << std::dec << "\n"
           << "  Mode/Ix: 0x" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(payload.mode_or_ix) << std::dec << "\n"
           << "  Tick Lo: 0x" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << payload.tick_lo << std::dec << "\n"
           << "  Millis/K: 0x" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << payload.millis_or_k << std::dec << "\n"
           << "  World/ID: 0x" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << payload.world_or_id << std::dec << "\n"
           << "  Flags: 0x" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << payload.flags << std::dec;

        return ss.str();
    }
}
