cmake_minimum_required (VERSION 2.6)

project (Pipes)

set (PIPES_SRCS AnonymousPipe.c ErrorHandling.c)
set (PIPES_INC ErrorHandling.h)

add_executable(Pipes ${PIPES_SRCS} ${PIPES_INC})





