#include <iostream>
#include <random>
#include "init.h"

using namespace std;

int main(int argc, char const *argv[])
{
  Patient **p = recieve_patients(5);

  for (int i = 0; i < 5; ++i)
  {
    cout << (*(p + i))->arrival_time << endl;
  }

  return 0;
}
