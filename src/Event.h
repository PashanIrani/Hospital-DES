#include "Heapable.h"
#include <iostream>
#include "Patient.h"
#include "Room.h"

#pragma once

enum EventType { ARRIVAL, START_SERVICE, DEPARTURE};
enum SystemType { SYSTEM_NURSE, SYSTEM_ROOM, SYSTEM_CLEAN };

class Event : Heapable {
  public:
    // Deteremins the type of event
    EventType event_type;

    // Time the event occurs
    double event_time;

    // Patient related to this event
    Patient * item; 

    // The type of system this event belongs to.
    SystemType system_type;

    Room * room;

    Event(EventType event_type, double event_time, Patient * item, SystemType system_type, Room* room) {
      this->event_type = event_type;
      this->event_time = event_time;
      this->item = item;
      this->system_type = system_type;
      this->room = room;
    }

    ~Event() {}

    /* Compare function to order events in a heap */    
    double compareTo(Event * other)  {
      return this->event_time  - other->event_time;
    }

    /* Print Function */ 
    void print()  {
      std::cout << "[type: " << this->eventTypeToString() << ", time: "<< this->event_time << "]" << std::endl;
    }

    /* Returns event type in a readable string, used for debug purposes */ 
    std::string eventTypeToString() {
      switch (this->event_type)
      {
      case ARRIVAL:
        return "ARRIVAL";
        break;
      
      case START_SERVICE:
        return "SERVICE";
        break;

      case DEPARTURE:
        return "DEPART ";
        break;

      default:
        return "UNDEFINED";
        break;
      }
    }
};