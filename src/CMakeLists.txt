
add_executable(main Main.cpp)

target_link_libraries(main 
    PUBLIC
        protobuf::libprotobuf
        myproto
)
