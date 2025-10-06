
# Tulip

**Tulip** is a small, modular C++ game engine built with Bazel. This branch focuses on a minimal, working workflow: SDL2 windowing/input and OpenGL rendering (a sample triangle), with ECS and core utilities.

## Table of Contents

1. [Features](#features)
2. [Directory Structure](#directory-structure)
3. [Prerequisites](#prerequisites)
4. [Quick Start (macOS)](#quick-start-macos)
5. [Building](#building)
6. [Running](#running)
7. [Notes](#notes)
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

- **Bazel:** Install via the [official guide](https://bazel.build/install).
- **C++ Compiler:** C++17-capable (Clang on macOS).
- **SDL2:** Use Homebrew on macOS: `brew install sdl2`.

## Quick Start (macOS)

```bash
git clone https://github.com/crrapi/tulip-engine.git
cd tulip-engine
# Ensure SDL2 is installed
brew install sdl2

# Build and run
bazel run //src/main:game_app
```

## Building

```bash
bazel build //src/main:game_app
```

## Running

```bash
bazel run //src/main:game_app
```

You should see an SDL2 window rendering a colored triangle. Press `Esc` or close the window to quit.

## Notes

- This configuration removes heavy optional subsystems (audio, physics, networking, scripting, editor) to keep the sample runnable. They can be reintroduced later.
- On macOS we link `OpenGL.framework`; on Linux we link `-lGL`. Adjust as needed for your platform.

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
