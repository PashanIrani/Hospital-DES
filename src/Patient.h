#include "Heapable.h"
#include <iostream>

#pragma once

enum PatientClassification { HIGH, MEDIUM, LOW };

class Patient : Heapable {
  public:
    /* Stores the arrival time of when the patient arrived to the system*/ 
    double arrival_time;

    /* Stores the arrival time of the patient when the enter a room */
    double arrival_time_room_system = -1.0;

    /* Stoes the service time for the patient in the CURRENT system*/
    double service_time;

    int patientID;

    /* Stores the patient's classification */
    PatientClassification classification;


    Patient(double arrival_time, PatientClassification classification);
    ~Patient();
    
    double compareTo(Patient *);
    void print();    
    std::string getClassificationAsString();
    std::string toString();
};