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

MESSAGE (STATUS "Attempting to locate SDL...")
IF (WIN32)
  FIND_LIBRARY (SDL_LIB
    NAMES
      SDL
    PATHS
      ${SDL_PREFIX}/lib)
  FIND_PATH (SDL_INCLUDE
    NAMES
      SDL/SDL.h
    PATHS
      ${SDL_PREFIX}/include)
  IF (SDL_LIB)
    FIND_FILE (SDL_DLL
      NAMES
        SDL.dll
      PATHS
        ${SDL_PREFIX}/bin
        ${SDL_PREFIX}/lib
    )
  ENDIF ()
ELSE ()
  FIND_LIBRARY (SDL_LIB
    NAMES
      SDL
    PATHS
      ${SDL_PREFIX}/lib
      /usr/lib
      /usr/lib64
      /usr/local/lib
      /usr/local/lib64)
  FIND_PATH (SDL_INCLUDE
    NAMES
      SDL/SDL.h
    PATHS
      /usr/include
      /usr/local/include)
ENDIF ()

IF (SDL_LIB)
  MESSAGE (STATUS "SDL located at ${SDL_LIB}")
ELSE ()
  MESSAGE (FATAL_ERROR "Could not locate the SDL library file. Either SDL_PREFIX needs to point to a directory containing include and lib directories for SDL, or you must specify the directory manually through SDL_LIB.")
ENDIF ()

IF (SDL_INCLUDE)
  MESSAGE (STATUS "SDL includes located at ${SDL_INCLUDE}")
ELSE ()
  MESSAGE (FATAL_ERROR "Could not locate the SDL header files. Either SDL_PREFIX needs to point to a directory containing include and lib directories for SDL, or you must specify the directory manually through SDL_INCLUDE.")
ENDIF ()

IF (WIN32)
  IF (SDL_DLL)
    MESSAGE (STATUS "SDL DLL found at ${SDL_DLL}")
  ENDIF ()
ENDIF ()