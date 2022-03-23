#include <random>

#pragma once

class NumberGenerator
{
public:
  std::exponential_distribution<double> *distribution;
  std::default_random_engine *generator;
  
  NumberGenerator(std::default_random_engine *generator, double var);
  double next();
  ~NumberGenerator();
};
