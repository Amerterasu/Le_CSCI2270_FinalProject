#include "Weather.h"
#include <iostream>
#include <stdlib.h>
using namespace std;
//constructor
Weather::Weather(){
    /*
        the tableSize number was chose by the (total data points)/ (acceptable linked list size) = 1339/4 ~ 335
        the closest prime number to 335 is 337 so therefore the tableSize is estimated to be 337
    */
    tableSize = 12;
    hashTable = new dayNode[tableSize];
    //initialize the hashTable
    //the high, when -1, represents an unused position in the table
    for(int i = 0;i < tableSize; i++){
        hashTable[i].high = -1;
    }

    month * m = new month;
    months = new month[12];
    //initialize months array
    for(int i = 0; i < 12; i++)
    {
        if(i == 0){
            m->name = "January";
            m->number = i+1;
            months[i] = *m;
        }
        if(i == 1){
            m->name = "February";
            m->number = i+1;
            months[i] = *m;
        }
        if(i == 2){
            m->name = "March";
            m->number = i+1;
            months[i] = *m;
        }
        if(i == 3){
            m->name = "April";
            m->number = i+1;
            months[i] = *m;
        }
        if(i == 4){
            m->name = "May";
            m->number = i+1;
            months[i] = *m;
        }
        if(i == 5){
            m->name = "June";
            m->number = i+1;
            months[i] = *m;
        }
        if(i == 6){
            m->name = "July";
            m->number = i+1;
            months[i] = *m;
        }
        if(i == 7){
            m->name = "August";
            m->number = i+1;
            months[i] = *m;
        }
        if(i == 8){
            m->name = "September";
            m->number = i+1;
            months[i] = *m;
        }
        if(i == 9){
            m->name = "October";
            m->number = i+1;
            months[i] = *m;
        }
        if(i == 10){
            m->name = "November";
            m->number = i+1;
            months[i] = *m;
        }
        if(i == 11){
            m->name = "December";
            m->number = i+1;
            months[i] = *m;
        }
    }
}
//destructor
Weather::~Weather(){

}
/*
Method: hashSum
Purpose: produces hashcode form the date of the node
Return: hashcode
*/
int Weather::hashSum(std::string k){
    int index;
    int slash = k.find('/');
    int month = atoi(k.substr(0, slash).c_str());
    index = month - 1;
    return index;
}
/*
Method: addDay
Purpose: Adds a dayNode to the hashTable in sorted order by string comparison of the dates
Returns: nothing
*/
void Weather::addDay(dayNode* newNode){
    newNode->next = NULL;
    newNode->prev = NULL;

    int index = hashSum(newNode->date);
    int firstSlash = newNode->date.find('/');
    int secondSlash = newNode->date.find_last_of('/') ;
    int day = atoi(newNode->date.substr(firstSlash+1, 3).c_str());
    int year = atoi(newNode->date.substr(secondSlash+1, 3).c_str());

    // if index is empty
    if(hashTable[index].high == -1){
        hashTable[index] = *newNode;
    }
    else{
        dayNode * temp = &hashTable[index];

        int indexSlash = hashTable[index].date.find('/');
        int secondIndexSlash = hashTable[index].date.find_last_of('/') ;
        int indexDay = atoi(hashTable[index].date.substr(indexSlash+1, 3).c_str());
        int indexYear = atoi(hashTable[index].date.substr(secondIndexSlash+1, 3).c_str());

        while(temp != NULL){
            int tempSlash = temp->date.find('/');
            int sTempSlash = newNode->date.find_last_of('/') ;
            int tempDay = atoi(temp->date.substr(tempSlash+1, 3).c_str());
            int tempYear = atoi(temp->date.substr(sTempSlash+1, 3).c_str());

            //day is less and year is less than the very first node in the list
            if(day < indexDay && year <= indexYear){
                hashTable->prev = newNode;
                newNode->next = &hashTable[index];
                hashTable[index] = *newNode;
                break;
            }
            // day is less and year is less than the current node
            else if(day < tempDay && year <= tempYear){
                newNode->prev = temp->prev;
                temp->prev->next = newNode;
                temp->prev = newNode;
                newNode->next = temp;
                break;
            }
            // if at end of the list
            else if(temp->next == NULL){
                temp->next = newNode;
                newNode->prev = temp;
                break;
            }
            temp = temp->next;
        }
    }
}
/*
Method: printTable
Purpose: to print out hashTable. Mostly for testing.
Return: Nothing
*/
void Weather::printTable(){
    for(int i = 0; i < tableSize; i++){
        dayNode* temp = &hashTable[i];
        while(temp != NULL){
            cout<<temp->date<<"- High:"<<temp->high<<" Low:"<<temp->low<<" Precip:"<<temp->precip<<" Snow:"<<temp->snow<<" Snow Depth:"<<temp->snow_depth<<endl;
            temp= temp->next;
        }
        cout<<"end of linked list"<<endl;
    }
}
/*
Method: getHigh
Purpose: return the day with the all-time highest temp
Return: dayNode with highest temperature
*/
dayNode* Weather::getHigh()
{
    dayNode* hi = new dayNode;
    hi->high = 0;
    for(int i = 0; i < tableSize; i++){
        dayNode* temp = &hashTable[i];
        while(temp != NULL){
            if(temp->high > hi->high)
                hi = temp;
            temp= temp->next;
        }
    }

    return hi;
}
/*
Method: getLow
Purpose: return the day with the all-time lowest temp
Return: dayNode with lowest temperature
*/
dayNode* Weather::getLow()
{
    dayNode* low = new dayNode;
    low->low = 0;
    for(int i = 0; i < tableSize; i++){
        dayNode* temp = &hashTable[i];
        while(temp != NULL){
            if(temp->low < low->low)
                low = temp;
            temp= temp->next;
        }
    }
    return low;
}
/*
Method: getHighSnow
Purpose: return the day with the all-time highest snow
Return: dayNode with highest snow
*/
dayNode* Weather::getHighSnow()
{
    dayNode* sHi = new dayNode;
    sHi->snow = 0;
    for(int i = 0; i < tableSize; i++){
        dayNode* temp = &hashTable[i];
        while(temp != NULL){
            if(temp->snow > sHi->snow)
                sHi = temp;
            temp= temp->next;
        }
    }
    return sHi;
}

