/*! \file point.cpp
    \brief  This file contains the definitions of the Point class member functions.
*/
#include "../inc/globals.h"
#include "../inc/point.h"
#include "../inc/manhattan.h"

using namespace std;

Point::Point(/* args */ vector<float> coords)
{
    this->_coordinates = coords;
}

Point::~Point()
{
    
}

/**
 * @brief _pointIdentifier Getter
 * 
 * @return string 
 */
string Point::getPointIdentifier(){
    return this->_pointIdentifier;
}

/**
 * @brief _pointIdentifier Setter
 * 
 * @param value 
 */
void Point::setPointIdentifier(string value){
    this->_pointIdentifier = value;
}

/**
 * @brief _coordinates Getter
 * 
 * @return vector<float> 
 */
vector<float> Point::getCoordinates(){
    return this->_coordinates;
}

/**
 * @brief _coordinates Setter
 * 
 * @param coordinates 
 */
void Point::setCoordinates(vector<float> coordinates){
    this->_coordinates = coordinates;
}

/**
 * @brief Prints the coordinates of a Point object in a tab-separated format.
 * 
 */
void Point::printCoordinatesFormatted(){
    for (unsigned int i = 0; i < this->_coordinates.size(); i++){
        cout << "c" << i << " - " << this->_coordinates[i] << "\t";
    }
    cout << endl;
}

int Point::getDimension(){
    return this->getCoordinates().size();
}

/**
 * @brief Returns the closest (minimum manhattan distance) dataset point of a query point.
 * 
 * @param allPointNeighborDistances Represents a row of the distance matrix.
 * @return int The index of the closest neighbor
 */
int Point::getClosestNeighbor(vector<float> allPointNeighborDistances){

    float minDistance = numeric_limits<float>::max();
    int indexOfNeighbor;

    for (unsigned int i = 0; i < allPointNeighborDistances.size(); i++){
        if(allPointNeighborDistances[i] < minDistance){
            minDistance = allPointNeighborDistances[i];
            indexOfNeighbor = i;
        }
    }
    
    return indexOfNeighbor;
}

tuple<int, float> Point::getClosestNeighborLSH(vector<Point *> allPointsInBucket){
    float minDistance = numeric_limits<float>::max();
    int indexOfNN;

    for (unsigned int i = 0; i < allPointsInBucket.size(); i++){
        float dist = calculate(this, allPointsInBucket[i]);
        if(dist < minDistance){
            minDistance = dist;
            indexOfNN = i;
        }
    }
    
    return make_tuple(indexOfNN, minDistance);
}