#include "XMLProcessor.h"

// ***********
// | PRIVATE |
// ***********

const char * XMLProcessor::TAG_CODE_INCLUSION = "eat";
const char * XMLProcessor::ATTR_PATH_INCLUSION = "path";

bool XMLProcessor::fetch_file_content(pugi::xml_node & node,
                                      XMLProcessingResult & result)
{
    pugi::xml_attribute path;

    /* Enter the block if 'node' is a code inclusion tag with
     * a path inclusion attribute - e.g. <code path="..."/> */
    if(strcmp(node.name(), TAG_CODE_INCLUSION) == 0
        && (path = node.attribute(ATTR_PATH_INCLUSION)))
    {
        std::ifstream ifstream(path.value());

        /* Enter the block if the path specified in
         * the attribute is successfully reached */
        if(ifstream.is_open())
        {
            std::stringstream buffer;
            std::string line;

            /* Node might have some plain text data; if so,
             * it gets prepended to the file's content. */
            buffer << node.text().get();

            while(std::getline(ifstream, line))
                buffer << line;

            ifstream.close();

            /* Remove the attribute and add the data as
             * plain text - e.g. <code path="..."/> becomes
             * <code>data_1.data_2.</code>. */
            node.remove_attribute(path);
            node.text() = buffer.str().c_str();
        }
        else
        {
            /* Result's error flag is set and its report field
             * updated with the unreachable path. */
            result.error = true;

            result.report += "Couldn't open: ";
            result.report += path.value();
        }
    }

    /* Return true if one of the following holds:
     * > It wasn't a code inclusion tag
     * > It was but had no path inclusion attribute
     * > It was and the attribute held a valid path */
    return !result.error;
}

// **********
// | PUBLIC |
// **********

XMLProcessingResult XMLProcessor::process(const std::string & input)
{
    XMLProcessingResult preprocessingResult;

    pugi::xml_document document;
    pugi::xml_parse_result result;

    /* Parse the string. On failure, update the XMLProcessingResult
     * instance and return it. */
    if(!(result = document.load_string(input.c_str())))
    {
        preprocessingResult.error = true;
        preprocessingResult.report = result.description();

        return preprocessingResult;
    }

    /* As of now, only the first tag is examined and every
     * trailing tags are discarded. */
    pugi::xml_node node = document.first_child();

    /* Resolve the paths if there are any. Failure is handled by
     * the fetch_file_content function itself; on success, update
     * the XMLProcessingResult instance. */
    if(fetch_file_content(node, preprocessingResult))
    {
        std::stringstream buffer;

        document.save(buffer);

        preprocessingResult.report = "OK";
        preprocessingResult.output = buffer.str();
    }

    return preprocessingResult;
}