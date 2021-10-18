/*******************************************************************************
 * Name    : sqrt.cpp
 * Author  : Robert Brandl
 * Version : 1.0
 * Date    : September 1, 2021
 * Description : Computes the square root of the command-line argument.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <limits>
#include <iomanip>
using namespace std;

double sqrt(double num, double epsilon){
	if (num < 0){
		return numeric_limits<double>::quiet_NaN();
	}
	if (num == 0 || num == 1){
		return num;
	}
	double last_guess = num;
	double next_guess = (last_guess + num/last_guess) / 2;
	while (abs(last_guess-next_guess) > epsilon){
		last_guess = next_guess;
		next_guess = (last_guess + num/last_guess) / 2;
	}
	return next_guess;
}

int main(int argc, char* argv[]) {
	if (argc > 3 || argc < 2){
		cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
		return 1;
	}
	istringstream iss;
	double n;
	double e = 1e-7;

	iss.str(argv[1]);
	if(!(iss >> n)) {
			cerr << "Error: Value argument must be a double." << endl;
			return 1;
	}

	iss.clear();
	if (argc == 3){
		iss.str(argv[2]);
		if(!(iss >> e) || !(e > 0)) {
			cerr << "Error: Epsilon argument must be a positive double." << endl;
			return 1;
		}
	}

	cout << fixed << setprecision(8) << sqrt(n, e) << endl;

	return 0;
}



