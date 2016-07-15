#include "XMLProcessor.h"

// ***********
// | PRIVATE |
// ***********

const std::string XMLProcessor::tag_code_inclusion = "eat";
const std::string XMLProcessor::attr_path_inclusion = "path";

bool XMLProcessor::expand_path(pugi::xml_node& node,
                               XMLProcessingResult& result)
{
    pugi::xml_attribute path;

    if(tag_code_inclusion.compare(node.name()) == 0
        && (path = node.attribute(attr_path_inclusion.c_str())))
    {
        std::ifstream ifstream(path.value());

        if(ifstream.is_open())
        {
            std::stringstream buffer;
            std::string line;

            while(std::getline(ifstream, line))
                buffer << line;

            node.remove_attribute(path);
            node.text() = buffer.str().c_str();
        }
        else
        {
            result.description += "Couldn't open ";
            result.description += path.value();

            return false;
        }
    }

    return true;
}

// **********
// | PUBLIC |
// **********

XMLProcessingResult XMLProcessor::process(const std::string& input)
{
    XMLProcessingResult preprocessingResult;

    pugi::xml_document document;
    pugi::xml_parse_result result;

    // --- XML Parsing
    if(!(result = document.load_string(input.c_str())))
    {
        preprocessingResult.description = result.description();

        return preprocessingResult;
    }

    // --- XML Validation
    // TODO

    pugi::xml_node node = document.first_child();

    // --- Path expansion
    if(expand_path(node, preprocessingResult))
    {
        std::stringstream buffer;

        document.save(buffer);
        preprocessingResult.output = buffer.str();
    }

    return preprocessingResult;
}