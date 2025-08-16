# CMSG_MOVEMENT (0x0012)

**Status:** Confirmed Hybrid (Manual Aggregation + Schema-Driven Serialization)

## Summary

This is the primary packet sent by the client during continuous player movement. It is a high-frequency packet that uses a sophisticated hybrid build process, confirming the existence of a "Fast Path" in the client's serialization engine.

While the packet is ultimately serialized using its full, complex schema, the process is initiated by a high-level "Data Aggregator" function that only provides a small subset of essential data (timestamps, coordinates). The serialization engine (`Msg::MsgPack`) then intelligently processes this minimal data against the full schema, skipping all optional or unprovided fields. This results in the small, efficient 24-byte packet observed in live traffic.

## Construction & Sending

The packet is created via a specialized "Agent Command" pipeline:

1.  **Data Aggregation (`Gw2::Engine::Agent::AgCommand`):** This high-level function gathers the player's current coordinates and state, and hardcodes the opcode value `0x12` into a temporary data structure.
2.  **Virtual Call to Builder (`FUN_141018E00`):** The aggregator makes a virtual call to a generic builder function, passing it the minimal data structure.
3.  **Serialization (`CMSG::BuildAndSendPacket`):** The generic builder calls the main serialization engine, which uses the schema for opcode `0x0012` to build the packet from the provided subset of data.
4.  **Sending Mechanism (Buffered Stream):** The packet is written to the main `MsgSendContext` buffer and sent in a batch when `MsgConn::FlushPacketBuffer` is called.

## Schema Information

- **Opcode:** `0x0012`
- **Schema Address (Live):** `0x7FF6E0EA50B0`

## Packet Structure (Live 24-Byte Variant)

This is the structure observed during normal gameplay. It represents a minimal subset of the full 11-field schema.

| Offset | Size | Name | Notes |
|---|---|---|---|
| 0 | 2 | Opcode | `0x0012` |
| 2 | 6 | Header Data | Timestamps / sequence counters. |
| 8 | 12 | **Position** | **(X, Y, Z coordinates)** |
| 20 | 4 | Trailer Data | Flags or other state. |