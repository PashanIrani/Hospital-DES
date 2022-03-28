#include "Heapable.h"
#include <stdexcept>

/* Throws an error message if subbclass hasn't overridden this method */
double Heapable::compareTo(Heapable * a) {
  throw std::runtime_error("Wrong compareTo() running, double check you polymorphism");
}

/* Throws an error message if subbclass hasn't overridden this method */
void Heapable::print() {
  throw std::runtime_error("Wrong print() running, double check you polymorphism");
}

Heapable::~Heapable() {}