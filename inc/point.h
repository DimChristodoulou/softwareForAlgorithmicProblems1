/*! \file point.h
    \brief This file contains the definition of the Point class
*/
#ifndef __POINT__
#define __POINT__

#include "globals.h"
#include "point.h"

class Point{
    private:
        /* data */
        std::vector<float> _coordinates;
        std::string _pointIdentifier;
    public:
        Point(/* args */ std::vector<float> coordinates);
        ~Point();
        std::string getPointIdentifier();
        void setPointIdentifier(std::string value);
        std::vector<float> getCoordinates();
        void setCoordinates(std::vector<float> coordinates);
        void printCoordinatesFormatted();
        int getDimension();
        int getClosestNeighbor(std::vector<float>);
        std::tuple<int, float> getClosestNeighborLSH(std::vector<Point *>);
};

#endif