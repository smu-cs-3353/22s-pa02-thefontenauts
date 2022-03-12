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
    void toHeapify(vector<T>&,int,int);
    void makeMaxHeap(vector<T>&,int);

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
    // Loop from 1 to the dataset size - 1
    for (int i = 1; i < data.size(); i++) {
        // Set the key to the current value and j to the current index - 1
        T key = data.at(i);
        int j = i - 1;
        // Loop until j == 0 or the value at j is less than or equal to the key
        while (j >= 0 && data.at(j) > key) {
            // Set value at j + 1 to the value at j and decrement j
            data.at(j + 1) = data.at(j);
            j -= 1;
        }
        // Set value at j + 1 to key
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

// Intro sort caller
template <typename T>
std::chrono::duration<double> Algorithms<T>::introSort(vector<T> data) {
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();

    // Calculate the depth
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

    // Create a 3d vector to hold sections to be merged
    vector<vector<vector<T> > > sections(1);
    int i;
    // Create sections of size 32 that are sorted with insertion sort
    for (i = 0; i < data.size(); i += 32) {
        vector<T> temp(data.begin() + i, data.begin() + min(i + 32, int(data.size())));
        insertionSort(temp);
        sections.at(0).push_back(temp);
    }
    // Iterative merge sort
    for (i = 0; i < sections.size(); i++) {
        // If there is 1 section, end the loop
        if (sections.at(i).size() == 1) {
            break;
        }
        // Create a 2d vector to store the merged sectiosn
        vector<vector<T> > curr;
        int j;
        // Merge every other value
        for (j = 1; j < sections.at(i).size(); j += 2) {
            vector<T> temp = merge(sections.at(i).at(j - 1), sections.at(i).at(j));
            curr.push_back(temp);
        }
        // If there is one section left, add it to the next section
        if (j == sections.at(i).size()) {
            vector<T> temp = sections.at(i).at(j - 1);
            curr.push_back(temp);
        }
        // Add the new set of sections
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
    // If there is more than 1 element in data, split data
    if (data.size() > 1) {
        // The halfway point is the size / 2
        int half = (data.size() / 2);
        // Create the first half of data
        vector<T> first(data.begin(), data.begin() + half);
        // Call merge sort for the first half
        first = mergeSort(first);
        // Create the second half of data
        vector<T> second(data.begin() + half, data.end());
        // Call merge sort for the second half
        second = mergeSort(second);
        // Merge the two halves
        return merge(first, second);
    } else {
        // Else, return data
        return data;
    }
}

template <typename T>
vector<T> Algorithms<T>::merge(vector<T>& first, vector<T>& second) {
    // Set the iterators for both halves to 0
    int it1 = 0;
    int it2 = 0;
    vector<T> merged;
    // Iterate while either iterator is less than the size of that half
    while (it1 < first.size() || it2 < second.size()) {
        if (it1 >= first.size()) {
            // If first is done, add the next value of second
            merged.push_back(second.at(it2));
            it2++;
        } else if (it2 >= second.size()) {
            // If second is done, add the next value of first
            merged.push_back(first.at(it1));
            it1++;
        } else if (first.at(it1) < second.at(it2)) {
            // If the current value of first is smaller, add it
            merged.push_back(first.at(it1));
            it1++;
        } else {
            // If the current value of second is smaller or equal, add it
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
        // If data is small, do insertion sort
        insertionSort(data);
        return data;
    } else if (depth == 0) {
        //heap sort
        //then keep popping off elements and putting them in the last index
        //basically form the array from back to front


        //create max heap with data vector.
        //since heaps start at element 1 push back the element 0 to the end so it also gets sorted.
        //In this implementation element 0 will be a buffer variable to hold the max value so there does not
        // need to be rearranged after the sort
        data.push_back(data[0]);

        //make max heap
        makeMaxHeap(data, data.size()-1);

        for (int i = data.size()-1; i >= 2; i--)
        {

            //temp is used to grab the buffer and put it in the sorted position
            T temp;
            if(i != data.size()-1)
                temp = data[0];

            //put the curr max into buffer slot
            data[0] = data[1];
            data[1] = data[i];

            //put temp into sorted position
            if(i != data.size()-1)
                data[i] = temp;

            //Build max heap of remaining element.
            toHeapify(data, 1, i - 1);
        }

        //since slot 0 is a buffer swap the
        T temp = data[0];
        data[0] = data[1];
        data[1] = temp;

        //pop the last position that allowed us to use proper heap indices
        data.pop_back();

        return data;
    } else {
        // Quick sort with intro sort
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

template <typename T>
void Algorithms<T>::makeMaxHeap(vector<T>& data, int n)
{
    int i;
    for(i = n/2; i >= 1; i--)
        toHeapify(data, i, n);
}

template <typename T>
void Algorithms<T>::toHeapify(vector<T>& data, int i, int n)
{
    T temp = data[i];
    int j = 2*i;

    while (j <= n)
    {
        if (j < n && data[j+1] > data[j])
            j = j+1;
        // Break if parent value is already greater than child value.
        if (temp > data[j])
            break;
        // Switching value with the parent node if temp < a[j].
        else if (temp <= data[j])
        {
            data[j/2] = data[j];
            j = 2*j;
        }
    }
    data[j/2] = temp;
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
