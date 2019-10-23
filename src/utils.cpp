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

/**
 * @brief Modular Exponentiation
 * 
 * @param base 
 * @param exponent
 * @param modulus
 * @return int 
 */
int modularExponentiation(unsigned int base, int exponent, int modulus){
    int remainder;
    int x = 1;
    while (exponent != 0){
        remainder = exponent % 2;
        exponent = exponent/2;

        if (remainder == 1)
        x = (x * base) % modulus;
        base = (base * base) % modulus; // New base equal b^2 % m
    }
    return x;
}

int mod(int a, int b) {
    return (abs(a) % b + b) % b;
}

long long convertDecimalToBinary(int n){
    long long binaryNumber = 0;
    int remainder, i = 1;
    while (n!=0){
        remainder = n%2;
        n /= 2;
        binaryNumber += remainder*i;
        i *= 10;
    }
    return binaryNumber;
}

/**
 * @brief This is the hi hash function
 * 
 * @param initialDatasetPoint the point xi
 * @param w the number we calculated beforehand (=10*mean(minimum_dist))
 * @return int a hash value
 */
int hiHashFunction(Point *initialDatasetPoint, int w, unsigned int base, int modulo){

    int dim = initialDatasetPoint->getDimension();
    int hashValue = 0;

    vector<float> xi = initialDatasetPoint->getCoordinates();
    vector<float> si = generateRandomNumbersBetween(0, w, dim);
    // for (size_t i = 0; i < si.size(); i++)
    // {
    //     cout << si[i] << " ";
    // }
    // cout << endl << endl;
    
    for (int i = 0; i < dim; i++){
        int modulus = modularExponentiation(base, dim-1-i, modulo);
        int lvalue = int ( floor( (xi[i]-si[i]) /w ));
        hashValue += ( mod(lvalue, modulo) *modulus) % modulo;
        //cout << "MODULUS " << modulus << " HASHVALUE " << hashValue << " FLOOR "  << floor(xi[i] - si[i]) << " w " << w << " lvalue " << lvalue << endl;
    }
    
    // cout << hashValue << " modulo " << modulo << endl;
    // cout << "return " << (hashValue % modulo) << endl;
    return (hashValue%modulo);
}

short int getBinaryDigitBasedOnHashValue(unordered_map<long long int, short int> memory, long long int hashValue){
    unordered_map<long long int, short int>::iterator it = memory.begin();

    // Iterate over the map using iterator
    while(it != memory.end()){
        if(it->first == hashValue){
            return it->second;
        }
    }
    memory[hashValue] = rand()%2;
    return memory[hashValue];
}

tuple<int, float> getNeighborOutOfPossibleNeighbors(vector<tuple<int, float>> possibleNeighbors){
    float minDistance = numeric_limits<float>::max();
    int index;
    float currentDist;

    for (int i = 0; i < possibleNeighbors.size(); i++){
        currentDist = get<1>(possibleNeighbors[i]);
        if(currentDist < minDistance){
            minDistance = currentDist;
            index = i;
        }
    }
    return possibleNeighbors[index];
    
}