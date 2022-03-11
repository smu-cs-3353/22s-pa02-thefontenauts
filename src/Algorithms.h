/* Wes Anderson and Ryan Schaefer
 * 22s-CS-3353 PA 2
 * 3/11/22
 *
 * Algorithms.h contains our implementations for all 6 algorithms and a checker function to make sure the algorithms operate properly
 */

#ifndef PA02_ALGORITHMS_H
#define PA02_ALGORITHMS_H

#include <vector>
#include <chrono>
#include <ctime>
#include <math.h>
using namespace std;

template <typename T>
class Algorithms {
public:
    Algorithms() = default;

    //Insertion Sort Function
    std::chrono::duration<double> insertionSort(vector<T>&);

    //Tim Sort Function
    std::chrono::duration<double> timSort(vector<T>);

    // Merge Sort Functions
    std::chrono::duration<double> mergeSortCall(vector<T>);
    vector<T> mergeSort(vector<T>);
    vector<T> merge(vector<T>&, vector<T>&);

    // Intro Sort Functions
    std::chrono::duration<double> introSort(vector<T>);
    vector<T> introSort(vector<T>, int);

    //Quick Sort functions
    std::chrono::duration<double> quickSort_caller(vector<T>);
    void quickSort(vector<T>&, int, int);
    void swap(T*, T*);
    int partition(vector<T>&, int, int);

    //Shell Sort functions
    std::chrono::duration<double> shellSort_caller(vector<T>);
    void shellSort(vector<T>&);

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

//merge sort caller to control time points and calls the checker function
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

//shell sort caller to manage timing points and checker function
template <typename T>
std::chrono::duration<double> Algorithms<T>::shellSort_caller(vector<T> data) {
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();

    shellSort(data);

    end = std::chrono::high_resolution_clock::now();
    if (isSorted(data)) {
        return end - start;
    } else {
        cout << "Shell sort failed" << endl;
        exit(1);
    }
}

template <typename T>
void Algorithms<T>::shellSort(vector<T>& data)
{
    //Shell sort operates on using different intervals to swap elements into a more correct order
    //It reduces the "gap" after every loop and compares on a smaller gap
    // until it is the same as insertion sort with gap = 1

    //When gap = 1 it will only ever swap two elements right next to each other
    // since the larger gaps put them in their general location

    for (int gap = data.size()/2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < data.size(); i += 1)
        {
            T temp = data[i];
            int j;
            //insertion sort with gap logic
            for (j = i; j >= gap && data[j - gap] > temp; j -= gap)
                data[j] = data[j - gap];
            data[j] = temp;
        }
    }
}

template <typename T>
std::chrono::duration<double> Algorithms<T>::introSort(vector<T> data) {
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();

    int depth = 2 * log(data.size());
    data = introSort(data, depth);

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

    vector<vector<vector<T> > > sections(1);
    int i;
    for (i = 0; i < data.size(); i += 32) {
        vector<T> temp(data.begin() + i, data.begin() + min(i + 32, int(data.size())));
        insertionSort(temp);
        sections.at(0).push_back(temp);
    }

    for (i = 0; i < sections.size(); i++) {
        if (sections.at(i).size() == 1) {
            break;
        }
        vector<vector<T> > curr;
        int j;
        for (j = 1; j < sections.at(i).size(); j += 2) {
            vector<T> temp = merge(sections.at(i).at(j - 1), sections.at(i).at(j));
            curr.push_back(temp);
        }
        if (j == sections.at(i).size()) {
            vector<T> temp = sections.at(i).at(j - 1);
            curr.push_back(temp);
        }
        sections.push_back(curr);
    }
    data = sections.at(sections.size() - 1).at(0);

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
vector<T> Algorithms<T>::mergeSort(vector<T> data) {
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

// Intro Sort Functions
template <typename T>
vector<T> Algorithms<T>::introSort(vector<T> data, int depth) {
    if (data.size() < 16) {
        insertionSort(data);
        return data;
    } else if (depth == 0) {
        make_heap(data.begin(), data.end());
        sort_heap(data.begin(), data.end());
        return data;
    } else {
        int part = partition(data, 0, data.size() - 1);
        vector<T> first(data.begin(), data.begin() + part);
        first = introSort(first, depth - 1);
        vector<T> last(data.begin() + part + 1, data.end());
        last = introSort(last, depth - 1);
        first.push_back(data.at(part));
        first.insert(first.end(), last.begin(), last.end());
        return first;
    }
}

//Quick Sort Functions
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


//This is randomized quicksort
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
    //put pivot in correct spot
    swap(&vec[i + 1], &vec[high]);
    return (i + 1);
}

//Checks if the vector is actually sorted. Used to test implementations
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
