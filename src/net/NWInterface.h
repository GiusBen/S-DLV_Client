#ifndef S_DLV_CLIENT_NWINTERFACE_H
#define S_DLV_CLIENT_NWINTERFACE_H

#include <sstream>
#include <string>
#include <stdexcept>

#include <dlib/iosockstream.h>

class NWInterface
{
    private:
        static const unsigned long DEFAULT_TIMEOUT;
        static const char EOM;

        dlib::iosockstream iosockstream;

        bool initialized;

    public:
        NWInterface();

        bool init(const std::string &, const unsigned short);
        void quit();

        std::string push(const std::string &);
};

#endif // S_DLV_CLIENT_NWINTERFACE_H
