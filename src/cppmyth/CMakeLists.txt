PROJECT(cppmyth)

ENABLE_LANGUAGE(CXX)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(SOURCES MythChannel.cpp
            MythConnection.cpp
            MythDatabase.cpp
            MythEPGInfo.cpp
            MythEventHandler.cpp
            MythFile.cpp
            MythProgramInfo.cpp
            MythRecorder.cpp
            MythRecordingRule.cpp
            MythScheduleManager.cpp
            MythSignal.cpp
            MythStorageGroupFile.cpp
            MythTimestamp.cpp)

ADD_LIBRARY(cppmyth STATIC ${SOURCES})
