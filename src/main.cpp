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

/*
$$\   $$\  $$$$$$\   $$$$$$\  $$$$$$$\ $$$$$$\ $$$$$$$$\  $$$$$$\  $$\             $$$$$$$\  $$$$$$$$\  $$$$$$\  
$$ |  $$ |$$  __$$\ $$  __$$\ $$  __$$\\_$$  _|\__$$  __|$$  __$$\ $$ |            $$  __$$\ $$  _____|$$  __$$\ 
$$ |  $$ |$$ /  $$ |$$ /  \__|$$ |  $$ | $$ |     $$ |   $$ /  $$ |$$ |            $$ |  $$ |$$ |      $$ /  \__|
$$$$$$$$ |$$ |  $$ |\$$$$$$\  $$$$$$$  | $$ |     $$ |   $$$$$$$$ |$$ |            $$ |  $$ |$$$$$\    \$$$$$$\  
$$  __$$ |$$ |  $$ | \____$$\ $$  ____/  $$ |     $$ |   $$  __$$ |$$ |            $$ |  $$ |$$  __|    \____$$\ 
$$ |  $$ |$$ |  $$ |$$\   $$ |$$ |       $$ |     $$ |   $$ |  $$ |$$ |            $$ |  $$ |$$ |      $$\   $$ |
$$ |  $$ | $$$$$$  |\$$$$$$  |$$ |     $$$$$$\    $$ |   $$ |  $$ |$$$$$$$$\       $$$$$$$  |$$$$$$$$\ \$$$$$$  |
\__|  \__| \______/  \______/ \__|     \______|   \__|   \__|  \__|\________|      \_______/ \________| \______/ 
CMPT305 Project 1 - Pashan Irani, Manav Meghpara & Divij Gupta
*/
int main(int argc, char const *argv[])
{
  if (argc < 14) {
    std::cout << "Insufficient number of arguments provided!" << std::endl;
    return -1;
  }


  Global * global = new Global(); // init global class; used to access certain values throughout the program

  // grab command line arguments and store them 
  //TODO: validate the args
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

  global->initRooms(); // init rooms
  
  Init * initialize = new Init(global->seed); // Object creation class, used to provide us with objects and random numbers

  Patient ** ps = initialize->recieve_patients(global->lambda_high, global->lambda_med, global->lambda_low); // initializee patients
  
  int patients_count = initialize->totalPatients; // get number of patients that were initialized 

  // DEBUG: Print Patients
  if (global->DEBUG) {
    for (int i = 0; i < patients_count; ++i) {
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
      if (currentEvent->system_type == SYSTEM_NURSE){
        // check if there is room, otherwise tell them to "buzz off"
        if(global->total_patients < global->B)
          ns->performArrival(currentEvent);
        else
          global->total_leaving_patients++; // count how many patients had to leave
      }
      // If a Room System event; perform it's arrival
      if (currentEvent->system_type == SYSTEM_ROOM) rs->performArrival(currentEvent);

      // If a Clean System event; perform it's arrival
      if (currentEvent->system_type == SYSTEM_CLEAN) cs->performArrival(currentEvent);

      incomingPatientIndex++; // increment index for next patient

      // Create next arrival for Nurse System if patients are still arriving to the hospital
      if (incomingPatientIndex < patients_count)
      eventList->push(new Event(ARRIVAL, ps[incomingPatientIndex]->arrival_time, ps[incomingPatientIndex], SYSTEM_NURSE, NULL));

      break;

      case START_SERVICE:
        // If a Nurse System event; perform it's service
        if (currentEvent->system_type == SYSTEM_NURSE) ns->performService(currentEvent);

        // If a Room System event; perform it's service
        if (currentEvent->system_type == SYSTEM_ROOM) rs->performService(currentEvent);

        // If a Clean System event; perform it's service
        if (currentEvent->system_type == SYSTEM_CLEAN) cs->performService(currentEvent);
        break;

      case DEPARTURE:
        // If a Nurse System event; perform it's departure
        if (currentEvent->system_type == SYSTEM_NURSE) ns->performDeparture(currentEvent);

        // If a Room System event; perform it's departure
        if (currentEvent->system_type == SYSTEM_ROOM) rs->performDeparture(currentEvent);

        // If a Clean System event; perform it's departure
        if (currentEvent->system_type == SYSTEM_CLEAN) cs->performDeparture(currentEvent);
        break;
      }

    delete currentEvent;
  }

  // debug LOG
  if (global->DEBUG) {
    cout<< "Average Wait time: "<<global->totalWaitE/patients_count<<endl;

    for (int i = 0; i < patients_count; ++i) {
      std::cout << "Patient " << i << " - ";
      ps[i]->print();
    }
  }

  std::cout<< "Total Patients who leave because system is full: "<< global->total_leaving_patients<<std::endl;

  // Free Pointers ----
  delete ns;
  delete rs;
  delete cs;
  delete eventList;
  delete initialize;
  delete global;
  
  for (int i = 0; i < patients_count; ++i) {
    delete ps[i];
  }
  free(ps);

  // ----

  // fin.
  return 0;
}
