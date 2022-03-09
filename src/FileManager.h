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

    void getFiles(char*, char*);
    void readFiles(char*);
    void createOutput(char*);
};


#endif //PA02_FILEMANAGER_H
