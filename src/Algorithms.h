#ifndef PA02_ALGORITHMS_H
#define PA02_ALGORITHMS_H

#include <vector>
#include <chrono>
#include <math.h>
using namespace std;

template <typename T>
class Algorithms {
public:
    Algorithms() = default;

    std::chrono::duration<double> insertionSort(vector<T>&);
    std::chrono::duration<double> quickSort(vector<T>);
    std::chrono::duration<double> mergeSortCall(vector<T>);
    std::chrono::duration<double> shellSort(vector<T>);
    std::chrono::duration<double> introSort(vector<T>);
    std::chrono::duration<double> timSort(vector<T>);

    // Merge Sort Functions
    vector<T>& mergeSort(vector<T>&);
    vector<T>& merge(vector<T>&, vector<T>&);

    // Intro Sort Functions
    vector<T>& introSort(vector<T>&, int);

    bool isSorted(vector<T>&);
};

template <typename T>
std::chrono::duration<double> Algorithms<T>::insertionSort(vector<T>& data) {
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

    int depth = 2 * log(data.size());
    introSort(data, depth);

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
vector<T>& Algorithms<T>::mergeSort(vector<T>& data) {
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
vector<T>& Algorithms<T>::merge(vector<T>& first, vector<T>& second) {
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

// Intro Sort Functions
template <typename T>
vector<T>& Algorithms<T>::introSort(vector<T>& data, int depth) {
    if (data.size() < 16) {
        insertionSort(data);
        return data;
    } else if (depth == 0) {
        make_heap(data.begin(), data.end());
        sort_heap(data.begin(), data.end());
        return data;
    } else {
        //int pivot = data.at(0);
        //swapValue(data, 0, data.size() - 1);
        //int partition = quickSort(data);
        vector<T> first(data.begin(), data.begin() + partition);
        first = introSort(first, depth - 1);
        vector<T> last(data.begin() + partition + 1, data.end());
        last = introSort(last, depth - 1);
        first.push_back(data.at(partition));
        first.insert(first.end(), last.begin(), last.end());
        return first;
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
