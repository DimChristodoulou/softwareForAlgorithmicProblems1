#ifndef CURVE_H_
#define CURVE_H_

#include "globals.h"

class Curve
{
	private:
		/* data */
		std::string _curveId;
		int _numberOfPoints;
		std::vector<std::tuple<float, float>> _curvePoints;

	public:
		Curve(std::string, int, std::vector<std::tuple<float, float>>);
		~Curve();
		std::string getCurveId();
		void setCurveId(std::string data);
		int getNumberOfPoints();
		void setNumberOfPoints(int data);
		std::vector<std::tuple<float, float>> getCurvePoints();
		void setCurvePoints(std::vector<std::tuple<float, float>> data);
};


#endif
