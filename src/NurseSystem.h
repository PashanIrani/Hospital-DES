#include "Patient.h"
#include "Event.h"
#include "Heap.h"
#include "queue.h"
#include "init.h"

#pragma once

class NurseSystem {
  public:
    struct Queue<Patient> * queue;
    double wait_time = 0;
    Heap<Event> * eventList;
    Init * init;

    NurseSystem(Heap<Event> * eventList, Init * init);
    void performArrival(Event * event);
    void performService(Event * event);
    void performDeparture(Event * event);

  private:
    double getWaitTimeOfQueue();
};