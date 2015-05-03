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
                    newNode->precip = atof(line.c_str());
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
    int input = 0;
    bool quit = false;
    string day;
    string usr_input;
    string month;
    string y;
    string year;
    dayNode* temp = new dayNode;
    dayNode* input_node = new dayNode;
    double average = 0.0;
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
                    cout << "Enter a day (MM/DD/YY). If the date only has a units digit (M/D/YY):" << endl;
                    getline(cin, day);
                    temp = w.findDay(day);
                    cout << "On this day:" << endl;
                    if(temp->high == 0)
                        cout << "No date found, check if your input is correct" << endl;
                    else
                        cout<<temp->date<<"- High:"<<temp->high<<" Low:"<<temp->low<<" Precip:"<<temp->precip<<" Snow:"<<temp->snow<<" Snow Depth:"<<temp->snow_depth<<endl;
                break;
            // Example Function
            case 2:
                    temp = w.getHighSnow();
                    cout<<"Date:"<<temp->date<<endl;
                    cout << "High Snow:" << temp->snow<<endl;
                break;
            // Example Function
            case 3:
                    temp = w.getHigh();
                    cout<<"Date:"<<temp->date<<endl;
                    cout << "High Temp:" << temp->high<<endl;
                break;
            // Example Function
            case 4:
                    temp = w.getLow();
                    cout<<"Date:"<<temp->date<<endl;
                    cout << "Low Temp:" << temp->low<< endl;
                break;
            case 5:
                    temp = w.getHighPercip();
                    cout<<"Date:"<<temp->date<<endl;
                    cout<<"Highest Precipitation:"<<temp->precip<<endl;
                break;
            case 6:
                    average = w.averageHighTemp();
                    cout<<"Average of High Temp:"<<average<<endl;
                break;
            case 7:
                    average = w.averagePrecip();
                    cout<<"Average of Precipitation:"<<average<<endl;
                break;
            case 8:
                    cout<<"Date:";
                    getline(cin, usr_input);
                    if ((usr_input.find_first_of('/') != 2) || (usr_input.find_last_of('/') != 5) ){
                        cout << "Incorrect Format" << endl;
                        break;
                    }
                    input_node->date = usr_input;
                    cout<<"High:";
                    getline(cin, usr_input);
                    input_node->high = atoi(usr_input.c_str());
                    cout<<"Low:";
                    getline(cin, usr_input);
                    input_node->high = atoi(usr_input.c_str());
                    cout<<"Precipitation:";
                    getline(cin, usr_input);
                    input_node->high = atof(usr_input.c_str());
                    cout<<"Snow:";
                    getline(cin, usr_input);
                    input_node->high = atof(usr_input.c_str());
                    cout<<"Snow Depth:";
                    getline(cin, usr_input);
                    input_node->high = atof(usr_input.c_str());
                break;
            case 9:
                    cout << "Enter a month:" << endl;
                    getline(cin, month);
                    cout << "Do you want this data from a specific year? Y/N" << endl;
                    getline(cin, y);
                    if(y == "Y"){
                        cout << "Which year?" << endl;
                        getline(cin, year);
                        w.getDataForMonth(month, year);
                    }
                    else
                        w.getDataForMonth(month, "-1");
                break;
            case 10:
                    w.printTable();
                break;
            // Quit
            case 11:
                    average = w.totalSnow();
                    cout<<"Total Snow: "<<average<<endl;
            case 12:
                    std::cout << "Goodbye!" << std::endl;
                    quit = true;
                break;
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
    std::cout << "This program runs on data from 1/1/10 through 8/31/13" << std::endl;
    std::cout << "====== Main Menu ======" << std::endl;
    std::cout << "1. Find Date" << std::endl;
    std::cout << "2. Highest Snow" << std::endl;
    std::cout << "3. Highest Temperature " << std::endl;
    std::cout << "4. Lowest Temperature" << std::endl;
    std::cout << "5. Highest Precipitation" << std::endl;
    std::cout << "6. Average High Temperature" << std::endl;
    std::cout << "7. Average Precipitation" << std::endl;
    std::cout << "8. Add Data Point" << std::endl;
    std::cout << "9. Find Data For A Specific Month" << std::endl;
    std::cout << "10. Print Data" << std::endl;
    std::cout << "11. Total Snow" << std::endl;
    std::cout << "12. Quit" << std::endl;
}
