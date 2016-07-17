#include "NWInterface.h"

// ***********
// * PRIVATE *
// ***********

const unsigned long NWInterface::DEFAULT_TIMEOUT = 5000;
const char NWInterface::EOM = '\0';

// **********
// * PUBLIC *
// **********

bool NWInterface::start(const std::string & address, const unsigned short port)
{
    /* Close iosockstream gracefully if already open */
    iosockstream.close(DEFAULT_TIMEOUT);

    dlib::network_address full_address(address, port);

    try
    {
        iosockstream.open(full_address, DEFAULT_TIMEOUT);
    }
    catch(std::exception & exception)
    {
        std::cerr << "Couldn't reach server at "
                  << address << ":" << port
                  << std::endl;

        return false;
    }

    return true;
}

const char * NWInterface::push(const std::string & msg)
{
    if(!iosockstream.good())
        return NULL;

    std::string reply;

    iosockstream << msg << EOM;

    std::getline(iosockstream, reply, EOM);

    return reply.c_str();
}