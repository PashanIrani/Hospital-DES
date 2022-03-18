#include <random>
#include "NumberGenerator.h"

NumberGenerator::NumberGenerator(double mu, double std, int seed)
{
  this->generator = new std::default_random_engine(seed);
  this->distribution = new std::normal_distribution<>(mu, std);
}

double NumberGenerator::next()
{
  return (*distribution)(*generator);
}

NumberGenerator::~NumberGenerator()
{
  delete generator;
  delete distribution;
}