#ifndef WAV_H
#define WAV_H

#include <fstream>
#include "IXArray.h"
#include "IXArray.cpp"

class Wav{
private:
  ifstream ifs;
  Header * header;

public:
  class Header{
  private:

  public:
    Header();

    ~Header();
  };

  Wav(std::string filePath);

  void read(char * data, int offset, int length);
  IXArray<char> * getData();

  Header * getHeader() const;
  bool isValid(std::string path);

  ~Wav();
};

#endif
