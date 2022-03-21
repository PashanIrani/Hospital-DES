#pragma once

/*
Any class that want's to be used in the heap WILL need to be a subclass of this class.
*/
class Heapable {
  double virtual compareTo(Heapable *);
  void virtual print();
};