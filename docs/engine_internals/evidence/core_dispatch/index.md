# Evidence: Core Dispatch

This section contains raw decompiled C code snippets related to the core game engine components, high-level dispatchers, and fundamental system handlers.

These functions represent critical parts of the game's internal architecture that are not directly tied to specific network message directions (CMSG/SMSG) but rather manage broader game systems, events, or command processing.

---

### Core Functions

#### `Gw2_Engine_Controls_CtlInstance.c`
*   **Purpose:** A high-level dispatcher for control-related events or commands within the game engine. This function processes specific control command IDs and either delegates their handling to the more general `SystemEventHandler` or handles them directly.

---

#### `SystemEventHandler.c`
*   **Purpose:** A generic, engine-wide event handler that processes a wide variety of system-level commands and events, dispatching them to appropriate subsystems.