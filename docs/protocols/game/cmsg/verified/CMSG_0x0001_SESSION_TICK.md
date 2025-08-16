# CMSG_0x0001_SESSION_TICK

**Direction**: Client -> Server
**Status**: Confirmed Overloaded Opcode

## Summary

This opcode is overloaded. The most commonly observed variant is a simple, 6-byte packet that appears to function as a session tick or keep-alive. It is sent periodically during idle gameplay and also during state transitions like using a portal. This variant is manually built by a dedicated function.

A much more complex, 10-field schema also exists for this opcode, but it has not been observed in common live traffic.

### Variant A: Session Tick (Live-Validated)

**Status:** Confirmed via live traffic and builder analysis.

**Construction:**
- **Builder Function:** `FUN_14023D765`
- **Pathway:** Manually built and written to the buffered stream.

**Packet Structure (Live):**
| Offset | Size | Data Type (Inferred) | Description |
|---|---|---|---|
| 0x00 | 2 | `ushort` | The opcode `0x0001`. |
| 0x02 | 4 | `uint` | A timestamp or sequence counter that increments over time. |

**Live Packet Sample:**
`18:41:11.483 [S] CMSG_UNKNOWN_0x0001 Op:0x0001 | Sz:6 | 01 00 FF 85 E2 07`

### Variant B: Unknown Complex Packet (Schema-Only)

**Status:** Unverified. This variant has not been observed in live traffic.

**Schema Information:**
- **Opcode:** `0x0001`
- **Schema Address (Live):** `0x7FF6E0E9FCF0`

**Structure:** A complex 10-field schema. See `unverified/CMSG_0x0001.md` for details.