# CMSG 0x0002 — Unknown / Performance Response (Confirmed Overloaded)

**Status:** Confirmed Overloaded Opcode

## Summary

`CMSG 0x0002` is a multi-purpose opcode. Live traffic shows a simple, periodic 3-byte packet. Static analysis has proven the existence of a more complex, 6-byte, schema-driven packet that functions as a direct response to a server command.

### Variant A: Simple Periodic Packet (Live-Validated)

This variant is observed being sent periodically during normal gameplay. Its exact purpose is unknown, but its regularity suggests a simple heartbeat or state check. The builder for this specific variant has not yet been located.

**Status:** Confirmed via live traffic.

**Log Entries:**
```
16:00:48.609 [S] CMSG_UNKNOWN Op:0x0002 | Sz:3 | 02 00 10
16:00:58.504 [S] CMSG_UNKNOWN Op:0x0002 | Sz:3 | 02 00 10
```

**Packet Structure (Live):**
| Offset | Type | Value | Notes |
|---|---|---|---|
| 0x00 | `ushort` | `0x0002`| Opcode echo. |
| 0x02 | `byte` | `0x10` | A constant value. |

### Variant B: Performance Response (Builder Confirmed)

This variant is a schema-driven, 6-byte packet that the client sends back to the server after receiving a specific server command.

**Status:** Confirmed via static analysis of the builder and trigger mechanism.

**Trigger:**
This packet is built and sent by the function `SMSG_Handler_Performance_Trigger` immediately after the client receives `SMSG_SERVER_COMMAND (0x0027)` with subtype `0x0003`.

**Purpose:**
The client's handler function calls an internal `GrPerf::GetCounterValue` function to get a performance metric (likely related to frame rate) and sends this value back to the server. This is a server-initiated performance monitoring handshake.

**Construction:**
- **Builder Function:** `SMSG_Handler_Performance_Trigger`
- **Serialization:** `CMSG::BuildAndSendPacket` (Schema-Driven)
- **Schema Address (Live):** `0x7FF6E0E9FD40`

**Packet Structure (from Schema and Builder Analysis):**
The payload is 6 bytes. Based on the builder logic, it contains the opcode and the 4-byte performance metric.
| Offset | Type | Name | Notes |
|---|---|---|---|
| 0x00 | `ushort` | opcode_echo | `0x0002` |
| 0x02 | `uint32` | performance_value | The calculated performance counter value. |
