#include "../inc/curve.h"

Curve::Curve(std::string curveId, int numberOfPoints, std::vector<std::tuple<float, float>> curvePoints){
    this->setCurveId(curveId);
    this->setNumberOfPoints(numberOfPoints);
    this->setCurvePoints(curvePoints);
}

Curve::~Curve(){}

std::string Curve::getCurveId(){
    return this->_curveId;
}
	
void Curve::setCurveId(std::string data){
    this->_curveId = data;
}

int Curve::getNumberOfPoints(){
    return this->_numberOfPoints;
}

void Curve::setNumberOfPoints(int data){
    this->_numberOfPoints = data;
}

std::vector<std::tuple<float, float>> Curve::getCurvePoints(){
    return this->_curvePoints;
}

void Curve::setCurvePoints(std::vector<std::tuple<float, float>> data){
    this->_curvePoints = data;
}