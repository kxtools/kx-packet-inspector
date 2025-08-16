# The Platform / Portal Server Protocol (`ps2c`/`c2ps`)

**Status:** Confirmed (Static Analysis of Dispatcher)

## Summary

The "Portal" system is the **Application Layer** responsible for handling all Platform Server (`ps2c`) messages. This includes account-wide services, social features (chat, guilds, friends), and commercial interactions (trading post, gem store). This is also sometimes referred to as the **Secure Token Server (STS)**.

Crucially, these `ps2c` messages are **tunneled through the main Game Server (`gs2c`) connection**. The `Portal::DispatchMessage` function is the central hub that receives these tunneled messages from the low-level network layer and routes them to the appropriate application logic.

For a full analysis of this system's discovery, see the [Portal Dispatch Analysis playbook](../../methodologies/discovery_playbooks/portal-dispatch-analysis.md).

## Architectural Role: The Post-Networking Application Layer

1.  **The Networking Layer (`Msg::DispatchStream`):** This low-level function receives the raw `gs2c` byte stream. For all Portal-related opcodes, it looks up the registered handler and finds that it points to a single function: `Portal::DynamicHandler_Entry`.

2.  **The Hand-off (`Portal::DynamicHandler_Entry`):** The main dispatcher calls [`Portal::DynamicHandler_Entry`](./evidence/Portal_DynamicHandler_Entry.c) via a dynamic `CALL RAX`. This is the hand-off from the Networking Layer to the Portal Application Layer.

3.  **The Application Layer (`Portal::DispatchMessage`):** This is the core of the Portal system. It receives the clean message and contains a massive `switch` statement that looks at the message's opcode. It then calls the final logic function (e.g., `PlManager`, `PlChannel`, `PlCliGemVault`) to actually perform the work.

## Key Functions & Evidence

The primary evidence for this architecture is the call chain and the large `switch` statement within the final dispatcher.

*   **The Dispatch Chain:**
    *   [`Msg::DispatchStream`](../../architectural_evidence/incoming_smsg/Msg_DispatchStream.c)
    *   [`Portal::DynamicHandler_Entry`](./evidence/Portal_DynamicHandler_Entry.c)
    *   [`Portal::DispatchMessage`](./evidence/Portal_DispatchMessage.c) (Contains the master `switch` statement for all Portal packets)

*   **Connection Initialization & Routing:**
    *   [`PortalCli_Startup.c`](./evidence/PortalCli_Startup.c)
    *   [`PortalCli_Auth.c`](./evidence/PortalCli_Auth.c)
    *   [`GcPortal_Router.c`](./evidence/GcPortal_Router.c)