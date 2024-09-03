// This header gives you all you need to interface with the OpenGL implementation and drivers.
#pragma once

#include <GL/gl.h>
#include <GL/glext.h>

#include "Exception.hpp"

// #ifdef _WIN32
//   typedef void* OMGLContext;
// #else
//   #error Gotta define it based on the system API.
// #endif

// void omglCreateContext();
// void omglMakeCurrent(omgl::Context&);
// void omglGetCurrentContext();
// void omglDestroyContext();
// void omglSwapBuffers();

// WILL NOT WORK WITHOUT CONTEXT!
// If a function fails to load nullptr is returned. Up to the caller to decide what to do with that.
void* omglGetProcAddress(const char* str) noexcept;
// WILL NOT WORK WITHOUT CONTEXT!
// Loads all the functions present in this here header. Throws an omgl::SystemException if a function failed to load, the code variable is irrelevant.
void omglGetAllProcAddresses();

#ifdef _OMGL_SOURCE
  #define EXTERN 
#else
  #define EXTERN extern
#endif

EXTERN PFNGLBUFFERDATAPROC glBufferData;
EXTERN PFNGLGENBUFFERSPROC glGenBuffers;
EXTERN PFNGLBINDBUFFERPROC glBindBuffer;

EXTERN PFNGLCREATESHADERPROC glCreateShader;
EXTERN PFNGLSHADERSOURCEPROC glShaderSource;
EXTERN PFNGLCOMPILESHADERPROC glCompileShader;
EXTERN PFNGLGETSHADERIVPROC glGetShaderiv;
EXTERN PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
EXTERN PFNGLATTACHSHADERPROC glAttachShader;
EXTERN PFNGLDELETESHADERPROC glDeleteShader;

EXTERN PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
EXTERN PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
// EXTERN PFNGLDRAWARRAYSEXTPROC glDrawArrays;
EXTERN PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
EXTERN PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;

EXTERN PFNGLCREATEPROGRAMPROC glCreateProgram;
EXTERN PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
EXTERN PFNGLLINKPROGRAMPROC glLinkProgram;
EXTERN PFNGLGETPROGRAMIVPROC glGetProgramiv;
EXTERN PFNGLGETPROGRAMBINARYPROC glGetProgramBinary;
EXTERN PFNGLPROGRAMBINARYPROC glProgramBinary;
EXTERN PFNGLUSEPROGRAMPROC glUseProgram;
EXTERN PFNGLDELETEPROGRAMPROC glDeleteProgram;

#undef EXTERN
