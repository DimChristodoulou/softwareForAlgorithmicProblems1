#ifndef _GRID_H_
#define _GRID_H_

#include "globals.h"

using namespace std;


template <typename T,typename N>
class Grid{
	std::vector<double> t;
	double d;
public:
	Grid(int,int);
	~Grid();
	N* Create_Grid_Curve(const T &);
};



#endif
