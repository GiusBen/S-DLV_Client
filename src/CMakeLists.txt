add_subdirectory("prep")

add_executable(sdlvc "main.cpp")

target_link_libraries(sdlvc xmlpreprocessor)