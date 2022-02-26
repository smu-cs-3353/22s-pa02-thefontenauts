//
// Created by Ryan Schaefer on 2/25/22.
//

#include "FileManager.h"
#include <iostream>
#include <dirent.h>
#include <unistd.h>
using namespace std;

void FileManager::getFiles() {
    char* p = new char[256];
    getcwd(p, 256);
    string path = p;
    path += "/input/";
    delete[] p;
    DIR* dr;
    struct dirent* en;
    dr = opendir(path.c_str());
    if (dr) {
        while ((en = readdir(dr)) != nullptr) {
            string file = en->d_name;
            if (file.find(".txt") != string::npos) {
                files.push_back(file);
            }
        }
        closedir(dr);
        readFiles();
    } else {
        cout << "Failed to find input file directory" << endl;
        exit(1);
    }
}

void FileManager::readFiles() {
    ifstream input;
    for (string& file : files) {
        string type;
        bool isInt;
        int size;
        if (file[3] == '-') {
            isInt = true;
            int index = file.find('-', 4);
            type = file.substr(4, index - 4);
            size = stoi(file.substr(index + 1, file.find('.') - (index + 1)));
            DataSet<int> curr(type, size, isInt);
            iData.push_back(curr);
        } else {
            isInt = false;
            int index = file.find('-', 7);
            type = file.substr(7, index - 7);
            size = stoi(file.substr(index + 1, file.find('.') - (index + 1)));
            DataSet<string> curr(type, size, isInt);
            sData.push_back(curr);
        }
        input.open("input/" + file);
        if (input.is_open()) {
            if (isInt) {
                while (!input.eof()) {
                    string temp;
                    getline(input, temp);
                    if (temp.length() > 0) {
                        iData.at(iData.size() - 1).addData(stoi(temp));
                    }
                }
            } else {
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
    createOutput();
}

void FileManager::createOutput() {
    ofstream output;
    output.open("sorting.csv");
    for (DataSet<int>& ds : iData) {
        output << ds << endl;
    }
    for (DataSet<string>& ds : sData) {
        output << ds << endl;
    }
    output.close();
}
