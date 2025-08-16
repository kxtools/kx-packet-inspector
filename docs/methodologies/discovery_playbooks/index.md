# Discovery Playbooks

This directory contains a collection of step-by-step guides for discovering and analyzing the three core network protocols used by the Guild Wars 2 client.

## Protocol Analysis Guides

*   **[Login Protocol Analysis](./login-protocol-analysis.md)**: A detailed guide to the initial authentication and character selection protocol (`ls2c`/`c2ls`).
*   **[Platform (Portal) Protocol Analysis](./portal-dispatch-analysis.md)**: A guide to the application-layer protocol (`ps2c`/`c2ps`) that handles account-wide services, social features, and the trading post.
*   **[CMSG Packet Discovery Playbook](./cmsg-parser-discovery-playbook.md)**: A repeatable method for discovering Client-to-Server (`c2gs`) packet structures using a static-first approach.
*   **[SMSG Packet Discovery Playbook](./smsg-parser-discovery-playbook.md)**: A repeatable method for discovering Server-to-Client (`gs2c`) packet structures based on dynamic analysis.
