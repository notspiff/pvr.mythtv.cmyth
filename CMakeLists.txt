project(pvr.mythtv.cmyth)

cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})

enable_language(CXX)
enable_language(C)

find_package(kodi REQUIRED)
find_package(kodiplatform REQUIRED)
find_package(Boost REQUIRED)
find_package(MySqlClient REQUIRED)

include_directories(${kodiplatform_INCLUDE_DIRS}
                    ${KODI_INCLUDE_DIR}
                    ${Boost_INCLUDE_DIRS}
                    ${MYSQLCLIENT_INCLUDE_DIRS}
                    ${PROJECT_SOURCE_DIR}/lib/cmyth/include
                    ${PROJECT_SOURCE_DIR}/lib/cmyth/libcmyth
                    ${PROJECT_SOURCE_DIR}/lib/cmyth/librefmem)

add_definitions(-DUSE_DEMUX -D__STDC_FORMAT_MACROS)

if(NOT WIN32)
  add_options(ALL_LANGUAGES ALL_BUILDS "-fPIC")
endif()

set(MYTHTV_SOURCES src/categories.cpp
                   src/client.cpp
                   src/demux.cpp
                   src/fileOps.cpp
                   src/pvrclient-mythtv.cpp
                   src/demuxer/bitstream.cpp
                   src/demuxer/debug.cpp
                   src/demuxer/elementaryStream.cpp
                   src/demuxer/ES_AAC.cpp
                   src/demuxer/ES_AC3.cpp
                   src/demuxer/ES_h264.cpp
                   src/demuxer/ES_MPEGAudio.cpp
                   src/demuxer/ES_MPEGVideo.cpp
                   src/demuxer/ES_Subtitle.cpp
                   src/demuxer/ES_Teletext.cpp
                   src/demuxer/tsDemuxer.cpp)

add_subdirectory(lib/cmyth/libcmyth)
add_subdirectory(lib/cmyth/librefmem)
add_subdirectory(src/cppmyth)

set(DEPLIBS ${kodiplatform_LIBRARIES}
            ${MYSQLCLIENT_LIBRARIES})
if(WIN32)
  list(APPEND DEPLIBS cmyth cppmyth refmem ws2_32)
else()
  list(APPEND DEPLIBS -Wl,--whole-archive cmyth cppmyth refmem -Wl,--no-whole-archive)
endif()

build_addon(pvr.mythtv.cmyth MYTHTV DEPLIBS)

if(WIN32)
  set_target_properties(pvr.mythtv.cmyth PROPERTIES LINK_FLAGS "/NODEFAULTLIB:libcmt")
endif()

include(CPack)
