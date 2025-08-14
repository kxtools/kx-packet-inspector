#include "pch.h"
#include "PacketParser.h"

// Include all individual parser headers
#include "parsers/ParseDeselectAgentPacket.h"
#include "parsers/ParseHeartbeatPacket.h"
#include "parsers/ParseInteractWithAgentPacket.h"
#include "parsers/ParseInteractionResponsePacket.h"
#include "parsers/ParseLogoutPacket.h"
#include "parsers/ParseMovementPacket.h"
#include "parsers/ParsePerformanceResponsePacket.h"
#include "parsers/ParsePlayerStateUpdatePacket.h"
#include "parsers/ParseSelectAgentPacket.h"
#include "parsers/ParseServerCommandPacket.h"
#include "parsers/ParseSessionTickPacket.h"
#include "parsers/ParseTimeSyncPacket.h"

namespace kx::Parsing {

// Define the type for the parser registry
using ParserRegistry = std::map<std::pair<kx::PacketDirection, uint16_t>, ParserFunc>;

// Function to initialize and return the parser registry
const ParserRegistry& GetParserRegistry() {
    static ParserRegistry registry = {
        // CMSG Parsers
        {{kx::PacketDirection::Sent, static_cast<uint16_t>(kx::CMSG_HeaderId::SESSION_TICK)}, ParseSessionTickPacket},
        {{kx::PacketDirection::Sent, static_cast<uint16_t>(kx::CMSG_HeaderId::PERFORMANCE_RESPONSE)}, ParsePerformanceResponsePacket},
        {{kx::PacketDirection::Sent, static_cast<uint16_t>(kx::CMSG_HeaderId::HEARTBEAT)}, ParseHeartbeatPacket},
        {{kx::PacketDirection::Sent, static_cast<uint16_t>(kx::CMSG_HeaderId::MOVEMENT)}, ParseMovementPacket},
        {{kx::PacketDirection::Sent, static_cast<uint16_t>(kx::CMSG_HeaderId::LOGOUT_TO_CHAR_SELECT)}, ParseLogoutPacket},
        {{kx::PacketDirection::Sent, static_cast<uint16_t>(kx::CMSG_HeaderId::DESELECT_AGENT)}, ParseDeselectAgentPacket},
        {{kx::PacketDirection::Sent, static_cast<uint16_t>(kx::CMSG_HeaderId::SELECT_AGENT)}, ParseSelectAgentPacket},
        {{kx::PacketDirection::Sent, static_cast<uint16_t>(kx::CMSG_HeaderId::INTERACT_WITH_AGENT)}, ParseInteractWithAgentPacket},
        {{kx::PacketDirection::Sent, static_cast<uint16_t>(kx::CMSG_HeaderId::INTERACTION_RESPONSE)}, ParseInteractionResponsePacket},

        // SMSG Parsers
        {{kx::PacketDirection::Received, static_cast<uint16_t>(kx::SMSG_HeaderId::PLAYER_STATE_UPDATE)}, ParsePlayerStateUpdatePacket},
        {{kx::PacketDirection::Received, static_cast<uint16_t>(kx::SMSG_HeaderId::TIME_SYNC)}, ParseTimeSyncPacket},
        {{kx::PacketDirection::Received, static_cast<uint16_t>(kx::SMSG_HeaderId::SERVER_COMMAND)}, ParseServerCommandPacket},
    };
    return registry;
}

// Central dispatcher function, now using the map
std::optional<std::string> GetParsedDataTooltipString(const kx::PacketInfo& packet) {
    const auto& registry = GetParserRegistry();
    auto key = std::make_pair(packet.direction, packet.rawHeaderId);
    
    auto it = registry.find(key);
    if (it != registry.end()) {
        // Found a parser, call it
        return it->second(packet);
    }

    // No parser found for this key
    return std::nullopt;
}

} // namespace kx::Parsing


