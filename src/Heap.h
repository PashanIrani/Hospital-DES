#include <iostream>

using namespace std;

/* Using template so this heap can support any class, 
that is also why all the definations are here, as the compiler will need it in it's
pre-processing step */
template <class O>
class Heap
{
private:
  int size;
  int allocatedSpace;
  O **data;

public:
  Heap() {
    size = 0;
    allocatedSpace = 1;
    data = (O **) malloc(sizeof(O *));
  }

  ~Heap() {
    for (int i = 0; i < allocatedSpace; ++i) {
      free(data[i]);
    }

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
    int safetySpace = 4; // TODO: confirm, this math and remove this.
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
    if (size == allocatedSpace) {
      allocateMoreSpace();
    }
    data[size] = n;
    updateHeapRelativeTo(size);
    size++;
  }

  /* Called from pop(), once it's called it re-orderes the tree
  to ensure a heap structure is maintained */
  void propogateHeadToCorrectPosition(int index) {
    int left = (index * 2) + 1;
    int right = (index * 2) + 2;

    // if no children, return, node[index] is at right place
    if (left >= size) return;

    int smallerLeafIndex;

    // if left is out of array, then use right
    if (right >= size) {
      smallerLeafIndex = left;
    } else {
      smallerLeafIndex = compare(left, right) < 0 ? left : right;
    }

    if (compare(smallerLeafIndex, index) < 0) {
      swap(smallerLeafIndex, index);
      propogateHeadToCorrectPosition(smallerLeafIndex);
    }
  }

  // Removes element from the top of the heap, and returns it's pointeer
  O * pop() {
    O * head = data[0];

    swap(size - 1, 0);
    data[size - 1] = NULL;
    size--;

    propogateHeadToCorrectPosition(0);
    allocateLessSpace();

    return head;
  }

  // Returns size of the heap
  int getSize() {
    return size;
  }
};
