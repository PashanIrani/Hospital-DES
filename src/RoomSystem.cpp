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

  // set arrival time of when patient arrive in the room system
  event->item->arrival_time_room_system = global->clock;

  // debug LOG
  if (global->DEBUG)
  std::cout << "RS service time: " << event->item->service_time <<  std::endl;

  // add event to priority queue, to await for service
  queue->push(event->item);

  // get a free room for this patient
  Room* availRoom = global->getFreeRoom();

  // if Room is available, start their service!
  if (availRoom != NULL) {
    Event * service_event = new Event(START_SERVICE, event->item->arrival_time_room_system, event->item, SYSTEM_ROOM, availRoom);
    eventList->push(service_event);  
  }
}

/*
Performs service for patients
*/
void RoomSystem::performService(Event * event) {
  beforeEventRoutine(event);

  // Mark room where this service is taking place to false
  event->room->isAvailable = false;

  // determine departing time
  double departing_time = global->clock + event->item->service_time;

  // remove patient from queue (patient is being serviced, they are no longer in the 'waiting room')
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
  
  // Grab departing patient
  Patient * departing_patient = event->item; 

  // Send room for cleaning
  Event * clean_event = new Event(ARRIVAL, global->clock, NULL, SYSTEM_CLEAN, event->room);
  eventList->push(clean_event);
  
  // Decrement total patients as one just left the system
  global->total_patients--;
}

