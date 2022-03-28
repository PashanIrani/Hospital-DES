#include "Init.h"
#include "Global.h"
#include "Heap.h"
#include "Event.h"
#include "Global.h"
#include "Patient.h"
#include "Queue.h"

#pragma once

class Clean {
  public:
    // A FCFS queue for patients to enter
    struct Queue<Room> * queue;

    // Priority Queue for patients
    Heap<Patient> * hqueue;

    // Stores a global event list
    Heap<Event> * eventList;

    // Stores a global Init instance
    Init * init;

    // Global class
    Global * global;

    // Number generator used to generate cleaning times
    NumberGenerator * ng;
  
    Clean(Heap<Event> * eventList, Init * init, Global * global, Heap<Patient> *hqueue);
    ~Clean();

    void performArrival(Event * event);
    void performService(Event * event);
    void performDeparture(Event * event);

  private:
    void beforeEventRoutine(Event * event);
};