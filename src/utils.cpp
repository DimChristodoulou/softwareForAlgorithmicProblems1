/*! \file utils.cpp
    \brief  This file contains various functions used in different assisting tasks and the functions of the Point class (refer to utils.h)
*/
#include "../inc/globals.h"
#include "../inc/point.h"
#include "../inc/manhattan.h"
#include "../inc/curve.h"

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
 * @brief Generates random numbers between a low and high bound.
 * 
 * @param lowBound The lowest possible number.
 * @param highBound The highest possible number.
 * @param amountOfOutputtedNums The amount of numbers that will be produced.
 * @return vector<float> A vector that contains the random numbers.
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
 * @param base The base value.
 * @param exponent The exponent.
 * @param modulus The amount of shifting we need
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

/**
 * @brief A sign-safe modulo function
 * 
 * @param a Modulo left operand.
 * @param b Modulo right operand.
 * @return int If a is positive, this acts exactly like the normal mod operation. 
 * Otherwise, this will return the negative modulo of a number, e.g. (-2)%5=3
 */
int mod(int a, int b) {
    return (abs(a) % b + b) % b;
}

/**
 * @brief Helper function to convert an integer to a binary.
 * 
 * @param n The decimal we want to convert.
 * @return long long The binary that was converted.
 */
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
    
    for (int i = 0; i < dim; i++){
        int modulus = modularExponentiation(base, dim-1-i, modulo);
        int lvalue = int ( floor( (xi[i]-si[i]) /w ));
        hashValue += ( mod(lvalue, modulo) *modulus) % modulo;
    }
    
    return (hashValue%modulo);
}

/**
 * @brief Gets a Binary Digit Based On the passed Hash Value. Initially has a 50% chance of providing 0 or 1.
 * However the function has a map of key value pairs, with the key being the hash value and the value being the actual
 * binary digit. In subsequent calls, the function looks up the hash value. If it's found, the in-memory value is returned.
 * 
 * @param memory An unordered map of long long int keys and short int values.
 * @param hashValue The value we want to produce the binary digit from.
 * @return short int A binary digit, 0 or 1.
 */
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

/**
 * @brief Get the closest neighbor out of a vector of possible neighbors
 * Only applicable in LSH, since Hypercube does not use multiple hash tables.
 * 
 * @param possibleNeighbors A vector of <int, float> tuples, with the int being the index of the neighbor 
 * and the float the distance between this neighbor and the query point.
 * @return tuple<int, float> The closest neighbor out of the possible ones.
 */
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


/***************************************************************************************************************************************************************
 ************************************************************* CURVE FUNCTIONS START FROM HERE *****************************************************************
 ***************************************************************************************************************************************************************/

vector<Curve*> parseFileForCurvePoints(string fileName){

    ifstream pointsFile;
    pointsFile.open(fileName);
    vector<Curve*> dataset;
    int numberOfPoints;

    setprecision(15);

    if(pointsFile.fail()){
        cerr << "Error: " << strerror(errno) << endl;
    }
    if(pointsFile.is_open()){
        string fileLine, currentPointIdentifier;
        vector<string> delimitedResult;
        vector<tuple<float, float>> coords;
        float x,y;

        while (getline(pointsFile, fileLine)){
            istringstream iss(fileLine);
            vector<string> results(istream_iterator<string>{iss}, istream_iterator<string>());
            currentPointIdentifier = results[0];
            numberOfPoints = stoi(results[1]);

            for (unsigned int i = 2; i < results.size(); i++){
                delimitedResult.clear();
                if(i%2==0){
                    results[i] = results[i].substr(1, results[i].size() - 2);
                    x = stof(results[i]);
                }
                else{
                    results[i].erase(results[i].size() - 1);
                    y = stof(results[i]);
                    coords.push_back( make_tuple(x, y) );
                    //cout << x << " - " << y << endl;
                }
                
                //cout << endl;
            }

            Curve *currentPoint = new Curve(currentPointIdentifier, numberOfPoints, coords);
            dataset.push_back(currentPoint);
            coords.clear();
        }
    }

    if(!dataset.empty()){
        return dataset;
    }
    return {};

}

// int getMaxDimension(vector<Curve*> dataset){

//     for (size_t i = 0; i < count; i++)
//     {
//         /* code */
//     }
    
// }

vector<float> generateUniformTVector(int dimension){
    static default_random_engine generator;
    static normal_distribution<float> distribution(0.0, 1);
    vector<float> tVector;
    for (size_t i = 0; i < dimension; i++)
    {
        tVector.push_back(distribution(generator));
    }
    return tVector;
}

// void createGridCurve(vector v){		//Create gric_curve
// 	N *vec = new N();
// 	double prev;
// 	//for each point
// 	for(unsigned int k=0;k<v.size();k++){
// 		unsigned int size = v[k].size();
// 		if(size != t.size()){
// 			cerr << "We expected " <<t.size()<<"-dimensional curve and get " << size <<"-dimensional curve!"<<endl;
// 			exit(1);
// 		}
// 		//for each dimension find the point on grid and shift the point
// 		for(unsigned int i=0;i<size;i++){
// 			double temp = (int)(((v[k])[i]+0.5)/this->delta) + this->t[i];
// 			if(i == 0 || prev != temp)
// 				vec->push_back(temp);	//If point is not equal with previous, push it to the vector
// 			prev = temp;
// 		}
// 	}
// 	return vec;							//Return the grid_curve
// }

template <typename T>
std::vector<T> operator+(const std::vector<T>& a, const std::vector<T>& b)
{
    assert(a.size() == b.size());

    std::vector<T> result;
    result.reserve(a.size());

    std::transform(a.begin(), a.end(), b.begin(), 
                   std::back_inserter(result), std::plus<T>());
    return result;
}