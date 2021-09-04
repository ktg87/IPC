cmake_minimum_required (VERSION 2.6)

project (Semaphores)

if(TYPE STREQUAL "thread")
    MESSAGE("Setting up the example for the threads.")
    set (SRCS threadExample.c)
else()
    MESSAGE("Setting up a example for Semaphores.")
    set (SRCS semaphoreExample.c)
endif()

add_executable(Semaphores ${SRCS})




