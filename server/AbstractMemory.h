// Definition of the AbstractMemory class

#ifndef AbstractMemory_class
#define AbstractMemory_class

using namespace std;

#include <list>

class AbstractMemory
{
  list<int> *pointers;

 public:

  AbstractMemory ();
  virtual ~AbstractMemory();
  
  void doAction();

  void *alloc(unsigned long size);
  void free(void *ptr);
  //READ
  //WRITE
};


#endif
