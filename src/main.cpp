#include <iostream>
#include <random>
#include "init.h"

using namespace std;

int main(int argc, char const *argv[])
{
  Init initialize(500);

  Patient **p = initialize.recieve_patients(5);

  for (int i = 0; i < 5; ++i)
  {
    cout << (*(p + i))->arrival_time << endl;
  }

  return 0;
}
