#include "Patient.h"
#include "NumberGenerator.h"
#include <random>

#pragma once

class Init {
public :
    std::default_random_engine *generator;
    Patient** patients;
    int totalPatients;

    Init(int seed);
    ~Init();

    NumberGenerator * getNumberGenerator(double variable);

    // todo: need to add lambdaHigh, lambdaLow and lambdaMed to the receivePatients() function params
    Patient **recieve_patients(int n);
    void deleteQueue(Patient** arr, int size);

private:
    Patient** generatePatientsOfClassification(double lambda, int totalPatients, PatientClassification classification);
};

