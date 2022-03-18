#include <random>

class NumberGenerator
{
public:
  std::default_random_engine *generator;
  std::normal_distribution<double> *distribution;

  NumberGenerator(double mu, double std, int seed);

  double next();

  ~NumberGenerator();
};
