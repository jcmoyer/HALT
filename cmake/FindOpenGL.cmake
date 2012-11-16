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
