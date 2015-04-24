#ifndef WEATHER_H_INCLUDED
#define WEATHER_H_INCLUDED

struct dayNode{
    std::string date;
    int high;
    int low;
    int percip;
    int snow;
    int snow_depth;
    dayNode* next;
};
class Weather{
public:
    void addDay();
    dayNode* getHead();
    dayNode* getHigh();
    dayNode* getTimeInterval(std::string start, std::string end); //returns head of a new separate linked list
    dayNode* getLow();
    dayNode* findDay(std::string time);
    dayNode* getHighInterval(dayNode* head, std::string criteria);
    dayNode* getHighSnow();
    dayNode* getHighPercip();
    dayNode* averageTemp(dayNode* head);
    dayNode* averagePercip(dayNode* head);

private:
    dayNode* head;
};


#endif // WEATHER_H_INCLUDED
