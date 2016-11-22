#include "NWInterface.h"

// **********
// * PUBLIC *
// **********

NWInterface::NWInterface() : initialized(false) { }

bool NWInterface::init(const std::string & address, const unsigned short port)
{
    dlib::network_address socket(address, port);

    if(!initialized)
        try
        {
            iosockstream.open(socket, DEFAULT_TIMEOUT);
            initialized = true;
            return true;
        }
        catch(std::exception & exception)
        {
            std::stringstream error_message;

            error_message << "Couldn't reach server at "
                          << "'" << address << ":" << port << "'"
                          << std::endl;

            throw std::runtime_error(error_message.str());
        }

    return false;
}

void NWInterface::quit()
{
    iosockstream.close(DEFAULT_TIMEOUT);
}

std::string NWInterface::push(const std::string & msg)
{
    if(!iosockstream.good())
        throw std::runtime_error
                ("Can't push message onto a closed connection.");

    std::string reply;

    iosockstream << msg << EOM;

    std::getline(iosockstream, reply, EOM);

    return reply;
}