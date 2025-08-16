# Evidence: Reflection System

This section contains raw decompiled C code snippets that serve as direct evidence for the `hkReflect` runtime reflection system used by the game engine.

---

### Core Functions

#### `Reflect_TypeDecoder.c`
*   **Purpose:** The core "virtual machine" of the reflection system. It decodes a type's blueprint and dispatches to the appropriate handlers to perform operations like copying or initialization.

#### `Reflect_FieldInitDispatcher.c`
*   **Purpose:** Dispatches to the correct member handler to initialize a field based on its reflection blueprint.

#### `Reflect_MemberHandler.c`
*   **Purpose:** A generic handler that processes a member of a class, applying a given operation (like initialization) to it, potentially recursively for complex types.

#### `Reflect_GetMemberHandler.c`
*   **Purpose:** Retrieves the appropriate handler function (e.g., for copying, initialization) for a specific class member from its blueprint.

#### `Reflect_FindBlueprint.c`
*   **Purpose:** Finds the reflection blueprint (class definition) for a given type tag or ID.

#### `Reflect_GenericCopyDispatcher.c` & `Reflect_MemmoveDispatcher.c`
*   **Purpose:** Low-level, highly optimized functions that copy or move blocks of data. They are the workhorses that perform the actual memory manipulation for the reflection system, with special cases for different data sizes.

#### `Reflect_CopyFunction.c` & `Reflect_ArrayCopyHelper.c`
*   **Purpose:** Higher-level helper functions that use the underlying dispatchers to copy specific types or arrays of types.
