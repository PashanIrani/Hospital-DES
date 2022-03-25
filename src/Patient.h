#include "Heapable.h"

#pragma once

enum PatientClassification { HIGH, MEDIUM, LOW };

class Patient : Heapable {
  public:
    /* Stores the arrival of the patient in the CURRENT system */ 
    double arrival_time;
    /* Stoes the service time for the patient in the CURRENT system*/
    double service_time;

    int patientID;

    /* Stores the patient's classification */
    PatientClassification classification;

    // TODO: will likey need to create another variable to start patient's initial arrival time

    Patient(double arrival_time, PatientClassification classification);
    ~Patient();
    
    double compareTo(Patient *);
    void print();    
    //PatientClassification determineClassification();
};