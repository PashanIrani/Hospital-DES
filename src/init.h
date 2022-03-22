#include "Patient.h"
#include <random>

class Init {
    public : 
      std::default_random_engine *generator;

      Init(int seed);
      Patient **recieve_patients(int n);

};