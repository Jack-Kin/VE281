#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <algorithm>
#include <cmath>
#include "priority_queue.h"
using namespace std;
// OVERVIEW: A specialized version of the 'heap' ADT implemented as a binary
//           heap.
template<typename TYPE, typename COMP = std::less<TYPE> >
class binary_heap: public priority_queue<TYPE, COMP> {
public:
  typedef unsigned size_type;

  // EFFECTS: Construct an empty heap with an optional comparison functor.
  //          See test_heap.cpp for more details on functor.
  // MODIFIES: this
  // RUNTIME: O(1)
  binary_heap(COMP comp = COMP());

  //Another Constructor
//  binary_heap(COMP comp = COMP(), TYPE *array=NULL, size_type length=0);


    // EFFECTS: Add a new element to the heap.
  // MODIFIES: this
  // RUNTIME: O(log(n))
  virtual void enqueue(const TYPE &val);

  // EFFECTS: Remove and return the smallest element from the heap.
  // REQUIRES: The heap is not empty.
  // MODIFIES: this
  // RUNTIME: O(log(n))
  virtual TYPE dequeue_min();

  // EFFECTS: Return the smallest element of the heap.
  // REQUIRES: The heap is not empty.
  // RUNTIME: O(1)
  virtual const TYPE &get_min() const;

  // EFFECTS: Get the number of elements in the heap.
  // RUNTIME: O(1)
  virtual size_type size() const;

  // EFFECTS: Return true if the heap is empty.
  // RUNTIME: O(1)
  virtual bool empty() const;

//  virtual void print() const;

private:
  // Note: This vector *must* be used in your heap implementation.
  std::vector<TYPE> data;
  // Note: compare is a functor object
  COMP compare;
private:
  // Add any additional member functions or data you require here.
  size_type Size;
//  void Heapify();
  void percolateUp(int id);
  void percolateDown(int id);
};


template<typename TYPE, typename COMP>
binary_heap<TYPE, COMP> :: binary_heap(COMP comp) : Size(0){
    compare = comp;
    data.push_back(TYPE());
}

//template<typename TYPE, typename COMP>
//binary_heap<TYPE, COMP> :: binary_heap(COMP comp,TYPE *array, size_type length){
//    compare = comp;
//    this->Size = length;
//    for (size_type i = 0; i < length; ++i) {
//        data[i] = array[i];
//    }
//    Heapify();
//}

//template<typename TYPE, typename COMP>
//void binary_heap<TYPE, COMP> :: Heapify(){
//    for (size_type i = Size/2 ; i >= 1 ; ++i) {
//        percolateDown(i);
//    }
//}

template<typename TYPE, typename COMP>
void binary_heap<TYPE, COMP> :: percolateUp(int id){
    while (id > 1 && compare(data[id], data[id/2]) ){
        swap(data[id], data[id/2]);
        id = id/2;
    }
}

template<typename TYPE, typename COMP>
void binary_heap<TYPE, COMP> :: percolateDown(int id){
    for (size_type j = 2*id; j <= Size ; j = 2*id) {
        if (j < Size && compare(data[j+1] , data[j]) ) j++;
        if (!compare(data[j], data[id])) break;
        swap(data[id], data[j]);
        id = j;
    }
}

template<typename TYPE, typename COMP>
void binary_heap<TYPE, COMP> :: enqueue(const TYPE &val) {
    Size = Size +1;
    data.push_back(val);
    percolateUp(Size);
}

template<typename TYPE, typename COMP>
TYPE binary_heap<TYPE, COMP> :: dequeue_min() {
    swap(data[1], data[Size--]);
    percolateDown(1);
    TYPE tmp = data[Size+1];
    data.pop_back();
    return tmp;
}

template<typename TYPE, typename COMP>
const TYPE &binary_heap<TYPE, COMP> :: get_min() const {
    return data[1];
}

template<typename TYPE, typename COMP>
bool binary_heap<TYPE, COMP> :: empty() const {
    return (this->Size == 0);
}

template<typename TYPE, typename COMP>
unsigned binary_heap<TYPE, COMP> :: size() const {
    return this->Size;
}



#endif //BINARY_HEAP_H
