cmake_minimum_required (VERSION 2.6)

project (Pipes)

set (ERR_SRCS ErrorHandling.c)

if(OPERATION STREQUAL "parent")
    MESSAGE("Setting up the example for the Parent/Child Pipes.")
    set (PIPES_SRCS ParentChildAnonymousPipe.c)
else()
    MESSAGE("Setting up a normal anonymous pipe.")
    set (PIPES_SRCS AnonymousPipe.c)
endif()

set(SRCS ${ERR_SRCS} ${PIPES_SRCS})

set(INCS ErrorHandling.h)

add_executable(Pipes ${SRCS} ${INCS})




