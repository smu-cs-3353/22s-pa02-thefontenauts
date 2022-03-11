/* Wes Anderson and Ryan Schaefer
 * 22s-CS-3353 PA 2
 * 3/11/22
 *
 * DataSet objects are what we used to store the information related to the format of each dataset
 * The name of the dataset file gave us all the information that is contained in this file
 */

#ifndef PA02_DATASET_H
#define PA02_DATASET_H

using namespace std;

template <typename T>
class DataSet {
private:
    vector<T> data;
    int size;
    bool isInt;
    string type;
public:
    DataSet(const string&, int, bool);

    void addData(const T&);

    vector<T>& getData();
    int getSize();
    bool getIsInt();
    string& getType();

    //overloaded operator for output file (gives the type of data sorted)
    friend ostream& operator<<(ostream& out, const DataSet& rhs) {
        if (rhs.isInt) {
            out << "int,";
        } else {
            out << "string,";
        }
        out << rhs.size << "," << rhs.type << ",";
        return out;
    }
};

//constructor to initialize values
template <typename T>
DataSet<T>::DataSet(const string& t, int s, bool i) {
    type = t;
    size = s;
    isInt = i;
}

//adding data to the vector
template <typename T>
void DataSet<T>::addData(const T& d) {
    data.push_back(d);
}


//Getters

template <typename T>
vector<T>& DataSet<T>::getData() {
    return data;
}

template <typename T>
int DataSet<T>::getSize() {
    return size;
}

template <typename T>
bool DataSet<T>::getIsInt() {
    return isInt;
}

template <typename T>
string& DataSet<T>::getType() {
    return type;
}

#endif //PA02_DATASET_H
