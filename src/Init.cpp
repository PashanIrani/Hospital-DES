#include "init.h"

/* Initializes Init class; 
* initializes a singular generator with a seed, that will be used for all random numbers for this Init instance
*/ 
Init::Init(int seed) {
  this->generator = new std::default_random_engine(seed);
}

Init::~Init() {
  delete generator;
}

/* Returns a new NumberGenerator instance used for generating exponential numbers based on a certain variable */ 
NumberGenerator * Init::getNumberGenerator(double variable) {
  return new NumberGenerator(generator, variable);
}

/* Returns an array of patients that will be "entering" the "hospital" */
Patient** Init::recieve_patients(int n)
{
  Patient **patients = (Patient **)malloc(sizeof(Patient *) * n);

  NumberGenerator *ng = getNumberGenerator(2);

  Patient *prevPatient = NULL;

  for (int i = 0; i < n; i++) {

    double arrival_time = ng->next() + (prevPatient != NULL ? prevPatient->arrival_time : 0);
    patients[i] = new Patient(arrival_time);
    prevPatient = patients[i];
  }

  delete ng;
  return patients;
}
