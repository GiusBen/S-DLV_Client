#include "Tester.h"

// ***********
// * PRIVATE *
// ***********

bool Tester::findEncoding()
{
    cout << "Looking for encoding... " << flush;

    stringstream filename;
    filename << workdir << "/" << "enc.dl";

    FILE * f_encoding = fopen(filename.str().c_str(), "r");
    bool result = (f_encoding != NULL);

    cout << (result ? "" : "not ") << "found." << endl;
    fclose(f_encoding);

    return result;
}

bool Tester::enumerateFactFiles()
{
    cout << "Enumerating fact files... " << flush;

    FILE * fact_file;
    unsigned counter = 0;

    while(true)
    {
        stringstream filename;
        bool result;

        filename << workdir << "/" << counter << ".dl";
        fact_file = fopen(filename.str().c_str(), "r");
        result = (fact_file != NULL);
        fclose(fact_file);

        if(!result)
            break;

        counter++;
    }

    cout << "found " << counter << ", ";
    fact_files_no = counter;

    if(counter)
        cout << "up to " << (counter - 1) << ".dl." << endl;
    else
        cout << "abort." << endl;

    return (bool) counter;
}

bool Tester::connect()
{
    cout << "Connecting to server... " << flush;

    try
    {
        nwInterface.init(DEFAULT_ADDRESS, DEFAULT_PORT);

        cout << "done." << endl;
    }
    catch(exception & exception)
    {
        cout << "failed --> " << exception.what() << endl;

        return false;
    }

    return true;
}

void Tester::computePermutations()
{
    cout << "Computing permutations (this may take a while)... " << flush;

    unsigned counter = 0;

    permutations.resize(fact_files_no);

    while(counter < fact_files_no)
    {
        Sequence first_seq;

        first_seq.push_back(counter);
        permutations[counter].push_back(first_seq);

        for(auto level = 0; level < counter; level++)
            for(auto seq : permutations[level])
                for(int i = 0; i <= seq.size(); i++)
                {
                    Sequence new_seq = seq;
                    auto it = next(new_seq.begin(), i);

                    new_seq.insert(it, counter);
                    permutations[counter].push_back(new_seq);
                }

        counter++;
    }

    cout << "done.\n";
}

void Tester::printPermutations()
{
    for(auto level = 0; level < permutations.size(); level++)
    {
        cout << level << ": ";

        for(auto seq : permutations[level])
        {
            cout << "{";

            for(int pos = 0; pos < seq.size(); pos++)
            {
                cout << seq[pos];

                if(pos < seq.size() - 1)
                    cout << ",";
            }

            cout << "}";
        }

        cout << "\n";
    }
}

// **********
// * PUBLIC *
// **********

void Tester::run(int argc, char * * argv)
{
    if(argc < 2)
    {
        cout << "No path specified.\n";
        exit(-1);
    }

    workdir = argv[1];

    if(findEncoding() && enumerateFactFiles() && connect())
    {
        computePermutations();

        std::cout << "\n\n";

        stringstream outfile;
        stringstream file_to_ground;

        for(auto level : permutations)
            for(auto seq : level)
            {
                outfile.str("");
                outfile << workdir << "/enc.dl";

                file_to_ground.str("");
                file_to_ground << "<put path=\""
                               << workdir << "/"
                               << "enc.dl" << "\"/>";

                std::cout << nwInterface.push(file_to_ground.str()) << endl;
                std::cout << nwInterface.push("<gr/>") << endl;

                outfile.str("");
                outfile << workdir << "/out/";

                for(int i = 0; i < seq.size(); i++)
                {
                    outfile << seq[i];

                    if(i < seq.size() - 1)
                        outfile << "_";
                }

                outfile << ".out";

                for(int i = 0; i < seq.size(); i++)
                {
                    file_to_ground.str("");

                    file_to_ground << "<put path=\""
                                   << workdir << "/"
                                   << seq[i] << ".dl"
                                   << "\"/>";

                    std::cout << nwInterface.push(file_to_ground.str()) << endl;
                    std::cout << nwInterface.push("<gr/>") << endl;
                }

                string result = nwInterface.push("<read/>");
                std::cout << result << endl;

                FILE * out = fopen(outfile.str().c_str(), "w");
                fputs(result.c_str(), out);

                std::cout << nwInterface.push("<reset/>") << endl;
            }
    }
}
