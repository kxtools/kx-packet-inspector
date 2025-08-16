# CMSG_0x0100_CHAT_MESSAGE

**Direction**: Client -> Server
**Status**: Confirmed (Schema-Driven, Live-Validated)

## Summary

This packet is sent by the client to send a chat message to the server. It is a schema-driven packet with a variable size payload that depends on the length of the message being sent. The packet's structure contains the message text, the target channel ID, and other metadata.

## Construction Chain

This packet originates from the UI command pipeline, which is distinct from the player-action (`AgCommand`) pipeline.

1.  **Context Creation (`Gw2::Game::Chat::Cli::CtCliContext`):** The top-level handler, documented in [`CMSG_Chat_Cli_CtCliContext.c`](./evidence/CMSG_Chat_Cli_CtCliContext.c), is called when the user sends a message. It gathers the message text and channel ID.
2.  **Serialization (`Gw2::Services::Msg::Msg`):** The context function then calls a helper function that passes the data down to the generic serialization engine to be built using the schema for opcode `0x0100`.
3.  **Sending Mechanism (Buffered Stream):** The packet is written to the main `MsgSendContext` buffer and sent in a batch when `MsgConn::FlushPacketBuffer` is called.

## Schema Information

- **Opcode:** `0x0100`
- **Schema Address (Live):** `0x7FF6E0ED1590`

## Packet Structure (from Live Analysis and Schema)

The structure is composed of the message text followed by a trailer containing metadata.

| Field | Data Type (Inferred) | Description |
|---|---|---|
| Message Text | `wchar_t[]` (UTF-16LE) | The chat message text, null-terminated. The variable length of this field is the primary reason for the packet's variable size. |
| Channel ID | `byte` | An ID representing the target chat channel (e.g., `0x23` for Say, `0x24` for Map). |
| Target Info | `int` | Unknown purpose. Often `0xFFFFFFFF`, which may indicate no specific player is being targeted (e.g., for whispers). |
| Flags/Padding | `short` | Unknown purpose. |

**Live Packet Example ("test" on "say" channel):**
`16:28:43.895 [S] CMSG_UNKNOWN Op:0x0100 | Sz:19 | 00 01 74 00 65 00 73 00 74 00 00 00 23 FF FF FF FF 0F 00`
- `00 01`: Opcode `0x0100`
- `74 00 ... 00 00`: UTF-16LE for "test"
- `23`: Channel ID for "Say"
- `FF FF FF FF`: Target Info
- `0F 00`: Flags/Padding