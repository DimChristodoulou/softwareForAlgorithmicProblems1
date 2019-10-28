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

std::vector<std::tuple<float, float>> Curve::generateShiftedGrid(std::vector<float> tVector, int delta){
    std::vector<std::tuple<float, float>> curveCoords = this->getCurvePoints();

    std::vector<std::tuple<float, float>> gdelta;
    for (size_t i = 0; i < curveCoords.size(); i++){
        for (size_t j = 0; j < curveCoords.size(); j++){
            gdelta.push_back(std::make_tuple(i*delta, j*delta));
        }
    }
    std::cout << "GDELTAAA " << gdelta.size() << std::endl;
    std::cout << "TVECTOR  " << tVector.size() << std::endl;
    std::vector<std::tuple<float, float>> generatedGrid;
    for (size_t i = 0; i < gdelta.size(); i++){
        generatedGrid.push_back( std::make_tuple( std::get<0>(gdelta[i])+tVector[i], std::get<1>(gdelta[i])+tVector[i]) );
    }
    
    return generatedGrid;
}