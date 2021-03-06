# Try to find allegro 5
#
# ALLEGRO5_FOUND - system has allegro5
# ALLEGRO5_INCLUDE_DIRS - the allrgo5 include directory
# ALLEGRO5_LIBRARIES - Link these to use allegro5
#

FIND_PATH(ALLEGRO5_INCLUDE_DIR allegro.h
  HINTS
  $ENV{LUA_DIR}
  PATH_SUFFIXES include/allegro5 include/allegro include
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw
  /opt/local
  /opt/csw
  /opt
)

FIND_LIBRARY(ALLEGRO5_LIBRARY
  NAMES allegro
  HINTS
  $ENV{ALLEGRO5_DIR}
  PATH_SUFFIXES lib64 lib
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
)

FIND_LIBRARY(ALLEGRO5_LIBRARY_MAIN
  NAMES allegro_main
  HINTS
  $ENV{ALLEGRO5_DIR}
  PATH_SUFFIXES lib64 lib
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
)

FIND_LIBRARY(ALLEGRO5_LIBRARY_FONT
  NAMES allegro_font
  HINTS
  $ENV{ALLEGRO5_DIR}
  PATH_SUFFIXES lib64 lib
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
)

FIND_LIBRARY(ALLEGRO5_LIBRARY_IMAGE
  NAMES allegro_image
  HINTS
  $ENV{ALLEGRO5_DIR}
  PATH_SUFFIXES lib64 lib
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
)

FIND_LIBRARY(ALLEGRO5_LIBRARY_PRIMITIVES
  NAMES allegro_primitives
  HINTS
  $ENV{ALLEGRO5_DIR}
  PATH_SUFFIXES lib64 lib
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
)

FIND_LIBRARY(ALLEGRO5_LIBRARY_TTF
  NAMES allegro_ttf
  HINTS
  $ENV{ALLEGRO5_DIR}
  PATH_SUFFIXES lib64 lib
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
)

IF(ALLEGRO5_LIBRARY)
  SET(ALLEGRO5_LIBRARIES "${ALLEGRO5_LIBRARY}" "${ALLEGRO5_LIBRARY_MAIN}" "${ALLEGRO5_LIBRARY_IMAGE}" "${ALLEGRO5_LIBRARY_FONT}" "${ALLEGRO5_LIBRARY_PRIMITIVES}" "${ALLEGRO5_LIBRARY_TTF}" CACHE STRING "Allegro5 Libraries")
  SET(ALLEGRO5_INCLUDE_DIRS "${ALLEGRO5_INCLUDE_DIR}" CACHE STRING "Allegro5 Include Dirs")
  SET(ALLEGRO5_FOUND TRUE)
  #MESSAGE(STATUS ${ALLEGRO5_LIBRARY})
ENDIF(ALLEGRO5_LIBRARY)

MARK_AS_ADVANCED(ALLEGRO5_INCLUDE_DIR ALLEGRO5_INCLUDE_DIRS ALLEGRO5_LIBRARIES ALLEGRO5_LIBRARY)

