#ifndef WEATHER_H_INCLUDED
#define WEATHER_H_INCLUDED

#include <iostream>
struct dayNode{
    std::string date;
    int high;
    int low;
    double precip;
    double snow;
    double snow_depth;
    dayNode* next;
    //empty constructor
    dayNode(){
        date = "";
        high = 0;
        low = 0;
        precip = 0;
        snow = 0;
        snow_depth = 0;
        next = NULL;
    };
    //overloaded instructor for copying purposes
    dayNode(std::string in_date, int in_high, int in_low, int in_precip, int in_snow, int in_snow_depth, dayNode* in_next){
        date = in_date;
        low = in_low;
        precip = in_precip;
        snow = in_snow;
        snow_depth = in_snow_depth;
    }
};
class Weather{
public:
    Weather();
    ~Weather();
    void addDay(dayNode* x);
    void printTable();
    dayNode* getHigh();
    //dayNode* getTimeInterval(std::string start, std::string end); //returns head of a new separate linked list
    dayNode* getLow();
    dayNode* findDay(std::string time);
    //dayNode* getHighInterval(dayNode* head, std::string criteria);
    dayNode* getHighSnow();
    dayNode* getHighPercip();
    double averageHighTemp();
    double averagePrecip();

private:
    int hashSum(std::string x);
    dayNode* hashTable;
    int tableSize;
};


#endif // WEATHER_H_INCLUDED
