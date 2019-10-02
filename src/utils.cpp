/*! \file utils.cpp
    \brief  This file contains various functions used in different assisting tasks and the functions of the Point class (refer to utils.h)
*/
#include "../inc/globals.h"
#include "../inc/point.h"

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