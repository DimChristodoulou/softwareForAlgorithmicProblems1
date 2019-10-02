#include "../inc/globals.h"
#include "../inc/manhattan.h"
#include "../inc/point.h"
#include "../inc/utils.h"

using namespace std;

int main(int argc, char const *argv[])
{
    vector<Point*> initialDataset = parseFileForPoints("datasets/sample1.txt");
    if(initialDataset.empty()){
        cout << "Error Occured; Exiting" << endl;
    }

    //Some debugging
    for (int i = 0; i < initialDataset.size(); i++)
    {
        cout << initialDataset[i]->getPointIdentifier() << endl;
        initialDataset[i]->printCoordinatesFormatted();

        cout << calculate(initialDataset[0], initialDataset[1]) << endl;
    }

}
