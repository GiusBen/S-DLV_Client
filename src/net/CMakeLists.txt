set(DLIB_ALL_SOURCE_CPP "${DLIB_DIR}/dlib/all/source.cpp")

if(${WIN32})
    set(ADDITIONAL_LIBRARIES ws2_32 winmm)
endif()

add_library(nwinterface
        ${DLIB_ALL_SOURCE_CPP}
        "NWInterface.cpp")

target_compile_definitions(nwinterface PUBLIC -DDLIB_NO_GUI_SUPPORT)

target_include_directories(nwinterface PUBLIC ${DLIB_DIR})

target_link_libraries(nwinterface ${ADDITIONAL_LIBRARIES})