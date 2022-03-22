#include "init.h"
// #include <cstddef>
// #include <cstdlib>
#include "NumberGenerator.h"

Init::Init(int seed) {
  this->generator = new std::default_random_engine(seed);
}

Patient** Init::recieve_patients(int n)
{
  // Patient **patients = (Patient **)malloc(sizeof(Patient *) * n);
  // //NumberGenerator *ng = new NumberGenerator(mu, std, seed);

  // // -------------testing --------------------
  // NumberGenerator *ng = new NumberGenerator(generator, 2);
  // for (int i = 0; i < 10; i++) {
  //   double arrival_time = ng->next();
  //   patients[i] = new Patient(arrival_time);
  // }
  // //------------------------------------------

  // // for (int i = 0; i < n; ++i)
  // // {
  // //   double arrival_time = ng->next();
  // //   patients[i] = new Patient(arrival_time);
  // // }

  // return patients;



  delete ng;

  return patients;
}
