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

  if (argc >= 14){

    Global * global = new Global();
    global->lambda_high = atof(argv[1]);
    global->lambda_med = atof(argv[2]);
    global->lambda_low = atof(argv[3]);
    global->mu_evaluation = atof(argv[4]);
    global->mu_high = atof(argv[5]);
    global->mu_med = atof(argv[6]);
    global->mu_low = atof(argv[7]);
    global->mu_cleanup = atof(argv[8]);
    global->B = atoi(argv[9]);
    global->R = atoi(argv[10]);
    global->m1 = atoi(argv[11]);
    global->m2 = atoi(argv[12]);
    global->seed = atoi(argv[13]);

    global->initRooms();
    //todo: validate the args
    
    Init * initialize = new Init(global->seed); // Init class with seed of 500 

    
    Patient ** ps = initialize->recieve_patients(global->lambda_high, global->lambda_med, global->lambda_low); // get patients
    int size = initialize->totalPatients;

    // DEBUG: Print Patients
    if (global->DEBUG) {
      for (int i = 0; i < size; ++i) {
        std::cout << "Patient " << i << " - ";
        ps[i]->print();
      }

      std::cout << std::endl << " ----- " << std::endl << std::endl;
    }

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

    if (global->DEBUG) {
      cout<< "Average Wait time: "<<global->totalWaitE/size<<endl;
      // Free Stuff

      int high = 0;
      for (int i = 0; i < size; ++i) {
        std::cout << "Patient " << i << " - ";
        ps[i]->print();
        if (ps[i]->classification == HIGH) {
          high++;
        }
      }

      std::cout << "High Patients: " << high << std::endl;

    }

    // Free Pointers
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
  }
  else {
    std::cout << "Insufficient number of arguments provided!" << std::endl;
  }
  
  return 0;
}
