#ifndef S_DLV_CLIENT_TESTER_H
#define S_DLV_CLIENT_TESTER_H

#include <iostream>
#include <sstream>
#include <vector>

#include "../net/NWInterface.h"

#define DEFAULT_ADDRESS "localhost"
#define DEFAULT_PORT 4790

using namespace std;

typedef vector<int> Sequence;
typedef vector<Sequence> Level;
typedef vector<Level> SeqTable;

class Tester
{
    private:
        char * workdir;
        unsigned fact_files_no;
        SeqTable permutations;
        NWInterface nwInterface;

        bool findEncoding();
        bool enumerateFactFiles();
        bool connect();

        void computePermutations();
        void printPermutations();

    public:
        void run(int, char * *);
};

#endif // S_DLV_CLIENT_TESTER_H