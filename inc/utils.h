/*! \file utils.h
    \brief This file contains the declarations of various functions used in different assisting tasks
*/

#include "globals.h"
#include "point.h"

std::vector<Point*> parseFileForPoints(std::string);
int strArraySearch(char const*[], int, char*);
int hashFunction(int);