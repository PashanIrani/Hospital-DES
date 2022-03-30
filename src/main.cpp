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
  // If not enough arguments, exit.
  if (argc < 14) {
    std::cout << "Insufficient number of arguments provided!" << std::endl;
    return -1;
  }

  Global * global = new Global(); // init global class; used to access certain values throughout the program

  // Grab command line arguments and store them:

  // Mean of inter-arrival time for High patients
  global->lambda_high = atof(argv[1]);
  if (global->lambda_high <= 0.0) {
    std::cout << "Lambda High must be > 0" << std::endl;
    return -1; 
  }

  // Mean of inter-arrival time for med patients
  global->lambda_med = atof(argv[2]);
  if (global->lambda_med <= 0.0) {
    std::cout << "Lambda Medium must be > 0" << std::endl;
    return -1; 
  }

  // Mean of inter-arrival time for low patients
  global->lambda_low = atof(argv[3]);
  if (global->lambda_low <= 0.0) {
    std::cout << "Lambda Low must be > 0" << std::endl;
    return -1; 
  }

  // Mean of evaluation time for patients
  global->mu_evaluation = atof(argv[4]);
  if (global->mu_evaluation <= 0.0) {
    std::cout << "Mu Evaluation must be > 0" << std::endl;
    return -1; 
  }

  // Mean of service time for high patients
  global->mu_high = atof(argv[5]);
  if (global->mu_high <= 0.0) {
    std::cout << "Mu High must be > 0" << std::endl;
    return -1; 
  }

  // Mean of service time for medium patients
  global->mu_med = atof(argv[6]);
  if (global->mu_med <= 0.0) {
    std::cout << "Mu Medium must be > 0" << std::endl;
    return -1; 
  }

  // Mean of service time for low patients
  global->mu_low = atof(argv[7]);
  if (global->mu_low <= 0.0) {
    std::cout << "Mu Low must be > 0" << std::endl;
    return -1; 
  }

  // Mean of  cleanup times
  global->mu_cleanup = atof(argv[8]);
  if (global->mu_cleanup <= 0.0) {
    std::cout << "Mu Cleanup must be > 0" << std::endl;
    return -1; 
  }

  // B: capactiy of hospital
  global->B = atoi(argv[9]);
  if (global->B <= 0.0) {
    std::cout << "B must be > 0" << std::endl;
    return -1; 
  }

  // R: Number of rooms
  global->R = atoi(argv[10]);
  if (global->R <= 0.0) {
    std::cout << "R must be > 0" << std::endl;
    return -1; 
  }

  // M1: Number of nurses
  global->m1 = atoi(argv[11]);
  if (global->m1 <= 0.0) {
    std::cout << "M1 must be > 0" << std::endl;
    return -1; 
  }

  // M2: number of cleaners
  global->m2 = atoi(argv[12]);
  if (global->m2 <= 0.0) {
    std::cout << "M2 must be > 0" << std::endl;
    return -1; 
  }

  global->seed = atoi(argv[13]); // Seed for random numbers


  // Debug Log
  if (global->DEBUG) {
    std::cout <<
    "lambda_high: " << global->lambda_high <<
    "\nlambda_med: " << global->lambda_med <<
    "\nlambda_low: " << global->lambda_low <<
    "\nmu_evaluation: " << global->mu_evaluation <<
    "\nmu_high: " << global->mu_high <<
    "\nmu_med: " << global->mu_med <<
    "\nmu_low: " << global->mu_low <<
    "\nmu_cleanup: " << global->mu_cleanup <<
    "\nB: " << global->B <<
    "\nR: " << global->R <<
    "\nm1 (Nurses): " << global->m1 <<
    "\nm2 (Cleaners): " << global->m2 <<
    "\nSeed: " << global->seed << std::endl;
  }

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
  Clean *cs = new Clean(eventList, initialize, global, rs->queue); // initialize clean/janitor system

  // Holds the last hour when the stats were printed
  int lastPrintHour = global->clock / 60;

  while (eventList->getSize() > 0 && global->clock <= global->terminating_time) {
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

      // If it's a new hour, print stats
      if ((int) global->clock / 60 > lastPrintHour) { // if it's a new hour
        global->printStats();
        lastPrintHour = (int) global->clock / 60; // track when this was printed
      }

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

  // Print final stats
  std::cout << "Simulated Ended." << std::endl;
  global->printStats();

  // debug LOG
  if (global->DEBUG) {
    cout<< "Average Wait time: "<<global->totalWaitE/patients_count<<endl;

    for (int i = 0; i < patients_count; ++i) {
      std::cout << "Patient " << i << " - ";
      ps[i]->print();
    }
  }

  // Free Pointers ----
  // delete all of the remaining events
  while (eventList->getSize() > 0) {
    delete eventList->pop();
  }

  // delete all patients
  for (int i = 0; i < patients_count; ++i) {
    delete ps[i];
  }
  free(ps);

  // delete all initiated classes
  delete ns;
  delete rs;
  delete cs;
  delete eventList;
  delete initialize;
  delete global;
  


  // ----

  // fin.
  return 0;
}
