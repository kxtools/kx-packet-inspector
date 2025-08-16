# Evidence: Core Event System

These files contain the core functions for the game's internal event queuing and dispatching system. This is a generic, engine-wide system used by many components, including the network pipeline.

---

### Core Functions

#### `Event_Dispatcher_ProcessEvent.c`
*   **Purpose:** Dispatches a queued event to its corresponding handler. It looks up the handler in a dispatch table using the event ID and executes it.

---

#### `Event_Factory_QueueEvent.c`
*   **Purpose:** A factory function used to create and queue a new event for later processing by the event dispatcher. It takes the event details, allocates memory for it, and places it in the appropriate queue.
