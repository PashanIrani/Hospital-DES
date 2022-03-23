#include <random>
#include "NumberGenerator.h"

/* Initialzied generator */ 
NumberGenerator::NumberGenerator(std::default_random_engine *generator, double var)
{
  this->distribution = new std::exponential_distribution<>(var);
  this->generator = generator;
}

/* returns a new random number in sequence */ 
double NumberGenerator::next()
{
  return (*distribution)(*generator);
}

NumberGenerator::~NumberGenerator()
{
  delete distribution;
}