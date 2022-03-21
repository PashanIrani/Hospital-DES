#include "Heapable.h"

enum PatientClassification { HIGH, MEDIUM, LOW };

class Patient : Heapable {
  public:
    double arrival_time;
    PatientClassification classification;
    
    Patient(double arrival_time);

    double compareTo(Patient *);
    void print();    
    PatientClassification determineClassification();
};