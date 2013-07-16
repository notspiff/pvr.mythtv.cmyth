PROJECT(cmyth)

ENABLE_LANGUAGE(C)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(SOURCES bookmark.c
            channel.c
            commbreak.c
            connection.c
            debug.c
            event.c
            file.c
            freespace.c
            input.c
            keyframe.c
            livetv.c
            mysql_query.c
            mythtv_mysql.c
            posmap.c
            proginfo.c
            proglist.c
            rec_num.c
            recorder.c
            recordingrule.c
            ringbuf.c
            socket.c
            storagegroup.c
            timestamp.c
            utf8tolatin1.c)

ADD_LIBRARY(cmyth STATIC ${SOURCES})
