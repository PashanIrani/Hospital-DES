#include "Patient.h"
#include "NumberGenerator.h"
#include <random>

#pragma once

class Init {
    public : 
      std::default_random_engine *generator;

      Init(int seed);
      ~Init();
      
      Patient **recieve_patients(int n);
      NumberGenerator * getNumberGenerator(double variable);

};