/*! \file utils.cpp
    \brief  This file contains various functions used in different assisting tasks and the functions of the Point class (refer to utils.h)
*/
#include "../inc/globals.h"
#include "../inc/point.h"

#define __HASH_PARAMETER 13

using namespace std;

/**
 * @brief Reads a file and returns a vector of Point objects from the points in the file (1 per line). 
 * 
 * @param filePath The path of the file starting from the root folder.
 * @return vector<Point*> The parsed text file represented in Point object vector.
 */
vector<Point*> parseFileForPoints(string filePath){
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

        while (getline(pointsFile, fileLine)){
            std::istringstream iss(fileLine);
            vector<string> results(istream_iterator<string>{iss}, istream_iterator<string>());

            currentPointIdentifier = results[0];
            for (int i = 1; i < results.size(); i++){
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

}

/**
 * @brief Gets an array of char[] pointers, searches for the given delimiter and returns its first position
 * 
 * @param array The argument array to be parsed
 * @param len The length of the argv array
 * @param delim The delimiter to check
 * @return int If delimiter was found, return its position. If not, return -1.
 */
int strArraySearch(char const *array[], int len, char *delim){
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
 */
void generateUniformNumbers(){
    const int range_from  = 0;
    const int range_to    = 10;
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>  distr(range_from, range_to);

    std::cout << distr(generator) << '\n';
}