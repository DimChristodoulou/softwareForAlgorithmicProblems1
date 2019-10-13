/**
 * @file lsh.cpp
 * @author Dimitris Christodoulou - Giorgos Tsiros
 * @brief Main function for the Locality Sensitive Hashing Algorithm on D-Dimensional Vectors
 * @version 0.1 - Build 2.1
 * @date 2019-10-04
 * 
 * HOW TO INVOKE FOR SAMPLE : ./exe/lsh -d datasets/sample1.txt -o output.txt -q querysets/sample1.txt -k 4 -L 5
 * HOW TO INVOKE FOR SAMPLE : ./exe/lsh -d datasets/input_small_id -o output.txt -q querysets/query_small_id -k 4 -L 5
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "../inc/globals.h"
#include "../inc/manhattan.h"
#include "../inc/point.h"
#include "../inc/utils.h"

#define __FULL_ARGUMENTS 11
#define __MINIMAL_ARGUMENTS 3

#define _N 20

using namespace std;

int main(int argc, char const *argv[])
{
    int count, numberOfHiFunctions = 0, numberOfHashTables = 0;
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

        count = strArraySearch(argv, argc, "-k");
        numberOfHiFunctions = count != -1 ? stoi(argv[count+1]) : 0;

        count = strArraySearch(argv, argc, "-L");
        numberOfHashTables = count != -1 ? stoi(argv[count+1]) : 0;
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

        numberOfHiFunctions = 4;
        numberOfHashTables = 5;
    }
    else{
        cerr << "Invalid number of arguments provided. Exiting." << endl;
        return -1;
    }

    if(inputFileName.empty() 
        || outputFileName.empty()
        || queryFileName.empty()
        || numberOfHiFunctions == 0 
        || numberOfHashTables == 0){
            cerr << "You have provided invalid arguments. Exiting." << endl;
    }
    //End Argument Handling
    
    long long unsigned w = generateRandomW();
    cout << "W is: " << w << endl;

    //Produce dataset
    vector<Point*> initialDataset = parseFileForPoints(inputFileName, false, NULL);
    if(initialDataset.empty()){
        cout << "Error Occured; Exiting" << endl;
    }
    //End produce dataset
    
    double radius;
    vector<Point*> queryDataset = parseFileForPoints(queryFileName, true, &radius);
    if(queryDataset.empty()){
        cout << "Error Occured; Exiting" << endl;
    }
    
    int pointsDimension = initialDataset[0]->getDimension();
    
    // vector<float> uniformNumbers = generateUniformNumbers(0, w, pointsDimension);
    // vector<float> randomNumbers = generateRandomNumbersBetween(0, w, pointsDimension);
    // for (i = 0; i < uniformNumbers.size(); i++){
    //     cout << uniformNumbers[i] << endl;
    //     cout << randomNumbers[i] << endl;
    // }

    // for (i = 0; i < initialDataset.size(); i++){
    //     cout << "Point " << initialDataset[i]->getPointIdentifier() << " coords ";
    //     initialDataset[i]->printCoordinatesFormatted();
    // }

    // for (i = 0; i < queryDataset.size(); i++){
    //     cout << "Point " << queryDataset[i]->getPointIdentifier() << " coords ";
    //     queryDataset[i]->printCoordinatesFormatted();
    // }

    cout << "EXPECTED: " << calculate(initialDataset[0], queryDataset[0]) << endl;
    cout << "EXPECTED: " << calculate(initialDataset[0], queryDataset[1]) << endl;
    cout << "EXPECTED: " << calculate(initialDataset[1], queryDataset[0]) << endl;
    cout << "EXPECTED: " << calculate(initialDataset[1], queryDataset[1]) << endl;
    

    vector<vector<float>> exhaustiveArray = generateExhaustiveArray(initialDataset, queryDataset);
    
    // for (i = 0; i < initialDataset.size(); i++){
    //     for (j = 0; j < queryDataset.size(); j++){
    //         cout << exhaustiveArray[i][j] << "\t" << endl;
    //     }
    // }

    ofstream myfile;
    myfile.open (outputFileName);
    cout << queryDataset[0]->getPointIdentifier() << endl;
    for (i = 0; i < queryDataset.size(); i++){
        int index = queryDataset[i]->getClosestNeighbor(exhaustiveArray[i]);
        myfile << "Nearest neighbor of " 
             << queryDataset[i]->getPointIdentifier() 
             << " is " 
             << initialDataset[index]->getPointIdentifier() 
             << " with distance " 
             << exhaustiveArray[i][index] << endl;
    }
    
    myfile.close();

}
