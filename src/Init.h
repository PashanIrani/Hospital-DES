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

    Patient **recieve_patients(double lambda_high, double lambda_med, double lambda_low);
    void deleteQueue(Patient** arr, int size);

private:
    Patient** generatePatientsOfClassification(double lambda, int totalPatients, PatientClassification classification);
};

