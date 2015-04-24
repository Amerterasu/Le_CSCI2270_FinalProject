#include <iostream>
#include <fstream>
#include "Weather.h"

using namespace std;

void displayMenu();

int main(int argc, char* argv[])
{
    ifstream infile;

    // not sure if we are going to use command line arguments to get the file
    // either way I've created both methods just in case
    //infile.open(argv[1]);
    infile.open("BoulderWeatherData.txt");

    string line;

    if(infile.is_open())
    {
        while (getline(infile, line))
        {
            // exclude the first line and all empty lines
            if (line.substr(0,4) != "Date" && line.empty() == false)
            {
                // parse line
            }
        }
    }
    else
    {
        cout << "Unable to open the file you specified." << endl;
    }

    int input = 0;
    bool quit = false;

    while(quit != true)
    {
        displayMenu();
        std::cin >> input;

        //clear out cin
        std::cin.clear();
        std::cin.ignore(10000,'\n');

        switch (input)
        {
            // Example Function
            case 1:
                break;
            // Example Function
            case 2:
                break;
            // Example Function
            case 3:
                break;
            // Example Function
            case 4:
                break;
            // Quit
            case 5:
                std::cout << "Goodbye!" << std::endl;
                quit = true;
                break;
            // invalid input
            default:
                std::cout << "Invalid Input" << std::endl;
                std::cin.clear();
                std::cin.ignore(10000,'\n');
                break;
        }
    }
    return 0;
}

void displayMenu()
{
    std::cout << "====== Main Menu ======" << std::endl;
    std::cout << "1. Example Function" << std::endl;
    std::cout << "2. Example Function" << std::endl;
    std::cout << "3. Example Function" << std::endl;
    std::cout << "4. Example Function" << std::endl;
    std::cout << "5. Quit" << std::endl;
    return;
}
