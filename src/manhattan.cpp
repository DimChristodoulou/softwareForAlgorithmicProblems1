/*! \file manhattan.cpp
    \brief This file contains the definitions of functions used in Manhattan distances and heuristics.
*/

#include "../inc/manhattan.h"
#include "../inc/globals.h"

using namespace std;

/**
 * @brief Calculates the Manhattan distance between two points
 * 
 * @return int 
 */
float calculate(Point *startingPoint, Point *endingPoint){
    vector<float> startingPointCoordinates = startingPoint->getCoordinates(), endingPointCoordinates = endingPoint->getCoordinates();
    float distance = 0;

    if( (startingPointCoordinates.size() != endingPointCoordinates.size()) || (startingPointCoordinates.empty() || endingPointCoordinates.empty() ) ){
        return -1;
    }

    for (unsigned int i = 0; i < startingPointCoordinates.size(); i++){
        //Absolute value notation
        distance += startingPointCoordinates[i] - endingPointCoordinates[i] > 0 ? 
                    startingPointCoordinates[i] - endingPointCoordinates[i] : 
                    endingPointCoordinates[i] - startingPointCoordinates[i];
    }

    return distance;
}