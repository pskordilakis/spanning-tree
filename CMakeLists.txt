CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
project(spanning-tree)

#set sources directory
set(SRC src)

#build library (.so)
add_library(ps SHARED 
    ${SRC}/lib/double_linked_list.c
    ${SRC}/lib/queue.c
    ${SRC}/lib/sparse.c
    ${SRC}/lib/graph.c
)

#create the executable
SET(EXEC spanning)
ADD_EXECUTABLE(${EXEC}
 ${SRC}/main.c
)

TARGET_LINK_LIBRARIES (${EXEC}
   ps
)