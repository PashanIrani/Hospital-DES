#include "Heapable.h"
#include <iostream>

enum EventType { ARRIVAL, START_SERVICE, DEPARTURE };

class Event : Heapable {
  public:
    EventType event_type;
    double event_time;

    Event(EventType event_type, double event_time);
    ~Event();
    
    double compareTo(Event *);
    void print();
    std::string eventTypeToString();
};