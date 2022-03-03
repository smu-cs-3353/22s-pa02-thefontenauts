#ifndef PA02_ALGORITHMS_H
#define PA02_ALGORITHMS_H

#include <vector>
#include <chrono>
#include <ctime>
//#include <random>
using namespace std;

template <typename T>
class Algorithms {
public:
    Algorithms() = default;

    std::chrono::duration<double> insertionSort(vector<T>);
    std::chrono::duration<double> shellSort(vector<T>);
    std::chrono::duration<double> introSort(vector<T>);
    std::chrono::duration<double> timSort(vector<T>);

    // Merge Sort Functions
    std::chrono::duration<double> mergeSortCall(vector<T>);
    vector<T> mergeSort(vector<T>&);
    vector<T> merge(vector<T>&, vector<T>&);

    //Quick Sort functions
    std::chrono::duration<double> quickSort_caller(vector<T>);
    void quickSort(vector<T>&, int, int);
    void swap(T*, T*);
    int partition(vector<T>&, int, int);


    bool isSorted(vector<T>&);
};

template <typename T>
std::chrono::duration<double> Algorithms<T>::insertionSort(vector<T> data) {
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i < data.size(); i++) {
        T key = data.at(i);
        int j = i - 1;
        while (j >= 0 && data.at(j) > key) {
            data.at(j + 1) = data.at(j);
            j -= 1;
        }
        data.at(j + 1) = key;
    }
    end = std::chrono::high_resolution_clock::now();
    if (isSorted(data)) {
        return end - start;
    } else {
        cout << "Insertion sort failed" << endl;
        exit(1);
    }
}


template <typename T>
std::chrono::duration<double> Algorithms<T>::mergeSortCall(vector<T> data) {
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();

    data = mergeSort(data);

    end = std::chrono::high_resolution_clock::now();
    if (isSorted(data)) {
        return end - start;
    } else {
        cout << "Merge sort failed" << endl;
        exit(1);
    }
}

template <typename T>
std::chrono::duration<double> Algorithms<T>::shellSort(vector<T> data) {
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();

    end = std::chrono::high_resolution_clock::now();
    if (isSorted(data)) {
        return end - start;
    } else {
        cout << "Shell sort failed" << endl;
        exit(1);
    }
}

template <typename T>
std::chrono::duration<double> Algorithms<T>::introSort(vector<T> data) {
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();

    end = std::chrono::high_resolution_clock::now();
    if (isSorted(data)) {
        return end - start;
    } else {
        cout << "Intro sort failed" << endl;
        exit(1);
    }
}

template <typename T>
std::chrono::duration<double> Algorithms<T>::timSort(vector<T> data) {
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();

    end = std::chrono::high_resolution_clock::now();
    if (isSorted(data)) {
        return end - start;
    } else {
        cout << "Tim sort failed" << endl;
        exit(1);
    }
}

// Merge Sort Functions
template <typename T>
vector<T> Algorithms<T>::mergeSort(vector<T>& data) {
    if (data.size() > 1) {
        int half = (data.size() / 2);
        vector<T> first(data.begin(), data.begin() + half);
        first = mergeSort(first);
        vector<T> second(data.begin() + half, data.end());
        second = mergeSort(second);
        return merge(first, second);
    } else {
        return data;
    }
}

template <typename T>
vector<T> Algorithms<T>::merge(vector<T>& first, vector<T>& second) {
    int it1 = 0;
    int it2 = 0;
    vector<T> merged;
    while (it1 < first.size() || it2 < second.size()) {
        if (it1 >= first.size()) {
            merged.push_back(second.at(it2));
            it2++;
        } else if (it2 >= second.size()) {
            merged.push_back(first.at(it1));
            it1++;
        } else if (first.at(it1) < second.at(it2)) {
            merged.push_back(first.at(it1));
            it1++;
        } else {
            merged.push_back(second.at(it2));
            it2++;
        }
    }
    return merged;
}

template <typename T>
bool Algorithms<T>::isSorted(vector<T>& data) {
    for (int i = 1; i < data.size(); i++) {
        if (data.at(i - 1) > data.at(i)) {
            return false;
        }
    }
    return true;
}


//Quick Sort Stuffs
template <typename T>
std::chrono::duration<double> Algorithms<T>::quickSort_caller(vector<T> data) {
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();

    quickSort(data,0,data.size()-1);

    end = std::chrono::high_resolution_clock::now();
    if (isSorted(data)) {
        return end - start;
    } else {
        cout << "Quick sort failed" << endl;
        exit(1);
    }
}

template <typename T>
void Algorithms<T>::quickSort(vector<T>& vec, int low, int high)
{

    if (low < high)
    {
        //Partition so that pivot is in the right spot
        int pivot = partition(vec, low, high);

        //Recursive calls
        quickSort(vec, low, pivot - 1);
        quickSort(vec, pivot + 1, high);
    }

}

//swap 2 elements
template <typename T>
void Algorithms<T>::swap(T* a, T* b)
{
    T temp = *a;
    *a = *b;
    *b = temp;
}

template <typename T>
int Algorithms<T>::partition(vector<T>& vec, int low, int high)
{
    //randomize the pivot then swap if not the last element
    srand (time(NULL));
    int pivot_loc = (rand() % (high - low)) + low;
    if(pivot_loc != high)
        swap(&vec[high], &vec[pivot_loc]);

    //make last element the pivot
    T pivot = vec[high];
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (vec[j] < pivot)
        {
            i++; // increment index of smaller element
            swap(&vec[i], &vec[j]);
        }
    }
    swap(&vec[i + 1], &vec[high]);
    return (i + 1);
}

#endif //PA02_ALGORITHMS_H
