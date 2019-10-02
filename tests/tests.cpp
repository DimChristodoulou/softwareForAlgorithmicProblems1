#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../inc/catch.hpp"

#include "../inc/globals.h"
#include "../inc/manhattan.h"
#include "../inc/point.h"
#include "../inc/utils.h"

using namespace std;

TEST_CASE( "Unit Test for Manhattan Distances", "[manhattan]" ) {
    //Default Case
    vector<float> p1coords{1.5, 2.5, 3.5};
    vector<float> p2coords{3.5, 2.5, 1.5};
    //Case with zeroed vectors
    vector<float> p3coords{0, 0, 0};
    vector<float> p4coords{0, 0, 0};
    //Case with empty vectors
    vector<float> p5coords;
    vector<float> p6coords;
    //Case with different dimensions
    vector<float> p7coords{1, 2};
    vector<float> p8coords{2, 5, 6, 9};

    Point *p1 = new Point(p1coords);
    Point *p2 = new Point(p2coords);
    Point *p3 = new Point(p3coords);
    Point *p4 = new Point(p4coords);
    Point *p5 = new Point(p5coords);
    Point *p6 = new Point(p6coords);
    Point *p7 = new Point(p7coords);
    Point *p8 = new Point(p8coords);
    
    REQUIRE( calculate(p1,p2) == 4.0 );
    REQUIRE( calculate(p3,p4) == 0.0 );
    REQUIRE( calculate(p5,p6) == -1.0 );
    REQUIRE( calculate(p7,p8) == -1.0 );
}