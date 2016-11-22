#include "XMLProcessor.h"

// ***********
// * PRIVATE *
// ***********

XMLProcessingResult XMLProcessor::process_node(pugi::xml_node & node)
{
    XMLProcessingResult result;
    std::stringstream buffer;

    /* Enter this block if it's a tag requesting code inclusion
     * from a local file.
     */
    if(strcmp(node.name(), TAG_LOCAL_PATH_INCLUSION) == 0)
    {
        const char * path = node.text().get();
        std::ifstream ifstream(path);

        /* Enter the block if the path specified in
         * pcdata is successfully reached */
        if(ifstream.is_open())
        {
            std::string line;

            while(std::getline(ifstream, line))
                buffer << line;

            ifstream.close();

            /* Add the data fetched from local path
             * as plain text and replace the tag's name
             * with the one expected server side.
             */
            node.text() = buffer.str().c_str();
            node.set_name(TAG_CODE_INCLUSION);
        }
        else
        {
            /* Result's error flag is set and its report field
             * updated with the unreachable path. */
            result.error = true;

            result.report += "Couldn't open: ";
            result.report += path;

            return result;
        }
    }

    /* Before returning, node is stored as a string into result's output field. */
    buffer.str(std::string());
    buffer.clear();

    node.print(buffer);

    result.output = buffer.str();

    return result;
}

// **********
// * PUBLIC *
// **********

XMLProcessingResult XMLProcessor::process(const std::string & input)
{
    pugi::xml_document document;
    pugi::xml_parse_result parse_result;

    /* Parse the string, returning on failure. */
    if(!(parse_result = document.load_string(input.c_str())))
    {
        XMLProcessingResult result;

        result.error = true;
        result.report = parse_result.description();

        return result;
    }

    /* As of now, only the first tag is examined and every
     * trailing tags are discarded. */
    pugi::xml_node node = document.first_child();

    /* Look for paths to process. */
    return process_node(node);
}