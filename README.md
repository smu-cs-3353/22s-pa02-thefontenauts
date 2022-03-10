# Spring 2022 CS 3353 PA02 - Sorting Algorithms
## The Fontenauts - Wes Anderson and Ryan Schaefer

## The Problem
 

## Building and Running the Program
Step 1: Navigate to the Working Directory

In your command line, use cd statements to navigate to the folder generated by opening the zip file containing this program.

Step 2: Create a Build Folder

Enter ```mkdir build``` into the command line to create a new folder called *build* which will be used for building and eventually running the program. Enter the folder with ```cd build```.

Step 3: Configure the Build

Enter ```cmake ..``` into the command line to configure the build folder. This will generate all of the files needed to build and run this program.

Step 4: Build the Program

Enter ```cmake -–build .``` into the command line to build the program. This will create an executable file to run this program.

Step 5: Run the Program

Enter ```./PA02 input/``` to run the program. During our testing insertion sort took 5-10 hours to sort the 1 million string datasets. If you would like to skip running insertion sort please enter ```./PA02 input/ -i``` to run the program.

## Analysis

### Generating Data

For data generation we used javascript. Add more stuff here.

### Randomized vs Presorted vs Semisorted

For all sorting algorithms the presorted data was the best case scenario. However the magnitude difference was only noticable for insertion and shell sort. For semisorted data the difference in magnitude was also only noticeable for insertion and shell sort. The difference was less noticeable for shell sort than with the fully sorted dataset.

Insert graphs here

### String vs Ints

As seen in the graphs below for all sorting algorithms the time to sort a string dataset was significantly longer than the time to sort the corresponding integer dataset.

Insert graphs here

### Large Datasets

For large datasets quick sort and shell sort function very well at under 1 second for 1 million ints and under 10 seconds for 1 million strings. Merge, intro, and tim sort were all in the same range and functioned slightly worse than quick and shell sorts. Insertion sort was by far the worst, taking over 5 hours on one testing machine and over 10 on another testing machine when sorting 1 million strings.

Instert graphs here

### Duplicates

All of the sorts handle duplicates rather well. While there is a little variance in the timings between the 0%, 20%, and 40% duplicate datasets, the magnitudes of the times were on the same scale. The variance is  most likely due to the data being ordered in a way that is slightly better or worse for the algorithms.

Insert graphs here

### Upper Bounds

Put R regressions here. 

...Using the coefficients we can see that quick sort is the best... (for section below)

### Best Algorithm

From the data we collected the best sorting algorithm is quick sort. It consistently operates faster than the other algorithms. 

```It also had the smallest coefficient for its upper bound.``` 

CHECK IF THIS IS TRUE
