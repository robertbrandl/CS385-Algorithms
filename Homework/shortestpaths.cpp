/*******************************************************************************
 * Name          : shortestpaths.cpp
 * Author        : Robert Brandl
 * Pledge        : I pledge my honor that I have abided by the Stevens Honor System.
 * Date          : 11/24/2021
 * Description   : Implements Floyd's algorithm for finding the shortest path
 ******************************************************************************/
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;
double inf = std::numeric_limits<double>::infinity();//global variable to use for infinity value
int len(long val){//function used to calculate the width for each column
	int count = 1;
	while (val > 9){//sets the width by dividing by 10 each time
		val /= 10;
		count++;
	}
	return count;
}
void print_table(vector<vector<double>> matrix, const int num_vertices, const bool use_letters = false) {//modified version of professor's code
	long max_val = 0;
	for (int i = 0; i < num_vertices; i++) {
		for (int j = 0; j < num_vertices; j++) {
			long cell = matrix[i][j];
			if (cell < inf && cell > max_val) {
				max_val = matrix[i][j];
			}
		}
	}
	int max_cell_width = use_letters ? len(max_val) :
			len(max(static_cast<long>(num_vertices), max_val));//calls the len function on the greater value to find the proper width
	cout << ' ';
	for (int j = 0; j < num_vertices; j++) {
		cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
	}
	cout << endl;
	for (int i = 0; i < num_vertices; i++) {
		cout << static_cast<char>(i + 'A');
		for (int j = 0; j < num_vertices; j++) {
			cout << " " << setw(max_cell_width);
			if (matrix[i][j] == inf) {
				cout << "-";
			} else if (use_letters) {
				cout << static_cast<char>(matrix[i][j] + 'A');
			} else {
				cout << (long)matrix[i][j];//converts the value from double to long to remove unnecessary scientific notation
			}
		}
		cout << endl;
	}
	cout << endl;
}
void getshortestpath(vector<vector<double>> &dist, vector<vector<double>> &path){//implementation of Floyd's algorithm based on textbook
	size_t vert = dist.size();//gets the size of the distance matrix
	for (size_t k= 0; k < vert; k++){
		for (size_t i = 0; i < vert; i++){
			for(size_t j = 0; j < vert; j++){
				if (min(dist[i][j],dist[i][k] + dist[k][j]) != dist[i][j]){//as long as the current value is not the min distance, continue
					dist[i][j] = dist[i][k] + dist[k][j];//sets the new distance value for i,j
					path[i][j] = k;//updates the matrix of paths
				}
			}
		}
	}

}
void pathprint(vector<vector<double>> path, int i, int j){//prints out an individual path recursively
	if(path[i][j] == inf){//if the path is infinite
		cout << " -> " << (char)(j + 'A');//adds in the new letter for the path
		return;
	}
	else{//otherwise, recursively call this function on subsets
		pathprint(path, i, path[i][j]);//first half of path
		pathprint(path, path[i][j], j);//second half of path
	}
}
void print_paths(vector<vector<double>> dist, vector<vector<double>> path, int vert){//general function to generate path values with distances
	for (int i = 0; i < vert; i++){
		for (int j = 0; j < vert; j++){
			if (dist[i][j] == inf){//if distance matrix value is infinite, print out the distance as infinity, with no valid path
				cout << (char)(i + 'A') << " -> " << (char)(j + 'A') << ", distance: infinity, path: none" << endl;
			}
			else if (i == j){//if i == j, then the distance for the path is 0 since the letters match
				cout << (char)(i + 'A') << " -> " << (char)(j + 'A') << ", distance: 0, path: " << (char)(i + 'A') << endl;
			}
			else if (path[i][j] == inf){// if path matrix value is infinite
				cout << (char)(i + 'A') << " -> " << (char)(j + 'A') << ", distance: " << (long)(dist[i][j]) <<", path: " << (char)(i + 'A') << " -> " << (char)(j + 'A') << endl;
			}
			else{//all other cases where a path exists
				cout << (char)(i + 'A') << " -> " << (char)(j + 'A') << ", distance: " << (long)(dist[i][j]) <<", path: " << (char)(i + 'A');
				pathprint(path, i, j);//calls function to get rest of path
				cout << endl;
			}
		}
	}
}
int main(int argc, char *argv[]){
	if (argc != 2){//checks for proper number of imput arguments
		cerr << "Usage: " << argv[0] << " <filename>" << endl;
		return 1;
	}
	// Create an ifstream object.
	ifstream input_file(argv[1]);//taken from the given c++ file on file input
	// If it does not exist, print an error message.
	if (!input_file) {//checks if the file exists within the same folder
		cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
		return 1;
	}
	string line;
	getline(input_file, line);//gets the value for the first line of the input file
	istringstream iss;
	iss.str(line);
	int vertices;//holds the number of vertices
	if (!(iss >> vertices) || vertices < 1 || vertices > 26){
		cerr << "Error: Invalid number of vertices '" << line << "' on line 1.";
		return 1;
	}
	vector<vector<double>> distance, paths;//creates two matrices, one for distance and one for paths, using a vector of vectors of doubles
	for (int i = vertices; i > 0; i--){//loop sets the initial values for the matrices to either 0 or infinity as necessary
		vector<double> disttemp;
		vector<double> pathtemp;
		for (int j = vertices; j > 0; j--){
			if (j == i){// if j==i, then the distance must be 0, like A == A
				disttemp.push_back(0);
			}
			else{//otherwise, set the initial distance to infinity
				disttemp.push_back(inf);
			}
			pathtemp.push_back(inf);//sets the path values to infinity
		}
		distance.push_back(disttemp);//puts the values from the temp vectors into the main matrices
		paths.push_back(pathtemp);
	}
	string text;
	int lines = 2;//goes through all the lines
	while(getline(input_file, text)){//goes line by line to perform error checking, and if the values are valid, adds them to the distance matrix
		istringstream i (text);
		string vertex1;
		i >> vertex1;
		if (vertex1.length() > 1){
			cerr << "Error: Starting vertex '" << vertex1 << "' on line " << lines << " is not among valid values A-" << char('A' + vertices - 1) << "." << endl;
			return 1;
		}
		char ch = vertex1.at(0);
		if (ch < 'A' || ch >= 'A' + vertices){
			cerr << "Error: Starting vertex '" << vertex1 << "' on line " << lines << " is not among valid values A-" << char('A' + vertices - 1) << "." << endl;
			return 1;
		}
		string vertex2;
		i >> vertex2;
		if (vertex2.length() > 1){
			cerr << "Error: Ending vertex '" << vertex2 << "' on line " << lines << " is not among valid values A-" << char('A' + vertices - 1) << "." << endl;
			return 1;
		}
		char ch2 = vertex2.at(0);
		if (ch2 < 'A' || ch2 >= 'A' + vertices){
			cerr << "Error: Ending vertex '" << vertex2 << "' on line " << lines << " is not among valid values A-" << char('A' + vertices - 1) << "." << endl;
			return 1;
		}
		string weight;
		if (!(i >> weight)){
			cerr << "Error: Invalid edge data '" << vertex1 << " " << vertex2 << "' on line " << lines << "." << endl;
			return 1;
		}
		for (int i = (int)weight.length() - 1; i > 0; i--){
			if (weight.at(i) < '0' || weight.at(i) > '9'){
				cerr << "Error: Invalid edge weight '" << weight << "' on line " << lines << "." << endl;
				return 1;
			}
		}
		double weightd = stod(weight);
		if (weightd <= 0){
			cerr << "Error: Invalid edge weight '" << weightd << "' on line " << lines << "." << endl;
			return 1;
		}
		distance[ch-'A'][ch2-'A'] = weightd;
		lines++;
	}
	input_file.close();//closes the input file since it is no longer needed
	cout << "Distance matrix:" << endl;
	print_table(distance, vertices);//calls the print table function to print out the initial distance matrix
	getshortestpath(distance, paths);//applies Floyd's algorithm to the distance and paths matrices
	cout << "Path lengths:" << endl;
	print_table(distance, vertices);//prints out the distance matrix with the appropriate path length values
	cout << "Intermediate vertices:" << endl;
	print_table(paths, vertices,true);//prints out the intermediate vertices used to get through the shortest path
	print_paths(distance, paths, vertices);//prints out all possible paths through the graph
	return 0;
}
