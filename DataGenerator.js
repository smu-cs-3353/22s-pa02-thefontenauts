const random = new(require('chance'));
const fs = require('fs');
let sizes = [5000, 10000, 50000, 100000, 500000, 1000000];
for (let i = 0; i < 2; i++) {
    if (i == 0) {
        console.log("Generating integer data sets...");
    } else {
        console.log("Generating string data sets...");
    }
    sizes.forEach(size => {
        console.log(size, "size data sets");
        console.log("No duplicates data set");
        let file = "input/";
        if (i == 0) {
            file += "int";
        } else {
            file += "string";
        }
        file += "-noDuplicates-"
        file += size.toString();
        file += ".txt";
        createOutput(noDuplicates(size, i, 0), file);
        console.log("Sorted data set");
        file = file.replace("noDuplicates", "sorted");
        createOutput(sorted(size, i, 0), file);
        console.log("60% sorted data set");
        file = file.replace("sorted", "60sorted");
        createOutput(sorted60(size, i, 0), file);
        console.log("20% duplicates data set");
        file = file.replace("60sorted", "20duplicates");
        createOutput(duplicates(size, i, 0.2), file);
        console.log("40% duplicates data set");
        file = file.replace("20duplicates", "40duplicates");
        createOutput(duplicates(size, i, 0.4), file);
        console.log();
    });
}

console.log("Done!");

function noDuplicates(size, type, start) {
    if (type == 0) {
        if (start === 0) {
            return mixArr([...Array(size).keys()]);
        } else {
            let temp = [...Array(size).keys()];
            temp.forEach((val, index) => {
                temp[index] = val + start;
            });
            return mixArr(temp);
        }
    } else {
        return random.unique(random.word, size);
    }
}

function sorted(size, type) {
    if (type == 0) {
        return [...Array(size).keys()];
    } else {
        return noDuplicates(size, type, 0).sort();
    }
}

function sorted60(size, type) {
    let arr1 = sorted(parseInt(size * 0.6), type);
    let arr2 = noDuplicates(parseInt(size * 0.4), type, parseInt(size * 0.6));
    let arr = arr1.concat(arr2);
    return arr;
}

function getDuplicates(arr, size) {
    let newArr = [];
    for (let i = 0; i < size; i++) {
        index = parseInt(Math.random() * arr.length);
        newArr.push(arr[index]);
    }
    return newArr;
}

function duplicates(size, type, percent) {
    let arr1 = noDuplicates(parseInt(size * (1 - percent)), type, 0);
    let arr2 = getDuplicates(arr1, parseInt(size * percent));
    let arr = arr1.concat(arr2);
    return arr;
} 

function mixArr(array) {
    let curr = array.length;
    var index;
    while (curr != 0) {
        index = parseInt(Math.random() * curr);
        curr--;
        [array[curr], array[index]] = [array[index], array[curr]];
    }
    return array;
}

function createOutput(arr, file) {
    let text = "";
    arr.forEach(value => {
        text += value;
        text += "\n";
    })
    fs.writeFile(file, text, (err) => {
        if (err) throw err;
    });
}