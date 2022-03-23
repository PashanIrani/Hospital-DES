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
  Event *firstPatientArrival = new Event(ARRIVAL, ps[incomingPatientIndex]->arrival_time, ps[incomingPatientIndex], NURSE_SYSTEM); // create an arrival event for it
  eventList->push(firstPatientArrival); // add to event list
  
  NurseSystem * ns = new NurseSystem(eventList, initialize); // initialize nurseSystem

  while (eventList->getSize() > 0) {
    Event * currentEvent = eventList->pop();

    switch (currentEvent->event_type)
    {
    case ARRIVAL:
      if (currentEvent->system_type == NURSE_SYSTEM) ns->performArrival(currentEvent);

      incomingPatientIndex++; // increment index for next patient
      
      if (incomingPatientIndex < size)
      eventList->push(new Event(ARRIVAL, ps[incomingPatientIndex]->arrival_time, ps[incomingPatientIndex], NURSE_SYSTEM));

      break;
    
    case START_SERVICE:
      if (currentEvent->system_type == NURSE_SYSTEM) ns->performService(currentEvent);
      break;

    case DEPARTURE:
      if (currentEvent->system_type == NURSE_SYSTEM) ns->performDeparture(currentEvent);
      break;
    }

    delete currentEvent;
  }

  // Free Stuff
  delete ns;
  free(ps);
  delete eventList;
  delete initialize;

  // Load Queue : Nurses (E) 

  // struct Queue<Patient> * queueE = (Queue<Patient> *) malloc(sizeof(Queue<Patient>)); 
  
  // for (int i = 0; i < size; ++i) {
  //   Insert(queueE, ps[i]);
  // }
  


  














  // IDEA:
  // NurseSystem ns {
  //   performArrival(EVENT) {
  //     jsdgjlkdfg
  //     el.add(start_serive, ns);

  //   }
  // };
  // RoomSystem rs;
  // CleanSystem cs;

  // EvenList el;

  // el.add(ARRIVAL for ns);

  // clock = 0;


  // while (!el.isEmpty()) {
  //   event = el.first()

  //   event->SYSTEM === NURSE ? :
  //     event->type === ARRIVAL ?
  //       ns->performArrival(event, eventList);

  // }

  // SERVICE
  // 1. nurse performs a "service" for X amount of time

  










  // struct Queue<Patient> * queueE = (Queue<Patient> *) malloc(sizeof(Queue<Patient>));

  
  // for (int i = 0; i < size; ++i) {
  //   Insert(queueE, ps[i]);
  // }

  // std::cout << CountNodes(queueE) << std::endl;

  // for (int i = 0; i < size; ++i) {
  //   Patient * leaving_patient = Delete(queueE);
  //   std::cout << leaving_patient->arrival_time << std::endl;
  // } 


  return 0;
}
