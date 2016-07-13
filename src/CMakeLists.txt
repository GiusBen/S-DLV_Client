add_executable(sdlvc "main.cpp")

include_directories(${PUGIXML_HDR})

target_link_libraries(sdlvc ${PUGIXML_LIB})