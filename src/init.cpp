#include "init.h"
#include <cstddef>
#include <cstdlib>
#include "NumberGenerator.h"

Patient **recieve_patients(int n)
{
  int seed = 500;
  double mu = 2;
  double std = 2;

  Patient **patients = (Patient **)malloc(sizeof(Patient *) * n);
  NumberGenerator *ng = new NumberGenerator(mu, std, seed);

  for (int i = 0; i < n; ++i)
  {
    double arrival_time = ng->next();
    patients[i] = new Patient(arrival_time);
  }

  return patients;
}
