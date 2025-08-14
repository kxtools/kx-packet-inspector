#include "pch.h"
#include "ParsePerformanceResponsePacket.h"

namespace kx::Parsing {
    std::optional<std::string> ParsePerformanceResponsePacket(const kx::PacketInfo& packet) {
        if (packet.direction != kx::PacketDirection::Sent ||
            packet.rawHeaderId != static_cast<uint16_t>(kx::CMSG_HeaderId::PERFORMANCE_RESPONSE)) {
            return std::nullopt;
        }
        const auto& data = packet.data;
        if (data.size() == 3) {
            return "Performance Response (Heartbeat Variant)";
        }
        if (data.size() >= 6) {
            uint32_t perf_value;
            std::memcpy(&perf_value, data.data() + 2, sizeof(uint32_t));
            std::stringstream ss;
            ss << "Performance Response Payload:\n" 
               << "  Perf Value: " << perf_value;
            return ss.str();
        }
        return "Performance Response (Unknown Variant)";
    }
}
