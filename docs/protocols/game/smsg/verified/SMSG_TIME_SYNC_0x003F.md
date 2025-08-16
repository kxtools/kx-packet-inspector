# SMSG_TIME_SYNC (0x003F)

**Direction:** Server -> Client
**Status:** Confirmed (Generic Path with Multiple Dynamic Handlers)

## Summary

`SMSG_TIME_SYNC` is a high-frequency packet responsible for synchronizing the client's internal timers with the server's master clock. It is a critical component for ensuring consistent game state and event timing.

Live analysis has confirmed that this packet is handled by the **generic dispatch system**. Crucially, the game dynamically switches between at least **two different handler functions** for this single opcode, strongly suggesting each handler is responsible for a different variant of the packet. This aligns with the two observed payload structures: a "Cadence/Tick" variant for continuous updates and a "Seed/Epoch" variant for state initialization.

## Dynamic Handlers & Dispatch

Unlike a "Fast Path" packet, `SMSG_TIME_SYNC` is processed through the standard pipeline that ends in a `call rax` dynamic dispatch. The specific handler loaded into the `RAX` register changes depending on the game's context (e.g., normal gameplay vs. map loading).

**Discovered Handlers:**

| Handler Address (RVA) | Likely Purpose (Hypothesized) |
| :-------------------- | :------------------------------ |
| `Gw2-64.exe+99DFC0`     | "Cadence/Tick" variant handler  |
| `Gw2-64.exe+99DF50`     | "Seed/Epoch" variant handler    |

## Payload Variants

### Variant A: Cadence/Tick (Handler: `...99DFC0`)

This variant is sent periodically during normal gameplay to provide a continuous time-sync signal.

**Live Packet Sample:**
`0F 05 88 B7 7F 09 88 B9 0E 00`

**Inferred Structure:**
| Offset | Type   | Name         | Notes |
| ------ | ------ | ------------ | ----- |
| 0x00   | u16    | Subtype      | Always `0x050F`. |
| 0x02   | u32    | `time_lo`      | Monotonically increasing low part of a 48-bit timestamp. |
| 0x06   | u16    | `time_hi`      | High part of the timestamp. |
| 0x08   | u16    | `flags_or_id`  | A low-variability field, purpose unknown. |

### Variant B: Seed/Epoch (Handler: `...99DF50`)

This variant is sent in a burst to initialize the client's clock to a new "epoch" when joining a new map or instance.

**Live Packet Sample:**
`0D 05 4A 8A E8 03 2A 02 00 00`

**Inferred Structure:**
| Offset | Type   | Name         | Notes |
| ------ | ------ | ------------ | ----- |
| 0x00   | u16    | Subtype      | Always `0x050D`. |
| 0x02   | u16    | `seed`         | A seed value for the new time epoch. |
| 0x04   | u16    | `millis_base`  | Observed as `0x03E8` (1000), likely a millisecond base unit. |
| 0x06   | u16    | `world_or_id`  | An ID for the current world or instance. |
| 0x08   | u16    | `flags`        | Observed as `0x0000`. |

## Evidence

The existence and addresses of the multiple dynamic handlers were confirmed using a live C++ message hook (`MessageHandlerHook.cpp`). The hook intercepts calls within the main dispatcher and logs the opcode and the address of the handler function in the `RAX` register.

**Live Log Snippet:**
```
[Packet Discovery] Opcode: 0x003F -> Handler: Gw2-64.exe+000000000099DFC0
[Packet Discovery] Opcode: 0x003F -> Handler: Gw2-64.exe+000000000099DF50
[Packet Discovery] Opcode: 0x003F -> Handler: Gw2-64.exe+000000000099DF50
[Packet Discovery] Opcode: 0x003F -> Handler: Gw2-64.exe+000000000099DFC0
```

This log provides definitive proof of the two distinct handlers being used for this opcode.

## Confidence

*   **Packet Identity:** High.
*   **Architectural Flow:** High (Confirmed via live C++ hook logs).
*   **Payload Structures:** High (Inferred from consistent live data).
