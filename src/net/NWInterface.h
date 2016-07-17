#ifndef S_DLV_CLIENT_NWINTERFACE_H
#define S_DLV_CLIENT_NWINTERFACE_H

#include <sstream>
#include <string>

#include <dlib/iosockstream.h>

class NWInterface
{
    private:
        static const unsigned long DEFAULT_TIMEOUT;
        static const char EOM;

        dlib::iosockstream iosockstream;

    public:
        bool start(const std::string &, const unsigned short);
        const char * push(const std::string &);
};

#endif // S_DLV_CLIENT_NWINTERFACE_H
