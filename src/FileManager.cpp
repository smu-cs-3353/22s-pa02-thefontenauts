/* Wes Anderson and Ryan Schaefer
 * 22s-CS-3353 PA 2
 * 2/8/22
 *
 * File manager opens a directory of files and grabs the 60 datasets contained.
 * It then runs those through 5-6 algorithms depending on if the user wants to run insertion sort
 */

#include "FileManager.h"
#include <iostream>
#include <dirent.h>
#include <unistd.h>
#include "Algorithms.h"
using namespace std;

//opens the directory and grabs all the dataset files
void FileManager::getFiles(char* folder, bool runInsert) {
    char* p = new char[256];
    getcwd(p, 256);
    string path = p;
    path += "/";
    path += folder;
    delete[] p;
    DIR* dr;
    dirent* en;
    dr = opendir(path.c_str());
    if (dr) {
        while ((en = readdir(dr)) != nullptr) {
            string file = en->d_name;
            if (file.find(".txt") != string::npos) {
                files.push_back(file);
            }
        }
        closedir(dr);
        readFiles(runInsert);
    } else {
        cout << "Failed to find input file directory" << endl;
        exit(1);
    }
}

//grab datasets from the files
void FileManager::readFiles(bool runInsert) {
    ifstream input;
    //go through all files found in the above directory
    for (string& file : files) {
        string type;
        bool isInt;
        int size;
        //tells if the data is int or string
        if (file[3] == '-') {
            isInt = true;
            int index = file.find('-', 4);

            //tells the dataset format (sorted, noduplicates, etc.)
            type = file.substr(4, index - 4);

            //tells the size
            size = stoi(file.substr(index + 1, file.find('.') - (index + 1)));

            //create object to store all info
            DataSet<int> curr(type, size, isInt);
            iData.push_back(curr);
        } else {
            //repeat for string data (same logic as above)
            isInt = false;
            int index = file.find('-', 7);
            type = file.substr(7, index - 7);
            size = stoi(file.substr(index + 1, file.find('.') - (index + 1)));
            DataSet<string> curr(type, size, isInt);
            sData.push_back(curr);
        }
        //actually open the file and start grabbing data
        input.open("input/" + file);
        if (input.is_open()) {
            if (isInt) {
                //grab lines and convert to integer dataset
                while (!input.eof()) {
                    string temp;
                    getline(input, temp);
                    if (temp.length() > 0) {
                        iData.at(iData.size() - 1).addData(stoi(temp));
                    }
                }
            } else {
                //don't need to convert this data
                while (!input.eof()) {
                    string temp;
                    getline(input, temp);
                    if (temp.length() > 0) {
                        sData.at(sData.size() - 1).addData(temp);
                    }
                }
            }
            input.close();
        } else {
            cout << "Failed to open input/" + file << endl;
        }
    }

    //run the output
    createOutput(runInsert);
}

//creates the csv file
void FileManager::createOutput(bool runInsert) {
    ofstream output;
    output.open("sorting.csv");
    output << "var_type,size,format,insertion_time,quick_time,merge_time,shell_time,intro_time,tim_time" << endl;
    Algorithms<int> intSort;

    //Goes through each dataset and runs the algorithms with it. The checker will exit if sorting fails.
    for (DataSet<int>& ds : iData) {
        output << ds;
        DataSet<int> temp = ds;

        //logic for insertion to run or skip
        if(runInsert)
            output << intSort.insertionSort(temp.getData()).count() << ",";
        else
            output << "N/A,";
        output << intSort.quickSort_caller(ds.getData()).count() << ",";
        output << intSort.mergeSortCall(ds.getData()).count() << ",";
        output << intSort.shellSort_caller(ds.getData()).count() << ",";
        output << intSort.introSort(ds.getData()).count() << ",";
        output << intSort.timSort(ds.getData()).count() << endl;
    }

    //same for the strings
    Algorithms<string> stringSort;
    for (DataSet<string>& ds : sData) {
        output << ds;
        DataSet<string> temp = ds;

        //logic for insertion to run or skip
        if(runInsert)
            output << stringSort.insertionSort(temp.getData()).count() << ",";
        else
            output << "N/A,";
        output << stringSort.quickSort_caller(ds.getData()).count() << ",";
        output << stringSort.mergeSortCall(ds.getData()).count() << ",";
        output << stringSort.shellSort_caller(ds.getData()).count() << ",";
        output << stringSort.introSort(ds.getData()).count() << ",";
        output << stringSort.timSort(ds.getData()).count() << endl;
    }
    output.close();
}
