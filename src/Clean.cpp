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

  this->ng = init->getNumberGenerator(global->mu_cleanup);
}

/* Steps that will be common in all routines for this system, and that need to be performed first */
void Clean::beforeEventRoutine(Event * event) {
  global->updateClock(event->event_time); // updates current time

  // debug LOG
  if (global->DEBUG) {
    std::cout << "(CS @ " << global->clock << ") - " << event->eventTypeToString() << " - [roomId: " << event->room->roomId << "]" << std::endl;
  }
}

Clean::~Clean() {
  FreeNodes(queue);
  free(queue);
  delete ng;
}

void Clean::performArrival(Event * event) {
  beforeEventRoutine(event);
  
  event->room->needed_cleanup_time = global->clock; // Store the time this room needed cleanup
  event->room->service_time = ng->next(); // determine service time

  // add room to queue to await cleanup
  Insert(queue, event->room);

  // debug LOG
  if (global->DEBUG)
  std::cout << "Service Time For cleaning room: " << event->room->service_time <<  std::endl;
  
  // If available server, start cleanup
  if (CountNodes(queue)  <= global->m2) {
    Event * service_event = new Event(START_SERVICE, global->clock, NULL, SYSTEM_CLEAN, event->room);
    eventList->push(service_event);
    queue->current = queue->tail;
  }
}

/* Service Event Routine */ 
void Clean::performService(Event * event) {
  beforeEventRoutine(event);

  // determine departing time
  double departing_time = global->clock + event->room->service_time;

  // Create departure event
  Event * departure_event = new Event(DEPARTURE, departing_time, NULL, SYSTEM_CLEAN, event->room);
  eventList->push(departure_event);
}

void Clean::performDeparture(Event * event) {
  beforeEventRoutine(event);

  Room * departing_room = Delete(queue); // remove departing patient from queue

  // mark room to available, so it can start service for next patient
  event->room->isAvailable = true;

  global->totalWaitR += global->clock - departing_room->needed_cleanup_time;
  global->totalRoomsCleaned++;

  // if patients are waiting for a room, start the next patient's service
  if(hqueue->getSize() > 0){
    Event * service_event = new Event(START_SERVICE, global->clock, hqueue->getHead(), SYSTEM_ROOM, event->room);
    eventList->push(service_event);
  }

  // if another room is awaiting cleanup, start it's clean up
  if(CountNodes(queue) >0 && queue->current->next!=NULL){
    Event * service_event = new Event(START_SERVICE, global->clock, NULL, SYSTEM_CLEAN, event->room);
    eventList->push(service_event);
    queue->current = queue->current->next;
  }
}
