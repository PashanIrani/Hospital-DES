#include "RoomSystem.h"


RoomSystem::RoomSystem(Heap<Event> * eventList, Init * init, Global * global) {
  this->queue = new Heap<Patient>();
  this->eventList = eventList;
  this->init = init;
  this->global = global;
}

/* Steps that will be common in all routines for this system, and that need to be performed first */
void RoomSystem::beforeEventRoutine(Event * event) {
  global->clock = event->event_time;
  std::cout << "[RS @ " << global->clock << "] " << event->eventTypeToString() << " for Patient " << event->item->patientID << std::endl;
}

RoomSystem::~RoomSystem() {

}

void RoomSystem::performArrival(Event * event) {

  beforeEventRoutine(event);
  
  NumberGenerator * ng = init->getNumberGenerator(3);
  event->item->service_time = ng->next();
  event->item->arrival_time_room = global->clock;
  std::cout << "RS service time: " << event->item->service_time <<  std::endl;
  delete ng;

  queue->push(event->item);


  int roomNum = global->getFreeRoom();


  if (roomNum!=-1) {
    Event * service_event = new Event(START_SERVICE, event->item->arrival_time_room, event->item, SYSTEM_ROOM, roomNum);
    eventList->push(service_event);  
  }

}

void RoomSystem::performService(Event * event) {
  beforeEventRoutine(event);

  (&global->rooms[event->roomId])->isAvailable = false;

  double departing_time = global->clock + event->item->service_time;

  Patient * servicing_patient = queue->pop();

  // Create departure event
  Event * departure_event = new Event(DEPARTURE, departing_time, servicing_patient, SYSTEM_ROOM, event->roomId);
  eventList->push(departure_event);
}

void RoomSystem::performDeparture(Event * event) {
  beforeEventRoutine(event);

  Patient * departing_patient = event->item; 
  
  (&global->rooms[event->roomId])->isAvailable = true;
  
  if (queue->getSize() > 0) {
        Event * service_event = new Event(START_SERVICE, global->clock, queue->getHead(), SYSTEM_ROOM, event->roomId);
        eventList->push(service_event);
  }
  
  // delete departing_patient;

  
}