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

SET (HALT_VERSION "0.1.0")

SET (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${HALT_SOURCE_DIR}/cmake")

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
OPTION (HALT_OMIT_SHARED "Does not build a shared library if enabled." OFF)
OPTION (HALT_OMIT_STATIC "Does not build a static library if enabled." OFF)

IF (NOT DEFINED GLEW_PREFIX)
  SET (GLEW_PREFIX "" CACHE PATH "Location of the GLEW include and lib folders.")
ENDIF ()

MESSAGE (STATUS "Attempting to locate dependencies...")
INCLUDE (FindOpenGL)
INCLUDE (FindGLEW)

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
IF (NOT HALT_OMIT_SHARED)
  ADD_LIBRARY (${PROJECT_NAME} SHARED ${SOURCE_FILES})
  SET_TARGET_PROPERTIES (${PROJECT_NAME} PROPERTIES VERSION ${HALT_VERSION} SOVERSION ${HALT_VERSION})
  SET (TARGET_NAMES "${PROJECT_NAME};${TARGET_NAMES}")
ENDIF ()

IF (NOT HALT_OMIT_STATIC)
  ADD_LIBRARY (${PROJECT_NAME}-s STATIC ${SOURCE_FILES})
  SET (TARGET_NAMES "${PROJECT_NAME}-s;${TARGET_NAMES}")
ENDIF ()

# Link HALT against OpenGL and GLEW
TARGET_LINK_LIBRARIES (${TARGET_NAMES} ${OPENGL_LIB} ${GLEW_LIB})

# Install headers
INSTALL (FILES ${INCLUDE_FILES} DESTINATION include/HALT)

# Install library
INSTALL (TARGETS ${TARGET_NAMES}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
