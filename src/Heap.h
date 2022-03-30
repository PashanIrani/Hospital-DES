#include <iostream>

#pragma once

using namespace std;

/* Using template so this heap can support any class, 
that is also why all the definations are here, as the compiler will need it in it's
pre-processing step */
template <class O>
class Heap
{
private:

  int size; // stores the number of nodes in heap
  
  int allocatedSpace; // stores the size of the allocated space

  O **data; // an array to hold all the data

public:
  Heap() {
    size = 0;
    allocatedSpace = 1;
    data = (O **) malloc(sizeof(O *));
  }

  ~Heap() {
    // for (int i = 0; i < allocatedSpace; ++i) {
    //   delete data[i]; // all data values MUST be initialized with 'new'
    // }

    free(data);
  }

  /* prints tree in the order: 
  root 
  left1 
  right1 
  left1's-left 
  left1's-right 
  right1's-left
  right1's-right

  *note: order here will be in heap order, not in the order of pops.
  */
  void print() {
    for (int i = 0; i < size; ++i) {
      data[i]->print();
    }
  }

  // re-allocates space for data to be twice it's size.
  void allocateMoreSpace() {
    allocatedSpace *= 2;
    data = (O **) realloc(data, sizeof(O *) * allocatedSpace);
  }

  // re-allocated data array to half it's size
  void allocateLessSpace() {
    int safetySpace = 4; // safety space incase my math is off lol.
    if (size > (allocatedSpace / 2) - safetySpace) return;

    allocatedSpace /= 2;
    data = (O**) realloc(data, sizeof(O *) * allocatedSpace);
  }

  // compare's nodes at indexes i and j
  double compare(int i, int j) {
    return data[i]->compareTo(data[j]);
  }

  // Swaps 2 elements
  void swap(int i, int j) {
    O * temp = data[i];
    data[i] = data[j];
    data[j] = temp;
  }

  // Positions node at index correctly in the tree
  void updateHeapRelativeTo(int index) {
    int parent = (index - 1) / 2;

    // keep swapping with parent until order is complete
    while(compare(index, parent) < 0) {
      swap(index, parent);
      index = parent;
      parent = (index - 1) / 2;
    }
  }

  /*
  Adds Node to heap
  */
  void push(O *n) {
    // allocate more space if needed
    if (size == allocatedSpace) {
      allocateMoreSpace();
    }
    // put node at the end of heap
    data[size] = n;

    // update node to be in the correct position
    updateHeapRelativeTo(size);

    // increment size
    size++;
  }

  /* Called from pop(), once it's called it re-orderes the tree
  to ensure a heap structure is maintained */
  void propogateHeadToCorrectPosition(int index) {
    // get left and right nodes from index
    int left = (index * 2) + 1;
    int right = (index * 2) + 2;

    // if no children, return, node[index] is at right place
    if (left >= size) return;

    int smallerLeafIndex; // holds the smaller leaf

    // if left is out of array, then use right
    if (right >= size) {
      smallerLeafIndex = left;
    } else {
      smallerLeafIndex = compare(left, right) < 0 ? left : right;
    }

    // swap with small leaf (essentially until it is in the correct place)
    if (compare(smallerLeafIndex, index) < 0) {
      swap(smallerLeafIndex, index); // swap
      propogateHeadToCorrectPosition(smallerLeafIndex); // propogate again, to ensure the node is in the correct place
    }
  }

  // Removes element from the top of the heap, and returns it's pointeer
  O * pop() {
    O * head = data[0]; // get current head

    swap(size - 1, 0); // swap head with last node
    data[size - 1] = NULL; // delete head (which was swapped to last node)
    size--; // decrement heap size to refelec the removal of head

    propogateHeadToCorrectPosition(0); // since a leaf is now the head, propgate it to the correct position in the tree
    allocateLessSpace(); // allocate less space

    return head;
  }

  // Returns size of the heap
  int getSize() {
    return size;
  }

  // Returns pointer to head
  O * getHead() {
    return data[0];
  }
};
