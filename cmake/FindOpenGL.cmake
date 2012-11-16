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

MESSAGE (STATUS "Attempting to locate OpenGL...")
IF (WIN32)
  FIND_LIBRARY (OPENGL_LIB opengl32)
ELSE ()
  FIND_LIBRARY (OPENGL_LIB
    NAMES GL MesaGL
    PATHS
      /usr/lib
      /usr/lib64
      /usr/local/lib
      /usr/local/lib64)
ENDIF ()

IF (OPENGL_LIB)
  MESSAGE (STATUS "OpenGL located at ${OPENGL_LIB}")
ELSE ()
  MESSAGE (FATAL_ERROR "Could not locate OpenGL. You must manually point to the OpenGL library file through OPENGL_LIB.")
ENDIF ()
