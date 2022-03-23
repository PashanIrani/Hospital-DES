#include "Heapable.h"
#include <iostream>
#include "Patient.h"

#pragma once

enum EventType { ARRIVAL, START_SERVICE, DEPARTURE };
enum SystemType { NURSE_SYSTEM };

class Event : Heapable {
  public:
    EventType event_type;
    double event_time;
    Patient * item; 
    SystemType system_type;

    Event(EventType event_type, double event_time, Patient * item, SystemType system_type) {
      this->event_type = event_type;
      this->event_time = event_time;
      this->item = item;
      this->system_type = system_type;
    }

    ~Event() {}
    
    double compareTo(Event * other)  {
      return this->event_time  - other->event_time;
    }

    void print()  {
      std::cout << "[type: " << this->eventTypeToString() << ", time: "<< this->event_time << "]" << std::endl;
    }

    std::string eventTypeToString() {
      switch (this->event_type)
      {
      case ARRIVAL:
        return "ARRIVAL";
        break;
      
      case START_SERVICE:
        return "START_SERVICE";
        break;

      case DEPARTURE:
        return "DEPARTURE";
        break;
        
      default:
        return "UNDEFINED";
        break;
      }
    }
};