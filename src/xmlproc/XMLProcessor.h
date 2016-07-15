#ifndef S_DLV_CLIENT_XMLPREPROCESSOR_H
#define S_DLV_CLIENT_XMLPREPROCESSOR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <pugixml.hpp>

#include "XMLProcessingResult.h"

class XMLProcessor
{
    private:
        static const std::string tag_code_inclusion;
        static const std::string attr_path_inclusion;

        bool expand_path(pugi::xml_node&, XMLProcessingResult&);

    public:
        XMLProcessingResult process(const std::string&);
};

#endif // S_DLV_CLIENT_XMLPREPROCESSOR_H