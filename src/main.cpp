/* Wes Anderson and Ryan Schaefer
 * 22s-CS-3353 PA 2
 * 2/8/22
 *
 */

#include <iostream>
#include "FileManager.h"
using namespace std;


int main(int argc, char** argv) {
    cout << "Segmentation fault" << endl;
    if (argc == 2) {
        FileManager fm;
        fm.getFiles(argv[1]);
    }
    return 0;
}