// normal_distribution
#include <iostream>
#include <string>
#include <random>

int main(int argc, char const *argv[])
{

  // const int nrolls=10000;  // number of experiments
  int wanted = 10;    // maximum number of stars to distribute
  int i = 0;

  std::default_random_engine generator;
  std::normal_distribution<double> distribution(5.0,2.0);

  double p[wanted];

  while ( i < wanted) {
    double number = distribution(generator);
    if ((number>=0.0)&&(number<10.0)) {
    	p[i] = number;
    	i++;
    } 
    
  }

  std::cout << "normal_distribution (5.0,2.0):" << std::endl;

  for (int j=0; j<10; ++j) {
    std::cout << p[j] << std::endl;
  }

  return 0;
}
