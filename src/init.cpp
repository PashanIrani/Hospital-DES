#include "init.h"
// #include <cstddef>
// #include <cstdlib>
// #include "NumberGenerator.h"

Init::Init(int seed) {
  this->generator = new std::default_random_engine(seed);
}

NumberGenerator * Init::getNumberGenerator(double variable) {
  return new NumberGenerator(generator, variable);
}

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

  return patients;
}
