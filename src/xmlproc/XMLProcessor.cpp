#include "XMLProcessor.h"

// ***********
// | PRIVATE |
// ***********

const char * XMLProcessor::TAG_CODE_INCLUSION = "eat";

const char * XMLProcessor::ATTR_PATH_INCLUSION = "path";
const char * XMLProcessor::ATTR_HANDLE_DEFINITION = "handle";

bool XMLProcessor::process_node(pugi::xml_node & node,
                                XMLProcessingResult & result)
{
    // # TAG_CODE_INCLUSION

    if(strcmp(node.name(), TAG_CODE_INCLUSION) == 0)
    {
        /* Before moving on, make sure the code inclusion tag
         * has a (proper) handle attribute. */
        if(!node.attribute(ATTR_HANDLE_DEFINITION))
        {
            result.description += "Code inclusion tag has no handle attribute.";

            return false;
        }

        if(strcmp(node.attribute(ATTR_HANDLE_DEFINITION).value(), "") == 0)
        {
            result.description += "Empty handle for code inclusion tag.";

            return false;
        }

        /* Handle ok, proceed with path processing. */
        pugi::xml_attribute path;

        if(path = node.attribute(ATTR_PATH_INCLUSION))
        {
            std::ifstream ifstream(path.value());

            /* Enter the block if the path specified in
             * the attribute is successfully reached */
            if(ifstream.is_open())
            {
                std::stringstream buffer;
                std::string line;

                /* Plain data might already be present;
                 * if so it gets prepended. */
                buffer << node.text().get();

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
                result.description += "Couldn't open: ";
                result.description += path.value();

                return false;
            }
        }
        // FIXME: As of now, a string made of only spaces would pass the test
        else if(strcmp(node.text().get(), "") == 0)
        {
            result.description = "Code inclusion tag has no path nor plain text data.";

            return false;
        }

        return true;
    }

    /* No 'if' block entered. */
    result.description += "Bad tag.";

    return false;
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
        preprocessingResult.description = result.description();

        return preprocessingResult;
    }

    /* Parsing successful. */

	/* Only the first tag is processed (and sent). Every trailing tag
     * is ignored, so you basically have to send it separately. */
    pugi::xml_node node = document.first_child();

    /* Process the node (e.g. resolve paths). Failure is handled by the process_node
     * function itself; on success, update the XMLProcessingResult instance. */
    if(process_node(node, preprocessingResult))
    {
        std::stringstream buffer;

        document.save(buffer);

        preprocessingResult.description = "OK";
        preprocessingResult.output = buffer.str();
    }

    return preprocessingResult;
}
