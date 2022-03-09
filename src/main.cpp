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
        if(argc == 2)
            fm.getFiles(argv[1],"");
        else
            fm.getFiles(argv[1],argv[2]);
    } else {
        cout << "Wrong number of command line arguments" << endl;
    }
    return 0;
}