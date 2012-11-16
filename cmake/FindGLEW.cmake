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
