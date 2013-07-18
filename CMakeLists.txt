PROJECT(pvr.mythtv.cmyth)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})

ENABLE_LANGUAGE(CXX)
ENABLE_LANGUAGE(C)

FIND_PACKAGE(xbmc REQUIRED)
FIND_PACKAGE(xbmcplatform REQUIRED)
FIND_PACKAGE(Boost REQUIRED)
FIND_PACKAGE(MySqlClient REQUIRED)
addon_version(pvr.mythtv.cmyth PVRMYTH)

INCLUDE_DIRECTORIES(${xbmcplatform_INCLUDE_DIRS}
                    ${XBMC_INCLUDE_DIR}
                    ${Boost_INCLUDE_DIRS}
                    ${LIBMYSQLCLIENT_INCLUDE_DIR}
                    ${PROJECT_SOURCE_DIR}/lib/cmyth/include
                    ${PROJECT_SOURCE_DIR}/lib/cmyth/libcmyth
                    ${PROJECT_SOURCE_DIR}/lib/cmyth/librefmem)

ADD_DEFINITIONS(-DUSE_DEMUX)

IF (NOT WIN32)
  include(AddOptions.cmake)
  add_options(ALL_LANGUAGES ALL_BUILDS "-fPIC")
ENDIF(NOT WIN32)

SET(SOURCES src/categories.cpp
            src/client.cpp
            src/fileOps.cpp
            src/pvrclient-mythtv.cpp)

ADD_SUBDIRECTORY(lib/cmyth/libcmyth)
ADD_SUBDIRECTORY(lib/cmyth/librefmem)
ADD_SUBDIRECTORY(src/cppmyth)

SET(DEPLIBS ${xbmcplatform_LIBRARIES}
            ${LIBMYSQLCLIENT_LIBRARIES}
            cmyth cppmyth refmem)

build_addon(pvr.mythtv.cmyth SOURCES DEPLIBS PVRMYTH_VERSION)
install_addon(pvr.mythtv.cmyth ${PVRMYTH_VERSION})
