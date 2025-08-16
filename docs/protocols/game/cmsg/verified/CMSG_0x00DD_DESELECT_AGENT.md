# CMSG_0x00DD_DESELECT_AGENT

**Direction**: Client -> Server
**Status**: Confirmed (Live-Validated), Builder Unknown

## Summary

This packet is sent by the client when the player deselects their current target. It is a very simple, fixed-size command packet.

## Construction

This packet is a manually-built "Fast Path" command, not created through the complex aggregator pipeline.

- **Builder Function:** `FUN_141241A1B`
- **Serialization:** The builder manually creates the 3-byte payload and calls a low-level write primitive to place it in the send buffer.
- **Sending Mechanism:** Buffered Stream.

## Schema Information

- **Opcode:** `0x00DD`
- **Schema Address (Live):** `0x7FF6E0EB1BB0`

## Packet Structure (Live-Validated)

The packet is a fixed 3 bytes.

| Offset | Size | Data Type (Inferred) | Value |
|---|---|---|---|
| 0x00 | 2 | `ushort` | The opcode `0x00DD`. |
| 0x02 | 1 | `byte` | A constant null byte (`0x00`). |

**Live Packet Sample (Deselecting a target):**
`16:53:16.152 [S] CMSG_DESELECT_AGENT Op:0x00DD | Sz:3 | DD 00 00`