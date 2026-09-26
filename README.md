# Daylight

Daylight is an exciting project that delves into the world of Raytracing and Basic Rendering. It aims to provide a playground for learning and experimenting with cutting-edge graphics techniques and other fascinating elements.

### Images Created by Daylight

<img src="https://i.imgur.com/kUBeGrB.png" width="512"/>
<img src="https://i.imgur.com/evDDHYZ.png" width="512"/>

## Getting Started

### Cloning the Repository
To get started, clone the Daylight repository using the following command in your terminal or command prompt:

```bash
git clone "https://github.com/swet-s/Daylight"
```

All other dependencies (GLFW, ImGui, glm, stb_image) are included in `Daylight/vendor`.

### Windows
Prerequisites:

- [Vulkan SDK](https://vulkan.lunarg.com/sdk/home#windows)
- Visual Studio 2022 (or later)
- [premake5](https://premake.github.io/download) available on your `PATH`

To start the app, run `scripts/Setup.bat` (double-click works) to generate the Visual Studio 2022 solution, open `Daylight.sln`, and press **F5**.

### macOS (Apple Silicon)
Prerequisites:

- Xcode Command Line Tools: `xcode-select --install`
- Vulkan (via MoltenVK) and premake5: `brew install vulkan-headers vulkan-loader molten-vk premake`

  Alternatively, install the [LunarG Vulkan SDK](https://vulkan.lunarg.com/sdk/home#mac) and set `VULKAN_SDK` before running setup.

To start the app, run this from the project folder:

```bash
./scripts/Setup.sh release
```

This builds the app and launches it. Other options:

- `./scripts/Setup.sh` builds and runs the `debug` configuration (slower rendering, easier to debug).
- `./scripts/Setup.sh release --no-run` only builds, without launching.
- `dist` is also accepted as a configuration.

Once the setup is complete, you can dive into Daylight's exciting world of Raytracing and Basic Rendering!

## License
This project is licensed under the [MIT License](LICENSE).
