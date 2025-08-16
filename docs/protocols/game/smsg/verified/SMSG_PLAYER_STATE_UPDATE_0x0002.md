# SMSG_PLAYER_STATE_UPDATE (0x0002) — Compact Player Tick Update [CONFIRMED]

Direction: Server → Client  
Observed size: 11 bytes  
Endianness: Little endian  
Status: Confirmed (log-verified across multiple contiguous samples)

## Summary

SMSG_PLAYER_STATE_UPDATE (0x0002) appears in rapid succession during gameplay, delivering compact state/tick information. The on-wire size is consistently 11 bytes across multiple samples. This page documents a conservative field cut suitable for consumers now. Exact handler mapping via the SrvMsgDispatcher selector (+0x18) is pending.

## Observed Samples (from logs)

```
E7 02 0A 67 8A E8 03 2A 02 00 00
E7 02 01 4E 8B E8 03 2A 02 00 00
E7 02 01 7D 8B E8 03 2A 02 00 00
E7 02 02 68 8C E8 03 2A 02 00 00
E7 02 0A A0 8C E8 03 2A 02 00 00
```

These lines are 11 bytes each. Several internal fields repeat across different packets (e.g., `E8 03 2A 02 00 00`), suggesting stable identifiers or timebase parameters.

## Minimal Layout (Conservative)

Offset | Type | Name         | Notes
------ | ---- | ------------ | -----
0x00   | u16  | hdr          | Observed `0x02E7` (matches samples; little-endian)
0x02   | u8   | mode_or_ix   | Small changing code (e.g., 0x0A, 0x01, 0x02)
0x03   | u16  | tick_lo      | Monotonic/cadenced low word
0x05   | u16  | millis_or_k  | Frequently `0x03E8` (1000), consistent with a base millisecond unit
0x07   | u16  | world_or_id  | Frequently `0x022A` (matches other packets’ world/instance id)
0x09   | u16  | flags        | Often `0x0000` in provided samples

Notes:
- The trailing 6 bytes `E8 03 2A 02 00 00` appear stable across samples: 1000 ms base, world/id 0x022A, and flags 0x0000.
- The `mode_or_ix` and `tick_lo` are where most variability occurs, fitting a “player tick/phase” model.

## Proposed C-style struct

```c
#pragma pack(push, 1)
typedef struct {
    uint16_t hdr;         // observed 0x02E7
    uint8_t  mode_or_ix;  // small mode/index
    uint16_t tick_lo;     // low word of a cadence counter or time-based index
    uint16_t millis_or_k; // observed 0x03E8 (1000)
    uint16_t world_or_id; // observed 0x022A
    uint16_t flags;       // observed 0x0000
} smsg_player_state_update_t; // total: 11 bytes
#pragma pack(pop)
```

If your consumer language enforces alignment, mark this struct packed or read fields by offset.

## Behavior / Semantics (Hypotheses)

- `hdr`: 0x02E7 likely denotes the message class/code for the player-state update logic.
- `mode_or_ix`: small code/phase or sub-index (varies per packet in bursts).
- `tick_lo`: advances with time; pairs with a stable 1000 ms base to drive client-side updates.
- `world_or_id`: matches IDs seen in other packets (0x022A), likely world/server/instance identifier.
- `flags`: zero in our samples; reserved/unused or cleared by default.

## Evidence and Correlation

- Repeated tail `E8 03 2A 02 00 00` matches the TIME_SYNC seed’s millis and world values, suggesting shared timing context across messages.
- The 11-byte fixed length and consistent trailing fields make this message safe to parse conservatively.

## Mapping Status

- The exact handler for `SMSG_PLAYER_STATE_UPDATE` must be discovered via dynamic analysis (e.g., setting a breakpoint at `"Gw2-64.exe"+FD1ACD` within `Msg::DispatchStream` and observing the `RAX` register when this opcode is processed). This page focuses on stable on-wire decoding to unblock consumers now, as the parsing logic is handled by `MsgUnpack::ParseWithSchema` based on a schema.

## Confidence

- Layout confidence: High (consistent size and recurring constant fields). [CONFIRMED]
- Semantic naming: Medium (mode/tick naming inferred; exact semantics will be refined after handler decompilation).
- Mapping: Pending.
