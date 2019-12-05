#ifndef UNSORTED_HEAP_H
#define UNSORTED_HEAP_H

#include <algorithm>
#include "priority_queue.h"

// OVERVIEW: A specialized version of the 'heap' ADT that is implemented with
//           an underlying unordered array-based container. Every time a min
//           is required, a linear search is performed.
template<typename TYPE, typename COMP = std::less<TYPE> >
class unsorted_heap: public priority_queue<TYPE, COMP> {
public:
  typedef unsigned size_type;

  // EFFECTS: Construct an empty heap with an optional comparison functor.
  //          See test_heap.cpp for more details on functor.
  // MODIFIES: this
  // RUNTIME: O(1)
  unsorted_heap(COMP comp = COMP());

//  ~unsorted_heap(){
//      while(!data.empty()){
//          data.pop_back();
//      }
//  }
  // EFFECTS: Add a new element to the heap.
  // MODIFIES: this
  // RUNTIME: O(1)
  virtual void enqueue(const TYPE &val);

  // EFFECTS: Remove and return the smallest element from the heap.
  // REQUIRES: The heap is not empty.
  // MODIFIES: this
  // RUNTIME: O(n)
  virtual TYPE dequeue_min();

  // EFFECTS: Return the smallest element of the heap.
  // REQUIRES: The heap is not empty.
  // RUNTIME: O(n)
  virtual const TYPE &get_min() const;

  // EFFECTS: Get the number of elements in the heap.
  // RUNTIME: O(1)
  virtual size_type size() const;

  // EFFECTS: Return true if the heap is empty.
  // RUNTIME: O(1)
  virtual bool empty() const;

private:
  // Note: This vector *must* be used in your heap implementation.
  std::vector<TYPE> data;
  // Note: compare is a functor object
  COMP compare;
private:
  // Add any additional member functions or data you require here.
  size_type Size;
};

template<typename TYPE, typename COMP>
unsorted_heap<TYPE, COMP> :: unsorted_heap(COMP comp):Size(0) {
    compare = comp;
    // Fill in the remaining lines if you need.
    data.push_back(TYPE());
}


template<typename TYPE, typename COMP>
void unsorted_heap<TYPE, COMP> :: enqueue(const TYPE &val) {
    Size = Size +1;
    data.push_back(val);
}

template<typename TYPE, typename COMP>
TYPE unsorted_heap<TYPE, COMP> :: dequeue_min() {
    size_type minIndex = 1;
    const TYPE *tmp = &data[1];
    // find the index of the smallest one
    for (size_type i = 2; i <= Size ; ++i) {
        if (compare(data[i], *tmp))  {
            minIndex = i;
            tmp = &data[i];
        }
    }
    TYPE min = data[minIndex];
    // move the data after the smallest one forward
    if (minIndex < Size) {
        for (size_type j = minIndex; j < Size; ++j) {data[j] = data[j + 1];}
    }
    data.pop_back();
    Size = Size -1;
    return min;
}

template<typename TYPE, typename COMP>
const TYPE &unsorted_heap<TYPE, COMP> :: get_min() const {
    const TYPE *tmp = &data[1];
    for (size_type i = 2; i <= Size ; ++i) {
        if (compare(data[i], *tmp))  tmp = &data[i];
    }
    return *tmp;
}

template<typename TYPE, typename COMP>
bool unsorted_heap<TYPE, COMP> :: empty() const {
    return (this->Size == 0);
}

template<typename TYPE, typename COMP>
unsigned unsorted_heap<TYPE, COMP> :: size() const { 
    return this->Size;
}

#endif //UNSORTED_HEAP_H
