#ifndef S_DLV_CLIENT_SDLVC_CLI_H
#define S_DLV_CLIENT_SDLVC_CLI_H

#include <iostream>
#include <string>

#include "net/NWInterface.h"
#include "xmlproc/XMLProcessor.h"

namespace SDLVC_CLI
{
    void prompt_loop(const std::string & address = "localhost",
                     const unsigned short port = 4790)
    {
        NWInterface nwInterface;

        /* Try to estabilsh a connection using the
         * NWInterface object. Upon failure, it collects
         * and prints the error message, then leaves
         * the function. */
        try
        {
            nwInterface.init(address, port);
        }
        catch(std::exception & exception)
        {
            std::cout << "! [NETWORK ERROR] : "
                      << exception.what()
                      << std::endl;

            return;
        }

        /* Connection established. */

        XMLProcessor xmlProcessor;
        XMLProcessingResult result;

        bool exit_requested = false;
        std::string tmp_buffer;

        /* Loop until an 'exit' string is typed in. */
        do
        {
            std::cout << std::endl << "[READY]"
                      << std::endl << "> "
                      << std::flush;

            std::getline(std::cin, tmp_buffer);

            if(tmp_buffer == "exit")
                exit_requested = true;
            else
            {
                /* Call the XMLProcessor instance to look for syntax
                 * errors and paths to resolve. */
                result = xmlProcessor.process(tmp_buffer);

                if(!result.error)
                    try
                    {
                        /* Send the message to the server. If everything's
                         * alright, collect the reply and print it. */
                        tmp_buffer = nwInterface.push(result.output);

                        std::cout << std::endl
                                  << "[REPLY]" << std::endl
                                  << tmp_buffer << std::endl;
                    }
                    catch(std::exception & exception)
                    {
                        std::cout << "! [NETWORK ERROR] : "
                                  << exception.what()
                                  << std::endl;
                    }
                else
                    std::cout << std::endl
                              << "! [XML PROCESSING ERROR]" << std::endl
                              << result.report << std::endl;
            }
        }
        while(!exit_requested);

        nwInterface.quit();

        std::cout << std::endl
                  << "Bye."
                  << std::endl;
    }
}

#endif // S_DLV_CLIENT_SDLVC_CLI_H
