#include "Patient.h"
#include <iostream>

/* Constructor */
Patient::Patient(double arrival_time, PatientClassification classification)
{
  this->arrival_time = arrival_time;
  this->classification = classification;
}

Patient::~Patient() { /* nothing to destructor, but adding a defination to make the compiler happy */ }

/* Compare function to order patients in a heap */
double Patient::compareTo(Patient * other)  {
  // TODO: handle classifications
  return this->arrival_time  - other->arrival_time;
}

/* Prints patient data, used for debug */
void Patient::print()  {
  std::cout << this->toString() << std::endl;
}

std::string Patient::toString() {
  std::ostringstream s;
  s << "[ ID: " << this->patientID << ", arrival_time: "<< this->arrival_time << ", Class: " << getClassificationAsString() << "]";
  return s.str();
}

std::string Patient::getClassificationAsString() {
  switch (this->classification)
  {
  case HIGH:
    return "HI";
    break;
  case MEDIUM:
    return "MD";
    break;
  case LOW:
    return "LO";
    break;
  default:
    return "Something is not right here; see Patient.cpp:getClassificationAsString()";
    break;
  }
}
