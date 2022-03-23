#include <iostream>
#include <random>
#include "Heap.h"
#include "init.h"
#include "Event.h"
#include "Queue.h"
#include "NurseSystem.h"

int main(int argc, char const *argv[])
{
  // TODO: read args

  Init * initialize = new Init(500); // Init class with seed of 500 

  int size = 100;
  Patient ** ps = initialize->recieve_patients(size); // get patients

  Heap<Event> * eventList = new Heap<Event>(); // initialize event list

  int incomingPatientIndex = 0; // point to first paitent arriving to hospital
  Event *firstPatientArrival = new Event(ARRIVAL, ps[incomingPatientIndex]->arrival_time, ps[incomingPatientIndex], SYSTEM_NURSE); // create an arrival event for it
  eventList->push(firstPatientArrival); // add to event list
  
  NurseSystem * ns = new NurseSystem(eventList, initialize); // initialize nurseSystem

  while (eventList->getSize() > 0) {
    Event * currentEvent = eventList->pop(); // Get next event;

    switch (currentEvent->event_type)
    {
    case ARRIVAL:
      // If a Nurse System event; perform it's arrival
      if (currentEvent->system_type == SYSTEM_NURSE) ns->performArrival(currentEvent);

      incomingPatientIndex++; // increment index for next patient
      
      // Create next arrival for Nurse System if patients are still arriving to the hospital
      if (incomingPatientIndex < size)
      eventList->push(new Event(ARRIVAL, ps[incomingPatientIndex]->arrival_time, ps[incomingPatientIndex], SYSTEM_NURSE));

      break;
    
    case START_SERVICE:
      // If a Nurse System event; perform it's service
      if (currentEvent->system_type == SYSTEM_NURSE) ns->performService(currentEvent);
      break;

    case DEPARTURE:
      // If a Nurse System event; perform it's departure
      if (currentEvent->system_type == SYSTEM_NURSE) ns->performDeparture(currentEvent);
      break;
    }

    delete currentEvent;
  }

  // Free Stuff
  delete ns;
  free(ps);
  delete eventList;
  delete initialize;
  
  return 0;
}
