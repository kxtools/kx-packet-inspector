# The Login Server Protocol (`ls2c`/`c2ls`)

**Status:** Confirmed (Static Analysis of Builders)

## Summary

This document details the architecture of the **Login Server protocol**. This is the initial, short-lived connection the Guild Wars 2 client makes upon startup to handle account authentication, character selection, and the hand-off to the persistent Game and Platform servers.

The system is managed by a high-level API (`GcApi`) which orchestrates a series of authentication commands (`GcAuthCmd`) that are sent to the server.

For a full analysis of this system's discovery, see the [Login Protocol Analysis playbook](../../methodologies/discovery_playbooks/login-protocol-analysis.md).

## Architectural Role: The First Contact

The Login Protocol is the first of the three major network systems the client interacts with. Its lifecycle is as follows:

1.  **Connection:** The client connects to the Login Server.
2.  **Authentication:** The client and server exchange a series of packets, managed by `GcApi` and built by the various `GcAuthCmd` functions.
3.  **Character Info:** The server sends character list data.
4.  **Hand-off:** Upon successful character selection, the Login Server sends a final command that contains the network coordinates for the specific Game Server and Platform Server that the client should connect to for the gameplay session.
5.  **Disconnect:** The client disconnects from the Login Server.

## Key Components & Evidence

The primary evidence for this protocol is the state machine and the large number of dedicated packet builder functions found in the client.

*   **The State Machine (`GcApi`):**
    *   **Evidence:** [`GcApi_StateMachine.c`](./evidence/GcApi_StateMachine.c)
    *   **Role:** This is the master controller for the login connection's lifecycle. It operates as a state machine, orchestrating the entire authentication process from start to finish.

*   **The Packet Builders (`GcAuthCmd`):**
    *   **Evidence:** [`GcAuthCmd_PacketBuilders.c`](./evidence/GcAuthCmd_PacketBuilders.c)
    *   **Role:** This is a collection of dozens of small, single-purpose functions. Each function is responsible for building and sending one specific Client-to-Login-Server (`c2ls`) packet. Analyzing these functions allows for the reverse-engineering of the entire authentication sequence.