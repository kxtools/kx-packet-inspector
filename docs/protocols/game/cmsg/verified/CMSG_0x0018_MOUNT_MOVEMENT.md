# CMSG 0x0018 — MOUNT_MOVEMENT

Status: Confirmed. This opcode has multiple variants.

## Summary

CMSG `0x0018` is sent for mount movement, but there are at least two different variants of this packet sent under different conditions.

### Variant A: Schema-Defined

The CMSG-to-Schema resolution table defines a complex, 11-field structure for this opcode, containing detailed information including position and rotation.

- **Schema Address (Live):** `0x7FF6E0EA61F0`

#### Packet Structure (Schema-Defined)

| Field Order | Type | Name | Notes |
|---|---|---|---|
| 1 | `short` | field_0 | Typecode: 0x01. Likely sequence number. |
| 2 | Compressed `int` | field_1 | Typecode: 0x04. Likely timestamp. |
| 3 | **`float[4]`** | **Rotation** | Typecode: 0x0A. Likely a quaternion. |
| 4 | **`float[3]`** | **Position** | Typecode: 0x08. (X, Y, Z coordinates). |
| 5 | `short` | field_4 | Typecode: 0x03. |
| 6 | `byte` | field_5 | Typecode: 0x02. Likely status flags. |
| 7 | Compressed `int` | field_6 | Typecode: 0x04. |
| 8 | Small Buffer | field_7 | Typecode: 0x14. |
| 9 | Optional Block | field_8 | Typecode: 0x0F. |
| 10 | `short` | field_9 | Typecode: 0x01. |
| 11 | Compressed `int` | field_10 | Typecode: 0x04. |

### Variant B: Manually-Built (Live Log)

Live logs show a different, large (180-byte) packet for mount movement. This variant is likely built by a specialized function that bypasses the schema system.

**Log Entry:**
`18:49:21.214 [S] CMSG_MOUNT_MOVEMENT Op:0x0018 | Sz:180 | 18 00 B7 0D ...`

**Note:**
Initial analysis pointed to an emitter function `CMSG_Build_0x0018_FromObj103C`, but live testing has proven this function is not responsible for the observed mount movement packets. The true builder function is currently unknown.

## Confidence

- Opcode: High
- Name: High
- Structure: High (Multiple variants confirmed)
