/*! \file point.cpp
    \brief  This file contains the definitions of the Point class member functions.
*/
#include "../inc/globals.h"
#include "../inc/point.h"

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

Point* getClosestNeighbor(vector<Point*> allPointNeighbors){
    for (unsigned int i = 0; i < allPointNeighbors.size(); i++){
        /* code */
    }
    
}