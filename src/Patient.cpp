#include "Patient.h"
#include <iostream>

Patient::Patient(double arrival_time)
{
  this->arrival_time = arrival_time;
  this->classification = this->determineClassification();
}

Patient::~Patient() { /* nothing to destructor, but adding a defination to make the compiler happy */ }

double Patient::compareTo(Patient * other)  {
  // TODO: handle classifications
  return this->arrival_time  - other->arrival_time;
}

void Patient::print()  {
  std::cout << "[arrival_time: "<< this->arrival_time << "]" << std::endl;
}

PatientClassification Patient::determineClassification()
{
  // TODO: Need to implement ACTUAL logic here.
  return PatientClassification::HIGH;
}