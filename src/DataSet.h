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

    friend ostream& operator<<(ostream& out, const DataSet<T>&);
};

template <typename T>
DataSet<T>::DataSet(const string& t, int s, bool i) {
    type = t;
    size = s;
    isInt = i;
}

template <typename T>
void DataSet<T>::addData(const T& d) {
    data.push_back(d);
}

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

template <typename T>
ostream& operator<<(ostream& out, const DataSet<T>& rhs) {
    if (rhs.getIsInt()) {
        out << "int,";
    } else {
        out << "string,";
    }
    out << rhs.getSize() << "," << rhs.getType();
    return out;
}

#endif //PA02_DATASET_H
