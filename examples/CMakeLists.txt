# ============================================================================
# Copyright (c) 2011-2012 J.C. Moyer
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.
# ============================================================================

OPTION (HALT_BUILD_EXAMPLES "If enabled, the examples will be built. SDL is required." OFF)

IF (HALT_BUILD_EXAMPLES)
  MESSAGE (STATUS "Examples will be built.")
ELSE ()
  MESSAGE (STATUS "Examples will not be built.")
  RETURN ()
ENDIF ()

# SDL is required for the examples
INCLUDE (FindSDL)

INCLUDE_DIRECTORIES (${SDL_INCLUDE})
INCLUDE_DIRECTORIES (${CMAKE_CURRENT_SOURCE_DIR})

FILE (GLOB UTIL_SOURCE_FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/utilities/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/utilities/*.c"
)

ADD_SUBDIRECTORY (HelloWorld)

# Install common resources for all example binaries
INSTALL (DIRECTORY res DESTINATION examples)

IF (WIN32)
  IF (HALT_LIB_PREFER_SHARED)
    INSTALL (FILES ${HALT_LIB_LOCATION} DESTINATION examples)
  ENDIF ()
  INSTALL (FILES ${GLEW_DLL} ${SDL_DLL}
    DESTINATION examples
  )
ENDIF ()