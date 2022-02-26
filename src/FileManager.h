#ifndef PA02_FILEMANAGER_H
#define PA02_FILEMANAGER_H

#include <vector>
#include <fstream>
#include "DataSet.h"
using namespace std;

class FileManager {
private:
    vector<string> files;
    vector<DataSet<int>> iData;
    vector<DataSet<string>> sData;
public:
    FileManager() = default;

    void getFiles();
    void readFiles();
    void createOutput();
};


#endif //PA02_FILEMANAGER_H
