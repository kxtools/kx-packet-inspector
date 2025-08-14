#include "pch.h"
#include "ParseTimeSyncPacket.h"
#include "../PacketStructures.h"

namespace kx::Parsing {
    std::optional<std::string> ParseTimeSyncPacket(const kx::PacketInfo& packet) {
        if (packet.direction != kx::PacketDirection::Received ||
            packet.rawHeaderId != static_cast<uint16_t>(kx::SMSG_HeaderId::TIME_SYNC)) {
            return std::nullopt;
        }

        const std::vector<uint8_t>& data = packet.data;
        constexpr size_t required_size = 10;

        if (data.size() < required_size) {
            return std::nullopt;
        }

        uint16_t type_discriminator;
        std::memcpy(&type_discriminator, data.data(), sizeof(uint16_t));

        std::stringstream ss;
        ss << "Time Sync Payload:\n";

        if (type_discriminator == 0x050F) { // Variant A: Cadence/Tick
            kx::Packets::SMSG_TimeSyncTickPayload payload;
            std::memcpy(&payload, data.data(), required_size);
            ss << "  Variant: Cadence/Tick\n"
               << "  Type: 0x" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << payload.type << std::dec << "\n"
               << "  Time Lo: 0x" << std::hex << std::uppercase << std::setw(8) << std::setfill('0') << payload.time_lo << std::dec << "\n"
               << "  Time Hi: 0x" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << payload.time_hi << std::dec << "\n"
               << "  Flags/ID: 0x" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << payload.flags_or_id << std::dec;
        } else if (type_discriminator == 0x050D) { // Variant B: Seed/Epoch
            kx::Packets::SMSG_TimeSyncSeedPayload payload;
            std::memcpy(&payload, data.data(), required_size);
            ss << "  Variant: Seed/Epoch\n"
               << "  Type: 0x" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << payload.type << std::dec << "\n"
               << "  Seed: 0x" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << payload.seed << std::dec << "\n"
               << "  Millis: 0x" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << payload.millis << std::dec << "\n"
               << "  World/ID: 0x" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << payload.world_or_id << std::dec << "\n"
               << "  Flags: 0x" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << payload.flags << std::dec;
        } else {
            ss << "  Unknown Time Sync Variant (Type: 0x" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << type_discriminator << std::dec << ")";
        }

        return ss.str();
    }
}
