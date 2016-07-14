#ifndef S_DLV_CLIENT_XMLPREPROCESSOR_H
#define S_DLV_CLIENT_XMLPREPROCESSOR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <pugixml.hpp>

#include "XMLPreprocessingResult.h"

class XMLPreprocessor
{
    private:
        static const std::string tag_code_inclusion;
        static const std::string attr_path_inclusion;

        bool expand_path(pugi::xml_node&, XMLPreprocessingResult&);

    public:
        XMLPreprocessingResult process(const std::string&);
};

#endif // S_DLV_CLIENT_XMLPREPROCESSOR_H