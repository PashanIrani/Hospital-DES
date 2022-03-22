#include <iostream>
#include <random>
#include "Heap.h"
#include "init.h"
#include "Event.h"
#include "queue.h"

int main(int argc, char const *argv[])
{
  // TODO: read args

  Init initialize(500); 

  int size = 5;
  Patient ** ps = initialize.recieve_patients(size);

  // Load Queue : Nurses (E) 

  











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
