#include "NurseSystem.h"
#include "NumberGenerator.h"
#include <iostream>

/* Initilizes a queue, and stores the program's eventList and init class for later usage */ 
NurseSystem::NurseSystem(Heap<Event> * eventList, Init * init, Global * global) {
  this->queue = (Queue<Patient> *) malloc(sizeof(Queue<Patient>));

  // initing to make c++ happy
  this->queue->head = NULL;
  this->queue->tail = NULL;

  this->eventList = eventList;
  this->init = init;
  this->global = global;
}

/* Frees memory */ 
NurseSystem::~NurseSystem() {
  FreeNodes(queue);
  free(queue);
}

/* Steps that will be common in all routines for this system, and that need to be performed first */
void NurseSystem::beforeEventRoutine(Event * event) {
  global->clock = event->event_time;
  std::cout << "[NS @ " << global->clock << "] " << event->eventTypeToString() << std::endl;
}

/* Arrival event routine */ 
void NurseSystem::performArrival(Event * event) {
  beforeEventRoutine(event);
  
  NumberGenerator * ng = init->getNumberGenerator(6); 
  event->item->service_time = ng->next(); // determine service time
  delete ng;

  std::cout << "Service Time For Arriving patient: " << event->item->service_time <<  std::endl;
  
  // If no patients in queue, begin service
  if (CountNodes(queue) == 0) {
    Event * service_event = new Event(START_SERVICE, global->clock, event->item, SYSTEM_NURSE);
    eventList->push(service_event);
  }

  Insert(queue, event->item);
}

/* Service Event Routine */ 
void NurseSystem::performService(Event * event) {
  beforeEventRoutine(event);
  
  double departing_time = global->clock + event->item->service_time;

  // Create departure event
  Event * departure_event = new Event(DEPARTURE, departing_time, event->item, SYSTEM_NURSE);
  eventList->push(departure_event);
}

/* Departure Event Routine */ 
void NurseSystem::performDeparture(Event * event) {
  beforeEventRoutine(event);

  Patient * departing_patient = Delete(queue); // remove departing patient from queue

  // If more nodes in queue, start service for next patient
  if (CountNodes(queue) > 0) {
    Event * service_event = new Event(START_SERVICE, global->clock, queue->head->item, SYSTEM_NURSE);
    eventList->push(service_event);
  }

  delete departing_patient; // TODO: this patient will then enter the Room Queue (heap).
}