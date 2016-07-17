set(PUGIXML_HDR "${PUGIXML_DIR}/src")

add_library(xmlprocessor
        "XMLProcessor.cpp"
        "${PUGIXML_HDR}/pugixml.cpp")

target_include_directories(xmlprocessor PUBLIC ${PUGIXML_HDR})