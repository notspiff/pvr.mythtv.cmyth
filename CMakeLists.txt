PROJECT(pvr.mythtv.cmyth)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

include(AddonVersion.cmake)
addon_version(pvr.mythtv.cmyth PVRMYTH)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})

ENABLE_LANGUAGE(CXX)
ENABLE_LANGUAGE(C)

OPTION(PACKAGE_ZIP "Package Zip file?" OFF)

FIND_PACKAGE(Boost REQUIRED)
FIND_PACKAGE(MySqlClient REQUIRED)

IF(WIN32)
  SET(BINDING_FILE ${XBMC_BINDINGS}.zip)
  message (STATUS "downloading XBMC bindings: " ${BINDING_FILE})
  file(DOWNLOAD http://mirrors.xbmc.org/build-deps/win32/${BINDING_FILE} ${CMAKE_BINARY_DIR}/downloads/${BINDING_FILE} STATUS STATUSLIST SHOW_PROGRESS)
  LIST(GET STATUSLIST 0 VALUE)
  IF(${VALUE} STRGREATER "0")
    LIST(GET STATUSLIST 1 VALUE)
    message (STATUS "failed to download XBMC bindings: " ${VALUE})
  ENDIF(${VALUE} STRGREATER "0")
  execute_process(
   COMMAND ${CMAKE_COMMAND} -E tar xzf ${CMAKE_BINARY_DIR}/downloads/${BINDING_FILE}
  )
  FIND_PATH(XBMC_INCLUDE_DIR xbmc/xbmc_pvr_dll.h ${CMAKE_BINARY_DIR}/include)
  INCLUDE_DIRECTORIES(${XBMC_INCLUDE_DIR})
  ADD_DEFINITIONS(-DTARGET_WINDOWS)
ELSE(WIN32)
  FIND_PATH(XBMC_INCLUDE_DIR xbmc/xbmc_pvr_dll.h)
  FIND_PACKAGE(xbmcplatform REQUIRED)
  INCLUDE_DIRECTORIES(${xbmcplatform_INCLUDE_DIRS}
                      ${XBMC_INCLUDE_DIR}
                      ${Boost_INCLUDE_DIRS}
                      ${LIBMYSQLCLIENT_INCLUDE_DIR}
                      ${PROJECT_SOURCE_DIR}/lib/cmyth/include
                      ${PROJECT_SOURCE_DIR}/lib/cmyth/libcmyth
                      ${PROJECT_SOURCE_DIR}/lib/cmyth/librefmem)
  ADD_DEFINITIONS(-DTARGET_LINUX -DUSE_DEMUX)

  include(AddOptions.cmake)
  add_options(ALL_LANGUAGES RELEASE "-fPIC")
ENDIF(WIN32)

SET(SOURCES src/categories.cpp
            src/client.cpp
            src/fileOps.cpp
            src/pvrclient-mythtv.cpp)

ADD_SUBDIRECTORY(lib/cmyth/libcmyth)
ADD_SUBDIRECTORY(lib/cmyth/librefmem)
ADD_SUBDIRECTORY(src/cppmyth)

ADD_LIBRARY(pvr.mythtv.cmyth ${SOURCES})
ADD_DEPENDENCIES(pvr.mythtv.cmyth cppmyth cmyth refmem)

IF(NOT WIN32)
  TARGET_LINK_LIBRARIES(pvr.mythtv.cmyth ${xbmcplatform_LIBRARIES}
                                         ${LIBMYSQLCLIENT_LIBRARIES}
                                         cmyth cppmyth refmem)
  set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "-s")
  set(CMAKE_MODULE_LINKER_FLAGS_RELEASE "-s")
ENDIF(NOT WIN32)
SET_TARGET_PROPERTIES(pvr.mythtv.cmyth PROPERTIES VERSION ${PVRMYTH_VERSION}
                                                  SOVERSION 13.0
                                                  PREFIX "")

IF(PACKAGE_ZIP)
  # Pack files together to create an archive
  INSTALL(DIRECTORY ${PROJECT_NAME} DESTINATION ./)
  IF(WIN32)
    INSTALL(PROGRAMS ${CMAKE_BINARY_DIR}/pvr.mythtv.cmyth.dll DESTINATION pvr.mythtv.cmyth)
  ELSE(WIN32)
    INSTALL(TARGETS pvr.mythtv.cmyth DESTINATION pvr.mythtv.cmyth)
  ENDIF(WIN32)
  SET(CPACK_GENERATOR "ZIP")
  SET(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
  SET(CPACK_PACKAGE_FILE_NAME ${CMAKE_PROJECT_NAME}-${PVRMYTH_VERSION})
  INCLUDE(CPack)
ELSE(PACKAGE_ZIP)
  INSTALL(TARGETS pvr.mythtv.cmyth DESTINATION lib/xbmc/addons/pvr.mythtv.cmyth)
  INSTALL(DIRECTORY pvr.mythtv.cmyth DESTINATION share/xbmc/addons)
ENDIF(PACKAGE_ZIP)
