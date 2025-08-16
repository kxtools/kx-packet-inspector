# SMSG_SERVER_COMMAND (0x0027)

**Direction:** Server -> Client
**Status:** Confirmed (Container Packet with Subtypes)

## Summary

`SMSG_SERVER_COMMAND` is a container packet used by the server to trigger specific, discrete actions on the client, such as performance checks or ping responses. It operates using a subtype system, where the first field of the payload is a `ushort` that dictates the message's actual purpose.

This packet is handled by a special subtype dispatcher which uses the Subtype ID to look up the correct schema and final handler function from a master dispatch table.

## Dispatch Mechanism

1.  The client receives a packet with opcode `0x0027`.
2.  The main dispatcher routes it to a preliminary handler.
3.  This handler reads the first 2 bytes of the payload to get the **Subtype ID**.
4.  It uses this ID to look up an entry in a master dispatch table (located at `.rdata:018fc8e0` in Ghidra).
5.  This table provides the specific **Schema Address** and **Final Handler Address** for that subtype.
6.  The payload is then parsed using the correct schema, and the final handler is called.

## Discovered Subtypes

### Subtype 0x0003: Performance Trigger

This variant commands the client to measure a graphics performance metric and send it back to the server in a `CMSG_0x0002` packet.

*   **Final Handler:** `SMSG_Handler_Performance_Trigger` (`Gw2-64.exe+23CEA0`)
*   **Schema Address:** `Gw2-64.exe+25700A0`
*   **On-Wire Payload:** `03 00`

**Schema Structure:**
| Field # | Typecode | Type Name | Notes |
| :------ | :------- | :-------- | :---- |
| 0       | `0x01`   | `short`   | The subtype ID, `0x0003`. |

---

### Subtype 0x0004: Ping Response Trigger

This variant commands the client to immediately reply with a `CMSG_0x0006_PING_RESPONSE` packet, echoing back a value provided by the server.

*   **Final Handler:** `SMSG_Handler_PingResponse_Trigger` (`Gw2-64.exe+23CF00`)
*   **Schema Address:** `Gw2-64.exe+25700F0`
*   **On-Wire Payload:** `04 00 [variable-length value]`

**Schema Structure:**
| Field # | Typecode | Type Name        | Notes |
| :------ | :------- | :--------------- | :---- |
| 0       | `0x01`   | `short`          | The subtype ID, `0x0004`. |
| 1       | `0x04`   | `compressed_int` | A value to be echoed back to the server. Parsed as a `uint` by the handler. |