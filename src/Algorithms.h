#ifndef PA02_ALGORITHMS_H
#define PA02_ALGORITHMS_H

#include <vector>
#include <chrono>
using namespace std;

template <typename T>
class Algorithms {
public:
    Algorithms() = default;

    std::chrono::duration<double> insertionSort(vector<T>);
    std::chrono::duration<double> mergeSort(vector<T>);
    std::chrono::duration<double> shellSort(vector<T>);
    std::chrono::duration<double> introSort(vector<T>);
    std::chrono::duration<double> timSort(vector<T>);



    //Quick Sort functions
    std::chrono::duration<double> quickSort(vector<T>, int, int);
    void swap(T*, T*);
    int partition(vector<T>, int, int);




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

//template <typename T>
//std::chrono::duration<double> Algorithms<T>::quickSort(vector<T> data) {
//    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
//    start = std::chrono::high_resolution_clock::now();
//
//    end = std::chrono::high_resolution_clock::now();
//    if (isSorted(data)) {
//        return end - start;
//    } else {
//        cout << "Quick sort failed" << endl;
//        exit(1);
//    }
//}

template <typename T>
std::chrono::duration<double> Algorithms<T>::mergeSort(vector<T> data) {
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();

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

std::chrono::duration<double> quickSort(vector<T> vec, int low, int high)
{
    std::chrono::time_point<chrono::high_resolution_clock> start, end;
    start = chrono::high_resolution_clock::now();

    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
		at right place */
        int pivot = partition(vec, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(vec, low, pivot - 1);
        quickSort(vec, pivot + 1, high);
    }

    end = chrono::high_resolution_clock::now();
    return end - start;
}

void swap(T* a, T* b)
{
    T temp = *a;
    *a = *b;
    *b = temp;
}

int partition(vector<T> vec, int low, int high)
{
    //Need to randomize the pivot
    T pivot = vec[high]; // pivot
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (vec[j] > pivot)
        {
            i++; // increment index of smaller element
            swap(&vec[i], &vec[j]);
        }
    }
    swap(&vec[i + 1], &vec[high]);
    return (i + 1);
}

#endif //PA02_ALGORITHMS_H
