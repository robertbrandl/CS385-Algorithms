/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Robert Brandl
 * Version     : 1.0
 * Date        : 10/20/2021
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <string>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    long inversions = 0;
    for (int i = 0; i < length; i++){//loops through all elements
    	for (int j = i + 1; j < length; j++){//loops through all elements again for comparison
    		if (array[i] > array[j]){//checks if value at i is greater than j, if so, incremenet inversion counter
    			inversions++;
    		}
    	}
    }
	return inversions;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
	int *scratch = new int[length];//creates an empty array for use
	long result = mergesort(array, scratch, 0, length - 1);//calls merge sort
	delete [] scratch;//cleans up array
	return result;//returns result from merge sort
}

static long mergesort(int array[], int scratch[], int low, int high) {
    long inversions = 0;//counter for number of inversions
    if (low < high){//implementation of merge sort as seen in lecture slides
    	int middle = low + (high - low)/2;
    	inversions += mergesort(array, scratch, low, middle);//recursive call, add result to counter
    	inversions += mergesort(array, scratch, middle + 1, high);//recursive call, add result to counter
    	int i1 = low;
    	int i = low;
    	int i2 = middle + 1;
    	while (i1 <= middle && i2 <= high){
    		if (array[i1] <= array[i2]){
    			scratch[i++] = array[i1++];
    		}
    		else{
    			scratch[i++] = array[i2++];
    	    	inversions += (middle - i1 + 1);//this is when inversions are fixed, so the counter must be updated
    		}
    	}
    	for (int j = i1; j <= middle; j++){
    		scratch[i++] = array[i1++];
    	}
    	for (int j = i2; j <= high; j++){
			scratch[i++] = array[i2++];
    	}
    	for (int i = low; i <= high; i++){//resets the array with the elements of scratch
    		array[i] = scratch[i];
    	}

    }
	return inversions;
}

int main(int argc, char *argv[]) {
	string word;
    if (argc > 2 || argc == 0){//check for proper argument amount
    	cerr << "Usage: "<< argv[0] << " [slow]" << endl;
    	return 1;
    }
    istringstream iss;
    if (argc == 2){//checks that is an argument is given, it must be slow, otherwise return an error message
    		iss.str(argv[1]);
    		if (!(iss >> word) || word.compare("slow")){
    			cerr << "Error: Unrecognized option '" << argv[1] << "'.";
    			return 1;
    		}
    		iss.clear();
     }
    cout << "Enter sequence of integers, each followed by a space: " << flush;//user input
    int value, index = 0;
    vector<int> values;//initial vector
    string str;
    str.reserve(11);
    char c;
    while (true) {//parsing for user input --> only integers
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }
    if (values.size() == 0){//checks if not integers given
    	cerr << "Error: Sequence of integers not received." << endl;
    	return 1;
    }
    //handles function call and output
    long result;
    if (word.compare("slow") == 0){//if slow option
    	result = count_inversions_slow(&values[0], values.size());
    }
    else{//if fast option
    	result = count_inversions_fast(&values[0], values.size());
    }
    cout << "Number of inversions: " << result << endl;//final result
    return 0;
}
