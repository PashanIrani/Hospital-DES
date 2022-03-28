#include "RoomSystem.h"


RoomSystem::RoomSystem(Heap<Event> * eventList, Init * init, Global * global) {
  this->queue = new Heap<Patient>();
  this->eventList = eventList;
  this->init = init;
  this->global = global;

  // init number generators with their respective means
  this->ng_high = init->getNumberGenerator(global->mu_high);
  this->ng_med = init->getNumberGenerator(global->mu_med);
  this->ng_low = init->getNumberGenerator(global->mu_low);
}

/* Steps that will be common in all routines for this system, and that need to be performed first */
void RoomSystem::beforeEventRoutine(Event * event) {
  global->clock = event->event_time; // updates current time

  // Debug log
  if (global->DEBUG) {
    std::cout << "(RS @ " << global->clock << ") - " << event->eventTypeToString() << " - " << event->item->toString() << std::endl;
  }
}

RoomSystem::~RoomSystem() {
  delete queue;
  delete ng_high;
  delete ng_med;
  delete ng_low;
}

/*
Performs arrival for patients
*/
void RoomSystem::performArrival(Event * event) {
  beforeEventRoutine(event);
  
  // determine service time based on patient's classification
  switch (event->item->classification)
  {
  case HIGH:
    event->item->service_time = ng_high->next();
    break;
  case MEDIUM:
    event->item->service_time = ng_med->next();
    break;
  case LOW:
    event->item->service_time = ng_low->next();
    break; 
  default:
    break;
  }

  
  event->item->arrival_time_room = global->clock;

  if (global->DEBUG)
  std::cout << "RS service time: " << event->item->service_time <<  std::endl;

  queue->push(event->item);

  Room* availRoom = global->getFreeRoom();


  if (availRoom!=NULL) {
    Event * service_event = new Event(START_SERVICE, event->item->arrival_time_room, event->item, SYSTEM_ROOM, availRoom);
    eventList->push(service_event);  
  }

}

/*
Performs service for patients
*/
void RoomSystem::performService(Event * event) {
  beforeEventRoutine(event);

  event->room->isAvailable = false;

  double departing_time = global->clock + event->item->service_time;

  Patient * servicing_patient = queue->pop();

  // Create departure event
  Event * departure_event = new Event(DEPARTURE, departing_time, servicing_patient, SYSTEM_ROOM, event->room);
  eventList->push(departure_event);
}

/*
Performs departure for patients
*/
void RoomSystem::performDeparture(Event * event) {
  beforeEventRoutine(event);
  global->total_patients--;
  Patient * departing_patient = event->item; 

  Event * clean_event = new Event(ARRIVAL, global->clock, NULL, SYSTEM_CLEAN, event->room);
  eventList->push(clean_event);
  
  

}

