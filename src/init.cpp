#include "init.h"
#include <cstddef>
#include <cstdlib>
#include "NumberGenerator.h"

Patient** Init::recieve_patients(int n)
{
  int seed = 500;
  double mu = 2;
  double std = 2;

  Patient **patients = (Patient **)malloc(sizeof(Patient *) * n);
  //NumberGenerator *ng = new NumberGenerator(mu, std, seed);

  // -------------testing --------------------
  *generator = new std::default_random_engine(seed);
  NumberGenerator *ng = new NumberGenerator(generator, mu);
  for (int i = 0; i < 10; i++) {
    double arrival_time = ng->next();
    patients[i] = new Patient(arrival_time);
  }
  //------------------------------------------

  // for (int i = 0; i < n; ++i)
  // {
  //   double arrival_time = ng->next();
  //   patients[i] = new Patient(arrival_time);
  // }

  return patients;
}
