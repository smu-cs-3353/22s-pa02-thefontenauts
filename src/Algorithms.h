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
    std::chrono::duration<double> quickSort(vector<T>);
    std::chrono::duration<double> mergeSort(vector<T>);
    std::chrono::duration<double> shellSort(vector<T>);
    std::chrono::duration<double> introSort(vector<T>);
    std::chrono::duration<double> timSort(vector<T>);

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
std::chrono::duration<double> Algorithms<T>::quickSort(vector<T> data) {
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();

    end = std::chrono::high_resolution_clock::now();
    if (isSorted(data)) {
        return end - start;
    } else {
        cout << "Quick sort failed" << endl;
        exit(1);
    }
}

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

#endif //PA02_ALGORITHMS_H
