#include "NurseSystem.h"
#include "NumberGenerator.h"
#include <iostream>

/* Initilizes a queue, and stores the program's eventList and init class for later usage */ 
NurseSystem::NurseSystem(Heap<Event> * eventList, Init * init) {
  this->queue = (Queue<Patient> *) malloc(sizeof(Queue<Patient>));

  // initing to make c++ happy
  this->queue->head = NULL;
  this->queue->tail = NULL;

  this->eventList = eventList;
  this->init = init;
}

/* Frees memory */ 
NurseSystem::~NurseSystem() {
  FreeNodes(queue);
  free(queue);
}

// double NurseSystem::getWaitTime() {
//   queue
// }

/* Arrival event routine */ 
void NurseSystem::performArrival(Event * event) {
  std::cout << "[NS] ARRIVAL" << std::endl;

  NumberGenerator * ng = init->getNumberGenerator(5); 
  event->item->service_time = ng->next(); // determin service time
  delete ng;

  Insert(queue, event->item);

  // double wait_time = getWaitTime();

  Event * service_event = new Event(START_SERVICE, event->item->arrival_time + wait_time, event->item, SYSTEM_NURSE);
  eventList->push(service_event);
}

/* Service Event Routine */ 
void NurseSystem::performService(Event * event) {
  std::cout << "[NS] SERVICE" << std::endl;
  // wait_time += service_time;
}

/* Departure Event Routine */ 
void NurseSystem::performDeparture(Event * event) {
  std::cout << "[NS] DEPARTURE" << std::endl;
}