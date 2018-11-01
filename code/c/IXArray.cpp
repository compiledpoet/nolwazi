#ifndef IX_ARRAY_CPP
#ifndef IX_ARRAY_CPP

#include "IXArray.h"

template<class T>
IXArray<T>::IXArray(int pLength){
  this->array = new T[pLength];
  this->length = pLength;
}

template<class T>
T & IXArray<T>::operator[](int index){
  return this->array[index];
}

template<class T>
T * IXArray<T>::getPointer(){
  return this->array;
}

template<class T>
int IXArray<T>::getLength() const{
  return this->length;
}

template<class T>
IXArray<T>::~IXArray(){
  if(this->array)
    delete [] this->array;

  this->length = 0;
}

#endif
