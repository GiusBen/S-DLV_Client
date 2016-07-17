add_subdirectory("net")
add_subdirectory("xmlproc")

add_executable(sdlvc "main.cpp")

target_link_libraries(sdlvc
        nwinterface
        xmlprocessor)