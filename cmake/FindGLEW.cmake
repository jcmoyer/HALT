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

MESSAGE (STATUS "Attempting to locate GLEW...")
IF (WIN32)
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
