// Load dependencies
const random = new(require('chance'));
const fs = require('fs');
// Array with dataset sizes
let sizes = [5000, 10000, 50000, 100000, 500000, 1000000];
// Loop twice for ints and strings
for (let i = 0; i < 2; i++) {
    // 0 == ints and 1 == strings
    if (i === 0) {
        console.log("Generating integer data sets...");
    } else {
        console.log("Generating string data sets...");
    }
    // Loop through each value in the sizes array
    sizes.forEach(size => {
        console.log(size, "size data sets");
        console.log("No duplicates data set");
        // Create file name for no duplicates
        let file = "input/";
        if (i == 0) {
            file += "int";
        } else {
            file += "string";
        }
        file += "-noDuplicates-"
        file += size.toString();
        file += ".txt";
        // Generate no duplicates 
        createOutput(noDuplicates(size, i, 0), file);
        console.log("Sorted data set");
        // Create file name for sorted
        file = file.replace("noDuplicates", "sorted");
        // Generate sorted 
        createOutput(sorted(size, i, 0), file);
        console.log("60% sorted data set");
        // Create file name for 60% sorted
        file = file.replace("sorted", "60sorted");
        // Generate 60% sorted
        createOutput(sorted60(size, i, 0), file);
        console.log("20% duplicates data set");
        // Create file name for 20% duplicates
        file = file.replace("60sorted", "20duplicates");
        // Generate 20% duplicates
        createOutput(duplicates(size, i, 0.2), file);
        console.log("40% duplicates data set");
        // Create file name for 40% duplicates
        file = file.replace("20duplicates", "40duplicates");
        // Generate 40% duplicates
        createOutput(duplicates(size, i, 0.4), file);
        console.log();
    });
}
// Done generating datasets
console.log("Done!");

// Return a dataset starting at start of size size and the given data type
function noDuplicates(size, type, start) {
    // If type == 0, make an integer data set
    if (type === 0) {
        // If start == 0, create an array of all values from 0 to size - 1 and randomize it
        if (start === 0) {
            return mixArr([...Array(size).keys()]);
        } else {
            // Create an array of all values from 0 to size - 1
            let temp = [...Array(size).keys()];
            // Add start to all values
            temp.forEach((val, index) => {
                temp[index] = val + start;
            });
            // Randomize the array
            return mixArr(temp);
        }
    } else {
        // Return an array of random strings
        return random.unique(random.word, size);
    }
}

// Return a sorted array of the given size and data type
function sorted(size, type) {
    // If type == 0, create an array of all values from 0 to size - 1
    if (type === 0) {
        return [...Array(size).keys()];
    } else {
        // Call noDuplicates for strings and sort it
        return noDuplicates(size, type, 0).sort();
    }
}

// Return an array that is 60% sorted of the given size and data type
function sorted60(size, type) {
    // Create a sorted array of size (size * 0.6)
    let arr1 = sorted(parseInt(size * 0.6), type);
    // Create a no duplicates array of size (size * 0.4) that starts at (size * 0.6)
    let arr2 = noDuplicates(parseInt(size * 0.4), type, parseInt(size * 0.6));
    // Concatenate the two arrays together
    let arr = arr1.concat(arr2);
    return arr;
}

// Return an array of size duplicates from array arr
function getDuplicates(arr, size) {
    let newArr = [];
    // Loop size times
    for (let i = 0; i < size; i++) {
        // Add the value from a random index of arr to the new array
        index = parseInt(Math.random() * arr.length);
        newArr.push(arr[index]);
    }
    return newArr;
}

// Create a dataset with the given % duplicates
function duplicates(size, type, percent) {
    // Create a no duplicates dataset of size (size * (1 - percent))
    let arr1 = noDuplicates(parseInt(size * (1 - percent)), type, 0);
    // Create an array of duplicates from arr1 of size (size * percent)
    let arr2 = getDuplicates(arr1, parseInt(size * percent));
    // Concatenate the two arrays together
    let arr = arr1.concat(arr2);
    return arr;
} 

// Randomize the values of an array
function mixArr(array) {
    // Initialize curr to the length of the array
    let curr = array.length;
    var index;
    // Continue looping until curr == 0
    while (curr != 0) {
        // Set the index to a random value between 0 and curr
        index = parseInt(Math.random() * curr);
        // Decrement curr
        curr--;
        // Swap the values at curr and index
        [array[curr], array[index]] = [array[index], array[curr]];
    }
    return array;
}

// Create an output file for a given dataset
function createOutput(arr, file) {
    // Initialize text as an empty string
    let text = "";
    // For each value in the dataset, add the value and a new line
    arr.forEach(value => {
        text += value;
        text += "\n";
    })
    // Convert text into an output file
    fs.writeFile(file, text, (err) => {
        if (err) throw err;
    });
}