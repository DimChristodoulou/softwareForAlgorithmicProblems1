/*! \file utils.h
    \brief This file contains the declarations of various functions used in different assisting tasks
*/

#include "globals.h"
#include "point.h"

std::vector<Point*> parseFileForPoints(std::string);
int strArraySearch(char const*[], int, char const*);
int hashFunction(int);
int generateRandomW();
std::vector<Point*> parseFileForPoints(std::string, bool isSearchDataset, double *radius);
std::vector<float> generateUniformNumbers(int, int, int);
std::vector<float> generateRandomNumbersBetween(int, int, int);
std::vector<std::vector<float>> generateExhaustiveArray(std::vector<Point *>, std::vector<Point*>);