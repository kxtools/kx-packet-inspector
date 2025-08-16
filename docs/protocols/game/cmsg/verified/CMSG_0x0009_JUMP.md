# CMSG_JUMP (0x0009)

**Direction**: Client -> Server
**Status**: Confirmed (Schema-Driven, Live-Validated)

## Summary

This packet is sent by the client when the player character jumps. It is a schema-driven packet with a variable size, which depends on the player's state at the moment of the action. Its construction is initiated by a high-level "Player Action" aggregator function that collects game state and passes it to a generic builder.

## Construction & Sending

The creation and sending of this packet follows a multi-step, abstracted process:

1.  **Data Aggregation (`FUN_14101f990`):** A high-level function gathers all necessary player state data (position, flags, IDs, etc.) for the jump action and sets a field to the opcode value `9`.
2.  **Virtual Call to Builder (`FUN_141018E00`):** The aggregator makes a virtual call to a builder function, passing it the aggregated data.
3.  **Serialization (`CMSG::BuildAndSendPacket`):** This builder function calls the generic serialization engine, which uses the schema to write the final packet bytes into the main outgoing `MsgSendContext` buffer.
4.  **Sending Mechanism (Buffered Stream):** The packet data now resides in the primary send buffer. It is not sent immediately. It will be sent to the server in a batch along with other packets when the client next calls **`MsgConn::FlushPacketBuffer`**.

## Schema Information

- **Opcode:** `0x0009`
- **Schema Address (Live):** `0x7FF6E0EA2460`

## Packet Structure (Decoded from Schema)

The packet's structure is defined by a 10-field schema. The variable size of the live packet is due to the `Small Buffer` and `Optional Block` fields.

| Field # | Typecode | Data Type (Inferred) | Description |
| :--- | :--- | :--- | :--- |
| 1 | `0x01` | `short` | A subtype or sequence ID. Observed as `0x009B` in logs. |
| 2 | `0x04` | Compressed `int` | A timestamp or server tick. |
| 3 | `0x02` | `byte` | A flag or state byte. |
| 4 | `0x04` | Compressed `int` | An ID, possibly related to the player agent or instance. |
| 5 | `0x14` | Small Buffer | A buffer with a 1-byte length prefix. Source of variable size. |
| 6 | `0x0F` | Optional Block | A block of data that is only present if a preceding flag is set. The primary source of variable size. |
| 7 | `0x01` | `short` | A field within the optional block. |
| 8 | `0x04` | Compressed `int` | A field within the optional block. |
| 9 | `0x02` | `byte` | A field within the optional block. |
| 10 | `0x04` | Compressed `int` | A field within the optional block. |

## Evidence

The packet's schema-driven nature was confirmed by tracing writes to the `MsgSendContext` buffer back up the call stack. A breakpoint on a low-level write inside `Msg::MsgPack` revealed the full call chain, leading to the high-level data aggregator function.

**Live Packet Sample (Size 75 bytes):**
`01:33:49.935 [S] CMSG_JUMP Op:0x0009 | Sz:75 | 09 00 9B 00 90 76 00 FC B6 81 80 08 02 5F 10 01 ...`

## Confidence

- **Opcode:** High
- **Name:** High
- **Structure:** High (Schema decoded and validated against live traffic)