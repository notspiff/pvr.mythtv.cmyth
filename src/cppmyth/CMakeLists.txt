PROJECT(mythcpp)

ENABLE_LANGUAGE(CXX)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(SOURCES MythChannel.cpp
            MythConnection.cpp
            MythDatabase.cpp
            MythEventHandler.cpp
            MythFile.cpp
            MythProgramInfo.cpp
            MythRecorder.cpp
            MythRecordingRule.cpp
            MythSignal.cpp
            MythStorageGroupFile.cpp
            MythTimestamp.cpp)

ADD_LIBRARY(mythcpp STATIC ${SOURCES})
