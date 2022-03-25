#include "Init.h"
#include "Global.h"
#include "Heap.h"
#include "Event.h"
#include "Global.h"
#include "Patient.h"

#pragma once

class RoomSystem {
  public:
    // Priority Queue for patients
    Heap<Patient> * queue;

    // Stores a global event list
    Heap<Event> * eventList;

    // Stores a global Init instance
    Init * init;

    // Global class
    Global * global;

    bool rooms[1] = {true}; // TODO:  make objects and make global
  
    RoomSystem(Heap<Event> * eventList, Init * init, Global * global);
    ~RoomSystem();

    void performArrival(Event * event);
    void performService(Event * event);
    void performDeparture(Event * event);

  private:
    void beforeEventRoutine(Event * event);
};