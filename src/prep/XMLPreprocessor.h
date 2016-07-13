#ifndef S_DLV_CLIENT_XMLPREPROCESSOR_H
#define S_DLV_CLIENT_XMLPREPROCESSOR_H

#include <iostream>
#include <pugixml.hpp>

class XMLPreprocessor
{
    public:
        void expand_paths(const pugi::xml_document&) const;
};

#endif // S_DLV_CLIENT_XMLPREPROCESSOR_H
