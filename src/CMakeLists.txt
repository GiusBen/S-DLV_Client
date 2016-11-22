add_subdirectory("net")
add_subdirectory("xmlproc")
add_subdirectory("tester")

add_executable(sdlvc "main.cpp")

target_link_libraries(sdlvc
        nwinterface
        xmlprocessor
        tester)