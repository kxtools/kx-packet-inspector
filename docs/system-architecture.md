# System Architecture: Network Message Processing

## High-Level Model: The Three-Server Architecture

The Guild Wars 2 client does not connect to a single monolithic server. Instead, it maintains simultaneous, specialized connections to **three distinct backend server systems**, each with its own dedicated protocol.

This documentation is organized to reflect this architecture. For detailed information on each protocol, please see the dedicated sections below.

### 1. Game Server (`gs2c`/`c2gs`) - **[Primary Focus]**
*   **Purpose:** Handles all real-time, in-world gameplay interactions, including movement, combat, and agent synchronization.
*   **[➤ View Game Server Protocol Details](./protocols/game/)**

### 2. Platform / Portal Server (`ps2c`/`c2ps`)
*   **Purpose:** Manages all account-level services, social features, and commercial interactions (Trading Post, Gem Store).
*   **[➤ View Platform/Portal Protocol Details](./protocols/portal/)**

### 3. Login Server (`ls2c`/`c2ls`)
*   **Purpose:** Handles initial client authentication, account validation, and character selection. This connection is short-lived.
*   **[➤ View Login Protocol Details](./protocols/login/)**

---
## Core Concepts & Game Internals
Before diving into the protocol details, it is helpful to understand some core concepts about how the game functions.

*   **[➤ View Core Game Concepts](./concepts/game-concepts.md)**
*   **[➤ View Coordinate Systems & Units](./concepts/coordinate-systems.md)**