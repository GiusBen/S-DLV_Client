#ifndef S_DLV_CLIENT_XMLPROCESSOR_H
#define S_DLV_CLIENT_XMLPROCESSOR_H

#define TAG_CODE_INCLUSION "put"
#define TAG_LOCAL_PATH_INCLUSION "lput"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>

#include "pugixml.hpp"

struct XMLProcessingResult
{
    bool error = false;
    
    std::string report = "NONE";
    std::string output = "NONE";

    std::string to_string()
    {
        std::stringstream buffer;

        buffer << "Error: " << error << std::endl
               << "Report: " << report << std::endl
               << "Output: " << output << std::endl;

        return buffer.str();
    }
};

class XMLProcessor
{
    private:
        XMLProcessingResult process_node(pugi::xml_node &);

    public:
        XMLProcessingResult process(const std::string &);
};

#endif // S_DLV_CLIENT_XMLPROCESSOR_H
