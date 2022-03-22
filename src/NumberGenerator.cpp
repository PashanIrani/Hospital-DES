#include <random>
#include "NumberGenerator.h"

NumberGenerator::NumberGenerator(std::default_random_engine *generator, double var)
{
  this->distribution = new std::exponential_distribution<>(var);
}

double NumberGenerator::next()
{
  return (*distribution)(*generator);
}

NumberGenerator::~NumberGenerator()
{
  delete distribution;
}