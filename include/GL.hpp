// This header gives you all you need to interface with the OpenGL implementation and drivers.

#include <GL/gl.h>
#include <GL/glext.h>

#include "Exception.hpp"

// If a function fails to load nullptr is returned. Up to the caller to decide what to do with that.
void* omglGetProcAddress(const char* str) noexcept;
// Loads all the functions present in this here header. Throws an OMGL::SystemException if a function failed to load, the code variable is irrelevant.
void omglGetAllProcAddresses();

#ifdef _OMGL_SOURCE
  #define EXTERN 
#else
  #define EXTERN extern
#endif

EXTERN PFNGLUSEPROGRAMPROC glUseProgram;
EXTERN PFNGLBINDBUFFERPROC glBindBuffer;

#undef EXTERN
