#include <iostream>
#include <random>
#include "Heap.h"
#include "init.h"
#include "Event.h"

// TODO: remove before submission
void HeapTesting() {
  int amount = 5;
  Patient **p = recieve_patients(amount);
  Heap<Patient> h;

  std::cout << "Heap Patient testing Started." << std::endl;
  std::cout << "Create patients, and add to heap:" << std::endl;

  for (int i = 0; i < amount; i++)
  {
    p[i]->print();
    h.push(p[i]);
  }

  std::cout << "Start Pops (output should be in lowest to highest):" << std::endl;
  for (int i = 0; i < amount; i++) {
    Patient *pp = h.pop();
    pp->print();
    delete pp;
  }

  free(p);

  std::cout << "EVENT TESTING:"<< std::endl << std::endl;
  // EVENT TESTING
  Heap<Event> eventList;
  Event *e1 = new Event(DEPARTURE, 1.0);
  eventList.push(e1);
  std::cout << "DEPARTURE event at time 1.0 added." << std::endl;

  Event *e2 = new Event(ARRIVAL, 0.0);
  eventList.push(e2);
  std::cout << "ARRIVAL event at time 1.0 added." << std::endl;

  Event *e3 = new Event(START_SERVICE, 0.5);
  eventList.push(e3);
  std::cout << "START_SERVICE event at time 1.0 added." << std::endl;

  Event *e4 = new Event(DEPARTURE, 3.0);
  eventList.push(e4);
  std::cout << "DEPARTURE event at time 1.0 added." << std::endl;

  Event *e5 = new Event(ARRIVAL, 1.2);
  eventList.push(e5);
  std::cout << "ARRIVAL event at time 1.0 added." << std::endl;

  Event *e6 = new Event(START_SERVICE, 1.5);
  eventList.push(e6);
  std::cout << "START_SERVICE event at time 1.0 added." << std::endl;

  std::cout << "Output should be ordered by time (Expected Output: ARRIVAL, START_SERVICE, DEPARTURE, ...)" << std::endl;

  Event *top;
  top = eventList.pop();
  top->print();
  delete top;

  top = eventList.pop();
  top->print();
  delete top;

  top = eventList.pop();
  top->print();
  delete top;

  top = eventList.pop();
  top->print();
  delete top;

  top = eventList.pop();
  top->print();
  delete top;

  top = eventList.pop();
  top->print();
  delete top;  
}

int main(int argc, char const *argv[])
{
  
  HeapTesting();
  
  return 0;
}
