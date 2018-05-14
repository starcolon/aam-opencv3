#ifndef PRIORITY_LLIST
#define PRIORITY_LLIST

#include "master.h"

template <class T>
class PriorityLinkedList
{
public:
  PriorityLinkedList(const PriorityLinkedList<T>& ) = delete;
  PriorityLinkedList() : ptr(nullptr), v(0), next(nullptr) {};
  PriorityLinkedList(unique_ptr<T> t, double v) 
    : ptr(move(t)), v(v), next(nullptr) {};
  virtual ~PriorityLinkedList();

  double v;
  unique_ptr<T> ptr;
  unique_ptr<PriorityLinkedList<T>> next;

  virtual void push(unique_ptr<T>& n, double v);
  virtual bool pop();
  void take(int n);
  int size() const;

  // TAOTOREVIEW: add cout 
};


#endif