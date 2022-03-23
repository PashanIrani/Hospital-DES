#include "NurseSystem.h"
#include "NumberGenerator.h"
#include <iostream>

NurseSystem::NurseSystem(Heap<Event> * eventList, Init * init) {
  this->queue = (Queue<Patient> *) malloc(sizeof(Queue<Patient>)); 
  this->eventList = eventList;
  this->init = init;
}

void NurseSystem::performArrival(Event * event) {
  std::cout << "[NS] ARRIVAL" << std::endl;

  NumberGenerator * ng = init->getNumberGenerator(5); 
  event->item->service_time = ng->next(); // determin service time

  Insert(queue, event->item);

  // double wait_time = getWaitTimeOfQueue();

  Event * service_event = new Event(START_SERVICE, event->item->arrival_time + wait_time, event->item, NURSE_SYSTEM);
  eventList->push(service_event);

  delete ng;
}

void NurseSystem::performService(Event * event) {
  std::cout << "[NS] SERVICE" << std::endl;
  // wait_time += service_time;
}

void NurseSystem::performDeparture(Event * event) {
  std::cout << "[NS] DEPARTURE" << std::endl;
  // delete event;
}