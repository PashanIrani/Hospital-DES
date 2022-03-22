#include <iostream>
#include "Event.h"

// Constructor Defination
Event::Event(EventType event_type, double event_time) {
  this->event_type = event_type;
  this->event_time = event_time;
}

Event::~Event() { /* nothing to destructor, but adding a defination to make the compiler happy */ }

// Compare function between 2 events
double Event::compareTo(Event * other)  {
  return this->event_time  - other->event_time;
}

// prints data for Event
void Event::print()  {
  std::cout << "[type: " << this->eventTypeToString() << ", time: "<< this->event_time << "]" << std::endl;
}

// Returns a string identifier of the EventType
std::string Event::eventTypeToString() {
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