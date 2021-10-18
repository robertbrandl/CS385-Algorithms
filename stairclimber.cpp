/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Robert Brandl
 * Date        : 9/29/2021
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // Returns a vector of vectors of ints representing the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
	vector <vector<int> > paths, temp;//creates a final set of paths (paths), and a temp variable for storing paths recursively
	vector<int> emptyvector;//empty vector for the base case
	if (num_stairs <= 0){//checks for negative or no stairs, adds empty vector and ends recursive stepping
		paths.push_back(emptyvector);
	}
	else{//assuming more than 0 stairs, recursively runs through steps
		for (int i = 1; i < 4; i++){//loops three times, since max of 3 steps at once
			if (num_stairs >= i){//if the num_stairs is at least i
				temp = get_ways(num_stairs - i);//stores the recursive call of stairs - i
				for (int k = 0; k < (int)temp.size(); k++){//iterates through the size of the new temp vector
					temp[k].push_back(i);//pushes back the value, i, to the k-th element of vector temp
					paths.push_back(temp[k]);//adds the value of vector temp at k to the final path array

				}
			}
		}
	}
	return paths;
}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
	int width = ways.size();
	int count = 0;
	while (width != 0){
		width /= 10;
		count++;
	}
	for (int i = 0; i < (int)ways.size(); i++){
		cout << setw(count) << i+1 << ". [";
		int col = 0;
		for (int k = (int)ways[i].size(); k >= 0; k--){
			if (k == 0){
				cout << ways[i][k];
			}
			else if (k != (int)ways[i].size()){
				cout << ways[i][k] << ", ";
			}
			col++;
		}
		cout  << "]" << endl;
	}
}

int main(int argc, char * const argv[]) {
	istringstream iss;
	if (argc < 2 || argc > 2){//checks for proper number of args
		cerr << "Usage: " << argv[0] << " <number of stairs>" << endl;
		return 1;
	}
	int m; //checks for proper input, store number of stairs
	iss.str(argv[1]);
	if (!((iss >> m) )){
		cout << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	}
	if (m <= 0){
		cout << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	}
	vector<vector<int>> list = get_ways(m);
	if (list[0].size() == 1){//when only one possible solution
		cout << list.size() << " way to climb " << list[0].size() << " stair." << endl;
	}
	else{//more than one possible solution
		cout << list.size() << " ways to climb " << list[0].size() << " stairs." << endl;
	}
	display_ways(list);
	return 0;
}
