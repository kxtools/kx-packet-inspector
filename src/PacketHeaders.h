#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <utility> // For std::pair
#include <string_view>
#include <map>

#include "PacketData.h" // Required for PacketDirection enum definition

namespace kx {

    // --- Client->Server Header IDs ---
    enum class CMSG_HeaderId : uint16_t {
        SESSION_TICK = 0x0001,
        PERFORMANCE_RESPONSE = 0x0002,
        MOVEMENT_END = 0x0004,
        PING_RESPONSE = 0x0006,
        JUMP = 0x0009,
        MOVEMENT_WITH_ROTATION = 0x000B,
        HEARTBEAT = 0x0011,
        MOVEMENT = 0x0012,
        CONTEXT_MENU_REQUEST = 0x0014,
        USE_SKILL = 0x0017,
        MOUNT_MOVEMENT = 0x0018,
        LANDED = 0x001A,
        LOGOUT_TO_CHAR_SELECT = 0x0023,
        AGENT_LINK = 0x0036,
        DESELECT_AGENT = 0x00DD,
        SELECT_AGENT = 0x00E5,
        CHAT_MESSAGE = 0x0100,
        INTERACT_WITH_AGENT = 0x010E,
        INTERACTION_RESPONSE = 0x010F,
        CLIENT_STATE_SYNC = 0x0113,
    };


    // --- Server->Client Header IDs ---
    enum class SMSG_HeaderId : uint16_t {
        AGENT_UPDATE_BATCH = 0x0001,    // Confirmed: Container for many agent-related events
        PLAYER_STATE_UPDATE = 0x0002,   // Confirmed: Periodic state update for the player
        PERFORMANCE_MSG = 0x0008,       // Unconfirmed
        INTERACTION_DIALOGUE = 0x000F,  // Unconfirmed: Multi-part message sequence for NPC dialogue
        UI_MESSAGE = 0x0014,            // Unconfirmed: UI state, notifications, chat, etc.
        PLAYER_DATA_UPDATE = 0x0015,    // Unconfirmed: Currency, inventory, achievements
        AGENT_STATE_BULK = 0x0016,      // Unconfirmed: Bulk agent states/effects
        SKILL_UPDATE = 0x0017,          // Unconfirmed: Skill bar, cooldowns, action results
        CONFIG_UPDATE = 0x001A,         // Unconfirmed: Settings/configuration sync
        AGENT_EFFECT_UPDATE = 0x001C,   // Unconfirmed: Agent effects, status, or interactions
        MAP_DATA_BLOCK = 0x0020,        // Unconfirmed: Map geometry, entities, terrain data
        PET_INFO = 0x0021,              // Unconfirmed: Pet/minion state
        MAP_DETAIL_INFO = 0x0023,       // Unconfirmed: Detailed info for specific map elements
        MAP_LOAD_STATE = 0x0026,        // Unconfirmed: Map loading sequence/status updates
        SERVER_COMMAND = 0x0027,        // Confirmed: Server-initiated command (e.g., ping/perf check)
        AGENT_ATTRIBUTE_UPDATE = 0x0028,// Unconfirmed: Agent stats, buffs/debuffs
        AGENT_APPEARANCE = 0x002B,      // Unconfirmed: Agent visuals, equipment loading
        AGENT_SYNC = 0x0034,            // Unconfirmed: Periodic sync of multiple nearby agents
        AGENT_LINK = 0x0036,            // Unconfirmed: Linking agents (target, relationship?)
        SOCIAL_UPDATE = 0x0039,         // Unconfirmed: Guild, party, friends list update
        TIME_SYNC = 0x003F,             // Confirmed: Periodic server tick/time update
    };

    // --- Extern declarations for the lookup maps defined in PacketHeaders.cpp ---
    extern const std::map<CMSG_HeaderId, std::string_view> g_cmsgNames;
    extern const std::map<SMSG_HeaderId, std::string_view> g_smsgNames;
    extern const std::map<InternalPacketType, std::string_view> g_specialTypeNames;


    // --- Public API ---

    inline std::string GetPacketName(PacketDirection direction, uint16_t rawHeaderId) {
        std::string prefix;
        std::string_view name_sv;
        bool found = false;

        if (direction == PacketDirection::Sent) {
            prefix = "CMSG_";
            auto it = g_cmsgNames.find(static_cast<CMSG_HeaderId>(rawHeaderId));
            if (it != g_cmsgNames.end()) {
                name_sv = it->second;
                found = true;
            }
        } else {
            prefix = "SMSG_";
            auto it = g_smsgNames.find(static_cast<SMSG_HeaderId>(rawHeaderId));
            if (it != g_smsgNames.end()) {
                name_sv = it->second;
                found = true;
            }
        }

        if (found) {
            return prefix + std::string(name_sv);
        } else {
            return prefix + "UNKNOWN";
        }
    }

    inline std::string GetSpecialPacketTypeName(InternalPacketType type) {
        auto it = g_specialTypeNames.find(type);
        if (it != g_specialTypeNames.end()) {
            return std::string(it->second);
        }
        return "INTERNAL_ERROR"; // Fallback
    }

    inline std::vector<std::pair<uint16_t, std::string>> GetKnownCMSGHeaders() {
        std::vector<std::pair<uint16_t, std::string>> headers;
        headers.reserve(g_cmsgNames.size());
        for (const auto& [value, name_sv] : g_cmsgNames) {
            headers.emplace_back(static_cast<uint16_t>(value), "CMSG_" + std::string(name_sv));
        }
        return headers;
    }

    inline std::vector<std::pair<uint16_t, std::string>> GetKnownSMSGHeaders() {
        std::vector<std::pair<uint16_t, std::string>> headers;
        headers.reserve(g_smsgNames.size());
        for (const auto& [value, name_sv] : g_smsgNames) {
            headers.emplace_back(static_cast<uint16_t>(value), "SMSG_" + std::string(name_sv));
        }
        return headers;
    }

    inline std::vector<std::pair<InternalPacketType, std::string>> GetSpecialPacketTypesForFilter() {
        std::vector<std::pair<InternalPacketType, std::string>> types;
        types.reserve(g_specialTypeNames.size());
        for (const auto& [value, name_sv] : g_specialTypeNames) {
            if (value == InternalPacketType::NORMAL) {
                continue;
            }
            types.emplace_back(value, std::string(name_sv));
        }
        return types;
    }

} // namespace kx
