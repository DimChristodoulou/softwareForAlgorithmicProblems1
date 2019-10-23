/*! \file utils.h
    \brief This file contains the declarations of various functions used in different assisting tasks
*/

#include "globals.h"
#include "point.h"

std::vector<Point*> parseFileForPoints(std::string);
int strArraySearch(char const*[], int, char const*);
int hashFunction(int);
int generateRandomW();
int hiHashFunction(Point *initialDatasetPoint, int w, unsigned int base, int modulo);
std::vector<Point*> parseFileForPoints(std::string, bool isSearchDataset, double *radius);
std::vector<float> generateUniformNumbers(int, int, int);
std::vector<float> generateRandomNumbersBetween(int, int, int);
std::vector<std::vector<float>> generateExhaustiveArray(std::vector<Point *>, std::vector<Point*>);
int modularExponentiation(unsigned int, int, int);
int mod(int, int);
long long convertDecimalToBinary(int n);
short int getBinaryDigitBasedOnHashValue(std::unordered_map<long long int, short int>, long long int);
std::tuple<int, float> getNeighborOutOfPossibleNeighbors(std::vector<std::tuple<int, float>> possibleNeighbors);