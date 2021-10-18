/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Robert Brandl
 * Date        : 9/9/2021
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_; // prevents leaks
    }

    int num_primes() const {
    	return num_primes_; // returns prime numbers up to and including limit
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
    int find_max_prime() const;
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
        	//initializes a bool array with all true values from 2 to n
        	for (int i = 2; i <= limit_; i++){
        		is_prime_[i] = true;
        	}
    sieve(); //initializes the object by calling the sieve function
}

void PrimesSieve::display_primes() const {
    // displays the primes according to the requirements
	const int max_prime_width = num_digits(max_prime_),
	     primes_per_row = 80 / (max_prime_width + 1);
	double numLines = primes_per_row - num_primes_;
	int counter = 0; //tracks the number of primes on each line
	int c = 0; //tracks the number of primes in total for multi-line sets of primes
	if (numLines > 0){//one line only responses
		for (int i = 2; i <= limit_; i++){
			if (is_prime_[i]){
				if (counter == num_primes_){// if reached end of primes, don't add space
					cout << i;
				}
				else if (counter == primes_per_row - 1 || num_primes_ - counter == 1){//checks if the primes are finished.
					cout << i;
				}
				else{//prints with a space
					cout << i << " ";
				}
				counter++;//adds 1 to counter of primes
			}
		}
	}
	else{//for multi-line sets of primes
		for (int i = 2; i <= limit_; i++){
			if (is_prime_[i]){
				if (counter == primes_per_row){//if max on a row, goes to next line and resets line counter for primes
					cout << endl;
					counter = 0;
					cout << setw(max_prime_width) << i << " ";//sets format based on width of max_prime_width
				}
				else if (counter == primes_per_row - 1 || num_primes_ - c == 1){ //checks if end of last line, no extra space
					cout << setw(max_prime_width) << i;
				}
				else{
					cout << setw(max_prime_width) << i;
					if (c != num_primes_){
						cout << " ";
					}
				}
				//increments total and line counters (of primes)
				counter++;
				c++;

			}
		}
	}
}

int PrimesSieve::count_num_primes() const {
	//loops through is_prime_ array and counts all primes
	int counter = 0;
	for (int i = 2; i <= limit_; i++){
		if (is_prime_[i]){
			counter++;
		}
	}
    return counter;
}

void PrimesSieve::sieve() {
    // sieve algorithm based on pseudocode
	for (int i = 2; i <= sqrt((double)limit_); i++){
		if (is_prime_[i]){//if it is prime
			for (int j = i*i; j <= limit_; j += i){
				is_prime_[j] = false;//sets all non-primes to false
			}
		}
	}
	num_primes_ = count_num_primes();//sets the number of primes variable
	max_prime_ = find_max_prime();//sets the max prime value
}

int PrimesSieve::num_digits(int num) {
	// determines how many digits are in an integer
	int numDig = 0;
	while (num > 0){
		numDig++;
		num = num / 10; //repeatedly divides by 10 until num = 0
	}
    return numDig;
}

int PrimesSieve::find_max_prime() const{
	//searches from reverse through the prime array, and sets max value to the first prime detected
	for (int i = limit_; i >= 2; i--){
		if (is_prime_[i]){
			return i;
		}
	}
	return 0;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }
    PrimesSieve p (limit);//create sieve object

    //handles the proper output
    cout << endl << "Number of primes found: " << p.num_primes() << endl;
    cout << "Primes up to " << limit << ":" << endl;
    p.display_primes();
    return 0;
}
