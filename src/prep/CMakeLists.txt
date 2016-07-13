add_library(xmlpreprocessor "XMLPreprocessor.cpp")

target_include_directories(xmlpreprocessor PUBLIC ${PUGIXML_HDR})
target_link_libraries(xmlpreprocessor ${PUGIXML_LIB})