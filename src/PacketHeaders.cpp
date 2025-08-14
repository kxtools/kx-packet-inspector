#include "PacketHeaders.h"
#include "pch.h"
#include <map>
#include <string_view>

namespace kx {

// Using maps for efficient lookup and easy maintenance.
// The string_view values point to string literals, so there's no runtime allocation cost.

// --- CMSG Name Registry ---
const std::map<CMSG_HeaderId, std::string_view> g_cmsgNames = {
    { CMSG_HeaderId::SESSION_TICK, "SESSION_TICK" },
    { CMSG_HeaderId::PERFORMANCE_RESPONSE, "PERFORMANCE_RESPONSE" },
    { CMSG_HeaderId::MOVEMENT_END, "MOVEMENT_END" },
    { CMSG_HeaderId::PING_RESPONSE, "PING_RESPONSE" },
    { CMSG_HeaderId::JUMP, "JUMP" },
    { CMSG_HeaderId::MOVEMENT_WITH_ROTATION, "MOVEMENT_WITH_ROTATION" },
    { CMSG_HeaderId::HEARTBEAT, "HEARTBEAT" },
    { CMSG_HeaderId::MOVEMENT, "MOVEMENT" },
    { CMSG_HeaderId::CONTEXT_MENU_REQUEST, "CONTEXT_MENU_REQUEST" },
    { CMSG_HeaderId::USE_SKILL, "USE_SKILL" },
    { CMSG_HeaderId::MOUNT_MOVEMENT, "MOUNT_MOVEMENT" },
    { CMSG_HeaderId::LANDED, "LANDED" },
    { CMSG_HeaderId::LOGOUT_TO_CHAR_SELECT, "LOGOUT_TO_CHAR_SELECT" },
    { CMSG_HeaderId::AGENT_LINK, "AGENT_LINK" },
    { CMSG_HeaderId::DESELECT_AGENT, "DESELECT_AGENT" },
    { CMSG_HeaderId::SELECT_AGENT, "SELECT_AGENT" },
    { CMSG_HeaderId::CHAT_MESSAGE, "CHAT_MESSAGE" },
    { CMSG_HeaderId::INTERACT_WITH_AGENT, "INTERACT_WITH_AGENT" },
    { CMSG_HeaderId::INTERACTION_RESPONSE, "INTERACTION_RESPONSE" },
    { CMSG_HeaderId::CLIENT_STATE_SYNC, "CLIENT_STATE_SYNC" }
};

// --- SMSG Name Registry ---
const std::map<SMSG_HeaderId, std::string_view> g_smsgNames = {
    { SMSG_HeaderId::AGENT_UPDATE_BATCH, "AGENT_UPDATE_BATCH" },
    { SMSG_HeaderId::PLAYER_STATE_UPDATE, "PLAYER_STATE_UPDATE" },
    { SMSG_HeaderId::PERFORMANCE_MSG, "PERFORMANCE_MSG" },
    { SMSG_HeaderId::INTERACTION_DIALOGUE, "INTERACTION_DIALOGUE" },
    { SMSG_HeaderId::UI_MESSAGE, "UI_MESSAGE" },
    { SMSG_HeaderId::PLAYER_DATA_UPDATE, "PLAYER_DATA_UPDATE" },
    { SMSG_HeaderId::AGENT_STATE_BULK, "AGENT_STATE_BULK" },
    { SMSG_HeaderId::SKILL_UPDATE, "SKILL_UPDATE" },
    { SMSG_HeaderId::CONFIG_UPDATE, "CONFIG_UPDATE" },
    { SMSG_HeaderId::AGENT_EFFECT_UPDATE, "AGENT_EFFECT_UPDATE" },
    { SMSG_HeaderId::MAP_DATA_BLOCK, "MAP_DATA_BLOCK" },
    { SMSG_HeaderId::PET_INFO, "PET_INFO" },
    { SMSG_HeaderId::MAP_DETAIL_INFO, "MAP_DETAIL_INFO" },
    { SMSG_HeaderId::MAP_LOAD_STATE, "MAP_LOAD_STATE" },
    { SMSG_HeaderId::SERVER_COMMAND, "SERVER_COMMAND" },
    { SMSG_HeaderId::AGENT_ATTRIBUTE_UPDATE, "AGENT_ATTRIBUTE_UPDATE" },
    { SMSG_HeaderId::AGENT_APPEARANCE, "AGENT_APPEARANCE" },
    { SMSG_HeaderId::AGENT_SYNC, "AGENT_SYNC" },
    { SMSG_HeaderId::AGENT_LINK, "AGENT_LINK" },
    { SMSG_HeaderId::SOCIAL_UPDATE, "SOCIAL_UPDATE" },
    { SMSG_HeaderId::TIME_SYNC, "TIME_SYNC" }
};

// --- Special Packet Type Name Registry ---
const std::map<InternalPacketType, std::string_view> g_specialTypeNames = {
    { InternalPacketType::NORMAL, "NORMAL" },
    { InternalPacketType::ENCRYPTED_RC4, "ENCRYPTED_RC4" },
    { InternalPacketType::UNKNOWN_HEADER, "UNKNOWN_HEADER" },
    { InternalPacketType::EMPTY_PACKET, "EMPTY_PACKET" },
    { InternalPacketType::PROCESSING_ERROR, "PROCESSING_ERROR" },
    { InternalPacketType::PACKET_TOO_SMALL, "PACKET_TOO_SMALL" }
};

} // namespace kx
