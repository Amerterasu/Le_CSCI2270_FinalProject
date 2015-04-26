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
}
//destructor
Weather::~Weather(){

}
/*
Method: hashSum
Purpose: produces hashcode form the date of the node
Return: hashcode
*/
/*
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

    int newNodeFirst = newNode->date.find('/') + 1;
    int newNodeSecond = newNode->date.find_last_of('/') - 1;
    int newNodeDay = atoi(newNode->date.substr(newNodeFirst, newNode->date.size() - newNodeSecond).c_str());
    cout<<newNodeDay<<endl;
    int index = hashSum(newNode->date);
    //if the index has never used
    if(hashTable[index].next == NULL && hashTable[index].high == -1){
        hashTable[index] = *newNode;
        hashTable[index].next = NULL;
    }
    //if the index has been used but there is no linked list
    else if(hashTable[index].next == NULL && hashTable[index].high != -1){
        int firstSlash = hashTable[index].date.find('/');
        int secondSlash = hashTable[index].date.find_last_of('/');
        int day = atoi(hashTable[index].date.substr(firstSlash, secondSlash).c_str());

        if(day >= newNodeDay){
           //temporarily storing first node at that index
            dayNode* temp = new dayNode(hashTable[index].date, hashTable[index].high, hashTable[index].low, hashTable[index].precip, hashTable[index].snow, hashTable[index].snow_depth, hashTable[index].next);
            temp->next = NULL;
            newNode->next = temp;
            hashTable[index] = *newNode;
            hashTable[index].next = temp;
            //cout<<hashTable[index].title<<hashTable[index].year<<"->"<<hashTable[index].next->title<<":"<<hashTable[index].next->year<<endl;
        }else{
            hashTable[index].next = newNode;
        }
    }
    //if the index has a linked list
    else{
        dayNode* temp = &hashTable[index];
        //if the node at the head of list is greater than the newNode then replace the head
        int firstSlash = hashTable[index].date.find('/');
        int secondSlash = hashTable[index].date.find_last_of('/');
        int day = atoi(hashTable[index].date.substr(firstSlash, secondSlash).c_str());
        if(day > newNodeDay){
            dayNode* secondTemp = new dayNode(hashTable[index].date, hashTable[index].high, hashTable[index].low, hashTable[index].precip, hashTable[index].snow, hashTable[index].snow_depth, hashTable[index].next);
            secondTemp->next = hashTable[index].next;
            newNode->next = secondTemp;
            hashTable[index] = *newNode;
        }
        //however if it is not then search through the whole list for its place
        else{
            int tempfirstSlash, tempsecondSlash, tempday;
            while(temp != NULL){
                 tempfirstSlash = temp->date.find('/');
                 tempsecondSlash = temp->date.find_last_of('/');
                 tempday = atoi(temp->date.substr(firstSlash, secondSlash).c_str());

                if(temp->next != NULL && temp->next->date < newNode->date)
                    temp = temp->next;
                else
                    break;
            }
            if(temp->next == NULL)
                temp->next = newNode;
            else{
                newNode->next = temp->next;
                temp->next = newNode;
        }
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
/*
Method: findDay
Purpose: return the day to which the user wants, expected formate DD/MM/YY. Ex: 8/5/13, 12/13/13;
Return: dayNode
*/
dayNode* Weather::findDay(std::string time)
{
    dayNode* day;
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
void Weather::sortIndexbyHigh(){

}
