enum PatientClassification { HIGH, MEDIUM, LOW };

class Patient {
  public:
    double arrival_time;
    PatientClassification classification;

    Patient(double arrival_time);
  PatientClassification determineClassification();
};