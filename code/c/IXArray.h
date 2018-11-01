#ifndef IX_ARRAY_H
#define IX_ARRAY_H

template<class T>
class IXArray{
private:
  T * array;
  int length;

public:
  IXArray(int pLength);

  T & operator[](int index);
  T * getPointer() const;
  int getLength() const;

  ~IXArray();
};
#endif
