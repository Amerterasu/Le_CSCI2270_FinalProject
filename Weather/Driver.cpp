#include <iostream>
#include <fstream>
#include "Weather.h"
#include <stdlib.h>
#include <sstream>
using namespace std;

void displayMenu();

int main(int argc, char* argv[])
{
    ifstream infile;

    // not sure if we are going to use command line arguments to get the file
    // either way I've created both methods just in case
    //infile.open(argv[1]);
    infile.open("BoulderWeatherData.txt");
    Weather w;
    string line, first;
    int counter = 0;
    dayNode* newNode;
    if(infile.is_open())
    {
        //gets first line which is just the header of the table
        getline(infile, first);
        while (getline(infile, line))
        {
            newNode = new dayNode;
            //removes all commas and fills in the data for each dayNode accordingly
            stringstream ss(line);
           while(getline(ss, line, ',')){

                switch(counter){
                case 0:
                    newNode->date = line;
                    counter++;
                    break;
                case 1:
                    //skip days, only need the date
                    counter++;
                    break;
                case 2:
                    newNode->high = atoi(line.c_str());
                    counter++;
                    break;
                case 3:
                    newNode->low = atoi(line.c_str());
                    counter++;
                    break;
                case 4:
                    newNode->percip = atof(line.c_str());
                    counter++;
                    break;
                case 5:
                    newNode->snow = atof(line.c_str());
                    counter++;
                    break;
                case 6:
                    newNode->snow_depth = atof(line.c_str());
                    counter = 0;
                    break;
                }
           }
           w.addDay(newNode);
        }
    }
    else
    {
        cout << "Unable to open the file you specified." << endl;
    }
    //w.printTable();
    int input = 0;
    bool quit = false;
    string day;
    dayNode* temp = new dayNode;

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
                    cout << "Enter a day (DD/MM/YY):" << endl;
                    getline(cin, day);
                    temp = w.findDay(day);
                    cout << "On this day:" << endl;
                    if(temp->high == 0)
                        cout << "No date found, check if your input is correct" << endl;
                    else
                        cout<<temp->date<<"- High:"<<temp->high<<" Low:"<<temp->low<<" Percip:"<<temp->percip<<" Snow:"<<temp->snow<<" Snow Depth:"<<temp->snow_depth<<endl;
                break;
            // Example Function
            case 2:
                    temp = w.getHighSnow();
                    cout << "High Snow:" << endl;
                    cout<<temp->date<<"- High:"<<temp->high<<" Low:"<<temp->low<<" Percip:"<<temp->percip<<" Snow:"<<temp->snow<<" Snow Depth:"<<temp->snow_depth<<endl;
                break;
            // Example Function
            case 3:
                    temp = w.getHigh();
                    cout << "High:" << endl;
                    cout<<temp->date<<"- High:"<<temp->high<<" Low:"<<temp->low<<" Percip:"<<temp->percip<<" Snow:"<<temp->snow<<" Snow Depth:"<<temp->snow_depth<<endl;
                break;
            // Example Function
            case 4:
                    temp = w.getLow();
                    cout << "Low:" << endl;
                    cout<<temp->date<<"- High:"<<temp->high<<" Low:"<<temp->low<<" Percip:"<<temp->percip<<" Snow:"<<temp->snow<<" Snow Depth:"<<temp->snow_depth<<endl;
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
}
