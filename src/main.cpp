/* Wes Anderson and Ryan Schaefer
 * 22s-CS-3353 PA 2
 * 2/8/22
 *
 */

#include <iostream>
#include "FileManager.h"
using namespace std;


int main(int argc, char** argv) {
    if (argc == 2 || argc == 3) {
        cout << "Segmentation fault" << endl;
        FileManager fm;
        if (argc > 2 && strcmp(argv[2], "-i") == 0)
        {
            cout << "-i detected. Running all but insertion sort" << endl;
            fm.getFiles(argv[1],false);
        }

        else if(argc == 2)
        {
            cout << "No -i detected. Running all algorithms" << endl;
            fm.getFiles(argv[1],true);
        }
        else
            cout << "Problem with command line arguments" << endl;
    } else {
        cout << "Wrong number of command line arguments" << endl;
    }
    return 0;
}