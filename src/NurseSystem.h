#include "Patient.h"
#include "Event.h"
#include "Heap.h"
#include "Queue.h"
#include "Init.h"
#include "Global.h"

#pragma once

class NurseSystem {
  public:
    // A FCFS queue for patients to enter
    struct Queue<Patient> * queue;

    // Stores a global event list
    Heap<Event> * eventList;

    // Stores a global Init instance
    Init * init;

    // Global class
    Global * global;

    // Number generator used to generate evalutaion times
    NumberGenerator * ng;

    NurseSystem(Heap<Event> * eventList, Init * init, Global * global);
    ~NurseSystem();

    void performArrival(Event * event);
    void performService(Event * event);
    void performDeparture(Event * event);

  private:
    double getWaitTimeOfQueue();
    void beforeEventRoutine(Event * event);
    int currently_being_serviced = 0; // keeps track of how many patients are currently being serviced
};