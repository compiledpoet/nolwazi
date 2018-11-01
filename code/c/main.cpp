#include <iostream>
#include <math.h>
#include <fftw3.h>
#include <iomanip>

#include "Wav.h"
#include "Wav.cpp"
#include "IXArray.h"

int main(){
  IXArray<char> * data = new IXArray(10);
  Wav wav("./test.wav");

  wav.read(data.getPointer(), 0, data.getLength() -1);
  Wav::Header * header = wav.getHeader();

  data[data.getLength() - 1] = '\0';
  std::cout << data.getPointer() << endl;

  delete [] data;
  return 0;
}
