#include "SDLVC_CLI.h"

int main(int argc, char * * argv)
{
    // TODO: parse options

    SDLVC_CLI::prompt_loop("localhost", 4790);

    return 0;
}