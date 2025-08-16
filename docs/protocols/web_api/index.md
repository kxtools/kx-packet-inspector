# The Web API Protocol

This protocol governs the communication between the native C++ game client and the embedded web browser's JavaScript environment. It is used for all web-based UI, including the Trading Post and Gem Store.

The functions registered here create a bridge, allowing JavaScript to call back into the game's C++ code to request information or perform actions.