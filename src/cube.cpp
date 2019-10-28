/**
 * @file cube.cpp
 * @author Dimitris Christodoulou - Giorgos Tsiros
 * @brief Main function for the Hypercube Algorithm on D-Dimensional Vectors
 * @version 0.1 - Build 2.1
 * @date 2019-10-04
 * 
 * HOW TO INVOKE FOR SAMPLE : ./exe/cube -d datasets/input_small_id -o outputCUBE.txt -q querysets/query_small_id -k 3 -M 10 -probes 2
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
    int count, M, probes, dimension;
    
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
        dimension = count != -1 ? stoi(argv[count+1]) : 0;

        count = strArraySearch(argv, argc, "-M");
        M = count != -1 ? stoi(argv[count+1]) : 0;

        count = strArraySearch(argv, argc, "-probes");
        probes = count != -1 ? stoi(argv[count+1]) : 0;
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

        dimension = 3;
        M = 10;
        probes = 2;
    }
    else{
        cerr << "Invalid number of arguments provided. Exiting." << endl;
        return -1;
    }

    if(inputFileName.empty() 
        || outputFileName.empty()
        || queryFileName.empty()
        || dimension == 0 
        || probes == 0
        || M == 0){
            cerr << "You have provided invalid arguments. Exiting." << endl;
    }

    cout << dimension << endl;
    unordered_map<int, vector<Point*>> hashTable;
    ofstream outputFile;
    outputFile.open (outputFileName);
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
    short int binaryDigits = 32/dimension;
    long long binHValue, tempBinHValue;

    clock_t begin = clock();
    vector<vector<float>> exhaustiveArray = generateExhaustiveArray(initialDataset, queryDataset);

    float w = 0;
    ofstream myfile;
    myfile.open ("exhaustive.txt");
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
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    outputFile << "Time passed to calculate W: " << elapsed_secs << endl;

    w = ((float)w/pointsDimension)*3;
    unsigned short int finalHashValue;
    int k;

    unordered_map<long long int, short int> fMemory;
    ostringstream oss, binaryOss;
    begin = clock();
    for (j = 0; j < initialDataset.size(); j++){
        finalHashValue = 0;
        binaryOss.str("");

        for(k=0; k < dimension; k++){
            fMemory.clear();            
            for (int i = 0; i < dimension; i++){
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
            finalHashValue = getBinaryDigitBasedOnHashValue(fMemory, binaryHashValue);
            binaryOss << to_string(finalHashValue);
        }

        string myStr = oss.str();
        char *strStart = &(myStr[0]), *strEnd;
        oss.clear();
        unsigned long long int binaryHashValue;
        binaryHashValue = strtoull(strStart, &strEnd, 2);
        hashTable[binaryHashValue].push_back(initialDataset[j]);

    }
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    outputFile << "Time Passed to perform Cube on Input dataset: " << elapsed_secs << endl;

    cout << endl << "Starting NN Search through Cube" << endl;
    tuple<int, float> closestNeighbor;

    begin = clock();
    //Actual search for NN
    for (j = 0; j < initialDataset.size(); j++){
        finalHashValue = 0;
        binaryOss.str("");
        clock_t begin2 = clock();
        for(k=0; k < dimension; k++){
            fMemory.clear();            
            for (int i = 0; i < dimension; i++){
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
            finalHashValue = getBinaryDigitBasedOnHashValue(fMemory, binaryHashValue);
            binaryOss << to_string(finalHashValue);
        }

        string myStr = oss.str();
        char *strStart = &(myStr[0]), *strEnd;
        oss.clear();
        unsigned long long int binaryHashValue;
        binaryHashValue = strtoull(strStart, &strEnd, 2);
        tuple<int, float> closestNeighbor = queryDataset[j]->getClosestNeighborLSH(hashTable[binaryHashValue]);
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
    outputFile << "Time Passed to classify query data: " << elapsed_secs << endl;
    outputFile.close();
}