#include <iostream>
#include <random>
#include "Heap.h"
#include "Init.h"
#include "Event.h"
#include "Queue.h"
#include "NurseSystem.h"
#include "RoomSystem.h"
#include "Global.h"
#include "Clean.h"

int main(int argc, char const *argv[])
{


  // TODO: read args
  
  Global * global = new Global();

  Init * initialize = new Init(500); // Init class with seed of 500 

  
  Patient ** ps = initialize->recieve_patients(); // get patients
  int size = initialize->totalPatients;

  // DEBUG: Print Patients
  for (int i = 0; i < size; ++i) {
    std::cout << "Patient " << i << " - ";
    ps[i]->print();
  }

  std::cout << std::endl << " ----- " << std::endl << std::endl;

  Heap<Event> * eventList = new Heap<Event>(); // initialize event list

  int incomingPatientIndex = 0; // point to first paitent arriving to hospital
  Event *firstPatientArrival = new Event(ARRIVAL, ps[incomingPatientIndex]->arrival_time, ps[incomingPatientIndex], SYSTEM_NURSE, NULL); // create an arrival event for it
  eventList->push(firstPatientArrival); // add to event list
  
  NurseSystem * ns = new NurseSystem(eventList, initialize, global); // initialize nurseSystem
  RoomSystem * rs = new RoomSystem(eventList, initialize, global); // initialize nurseSystem
  Clean *cs = new Clean(eventList, initialize, global, rs->queue);

  while (eventList->getSize() > 0) {
    Event * currentEvent = eventList->pop(); // Get next event;
    switch (currentEvent->event_type)
    {
    case ARRIVAL:
      // If a Nurse System event; perform it's arrival
      if (currentEvent->system_type == SYSTEM_NURSE) ns->performArrival(currentEvent);
      if (currentEvent->system_type == SYSTEM_ROOM) rs->performArrival(currentEvent);
      if (currentEvent->system_type == SYSTEM_CLEAN) cs->performArrival(currentEvent);

      incomingPatientIndex++; // increment index for next patient
      
      // Create next arrival for Nurse System if patients are still arriving to the hospital
      if (incomingPatientIndex < size)
      eventList->push(new Event(ARRIVAL, ps[incomingPatientIndex]->arrival_time, ps[incomingPatientIndex], SYSTEM_NURSE, NULL));

      break;
    
    case START_SERVICE:
      // If a Nurse System event; perform it's service
      if (currentEvent->system_type == SYSTEM_NURSE) ns->performService(currentEvent);
      if (currentEvent->system_type == SYSTEM_ROOM) rs->performService(currentEvent);
      if (currentEvent->system_type == SYSTEM_CLEAN) cs->performService(currentEvent);
      break;

    case DEPARTURE:
      // If a Nurse System event; perform it's departure
      if (currentEvent->system_type == SYSTEM_NURSE) ns->performDeparture(currentEvent);
      if (currentEvent->system_type == SYSTEM_ROOM) rs->performDeparture(currentEvent);
      if (currentEvent->system_type == SYSTEM_CLEAN) cs->performDeparture(currentEvent);
      break;
    }
    
    delete currentEvent;
  }

  cout<< "Average Wait time: "<<global->totalWaitE/size<<endl;
  // Free Stuff

  for (int i = 0; i < size; ++i) {
    std::cout << "Patient " << i << " - ";
    ps[i]->print();
  }


  delete ns;
  delete rs;
  delete cs;
  delete eventList;
  delete initialize;
  delete global;

  for (int i = 0; i < size; ++i) {
    delete ps[i];
  }
  free(ps);
  
  return 0;
}
