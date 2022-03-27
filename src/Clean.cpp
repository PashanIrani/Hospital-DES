#include "Clean.h"
#include "Queue.h"
#include "NumberGenerator.h"
#include <iostream>

Clean::Clean(Heap<Event> * eventList, Init * init, Global * global, Heap<Patient> * hqueue) {
  this->queue = (Queue<Room> *) malloc(sizeof(Queue<Room>));

  // initing to make c++ happy
  this->queue->head = NULL;
  this->queue->tail = NULL;

  this->eventList = eventList;
  this->init = init;
  this->global = global;
  this->hqueue = hqueue;
}

/* Steps that will be common in all routines for this system, and that need to be performed first */
void Clean::beforeEventRoutine(Event * event) {
  global->clock = event->event_time;
  std::cout << "[CS @ " << global->clock << "] " << event->eventTypeToString() << " for Room " << event->room->roomId<< std::endl;
}

Clean::~Clean() {
  FreeNodes(queue);
  free(queue);
}

void Clean::performArrival(Event * event) {
  beforeEventRoutine(event);

  NumberGenerator * ng = init->getNumberGenerator(3); 
  event->room->service_time = ng->next(); // determine service time
  delete ng;

  Insert(queue, event->room);
  std::cout << "Service Time For cleaning room: " << event->room->service_time <<  std::endl;
  

  if (CountNodes(queue)  <= global->m2) {
    Event * service_event = new Event(START_SERVICE, global->clock, NULL, SYSTEM_CLEAN, event->room);
    eventList->push(service_event);
    queue->current = queue->tail;
  }
}

/* Service Event Routine */ 
void Clean::performService(Event * event) {
  beforeEventRoutine(event);
  double departing_time = global->clock + event->room->service_time;

  // Create departure event
  Event * departure_event = new Event(DEPARTURE, departing_time, NULL, SYSTEM_CLEAN, event->room);
  eventList->push(departure_event);
}


void Clean::performDeparture(Event * event) {
  beforeEventRoutine(event);

  Room * departing_room = Delete(queue); // remove departing patient from queue

  event->room->isAvailable = true;

  if(hqueue->getSize() > 0){
    Event * service_event = new Event(START_SERVICE, global->clock, hqueue->getHead(), SYSTEM_ROOM, event->room);
    eventList->push(service_event);
  }

  if(CountNodes(queue) >0 && queue->current->next!=NULL){
    Event * service_event = new Event(START_SERVICE, global->clock, NULL, SYSTEM_CLEAN, event->room);
    eventList->push(service_event);
    queue->current = queue->current->next;
  }
}
