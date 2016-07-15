#ifndef S_DLV_CLIENT_XMLPREPROCESSOR_H
#define S_DLV_CLIENT_XMLPREPROCESSOR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <pugixml.hpp>

struct XMLProcessingResult
{
    std::string description;
    std::string output;
};

class XMLProcessor
{
    private:
        static const std::string tag_code_inclusion;
        static const std::string attr_path_inclusion;

        bool fetch_file_content(pugi::xml_node &, XMLProcessingResult &);

    public:
        XMLProcessingResult process(const std::string&);
};

#endif // S_DLV_CLIENT_XMLPREPROCESSOR_H