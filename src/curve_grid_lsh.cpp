/**
 * @file curve_grid_lsh.cpp
 * @author Dimitris Christodoulou - Giorgos Tsiros
 * @brief Main function for the Locality Sensitive Hashing Algorithm on D-Dimensional Curves
 * @version 0.1 - Build 2.1
 * @date 2019-10-04
 * 
 * HOW TO INVOKE FOR SAMPLE : ./exe/curve_grid_lsh -d datasets/trajectories_dataset -o outputLSHCurves.txt -q querysets/query_small_id -k_vec 4 -L_grid 5
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "../inc/globals.h"
#include "../inc/manhattan.h"
#include "../inc/point.h"
#include "../inc/utils.h"
#include "../inc/curve.h"

#define __FULL_ARGUMENTS 11
#define __MINIMAL_ARGUMENTS 3

#define _N 20

using namespace std;

int main(int argc, char const *argv[])
{
    srand (time(NULL));
    unsigned int m = pow(2,32)-5;

    int count, kVector = 0, lGrid = 4;
    unsigned int i,j;
    //FILE *inputFile, *outputFile, *queryFile;
    string inputFileName, outputFileName, queryFileName;

    //Argument Handling
    if(argc == __FULL_ARGUMENTS){
        count = strArraySearch(argv, argc, "-d");
        inputFileName = count != -1 ? argv[count+1] : NULL;

        count = strArraySearch(argv, argc, "-o");
        outputFileName = count != -1 ? argv[count+1] : NULL;

        count = strArraySearch(argv, argc, "-q");
        queryFileName = count != -1 ? argv[count+1] : NULL;

        count = strArraySearch(argv, argc, "-k_vec");
        kVector = count != -1 ? stoi(argv[count+1]) : 0;

        count = strArraySearch(argv, argc, "-L_grid");
        lGrid = count != -1 ? stoi(argv[count+1]) : 0;
    }
    else if (argc == __MINIMAL_ARGUMENTS){
        cout << "You haven't provided an input file location. Please enter one now: ";
        cin >> inputFileName;
        cout << endl;

        cout << "You haven't provided a query file location. Please enter one now: ";
        cin >> queryFileName;
        cout << endl;

        count = strArraySearch(argv, argc, "-o");
        outputFileName = count != -1 ? argv[count+1] : NULL;

        lGrid = 4;
    }
    else{
        cerr << "Invalid number of arguments provided. Exiting." << endl;
        return -1;
    }

    if(inputFileName.empty() 
        || outputFileName.empty()
        || queryFileName.empty()
        || kVector == 0 
        || lGrid == 0){
            cerr << "You have provided invalid arguments. Exiting." << endl;
    }
    //End Argument Handling

    vector<Curve*> dataset = parseFileForCurvePoints(inputFileName);
    vector<tuple<float,float>> coords;

    setprecision(15);
    
    ofstream outputFile;
    outputFile.open(outputFileName);
    // for (int i = 0; i < dataset.size(); i++){
    //     outputFile << dataset[i]->getCurveId() << endl;
    //     outputFile << dataset[i]->getNumberOfPoints() << endl;
    //     coords = dataset[i]->getCurvePoints();
    //     for (size_t j = 0; j < coords.size(); j++)
    //     {
    //         outputFile << " (" << get<0>(coords[j]) << "," << get<1>(coords[j]) << ") ";
    //     }
    //     outputFile << endl;
    // }

    int delta;
    vector<float> tVector;
    Curve * currentCurve;
    //Foreach curve we need to create lGrid grid curves and flatten them
    for (size_t i = 0; i < dataset.size(); i++){
        
        currentCurve = dataset[i];

        //δ is calculated by 4*dimension*m1
        delta = 4 * 2 * currentCurve->getNumberOfPoints();
        //Dimension is 2
        tVector = generateUniformTVector(2);
        for (size_t k = 0; k < tVector.size(); k++)
        {
            cout << tVector[k];
        }
        
        for (size_t j = 0; j < lGrid; j++){
        /* code */
        }
    }
    
    

}