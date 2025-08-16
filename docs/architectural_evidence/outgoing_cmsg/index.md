# Evidence: Outgoing (CMSG) Pipeline

This section contains raw decompiled C code snippets for the core components of the outgoing (Client-to-Server) message pipeline. These functions represent the generic machinery responsible for building, serializing, and sending messages to the Game Server.

They serve as the primary source evidence for the descriptions of the CMSG pipeline in the main [System Architecture document](../../system-architecture.md).

---

### Core Functions

Below is a summary of the key functions involved in this pipeline.

---

#### `CMSG_BuildAndSendPacket.c`
*   **Purpose:** The final function in the CMSG pipeline. It takes a data structure and a corresponding schema, serializes the data into a packet, and queues it to be sent to the server.

---

#### `CMSG_Builder_FromAggregatedData.c`
*   **Purpose:** A wrapper function that receives aggregated player action data (e.g., for a skill use or movement) and passes it to the generic, schema-driven packet builder, `CMSG::BuildAndSendPacket`.

---

#### `Msg_MsgPack.c`
*   **Purpose:** The core serialization engine, formerly known as `MsgBuilder_ProcessSchema`. This function iterates through a message schema to correctly pack data from a C++ struct into the raw packet buffer.

---

#### `Msg_WriteDataToBuffer.c`
*   **Purpose:** A low-level utility function to write a block of raw data into the outgoing packet buffer, flushing the buffer if it becomes full.

---

#### `MsgConn_BuildPacketFromSchema.c`
*   **Purpose:** A utility function that uses a message schema to build a complete packet from a given data structure, handling buffer allocation and serialization.

---

#### `MsgConn_EnqueuePacket.c`
*   **Purpose:** Enqueues a fully constructed packet into the outgoing send queue to be sent to the server during the next buffer flush.

---

#### `MsgConn_FlushPacketBuffer.c`
*   **Purpose:** Flushes the main outgoing packet buffer, sending all queued gameplay-related packets to the server in a batch.

---

#### `MsgConn_QueuePacket.c`
*   **Purpose:** A higher-level function to queue an outgoing packet. This is often used for simpler, out-of-band system commands that bypass the main buffered stream.

---

#### `MsgConn_WriteCompressedInt.c`
*   **Purpose:** A utility function to serialize a variable-length compressed integer into the outgoing packet buffer, which is a common data type in the protocol.
