#include "Patient.h"

Patient::Patient(double arrival_time)
{
  this->arrival_time = arrival_time;
  this->classification = this->determineClassification();
}

PatientClassification Patient::determineClassification()
{
  // TODO: Need to implement ACTUAL logic here.
  return PatientClassification::HIGH;
}