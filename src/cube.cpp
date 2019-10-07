/**
 * @file cube.cpp
 * @author Dimitris Christodoulou - Giorgos Tsiros
 * @brief Main function for the Hypercube Projection problem on D-Dimensional Vectors
 * @version 0.1 - Build 2.1
 * @date 2019-10-04
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

using namespace std;

int main(int argc, char const *argv[]){

    int count, numberOfHiFunctions, numberOfHashTables;
    FILE *inputFile, *outputFile, *queryFile;
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
        numberOfHiFunctions = count != -1 ? stoi(argv[count+1]) : NULL;

        count = strArraySearch(argv, argc, "-L");
        numberOfHashTables = count != -1 ? stoi(argv[count+1]) : NULL;
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

    if(empty(inputFileName) 
        || empty(outputFileName) 
        || empty(queryFileName) 
        || numberOfHiFunctions == NULL 
        || numberOfHashTables == NULL){
            cerr << "You have provided invalid arguments. Exiting." << endl;
    }

}