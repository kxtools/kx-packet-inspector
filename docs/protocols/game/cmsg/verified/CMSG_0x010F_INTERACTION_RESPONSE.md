# CMSG_0x010F_INTERACTION_RESPONSE

**Direction**: Client -> Server
**Status**: Confirmed (Live-Validated), Builder Unknown

## Summary

This packet is sent by the client immediately after exiting a dialogue with an NPC. It appears to be the final confirmation in a multi-packet interaction sequence, likely signaling to the server that the dialogue UI has been closed.

## Construction

This packet originates from a dedicated UI command pipeline.

- **Builder Function:** `FUN_1412EEB1E`
- **Serialization:** The builder calls down into the generic serialization engine, confirming this is a schema-driven packet.
- **Sending Mechanism:** Buffered Stream.

## Schema Information

- **Opcode:** `0x010F`
- **Schema Address (Live):** `0x7FF6E0EE3330`

## Packet Structure (Live-Validated)

The packet is a fixed 3 bytes.

| Offset | Size | Data Type (Inferred) | Value |
|---|---|---|---|
| 0x00 | 2 | `ushort` | The opcode `0x010F`. |
| 0x02 | 1 | `byte` | A constant value, always observed as `0x01`. |

**Live Packet Sample (Exiting a dialogue):**
`16:47:09.305 [S] CMSG_UNKNOWN Op:0x010F | Sz:3 | 0F 01 01`