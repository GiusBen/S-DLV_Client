#include "XMLProcessor.h"

// ***********
// | PRIVATE |
// ***********

const std::string XMLProcessor::tag_code_inclusion = "eat";
const std::string XMLProcessor::attr_path_inclusion = "path";

bool XMLProcessor::fetch_file_content(pugi::xml_node &node,
                                      XMLProcessingResult &result)
{
    pugi::xml_attribute path;

    /* Enter the block if 'node' is a code inclusion tag with
     * a path inclusion attribute - e.g. <code path="..."/> */
    if(tag_code_inclusion.compare(node.name()) == 0
        && (path = node.attribute(attr_path_inclusion.c_str())))
    {
        std::ifstream ifstream(path.value());

        /* Enter the block if the path specified in
         * the attribute is successfully reached */
        if(ifstream.is_open())
        {
            std::stringstream buffer;
            std::string line;

            while(std::getline(ifstream, line))
                buffer << line;

            ifstream.close();

            /* Remove the attribute and add the data as
             * plain text - e.g. <code path="..."/> becomes
             * <code>data_1.data_2.</code> */
            node.remove_attribute(path);
            node.text() = buffer.str().c_str();
        }
        else
        {
            /* Result's description is updated
             * with the unreachable path */
            result.description += "Couldn't open ";
            result.description += path.value();

            return false;
        }
    }

    /* True if one of the following holds:
     * > It wasn't a code inclusion tag
     * > It was but had no path inclusion attribute
     * > It was and the attribute held a valid path */
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
    if(fetch_file_content(node, preprocessingResult))
    {
        std::stringstream buffer;

        document.save(buffer);
        preprocessingResult.output = buffer.str();
    }

    return preprocessingResult;
}