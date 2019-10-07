/*! \file utils.h
    \brief This file contains the declarations of various functions used in different assisting tasks
*/

#include "globals.h"
#include "point.h"

int generateRandomW();
std::vector<Point*> parseFileForPoints(std::string);
int strArraySearch(char const*[], int, char const*);
int hashFunction(int);
std::vector<Point*> parseFileForPoints(std::string, bool isSearchDataset, double *radius);
