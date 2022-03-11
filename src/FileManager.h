/* Wes Anderson and Ryan Schaefer
 * 22s-CS-3353 PA 2
 * 2/8/22
 *
 */

#ifndef PA02_FILEMANAGER_H
#define PA02_FILEMANAGER_H

#include <vector>
#include <fstream>
#include "DataSet.h"
using namespace std;

class FileManager {
private:
    vector<string> files;
    vector<DataSet<int> > iData;
    vector<DataSet<string> > sData;
public:
    FileManager() = default;

    void getFiles(char*, bool);
    void readFiles(bool);
    void createOutput(bool);
};


#endif //PA02_FILEMANAGER_H
