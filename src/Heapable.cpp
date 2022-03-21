#include "Heapable.h"
#include <stdexcept>

double Heapable::compareTo(Heapable * a) {
  throw std::runtime_error("Wrong compareTo() running, double check you polymorphism");
}

void Heapable::print() {
  throw std::runtime_error("Wrong print() running, double check you polymorphism");
}