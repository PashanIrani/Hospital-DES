#include "Heapable.h"

#pragma once

enum PatientClassification { HIGH, MEDIUM, LOW };

class Patient : Heapable {
  public:
    double arrival_time;
    double service_time;
    PatientClassification classification;

    Patient(double arrival_time);
    ~Patient();
    
    double compareTo(Patient *);
    void print();    
    PatientClassification determineClassification();
};