#include <iostream>
#include <string>
#include <random>


double* normalDistribution(int wanted, int margin)
{

  int i = 0;
  std::default_random_engine generator;
  std::normal_distribution<double> distribution(5.0,2.0);
  static double p[sizeof(wanted) / 4];

  while ( i < wanted) {
    double number = distribution(generator);
    if ((number >= 0.0) && (number < margin )) {
        p[i] = number;
        i++;
    }
  }

  std::cout << "normal_distribution (5.0,2.0):" << std::endl;

  for (int j=0; j<10; ++j) {
    std::cout << p[j] << std::endl;
  }

  return p;
}


int main(int argc, char const *argv[]){

  double* result;
  result = normalDistribution(10, 10);
  std::cout << "Result: " << std::endl;
 for (int j=0; j<10; ++j) {
    std::cout << result[j] << std::endl;
  }
}

