
# to find *.bp.h files
# include_directories(${CMAKE_CURRENT_BINARY_DIR})
# message("CMAKE_CURRENT_BINARY_DIR: " ${CMAKE_CURRENT_BINARY_DIR})

set(PROTO_FILES
    myproto/Game.proto
)
add_library(myproto ${PROTO_FILES})
target_link_libraries(myproto
    PUBLIC
        protobuf::libprotobuf
)
target_include_directories(myproto PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
protobuf_generate(TARGET myproto LANGUAGE cpp)
