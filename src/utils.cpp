/*! \file utils.cpp
    \brief  This file contains various functions used in different assisting tasks and the functions of the Point class (refer to utils.h)
*/
#include "../inc/globals.h"
#include "../inc/point.h"
#include "../inc/manhattan.h"

#define __HASH_PARAMETER 13

using namespace std;

/**
 * @brief Returns a random large integer (W >> r)
 * 
 * @return int 
 */
long long unsigned generateRandomW(){
    std::random_device rd;
    std::default_random_engine generator(rd());
    /* Distribution on which to apply the generator */
    std::uniform_int_distribution<long long unsigned> distribution(0,0xFFFFFFFFFFFFFFFF);
    return distribution(generator);
}

/**
 * @brief Reads a file and returns a vector of Point objects from the points in the file (1 per line). 
 * 
 * @param filePath The path of the file starting from the root folder.
 * @return vector<Point*> The parsed text file represented in Point object vector.
 */
vector<Point*> parseFileForPoints(string filePath, bool isSearchDataset = false, double *radius = NULL){
    cout << filePath << endl;
    ifstream pointsFile;
    pointsFile.open(filePath);
    vector<Point*> dataset;

    if(pointsFile.fail()){
        cerr << "Error: " << strerror(errno) << endl;
    }
    if(pointsFile.is_open()){
        string fileLine, currentPointIdentifier;
        vector<float> currentPointCoordinates;

        if(isSearchDataset){
            getline(pointsFile, fileLine);
            istringstream iss(fileLine);
            vector<string> results(istream_iterator<string>{iss}, istream_iterator<string>());
            if(results.size() > 1){
                pointsFile.clear();
                pointsFile.seekg(0, ios::beg);
                cout << results[0] << endl;
                *radius = stod(results[0]);
            }
        }

        while (getline(pointsFile, fileLine)){
            istringstream iss(fileLine);
            vector<string> results(istream_iterator<string>{iss}, istream_iterator<string>());
            currentPointIdentifier = results[0];
            for (unsigned int i = 1; i < results.size(); i++){
                currentPointCoordinates.push_back(stof(results[i]));
            }

            Point *currentPoint = new Point(currentPointCoordinates);
            currentPoint->setPointIdentifier(currentPointIdentifier);
            dataset.push_back(currentPoint);

            currentPointCoordinates.clear();
        }
    }

    if(!dataset.empty()){
        return dataset;
    }
    return {};
}

/**
 * @brief Gets an array of char[] pointers, searches for the given delimiter and returns its first position
 * 
 * @param array The argument array to be parsed
 * @param len The length of the argv array
 * @param delim The delimiter to check
 * @return int If delimiter was found, return its position. If not, return -1.
 */
int strArraySearch(char const *array[], int len, char const *delim){
    if(len == 0){
        return -1;
    }
	for(int i = 0; i < len; ++i){
	    if(!strcmp(array[i], delim))
	        return i;
	}
	return -1;
}

/**
 * @brief Simple modulus hash function
 * 
 * @param value The hash value
 * @return int Corresponds to the bucket index of the @param value
 */
int hashFunction(int value){
    return value % __HASH_PARAMETER;
}

/**
 * @brief IMPORTANT: Only available in c++11. Need to verify if that's what we'll be running.
 * 
 * @param lowBound From <range modifier>
 * @param highBound To <range modifier>
 * @param amountOfOutputtedNums How many numbers will be returned
 * @return vector<float> 
 */
vector<float> generateUniformNumbers(int lowBound, int highBound, int amountOfOutputtedNums){
    random_device rand_dev;
    mt19937 generator(rand_dev());
    //uniform_int_distribution<int> distr(lowBound, highBound);
    uniform_real_distribution<float> realDistribution(lowBound, highBound);

    vector<float> numbersGenerated;

    for (int i=0; i<amountOfOutputtedNums; ++i) {
        numbersGenerated.push_back(realDistribution(generator));
    }

    return numbersGenerated;
}

/**
 * @brief 
 * 
 * @return vector<float> 
 */
vector<float> generateRandomNumbersBetween(int lowBound, int highBound, int amountOfOutputtedNums){
    srand (time(NULL));
    vector<float> generatedNumbers;
    for (int i = 0; i < amountOfOutputtedNums; i++){
        generatedNumbers.push_back( (rand()%highBound) + lowBound );
    }
    return generatedNumbers;
}

/**
 * @brief generates a PxQ array of floats. Each row represents the distance of a query point from each other dataset point.
 * 
 * @param initialDataset The training dataset (columns)
 * @param queryDataset The search dataset (rows)
 * @return vector<vector<float>> The distance matrix
 */
vector<vector<float>> generateExhaustiveArray(vector<Point *> initialDataset, vector<Point*> queryDataset){
    unsigned int i,j;
    vector<vector<float>> exhaustiveArray;
    vector<float> exhaustiveArrayRow;
    cout << initialDataset.size() << endl;
    for(i=0; i<queryDataset.size();i++){
        exhaustiveArrayRow.clear();
        for (j = 0; j < initialDataset.size(); j++){
            exhaustiveArrayRow.push_back( calculate(initialDataset[j], queryDataset[i]) );
        }
        exhaustiveArray.push_back(exhaustiveArrayRow);
    }
    return exhaustiveArray;
}