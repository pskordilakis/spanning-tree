CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
project(spanning-tree)

#set sources dir
set(SRC src)

#build library (.so)
add_library(ps SHARED 
    ${SRC}/double_linked_list/DoubleLinkedList.c
    ${SRC}/queue/Queue.c
    ${SRC}/sparse/Sparse.c
)

#create the executable
SET(EXEC spanning)
ADD_EXECUTABLE(${EXEC}
 ${SRC}/Spanning.c
)

TARGET_LINK_LIBRARIES (${EXEC}
   ps
)