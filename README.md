# Oh My Graphics Library
Idk really if it will be a library or a standalone.\
The idea is to make a performant and well optimized wrapper for OpenGL to load complex, modern and "realistic" 3D scenes. And of course display them.

# Roadmap
Might change too.
- [ ] Basics.
  - [x] Pushing the project.(I want something to be ticked lol)
  - [ ] Setting up the basics.
  - [ ] An OpenGL context.
  - [ ] Handling models.
  - [ ] Rendering basic shapes with shaders.
  - [ ] Loading models and rendering them.
  - [ ] Basic lighting.
  - [ ] Loading UVs and rendering them.
- [ ] Improved lighting.
- [ ] Advanced shading to prepare for next step.
  - [ ] Specular highlighting.
  - [ ] Metalic shaders.
  - [ ] Sheen.
  - [ ] Sub-surface scattering, a cool one.
- [ ] Writing shaders for more complex things.
  - [ ] Good ol' bump maps.
  - [ ] Normals.
  - [ ] Specular maps.
- [ ] Extras.
  - [ ] Font rendering. For now monospaced.


# Making on Linux for Windows

use `cmake` with the `toolchains/unix-win32.cmake` toolchain. In a nutshell:
```sh
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=toolchains/unix-win32.cmake ..
make
```
