#ifndef ARRAY_FIND_H
#define ARRAY_FIND_H

#include "Array.h"

template <class T, size_t size>
size_t ArrayFind(const Array<T, size> &array, const T &toFind) {
  for (size_t i = 0; i < array.size(); ++i) {
    if (array[i] == toFind)
      return i;
  }
  return -1;
}

#endif
