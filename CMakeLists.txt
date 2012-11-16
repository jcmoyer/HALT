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

CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT (HALT)

MESSAGE (STATUS "Detecting platform...")
IF (WIN32)
  SET (PLATFORM win32)
  MESSAGE ("Platform set to win32")
ELSEIF (UNIX)
  SET (PLATFORM linux)
  MESSAGE ("Platform set to linux")
ELSE ()
  MESSAGE (FATAL_ERROR "Platform not supported")
ENDIF ()

#
# Options that control how HALT will be built
#
OPTION (HALT_SHARED "Build HALT as a shared or dynamic library." OFF)

IF (HALT_SHARED)
  SET (HALT_LIB_TYPE SHARED)
ELSE ()
  SET (HALT_LIB_TYPE STATIC)
ENDIF ()

IF (NOT DEFINED GLEW_PREFIX)
  SET (GLEW_PREFIX "" CACHE PATH "Location of the GLEW include and lib folders.")
ENDIF ()

MESSAGE (STATUS "Attempting to locate dependencies...")
IF (WIN32)
  FIND_LIBRARY (OPENGL_LIB opengl32)
  FIND_LIBRARY (GLEW_LIB
    NAMES
      glew glew32 libglew libglew32
    PATHS
      ${GLEW_PREFIX}/lib)
  FIND_PATH(GLEW_INCLUDE
    NAMES
      GL/glew.h
    PATHS
      ${GLEW_PREFIX}/include)
ELSE ()
  FIND_LIBRARY (OPENGL_LIB
    NAMES GL MesaGL
    PATHS
      /usr/lib
      /usr/lib64
      /usr/local/lib
      /usr/local/lib64)
  FIND_LIBRARY (GLEW_LIB
    NAMES
      GLEW
    PATHS
      ${GLEW_PREFIX}/lib
      /usr/lib
      /usr/lib64
      /usr/local/lib
      /usr/local/lib64)
  FIND_PATH(GLEW_INCLUDE
    NAMES
      GL/glew.h
    PATHS
      /usr/include
      /usr/local/include)
ENDIF ()

IF (OPENGL_LIB)
  MESSAGE (STATUS "OpenGL located at ${OPENGL_LIB}")
ELSE ()
  MESSAGE (FATAL_ERROR "Could not locate OpenGL. You must manually point to the OpenGL library file through OPENGL_LIB.")
ENDIF ()

IF (GLEW_LIB)
  MESSAGE (STATUS "GLEW located at ${GLEW_LIB}")
ELSE ()
  MESSAGE (FATAL_ERROR "Could not locate the GLEW library file. Either GLEW_PREFIX needs to point to a directory containing include and lib directories for GLEW, or you must specify the directory manually through GLEW_LIB.")
ENDIF ()

IF (GLEW_INCLUDE)
  MESSAGE (STATUS "GLEW includes located at ${GLEW_INCLUDE}")
ELSE ()
  MESSAGE (FATAL_ERROR "Could not locate the GLEW header files. Either GLEW_PREFIX needs to point to a directory containing include and lib directories for GLEW, or you must specify the directory manually through GLEW_INCLUDE.")
ENDIF ()

# Where to look for stuff
INCLUDE_DIRECTORIES (${GLEW_INCLUDE})
INCLUDE_DIRECTORIES (${HALT_SOURCE_DIR}/include)

FILE (GLOB INCLUDE_FILES
  "${HALT_SOURCE_DIR}/include/*.h"
)

FILE (GLOB SOURCE_FILES
  "${HALT_SOURCE_DIR}/src/*.cpp"
)

# Output
ADD_LIBRARY (${PROJECT_NAME} ${HALT_LIB_TYPE} ${SOURCE_FILES})

# Link HALT against OpenGL and GLEW
TARGET_LINK_LIBRARIES (${PROJECT_NAME} ${OPENGL_LIB} ${GLEW_LIB})

# Enable installs for all platforms
INSTALL (FILES ${INCLUDE_FILES} DESTINATION include/HALT)

INSTALL (TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
