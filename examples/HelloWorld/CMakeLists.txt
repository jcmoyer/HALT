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

PROJECT (HelloWorld)

#FIND_LIBRARY (HALT_LLIB HALT-s)
MESSAGE (STATUS "HALT is ${HALT_LIB}")



ADD_EXECUTABLE (${PROJECT_NAME} HelloWorld.cpp ${UTIL_SOURCE_FILES})
#ADD_DEPENDENCIES (${PROJECT_NAME})
TARGET_LINK_LIBRARIES (${PROJECT_NAME} ${HALT_LIB} ${OPENGL_LIB} ${SDL_LIB} ${HALT_LIB} ${OPENGL_LIB} ${SDL_LIB})

INSTALL (TARGETS HelloWorld
  RUNTIME DESTINATION examples
  LIBRARY DESTINATION examples
  ARCHIVE DESTINATION examples
)
