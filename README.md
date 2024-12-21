
# Tulip

**Tulip** is a comprehensive C++ game engine designed for high performance and modularity. It integrates various subsystems such as rendering, audio, physics, input handling, scripting, AI, networking, and tools, all managed under the Bazel build system.

## Table of Contents

1. [Features](#features)
2. [Directory Structure](#directory-structure)
3. [Prerequisites](#prerequisites)
4. [Setup and Installation](#setup-and-installation)
5. [Building the Project](#building-the-project)
6. [Running Tulip](#running-tulip)
7. [Third-Party Libraries](#third-party-libraries)
8. [Contributing](#contributing)
9. [License](#license)

## Features

- **Rendering:** OpenGL-based rendering pipeline with support for shaders, meshes, materials, and scenes.
- **Audio:** FMOD integration for audio playback and management.
- **Physics:** Bullet Physics for realistic physics simulations.
- **Input Handling:** SDL2 for robust input and window management.
- **Scripting:** Lua integration for dynamic scripting capabilities.
- **AI:** Basic AI systems for entity behavior.
- **Networking:** ENet-based networking for client-server communication.
- **Tools:** In-game level editor for designing and managing game levels.
- **Entity-Component-System (ECS):** Flexible ECS architecture for managing game entities and their behaviors.
- **Resource Management:** Efficient resource loading and management system.

## Prerequisites

- **Bazel:** Ensure Bazel is installed on your system. Follow the [official installation guide](https://bazel.build/install) for your operating system.
- **C++ Compiler:** A modern C++ compiler supporting C++17 or later (e.g., GCC, Clang, MSVC).
- **Third-Party Libraries:** Tulip uses several third-party libraries which should be placed in the `third_party/` directory.

## Setup and Installation

1. **Clone the Repository:**

   ```bash
   git clone https://github.com/crrapi/tulip-engine.git
   cd tulip
   ```

2. **Add Third-Party Libraries:**

   Download and place the required third-party libraries into the `third_party/` directory:

   - **SDL2:** [https://www.libsdl.org/](https://www.libsdl.org/)
   - **Bullet Physics:** [https://pybullet.org/wordpress/](https://pybullet.org/wordpress/)
   - **FMOD:** [https://www.fmod.com/](https://www.fmod.com/)
   - **ENet:** [http://enet.bespin.org/](http://enet.bespin.org/)
   - **Lua:** [https://www.lua.org/](https://www.lua.org/)

   Ensure each library has its corresponding `BUILD` file within its directory or is referenced correctly in the top-level `third_party/BUILD`.

## Building the Project

From the root directory of the project, execute the following command to build **Tulip**:

```bash
bazel build //src/main:game_app
```

This command compiles all necessary components and generates the executable.

## Running Tulip

After a successful build, run the game application using:

```bash
bazel run //src/main:game_app
```

This will launch the Tulip Engine, initializing all subsystems and opening the main game window.

## Third-Party Libraries

**Tulip** leverages several third-party libraries to provide rich functionality:

- **SDL2:** Handles window creation, input, and OpenGL context management.
- **Bullet Physics:** Provides physics simulation capabilities.
- **FMOD:** Manages audio playback and audio-related features.
- **ENet:** Facilitates reliable networking for client-server communication.
- **Lua:** Enables scripting support for dynamic game behavior.

Ensure that all dependencies are correctly integrated and referenced in the Bazel build configurations.

## Contributing

Contributions are welcome! Please follow these steps:

1. **Fork the Repository.**
2. **Create a Feature Branch:**

   ```bash
   git checkout -b feature/YourFeature
   ```

3. **Commit Your Changes:**

   ```bash
   git commit -m "Add your feature"
   ```

4. **Push to the Branch:**

   ```bash
   git push origin feature/YourFeature
   ```

5. **Open a Pull Request.**

Please ensure your code adheres to the project's coding standards and includes appropriate documentation.