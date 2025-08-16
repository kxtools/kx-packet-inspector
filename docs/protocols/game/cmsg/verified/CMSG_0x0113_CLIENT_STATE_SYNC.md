# CMSG_0x0113_CLIENT_STATE_SYNC

**Direction**: Client -> Server
**Status**: Confirmed (Schema-Driven, Live-Validated)

## Summary

This packet appears to be a client state synchronization or detailed keep-alive message. It is sent periodically during idle gameplay and also with a larger payload during major state transitions, such as using a portal to switch maps.

The packet is schema-driven, and its variable size (e.g., 82 bytes when idle, 104 bytes when changing maps) is due to optional fields or arrays within its schema that are filled based on the context of the action.

## Construction Chain

This packet originates from a different subsystem than the common player-action (`AgCommand`) commands.

1.  **Data Aggregation (`FUN_1412F9D5D`):** A high-level function is called that gathers detailed session and client state information.
2.  **Serialization:** This function calls down into the generic serialization engine (`...FD2A1A` etc.) to build the packet using its schema.
3.  **Sending Mechanism (Buffered Stream):** The packet is written to the main `MsgSendContext` buffer and sent in a batch when `MsgConn::FlushPacketBuffer` is called.

## Schema Information

- **Opcode:** `0x0113`
- **Schema Address (Live):** `0x7FF6E0EE4910`

## Packet Structure

A full analysis of the schema is required to determine the exact field layout. However, based on the variable size and triggers, the structure contains optional blocks that are populated with extra data during events like a map change.

## Live Packet Samples

**Idle State (82 bytes):**
`16:19:47.408 [S] CMSG_UNKNOWN Op:0x0113 | Sz:82 | 13 01 BF CE B6 E2 04 07 AA 9F 0B 8B 05 8B 05 B4 08 E2 05 8C 01 00 AD 14 F0 01 92 24 4A 2E AE 14 F0 01 92 24 4A 2E 00 13 01 EC 89 A5 BA 09 10 50 6E 10 10 00 00 00 01 C9 11 A5 09 00 02 00 00 02 02 AD 14 F0 01 92 24 4A 2E AE 14 F0 01 92 24 4A 2E 00`

**Portal Use (104 bytes):**
`16:22:17.355 [S] CMSG_UNKNOWN Op:0x0113 | Sz:104 | 13 01 FF 8C C8 D5 04 0D F7 23 2B 5B 8F 05 A0 01 9C 01 12 C5 01 10 F6 02 C6 16 92 01 7B AD 14 F0 01 92 24 4A 2E AE 14 F0 01 92 24 4A 2E 00 13 01 F3 E7 AE E7 0C 02 09 00 AD 14 F0 01 92 24 4A 2E AE 14 F0 01 92 24 4A 2E 00 13 01 F3 E7 AE E7 0C 02 0A 07 AD 14 F0 01 92 24 4A 2E AE 14 F0 01 92 24 4A 2E 00 11 00 00 00`