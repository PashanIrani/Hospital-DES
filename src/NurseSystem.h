#include "Patient.h"
#include "Event.h"
#include "Heap.h"
#include "Queue.h"
#include "Init.h"

#pragma once

class NurseSystem {
  public:
    // A FCFS queue for patients to enter
    struct Queue<Patient> * queue;

    // Total wait time for the system to be "ready" again
    double wait_time = 0.0;

    // Stores a global event list
    Heap<Event> * eventList;

    // Stores a global Init instance
    Init * init;

    NurseSystem(Heap<Event> * eventList, Init * init);
    ~NurseSystem();
    
    void performArrival(Event * event);
    void performService(Event * event);
    void performDeparture(Event * event);

  private:
    double getWaitTimeOfQueue();
};