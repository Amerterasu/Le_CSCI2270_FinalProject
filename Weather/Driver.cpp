#include <iostream>
#include <fstream>
#include "Weather.h"
using namespace std;

int main(int argc, char* argv[])
{
    ifstream infile;
    //infile.open(argv[1]);
    infile.open("BoulderWeatherData.txt");

    string line;

    if(infile.is_open())
    {
        while (getline(infile, line))
        {
            if (line.substr(0,4) == "Date" || line.empty() == true)
            {

            }
            else
            {
                cout << line << endl;
            }

            cout << "end" << endl;
        }
    }
    else
    {
        cout << "Unable to open the file you specified." << endl;
    }

    return 0;
}
