#include <iostream>
#include <random>
#include "Heap.h"
#include "Init.h"
#include "Event.h"
#include "Queue.h"
#include "NurseSystem.h"
#include "RoomSystem.h"
#include "Global.h"

int main(int argc, char const *argv[])
{


  // TODO: read args
  
  Init * initialize = new Init(500); // Init class with seed of 500 
  Global * global = new Global();

  int size = 6;
  Patient ** ps = initialize->recieve_patients(size); // get patients

  // DEBUG: Print Patients
  for (int i = 0; i < size; ++i) {
    std::cout << "Patient " << i << " - ";
    ps[i]->print();
  }

  std::cout << std::endl << " ----- " << std::endl << std::endl;

  Heap<Event> * eventList = new Heap<Event>(); // initialize event list

  int incomingPatientIndex = 0; // point to first paitent arriving to hospital
  Event *firstPatientArrival = new Event(ARRIVAL, ps[incomingPatientIndex]->arrival_time, ps[incomingPatientIndex], SYSTEM_NURSE, -1); // create an arrival event for it
  eventList->push(firstPatientArrival); // add to event list
  
  NurseSystem * ns = new NurseSystem(eventList, initialize, global); // initialize nurseSystem
  RoomSystem * rs = new RoomSystem(eventList, initialize, global); // initialize nurseSystem
  

  while (eventList->getSize() > 0) {
    Event * currentEvent = eventList->pop(); // Get next event;
    switch (currentEvent->event_type)
    {
    case ARRIVAL:
      // If a Nurse System event; perform it's arrival
      if (currentEvent->system_type == SYSTEM_NURSE) ns->performArrival(currentEvent);
      if (currentEvent->system_type == SYSTEM_ROOM) rs->performArrival(currentEvent);

      incomingPatientIndex++; // increment index for next patient
      
      // Create next arrival for Nurse System if patients are still arriving to the hospital
      if (incomingPatientIndex < size)
      eventList->push(new Event(ARRIVAL, ps[incomingPatientIndex]->arrival_time, ps[incomingPatientIndex], SYSTEM_NURSE, -1));

      break;
    
    case START_SERVICE:
      // If a Nurse System event; perform it's service
      if (currentEvent->system_type == SYSTEM_NURSE) ns->performService(currentEvent);
      if (currentEvent->system_type == SYSTEM_ROOM) rs->performService(currentEvent);
      break;

    case DEPARTURE:
      // If a Nurse System event; perform it's departure
      if (currentEvent->system_type == SYSTEM_NURSE) ns->performDeparture(currentEvent);
      if (currentEvent->system_type == SYSTEM_ROOM) rs->performDeparture(currentEvent);
      break;
    }

    delete currentEvent;
  }

  cout<< "Average Wait time: "<<global->totalWaitE/size<<endl;
  // Free Stuff
  delete ns;
  delete eventList;
  delete initialize;
  delete global;
  for (int i = 0; i < size; ++i) {
    delete ps[i];
  }
  free(ps);
  
  return 0;
}
