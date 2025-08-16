# CMSG_0x010E_INTERACT_WITH_AGENT

**Direction**: Client -> Server
**Status**: Confirmed (Schema-Driven, Live-Validated)

## Summary

This packet is sent by the client when the player interacts with an agent, such as an NPC. It is used to initiate a conversation or to select a specific dialogue option. It is a simple, fixed-size packet that conveys the interaction type or choice.

## Construction Chain

This packet originates from the UI command pipeline, which is distinct from the player-action (`AgCommand`) pipeline.

1.  **Data Aggregation (`FUN_14106AF9E`):** A high-level function, likely called by the dialogue UI, gathers the context of the interaction (e.g., which dialogue option was selected).
2.  **Serialization:** This function calls down into the generic serialization engine to build the packet using its schema.
3.  **Sending Mechanism (Buffered Stream):** The packet is written to the main `MsgSendContext` buffer and sent in a batch when `MsgConn::FlushPacketBuffer` is called.

## Schema Information

- **Opcode:** `0x010E`
- **Schema Address (Live):** `0x7FF6E0EE3290`

## Packet Structure (Live-Validated)

The packet is a fixed 4 bytes.

| Offset | Size | Data Type (Inferred) | Description |
|---|---|---|---|
| 0x00 | 2 | `ushort` | The opcode `0x010E`. |
| 0x02 | 2 | `ushort` | A **Command ID** indicating the type of interaction. Known values: `0x0001` (Continue/Next), `0x0002` (Select Option), `0x0004` (Exit Dialogue). |

**Live Packet Sample (Selecting an option):**
`16:40:22.740 [S] CMSG_UNKNOWN Op:0x010E | Sz:4 | 0E 01 01 00`