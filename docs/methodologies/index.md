# Reverse Engineering Methodologies

This section contains detailed documentation on the methodologies and workflows used for reverse engineering the Guild Wars 2 client, particularly focusing on network packet analysis and client internals.

## Core Techniques

These documents describe foundational techniques that apply across various reverse engineering tasks.

*   **[Discovery Playbooks](./discovery_playbooks/):** A collection of step-by-step guides for discovering and analyzing the three core network protocols (Login, Platform, and Game).
*   **[Hooking Implementation](./hooking-implementation.md):** Describes the practical implementation of the packet hooking mechanism used by the KX Packet Inspector.
*   **[Function Naming from Assert Strings](./function-naming-from-assert-strings.md):** A powerful methodology for recovering original function names by analyzing debug assertion strings.
*   **[Memory Correlation Workflow](./memory-correlation-workflow.md):** A foundational technique for deducing packet structures by correlating live memory values with captured packet data.

These documents are crucial for understanding the approach taken in this project and for replicating or extending the research.
