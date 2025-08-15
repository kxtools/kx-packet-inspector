# Architectural Evidence: The Network Pipeline

This directory contains raw decompiled C code for the most critical, foundational components of the Guild Wars 2 network message processing pipeline.

Unlike evidence for specific packets, the files here represent the generic, reusable "machinery" that builds, sends, receives, and dispatches **all** network messages. They serve as the primary source evidence for the diagrams and descriptions in the main [System Architecture](../system-architecture.md) document.

*   `./incoming_smsg/`: The core pipeline for receiving and processing messages from the server.
*   `./outgoing_cmsg/`: The core pipeline for building and sending messages to the server.