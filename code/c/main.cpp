#include <iostream>
#include <math.h>
#include <fftw3.h>
#include <iomanip>

const double PI = 3.14159265;

double abs(fftw_complex complex);

template<class T>
fftw_complex * generateSignal(int sampleRate, float offset, float duration, float freq, T amplitude);

int main(){
  std::cout << "Eggs" << std::endl;
  const int sampleRate = 32;
  int sigLen = sampleRate * 1 + 1;
  if(sigLen == 0)
    return 0;

  fftw_complex * sig = generateSignal(sampleRate, 0, 1, 1, (short)2);
  fftw_complex * sigFFT = new fftw_complex[sigLen];

  fftw_plan plan = fftw_plan_dft_1d(sigLen, sig, sigFFT, FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(plan);
  fftw_destroy_plan(plan);

  for(int pos = 0; pos < sigLen; pos++){
    double r = sig[pos][0];
    std::cout << std::setprecision(2) << std::fixed << r << ", ";
  }

  std::cout << '\n';

  for(int pos = 0; pos < sigLen; pos++){
    double r = abs(sigFFT[pos]);
    std::cout << std::setprecision(2) << std::fixed << r << ", ";
  }

  delete [] sig;
  delete [] sigFFT;
  return 0;
}


double abs(fftw_complex complex){
  double real = complex[0], img = complex[1];
  return sqrt(real * real + img * img);
}

template<class T>
fftw_complex * generateSignal(int sampleRate, float offset, float duration, float freq, T amplitude){
  const int REAL = 0;
  int sampleCount = (int)(sampleRate * duration) + 1;
  double w = (2 * PI * freq);

  fftw_complex * samples = new fftw_complex[sampleCount];
  for(int pos = 0; pos < sampleCount; pos++){
    samples[pos][REAL] = (amplitude * sin(w * (pos / (float)(sampleCount - 1)) + offset));
  }

  return samples;
}
