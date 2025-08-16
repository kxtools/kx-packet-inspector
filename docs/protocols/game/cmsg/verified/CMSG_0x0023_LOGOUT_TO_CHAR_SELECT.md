# CMSG_LOGOUT_TO_CHAR_SELECT (0x0023)

**Direction**: Client -> Server
**Status**: Confirmed Overloaded Opcode

## Summary

Opcode `0x0023` is used for at least two different purposes, sending completely different payloads depending on the context.

### Variant A: Logout Command (Live-Validated)

When the player logs out to character select, a simple 2-byte packet is sent. This is a manually-built "command" packet.

**Pathway:** Direct Queue (`MsgConn::QueuePacket`)

**Packet Structure (Live):**
| Offset | Type | Name | Value |
|---|---|---|---|
| 0x00 | `uint16` | Opcode | `0x0023` |

### Variant B: Unknown Pointer (Static Analysis)

A different builder function (`FUN_14023C240`) sends a more complex, pointer-based payload using the same opcode. This variant's purpose and structure are unconfirmed by live traffic.