double Weather::totalSnow(){
    int total = 0;
    double answer = 0.0;
    for(int i = 0; i < tableSize; i++){
        dayNode* temp = &hashTable[i];
        while(temp != NULL){
            total += temp->snow;
            temp= temp->next;
        }
    }
    answer = total;
    return answer;

}

/*
Method: findDay
Purpose: return the day to which the user wants, expected formate DD/MM/YY. Ex: 8/5/13, 12/13/13;
Return: dayNode
*/
dayNode* Weather::findDay(std::string time)
{
    dayNode* day = new dayNode;
    for(int i = 0; i < tableSize; i++){
        dayNode* temp = &hashTable[i];
        while(temp != NULL){
            if(time == temp->date)
                day = temp;
            temp= temp->next;
        }
    }
    return day;
}
/*
Method: getHighPrecip
Purpose: finds highest precipitation in the table
Return: dayNode
*/
dayNode* Weather::getHighPercip(){
    dayNode* largest = new dayNode;
    for(int i = 0; i < tableSize; i++){
        dayNode* temp = &hashTable[i];
        while(temp != NULL){
            if(temp->precip > largest->precip)
                largest = temp;
            temp= temp->next;
        }
    }
    return largest;
}
/*
Method: averageHighTemp()
Purpose: finds the average high through the table
Return: double
*/
double Weather::averageHighTemp(){
    int total = 0;
    int total_data = 0;
    double answer = 0.0;
    for(int i = 0; i < tableSize; i++){
        dayNode* temp = &hashTable[i];
        while(temp != NULL){
            total += temp->high;
            total_data++;
            temp= temp->next;
        }
    }
    answer = total/ total_data;
    return answer;
}
/*
Method: averagePrecip()
Purpose: Finds the average precipitation through the table
Return: double
*/
double Weather::averagePrecip(){
    double total = 0;
    int total_data = 0;
    double answer = 0.0;
    for(int i = 0; i < tableSize; i++){
        dayNode* temp = &hashTable[i];
        while(temp != NULL){
            total += temp->precip;
            total_data++;
            temp= temp->next;
        }
    }
    answer = total/ total_data;
    return answer;
}
/*
Method: getDataForMonth()
Purpose: Finds data for a certain month overall, or for a certain month in a specific year
Return: Nothing
*/
void Weather::getDataForMonth(std::string mon, std::string year){
    double hiSnow = -100.0;
    int hiTemp = -100;
    int lowTemp = 100;
    double hiPrecip = -100.0;
    int daysWSnow = 0;

    // -1 means user wants it from all years
    bool all = false;
    if (year == "-1")
        all = true;
    //all years
    if(all == true)
    {
        // find the index where the month data is stored
        int index = 0;
        for (int i = 0; i < 12; ++i)
        {
            if (mon == months[i].name){
                index = months[i].number-1;
                break;
            }
        }

        dayNode * temp = new dayNode;

        //find all of the data
        temp = &hashTable[index];
        while (temp != NULL)
        {
            if(temp->snow > hiSnow)
                hiSnow = temp->snow;

            if(temp->high > hiTemp)
                hiTemp = temp->high;

            if(temp->low < lowTemp)
                lowTemp = temp->low;

            if(temp->precip > hiPrecip)
                hiPrecip = temp->precip;

            if(temp->snow > 0)
                daysWSnow++;

            temp = temp->next;
        }

        cout << "Data for the month of " << mon << " in all years:" << endl;
        cout << "High Snow:" << hiSnow << " High:" << hiTemp << " Low:" << lowTemp << " High Precipitation:" << hiPrecip << " Days With Snow:" << daysWSnow << endl;
    }
    // a specific year
    else
    {
        int index = 0;
        for (int i = 0; i < 12; ++i)
        {
            if (mon == months[i].name){
                index = months[i].number-1;
                break;
            }
        }

       int y = atoi(year.substr(2,2).c_str());

       dayNode * temp = &hashTable[index];

       while (temp != NULL)
       {
           int secondSlash = temp->date.find_last_of('/');
           int tempY = atoi(temp->date.substr(secondSlash+1, 2).c_str());

           if (tempY == y)
            {
                if(temp->snow > hiSnow)
                hiSnow = temp->snow;

                if(temp->high > hiTemp)
                    hiTemp = temp->high;

                if(temp->low < lowTemp)
                    lowTemp = temp->low;

                if(temp->precip > hiPrecip)
                    hiPrecip = temp->precip;

                if(temp->snow > 0)
                    daysWSnow++;
           }
           temp = temp->next;
       }

       cout << "Data for the month of " << mon << " in the year " << year << ":" << endl;
       cout << "High Snow:" << hiSnow << " High:" << hiTemp << " Low:" << lowTemp << " High Precipitation:" << hiPrecip << " Days With Snow:" << daysWSnow << endl;
    }
}
