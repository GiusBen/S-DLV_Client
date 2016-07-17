#ifndef S_DLV_CLIENT_XMLPROCESSOR_H
#define S_DLV_CLIENT_XMLPROCESSOR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>

#include <pugixml.hpp>

struct XMLProcessingResult
{
    std::string description;
    std::string output;
};

class XMLProcessor
{
    private:
        static const char * TAG_CODE_INCLUSION;
        static const char * ATTR_PATH_INCLUSION;

        bool fetch_file_content(pugi::xml_node &, XMLProcessingResult &);

    public:
        XMLProcessingResult process(const std::string &);
};

#endif // S_DLV_CLIENT_XMLPROCESSOR_H