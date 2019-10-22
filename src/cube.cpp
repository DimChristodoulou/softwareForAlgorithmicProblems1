/**
 * @file cube.cpp
 * @author Dimitris Christodoulou - Giorgos Tsiros
 * @brief Main function for the Hypercube Algorithm on D-Dimensional Vectors
 * @version 0.1 - Build 2.1
 * @date 2019-10-04
 * 
 * HOW TO INVOKE FOR SAMPLE : ./exe/cube -d datasets/sample1.txt -o output.txt -q querysets/sample1.txt -k 4 -L 5
 * HOW TO INVOKE FOR SAMPLE : ./exe/cube -d datasets/input_small_id -o output.txt -q querysets/query_small_id -k 4 -L 5
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "../inc/globals.h"
#include "../inc/manhattan.h"
#include "../inc/point.h"
#include "../inc/utils.h"

#define __FULL_ARGUMENTS 13
#define __MINIMAL_ARGUMENTS 5

using namespace std;

int main(int argc, char const *argv[]){

    srand (time(NULL));
    unsigned int m = pow(2,32)-5;
    unsigned int i, j;
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
        numberOfHiFunctions = count != -1 ? stoi(argv[count+1]) : 0;

        count = strArraySearch(argv, argc, "-L");
        numberOfHashTables = count != -1 ? stoi(argv[count+1]) : 0;

        count = strArraySearch(argv, argc, "-probes");
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

    if(inputFileName.empty() 
        || outputFileName.empty()
        || queryFileName.empty()
        || numberOfHiFunctions == 0 
        || numberOfHashTables == 0){
            cerr << "You have provided invalid arguments. Exiting." << endl;
    }

    int tempPow = 32 / numberOfHiFunctions;
    cout << numberOfHiFunctions << endl;
    unsigned int M = pow(2,tempPow);
    unordered_map<int, vector<Point*>> hashTable;

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
    int queryDimension = queryDataset[0]->getDimension();
    if(pointsDimension != queryDimension){
        cerr << "Dimensions are not equal" << endl;
        return -1;
    }

    int hvalue, length;
    short int binaryDigits = 32/numberOfHiFunctions;
    long long binHValue, tempBinHValue;

    vector<vector<float>> exhaustiveArray = generateExhaustiveArray(initialDataset, queryDataset);

    float w = 0;

    ofstream myfile;
    myfile.open (outputFileName);
    for (i = 0; i < queryDataset.size(); i++){
        int index = queryDataset[i]->getClosestNeighbor(exhaustiveArray[i]);
        myfile << "Nearest neighbor of " 
             << queryDataset[i]->getPointIdentifier() 
             << " is " 
             << initialDataset[index]->getPointIdentifier() 
             << " with distance " 
             << exhaustiveArray[i][index] << endl;
        w += exhaustiveArray[i][index];
    }

    myfile.close();

    w = ((float)w/pointsDimension)*3;
    short int fHashValue;
    unsigned int dEntoned;
    unsigned int k;

    for(k=0; k < dEntoned; k++){

    }

    ostringstream oss;
    for (j = 0; j < initialDataset.size(); j++){

        for(k=0; k < dEntoned; k++){
    
            for (int i = 0; i < numberOfHiFunctions; i++){
                length = 1;

                hvalue = hiHashFunction(initialDataset[j],w,m,M);
                binHValue = convertDecimalToBinary(hvalue);
                tempBinHValue = binHValue;

                while ( tempBinHValue /= 10 )
                    length++;

                while(length < binaryDigits){
                    oss << '0';
                    length++;
                }
                oss << binHValue;
            }
            string myStr = oss.str();
            char *strStart = &(myStr[0]), *strEnd;
            oss.clear();
            unsigned long long int binaryHashValue;
            binaryHashValue = strtoull(strStart, &strEnd, 2);

            /* HERE IS THE DIFFERENCE BETWEEN LSH AND HYPERCUBE - in hypercube we pass the binary hash value in a function
            * that initially assigns a random value between 0 and 1 but stores the binary hash value + the number it generated
            * and produces this number every time we get this hash value.
            */

        
        }

    }

}