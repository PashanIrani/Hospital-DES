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
  
  this->ng = init->getNumberGenerator(global->mu_evaluation);
}

/* Frees memory */ 
NurseSystem::~NurseSystem() {
  //FreeNodes(queue);
  free(queue);
  delete ng;
}

/* Steps that will be common in all routines for this system, and that need to be performed first */
void NurseSystem::beforeEventRoutine(Event * event) {
  global->updateClock(event->event_time); // update current time

  // debug LOG
  if (global->DEBUG) {
    std::cout << "(NS @ " << global->clock << ") - " << event->eventTypeToString() << " - " << event->item->toString() << std::endl;
  }
}

/* Arrival event routine */ 
void NurseSystem::performArrival(Event * event) {
  beforeEventRoutine(event);

  event->item->service_time = ng->next(); // determine service time
    
  // increment count of total patients in the system
  global->total_patients++;

  // add patient to a FCFS queue
  Insert(queue, event->item);

  // debug LOG
  if (global->DEBUG)
  std::cout << "Service Time For Arriving patient: " << event->item->service_time <<  std::endl;
  
  // Free queue if hospital terminates after 24 hrs
  if (global->clock + event->item->service_time >=24){
    Delete(queue);
  }
  // starts service if there is an available server
  if (CountNodes(queue) <= global->m1) {
    Event * service_event = new Event(START_SERVICE, event->item->arrival_time, event->item, SYSTEM_NURSE, NULL);
    eventList->push(service_event);
    queue->current = queue->tail;
  }
  
}

/* Service Event Routine */ 
void NurseSystem::performService(Event * event) {
  beforeEventRoutine(event);

  // determine departing time
  double departing_time = global->clock + event->item->service_time;
  
  // Create departure event
  Event * departure_event = new Event(DEPARTURE, departing_time, event->item, SYSTEM_NURSE, NULL);
  eventList->push(departure_event);
}

/* Departure Event Routine */ 
void NurseSystem::performDeparture(Event * event) {
  beforeEventRoutine(event);

  Patient * departing_patient = Delete(queue); // remove departing patient from queue
  
  // record wait time for queue E
  global->totalWaitE += global->clock - event->item->arrival_time;
  
  // if there are patients awaiting service, start their service
  if(CountNodes(queue) > 0 && queue->current->next != NULL){
    Event * service_event = new Event(START_SERVICE, global->clock, queue->current->next->item, SYSTEM_NURSE, NULL);
    eventList->push(service_event);
    queue->current = queue->current->next;
  }

  // This patient will then enter the Room Queue.
  Event * room_arrival_event = new Event(ARRIVAL, global->clock, departing_patient, SYSTEM_ROOM, NULL);
  eventList->push(room_arrival_event);
}