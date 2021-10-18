/*******************************************************************************
 * Name    : unique.cpp
 * Author  : Robert Brandl
 * Version : 1.0
 * Date    : September 22, 2021
 * Description :  determines if a string has all unique lowercase letters
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <cctype>
#include <sstream>

using namespace std;

bool is_all_lowercase(const string &s){
	// Returns true if all characters in string are lowercase letters in the English alphabet; false otherwise.
	for (const auto &c: s){//iterates through the string's characters
		if (c < 'a' || c > 'z'){//checks if all lowercase
			return false;
		}
	}
	return true;
}

bool all_unique_letters(const string &s){
	// Returns true if all letters in string are unique, that is no duplicates are found; false otherwise.
	unsigned int bits = 0;//uses unsigned int for bits
	unsigned int setter;//uses setter to hold current letter
	for (const auto &c: s){//iterates through string
		setter = 1 << (c - 'a');//bitshifts the char based on 'a', the first lowercase letter
		if (bits & setter){//if both true, it is a repeat
			return false;
		}
		bits = bits | setter;//resets the bits back, adding in the new letter

	}
	return true;
}

int main(int argc, char* const argv[]) {
	// Reads and parses command line arguments, calls other functions to produce correct output.
	istringstream iss;
	if (argc < 2 || argc > 2){//checks for proper number of args
		cerr << "Usage: " << argv[0] << " <string>" << endl;
		return 1;
	}
	string str;

	iss.str(argv[1]);
	if (!(iss >> str) || !(is_all_lowercase(str))) {//check for appropriate input type, strings with lowercase letters
	    cerr << "Error: String must contain only lowercase letters." << endl;
	    return 1;
	}
	iss.clear();
	if (str.length() > 26 || !all_unique_letters(str)) {//checks for duplicate letters
	    cout << "Duplicate letters found." << endl;
	}
	else {
	    cout << "All letters are unique." << endl;
	}

	return 0;
}
