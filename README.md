# Oh My Graphics Library
Idk really if it will be a library or a standalone.\
The idea is to make a performant and well optimized wrapper for OpenGL to load complex, modern and "realistic" 3D scenes. And of course display them.

# Roadmap
Might change too.
- [ ] Basics.
  - [x] Pushing the project.(I want something to be ticked lol)
  - [x] Setting up the basics.
  - [x] An OpenGL context.
  - [x] Rendering loop.
  - [ ] Handling hard-coded models.
  - [ ] Rendering said hard-coded models with shaders.
  - [ ] Loading model files and rendering them.
  - [ ] Basic lighting.
  - [ ] Loading UVs and rendering them.
- [ ] Advanced multi-source lighting.
- [ ] Camera for viewing.
- [ ] Advanced shading to prepare for next step.
  - [ ] Specular highlighting.
  - [ ] Metalic shaders.
  - [ ] Sheen.
  - [ ] Sub-surface scattering, a cool one.
- [ ] Writing shaders for more complex maps.
  - [ ] Good ol' bump maps.
  - [ ] Normal maps.
  - [ ] Specular maps.
- [ ] Rigging.
- [ ] Animation?
- [ ] Extras.
  - [ ] Implement for Linux, not that complex.
  - [ ] Font rendering. For now monospaced.
  - [ ] Using the new font renderer to render useful info.

# Basic making
Your usual:
```sh
mkdir build
cd build
cmake ..
make
```

# Making on Linux for Windows
use `cmake` with the `toolchains/unix-win32.cmake` toolchain. In a nutshell:
```sh
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=toolchains/unix-win32.cmake ..
make
```
