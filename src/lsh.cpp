/**
 * @file lsh.cpp
 * @author Dimitris Christodoulou - Giorgos Tsiros
 * @brief Main function for the Locality Sensitive Hashing Algorithm on D-Dimensional Vectors
 * @version 0.1 - Build 2.1
 * @date 2019-10-04
 * 
 * HOW TO INVOKE FOR SAMPLE : ./exe/lsh -d datasets/sample1.txt -o output.txt -q querysets/sample1.txt -k 4 -L 5
 * HOW TO INVOKE FOR SAMPLE : ./exe/lsh -d datasets/input_small_id -o outputLSH.txt -q querysets/query_small_id -k 4 -L 5
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
    srand (time(NULL));
    unsigned int m = pow(2,32)-5;

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

    int tempPow = 32 / numberOfHiFunctions;
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
    
    vector<vector<float>> exhaustiveArray = generateExhaustiveArray(initialDataset, queryDataset);

    float w = 0;

    ofstream myfile, outputFile;
    myfile.open ("exhaustive.txt");
    //cout << queryDataset[0]->getPointIdentifier() << endl;
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
    //cout << w << endl;

    int d = queryDataset[0]->getDimension();
    
    //cout << "MODULAR EXPO: " << modularExponentiation(m, d-1, M) << endl;

    //cout << "HASH VALUE H1: " << hiHashFunction(initialDataset[0],w,m,M);

    int hvalue, length;
    short int binaryDigits = 32/numberOfHiFunctions;
    long long binHValue, tempBinHValue;
    vector<unordered_map<int, vector<Point*>>> listOfHashTables;
    for (int i = 0; i < numberOfHashTables; i++)
    {
        unordered_map<int, vector<Point*>> hashTable;
        listOfHashTables.push_back( hashTable );
    }
    
    clock_t begin = clock();
    ostringstream oss;
    for (j = 0; j < initialDataset.size(); j++){

        for (int k = 0; k < numberOfHashTables; k++){
    
            for (int i = 0; i < numberOfHiFunctions; i++){
                length = 1;

                hvalue = hiHashFunction(initialDataset[j],w,m,M);
                binHValue = convertDecimalToBinary(hvalue);
                tempBinHValue = binHValue;

                while ( tempBinHValue /= 10 )
                    length++;

                //cout << "hvalue " << hvalue << " BINARY " << binHValue << " length " << length << endl;

                while(length < binaryDigits){
                    oss << '0';
                    //cout << oss.str() << endl;
                    length++;
                }
                oss << binHValue;
                //cout << oss.str() << endl;
            }
            string myStr = oss.str();
            char *strStart = &(myStr[0]), *strEnd;
            oss.clear();
            unsigned long long int binaryHashValue;
            binaryHashValue = strtoull(strStart, &strEnd, 2);

            //printf("DECIMAL %llu", binaryHashValue);
            
            //This is the index of the specific point
            int tokenBucket = binaryHashValue % M;
            
            listOfHashTables[k][tokenBucket].push_back(initialDataset[j]);
        }
    }
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time Passed to perform LSH on Input dataset: " << elapsed_secs << endl;

    //Simply output hash buckets - for now
    // for (auto& it: hashTable) {
    //     cout << "PIDs of bucket " << it.first << " - ";
    //     for (i = 0; i < it.second.size(); i++){
    //         cout << it.second[i]->getPointIdentifier() << " - ";
    //     }
    //     cout << endl;
    // }

    cout << endl << "Starting NN Search through LSH" << endl;
    vector<tuple<int, float>> possibleNeighborsVector;
    tuple<int, float> closestNeighbor;

    outputFile.open(outputFileName);

    begin = clock();
    //Actual search for NN
    for (j = 0; j < queryDataset.size(); j++){
        possibleNeighborsVector.clear();
        clock_t begin2 = clock();
        for(int k=0; k<numberOfHashTables; k++){
    
            for (int i = 0; i < numberOfHiFunctions; i++){
                length = 1;

                hvalue = hiHashFunction(queryDataset[j],w,m,M);
                binHValue = convertDecimalToBinary(hvalue);
                tempBinHValue = binHValue;

                while ( tempBinHValue /= 10 )
                    length++;

                //cout << "hvalue " << hvalue << " BINARY " << binHValue << " length " << length << endl;

                while(length < binaryDigits){
                    oss << '0';
                    //cout << oss.str() << endl;
                    length++;
                }
                oss << binHValue;
                //cout << oss.str() << endl;
            }
            string myStr = oss.str();
            char *strStart = &(myStr[0]), *strEnd;
            oss.clear();
            unsigned long long int binaryHashValue;
            binaryHashValue = strtoull(strStart, &strEnd, 2);

            //printf("DECIMAL %llu", binaryHashValue);
            
            //This is the index of the specific point
            int tokenBucket = binaryHashValue % M;
            tuple<int, float> NNofQueryPoint = queryDataset[j]->getClosestNeighborLSH(listOfHashTables[k][tokenBucket]);
            possibleNeighborsVector.push_back(NNofQueryPoint);
            //cout << get<0>(NNofQueryPoint) << " - " << get<1>(NNofQueryPoint) << endl;
        }
        closestNeighbor = getNeighborOutOfPossibleNeighbors(possibleNeighborsVector);
        clock_t end2 = clock();
        double elapsed_secs2 = double(end2 - begin2) / CLOCKS_PER_SEC;

        clock_t begin3 = clock();
        int index = queryDataset[j]->getClosestNeighbor(exhaustiveArray[j]);
        clock_t end3 = clock();
        double elapsed_secs3 = double(end3 - begin3) / CLOCKS_PER_SEC;

        outputFile << "Query: " << j << endl;
        outputFile << "Nearest Neighbor: " << get<0>(closestNeighbor) << endl;
        outputFile << "distanceLSH: " << get<1>(closestNeighbor) << endl;
        outputFile << "distanceTrue: " << exhaustiveArray[j][index] << endl;
        outputFile << "tLSH: " << elapsed_secs2 << endl;
        outputFile << "tTrue: " << elapsed_secs3 << endl << endl;

    }
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time Passed to classify query data: " << elapsed_secs << endl;
    outputFile.close();
}
