#include "pch.h"
#include "ParseMovementPacket.h"
#include "../PacketStructures.h"

namespace kx::Parsing {

    std::optional<std::string> ParseMovementPacket(const kx::PacketInfo& packet) {
        if (packet.direction != kx::PacketDirection::Sent ||
            packet.rawHeaderId != static_cast<uint16_t>(kx::CMSG_HeaderId::MOVEMENT)) {
            return std::nullopt;
        }

        const std::vector<uint8_t>& data = packet.data;
        constexpr size_t assumed_offset_from_end = 16;

        if (data.size() < assumed_offset_from_end) {
            return std::nullopt;
        }

        kx::Packets::MovementPayload payload;
        const uint8_t* floatStart = data.data() + data.size() - assumed_offset_from_end;

        std::memcpy(&payload.x, floatStart, sizeof(float));
        std::memcpy(&payload.y, floatStart + sizeof(float), sizeof(float));
        std::memcpy(&payload.z, floatStart + 2 * sizeof(float), sizeof(float));

        std::stringstream ss;
        ss << "Movement Payload:\n"
           << "  X: " << std::fixed << std::setprecision(2) << payload.x << "\n"
           << "  Y: " << std::fixed << std::setprecision(2) << payload.y << "\n"
           << "  Z: " << std::fixed << std::setprecision(2) << payload.z;

        return ss.str();
    }

}