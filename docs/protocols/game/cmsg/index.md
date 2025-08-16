# CMSG Packet Reference (Game Server)

> **For a complete, automatically generated layout of all CMSG packet schemas, see the master reference document:**
> *   **[CMSG Complete Schema Layout](./reference/CMSG_Complete_Schema_Layout.md)**

---

This section contains documentation for Client-to-Server packets that have been **fully validated against live network traffic**. Each packet's structure and builder function have been confirmed through dynamic analysis.

For packets that have a known schema or builder but have not been observed or confirmed in common gameplay, see the [Unverified Packets](./unverified/) directory.

---

## Live-Validated Packets

| Opcode | Name | Details |
|---|---|---|
| `0x0001` | Session Tick | [CMSG_0x0001_SESSION_TICK.md](./verified/CMSG_0x0001_SESSION_TICK.md) |
| `0x0002` | Performance Response / Unknown | [CMSG_0x0002_PERFORMANCE_RESPONSE.md](./verified/CMSG_0x0002_PERFORMANCE_RESPONSE.md) |
| `0x0004` | Movement End | [CMSG_0x0004_MOVEMENT_END.md](./verified/CMSG_0x0004_MOVEMENT_END.md) |
| `0x0009` | Jump | [CMSG_0x0009_JUMP.md](./verified/CMSG_0x0009_JUMP.md) |
| `0x000B` | Movement with Rotation | [CMSG_0x000B_MOVEMENT_WITH_ROTATION.md](./verified/CMSG_0x000B_MOVEMENT_WITH_ROTATION.md) |
| `0x0012` | Movement | [CMSG_0x0012_MOVEMENT.md](./verified/CMSG_0x0012_MOVEMENT.md) |
| `0x0014` | Context Menu Request | [CMSG_0x0014_CONTEXT_MENU_REQUEST.md](./verified/CMSG_0x0014_CONTEXT_MENU_REQUEST.md) |
| `0x0017` | Use Skill | [CMSG_0x0017_USE_SKILL.md](./verified/CMSG_0x0017_USE_SKILL.md) |
| `0x0018` | Mount Movement | [CMSG_0x0018_MOUNT_MOVEMENT.md](./verified/CMSG_0x0018_MOUNT_MOVEMENT.md) |
| `0x001A` | Landed | [CMSG_0x001A_LANDED.md](./verified/CMSG_0x001A_LANDED.md) |
| `0x0023` | Logout to Character Select | [CMSG_0x0023_LOGOUT_TO_CHAR_SELECT.md](./verified/CMSG_0x0023_LOGOUT_TO_CHAR_SELECT.md) |
| `0x00DD` | Deselect Agent | [CMSG_0x00DD_DESELECT_AGENT.md](./verified/CMSG_0x00DD_DESELECT_AGENT.md) |
| `0x00E5` | Select Agent | [CMSG_0x00E5_SELECT_AGENT.md](./verified/CMSG_0x00E5_SELECT_AGENT.md) |
| `0x0100` | Chat Message | [CMSG_0x0100_CHAT_MESSAGE.md](./verified/CMSG_0x0100_CHAT_MESSAGE.md) |
| `0x010E` | Interact with Agent | [CMSG_0x010E_INTERACT_WITH_AGENT.md](./verified/CMSG_0x010E_INTERACT_WITH_AGENT.md) |
| `0x010F` | Interaction Response | [CMSG_0x010F_INTERACTION_RESPONSE.md](./verified/CMSG_0x010F_INTERACTION_RESPONSE.md) |
| `0x0113` | Client State Sync | [CMSG_0x0113_CLIENT_STATE_SYNC.md](./verified/CMSG_0x0113_CLIENT_STATE_SYNC.md) |
