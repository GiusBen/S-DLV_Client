add_library(xmlprocessor "XMLProcessor.cpp")

target_include_directories(xmlprocessor PUBLIC ${PUGIXML_HDR})
target_link_libraries(xmlprocessor ${PUGIXML_LIB})