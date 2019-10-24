#ifndef CURVE_H_
#define CURVE_H_

#include "globals.h"


template <typename Curve,typename GridCurve>
class Curve{
	Curve* curve;
	GridCurve* grid_curve;
	char* CurveID;
public:
	Curve(Curve*, GridCurve*,char*);
	~Curve();
	bool Compare_Grid_Curve(Curve*);
	const GridCurve & Get_Grid_Curve();
	Curve& Get_Curve();
	char* Get_CurveId();
	void Destroy();
};

#endif
