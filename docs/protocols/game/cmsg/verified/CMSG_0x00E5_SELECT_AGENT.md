# CMSG_0x00E5_SELECT_AGENT

**Direction**: Client -> Server
**Status**: Confirmed (Schema-Driven, Live-Validated)

## Summary

This packet is sent by the client when the player selects a target agent, such as an NPC or another player. It is a schema-driven packet that follows the "Fast Path" hybrid model. A high-level aggregator provides a minimal 8-byte structure containing the agent ID, which is then serialized against a more complex schema.

## Construction Chain

1.  **Data Aggregation (`FUN_141241C79`):** A high-level function is called when the player selects a target. It gathers the necessary agent IDs.
2.  **Serialization:** This function calls down into the generic serialization engine to build the packet using its schema.
3.  **Sending Mechanism (Buffered Stream):** The packet is written to the main `MsgSendContext` buffer and sent in a batch when `MsgConn::FlushPacketBuffer` is called.

## Schema Information

- **Opcode:** `0x00E5`
- **Schema Address (Live):** `0x7FF6E0EB2470`

## Packet Structure (Live-Validated)

The packet is a fixed 8 bytes.

| Offset | Size | Data Type (Inferred) | Description |
|---|---|---|---|
| 0x00 | 2 | `ushort` | The opcode `0x00E5`. |
| 0x02 | 2 | `ushort` | The **Agent ID** of the selected target. |
| 0x04 | 2 | `ushort` | Unknown. Possibly the previously selected agent ID or a command subtype. Observed as `0x00DD`. |
| 0x06 | 2 | `ushort` | The **Agent ID**, repeated. |

**Live Packet Sample (Selecting an NPC with ID 0x01AC):**
`16:53:17.541 [S] CMSG_SELECT_AGENT Op:0x00E5 | Sz:8 | E5 00 AC 01 DD 00 AC 01`