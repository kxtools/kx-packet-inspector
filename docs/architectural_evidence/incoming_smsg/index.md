# Evidence: Incoming (SMSG) Pipeline

The files on this page contain raw decompiled C code snippets for the core components of the incoming (Server-to-Client) message pipeline. These functions represent the generic machinery responsible for receiving, decrypting, deframing, and dispatching messages from the Game Server.

They serve as the primary source evidence for the descriptions of the SMSG pipeline in the main [System Architecture document](../../system-architecture.md).

---

### Core Functions

Below is a summary of the key functions involved in this pipeline.

---

#### `GcGameCmd_HandleGameSrvEncryptCallbackResult.c`
*   **Purpose:** Handles the result of a Game Server Encryption Callback. This function processes the outcome (success or failure) of an operation related to game server encryption, and sets up appropriate state or error messages.

---

#### `GcGameCmd_Handler.c`
*   **Purpose:** A central handler for "Game Commands" (GcGameCmd). It dispatches based on a command ID to various code paths, managing the lifecycle of the GcGameCmd system.

---

#### `GcGameCmd_InitializeState.c`
*   **Purpose:** An initialization or configuration routine for the GcGameCmd system. It sets various global variables to configure the system's internal state, preparing it to receive and process game commands.

---

#### `GcSrv_Dispatch.c`
*   **Purpose:** A top-level dispatcher for "Game Server" (GcSrv) related commands. It processes commands originating from the game server's perspective, which can then lead to various client-side actions.

---

#### `Msg_DispatchStream.c`
*   **Purpose:** The main dispatcher for the Game Server-to-Client (`Gs2c`) message stream. It takes framed messages from the lower-level `MsgConn` system and routes them to the appropriate handlers or parsing functions based on their opcode.

---

#### `MsgConn_BuildArgsFromSchema.c`
*   **Purpose:** A utility function that uses a message schema to parse arguments from a raw packet buffer into a structured format that can be used by handler functions.

---

#### `MsgConn_Dispatch.c`
*   **Purpose:** The main entry point for processing raw incoming network data for the `MsgConn` system. This function sits at the very beginning of the incoming pipeline, handling the raw byte stream and feeding individual messages into `Msg::DispatchStream`.

---

#### `MsgConn_ProcessIncomingRawData.c`
*   **Purpose:** A wrapper or intermediary function for calling `Msg::MsgConn_Dispatch`. It serves as a specific entry point for feeding raw incoming data into the `MsgConn` system.

---

#### `MsgRaw_ClientRecvEncrypt.c`
*   **Purpose:** Handles the initial encrypted packet received from the server during the connection handshake, setting up the client-side decryption state.

---

#### `MsgRaw_RecvInvalid.c`
*   **Purpose:** A generic error reporting function for invalid or malformed incoming messages within the `Msg::Raw` namespace.

---

#### `MsgUnpack_ParseWithSchema.c`
*   **Purpose:** The core "virtual machine" for parsing incoming packets. It reads a message schema and uses it to dynamically unpack the arguments from a raw packet buffer into a data structure.

---

#### `SMSG_DispatchMap_MapSchemaWithInternalID.c`
*   **Purpose:** A function responsible for mapping a message schema to an internal opcode or ID within a dispatch table, preparing it for later lookup by the message dispatcher.

---

#### `SMSG_MasterTable_BuildDispatchMap.c`
*   **Purpose:** A higher-level function that orchestrates the construction of the master dispatch map by registering multiple schemas and their handlers.

---

#### `SMSG_MasterTable_Registration_Entry.c`
*   **Purpose:** The top-level entry point called during client initialization to register all the default SMSG packet handlers and schemas into the master dispatch table.
