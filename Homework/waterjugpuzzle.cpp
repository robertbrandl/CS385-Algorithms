/*******************************************************************************
 * Name    : waterjugpuzzle.cpp
 * Author  : Robert Brandl
 * Version : 1.0
 * Date    : October 7, 2021
 * Description :  uses BFS to determine solution to given waterjug problem
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <queue>
#include <string>
using namespace std;
struct State {// Struct to represent state of water in the jugs.
	int a, b, c;
	string directions;
	State(int _a, int _b, int _c, string _directions) : a{_a}, b{_b}, c{_c}, directions{_directions}{ }
	string to_string() {// String representation of state in tuple form.
		ostringstream oss;
		oss << "(" << a << ", " << b << ", " << c << ")";
		return oss.str();
	}
};
string waterjugSolution(int capA, int capB, int capC, int goalA, int goalB, int goalC){
	queue<State> jugStates;//initializes queue
	int tempA = 0, tempB = 0;
	int tempC = capC;//starts with all water in C
	int poured = 0;//keeps track of poured value
	int len = capA+1;//size of new array
	bool **arr = new bool*[len]; //allocate 2D array onto heap --> clean up later!
	for (int i = 0; i < len; i++){//create array to check for repeats, sets all values initially to false
		arr[i] = new bool [capB+1];
		for (int j = 0; j < capB + 1; j++){
			arr[i][j] = false;
		}
	}
	arr[tempA][tempB] = true; //for initial State
	State temp(0,0,capC, ("Initial state. (0, 0, " + to_string(capC) + ")\n"));//creates the first State for queue
	State final(-1,-1,-1, "end");//check for no solution, or returns the final solution
	string a1[6] = {"C","B","C","A","B","A"};//allows for automation of jug pouring (what is being poured from)
	string a2[6] = {"A","A","B","B","C","C"};//allows for automation of jug pouring (what is being poured to)
	jugStates.push(temp);//places first State on queue
	while(!jugStates.empty()){//while queue has elements
		temp = jugStates.front();//State to work with
		jugStates.pop();//removes temp from queue
		if (temp.a == goalA && temp.b == goalB && temp.c == goalC){//checks if goal State found
			final.a = 1, final.b = 1, final.c = 1, final.directions = temp.directions;//sets final values
			break;//exits loop!
		}
		for (int i = 0; i < 6; i++){//loops through the possible pourings of water from jugs
			tempA = temp.a, tempB = temp.b, tempC = temp.c;//sets up temp values
			int* cur1 = 0;//creates pointers to work with
			int* cur2 = 0;
			int* current1 = 0;
			int* current2 = 0;
			int* cap1 = 0;
			if (a1[i].compare("A") == 0){//checks the current value and adjusts the pointers from above to the addresses of the values to be worked with
				current2 = &(temp.a);
				cur2 = &tempA;
			}
			if (a1[i].compare("B") == 0){
				current2 = &(temp.b);
				cur2 = &tempB;
			}
			if (a1[i].compare("C") == 0){
				current2 = &(temp.c);
				cur2 = &tempC;
			}
			if (a2[i].compare("A") == 0){
				current1 = &(temp.a);
				cap1 = &capA;
				cur1 = &tempA;
			}
			if (a2[i].compare("B") == 0){
				current1 = &(temp.b);
				cap1 = &capB;
				cur1 = &tempB;
			}
			if (a2[i].compare("C") == 0){
				current1 = &(temp.c);
				cap1 = &capC;
				cur1 = &tempC;
			}
			if (*current1 + *current2 > *cap1){//checks if values exceed cap
				*cur1 = *cap1;//uses dereferences so actual values of temp and temp variables are changes
				poured = *cap1 - *current1;
				*cur2 = *current2 - poured;
			}
			else{//otherwise, fill until cur2 is empty
				*cur1 = *current1 + *current2;
				*cur2 = 0;
				poured = *current2;
			}
			if(!arr[tempA][tempB]){//checks if the current combination has been seen, only continues if false!!!
				string concat;//new string to be added
				State curre(0,0,0,temp.directions);//creates a current State to be added to queue
				if (a1[i].compare("A") != 0 && a2[i].compare("A") != 0){//sets up the values for curre
						curre.a = temp.a, curre.b = tempB, curre.c = tempC;
				}
				if (a1[i].compare("B") != 0 && a2[i].compare("B") != 0){
					curre.a = tempA, curre.b = temp.b, curre.c = tempC;
				}
				if (a1[i].compare("C") != 0 && a2[i].compare("C") != 0){
					curre.a = tempA, curre.b = tempB, curre.c = temp.c;
				}
				if (poured == 1){//adjusts for gramatical changes, uses the toString of the curre State
					concat = ("Pour 1 gallon from " + a1[i] + " to " + a2[i] + ". " + curre.to_string() + "\n");
				}
				else{
					concat = ("Pour " + to_string(poured) + " gallons from " + a1[i] + " to " + a2[i] + ". "  + curre.to_string() + "\n");
				}
				curre.directions += concat;//updates curre's directions
				jugStates.push(curre);//pushs new State onto heap
				arr[tempA][tempB] = true;//sets combination in main array
			}
		}
	}
	string returned;//creates a final solution string
	if (final.directions.compare("end") == 0){//if the directions in final are unchanged, no solution was found
		returned = "No solution.";
	}
	else{//otherwise, solution found
		returned = final.directions;

	}
	for (int i = 0; i < len; i++){//deletes every array in the 2D array
		delete [] arr[i];
	}
	delete [] arr;//deletes 2D array itself
	return returned;//returns solution
}
int main(int argc, char* argv[]){
	istringstream iss;
	if (argc != 7){//checks for invalid number of input arguments
		cout << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
		return 1;
	}
	int ar[6];
	string jugs[6] = {"A","B","C","A","B","C"};
	for (int i = 1; i < 7; i++){//checks for invalid input for each of the 6 arguments
		iss.str(argv[i]);
		if (!(iss >> ar[i-1])){
			if (i == 1 || i == 2 || i == 3){
				cout <<"Error: Invalid capacity \'" << argv[i] <<"\' for jug " + jugs[i-1] + "." << endl;
			}
			else{
				cout <<"Error: Invalid goal \'" << argv[i] <<"\' for jug " + jugs[i-1] + "." << endl;
			}
			return 1;
		}
		if ((ar[i-1] < 0) || (ar[i-1] == 0 && (i == 1 || i == 2 || i ==3))){
			if (i == 1 || i == 2 || i == 3){
				cout <<"Error: Invalid capacity \'" << argv[i] <<"\' for jug " + jugs[i-1] + "." << endl;
			}
			else{
				cout <<"Error: Invalid goal \'" << argv[i] <<"\' for jug " + jugs[i-1] + "." << endl;
			}
			return 1;
		}
		iss.clear();
	}
	if (ar[3] > ar[0]){//checking for goal vs jug capacities to ensure goal does not exceed capacity
		cout << "Error: Goal cannot exceed capacity of jug A." << endl;
		return 1;
	}
	if (ar[4] > ar[1]){
		cout << "Error: Goal cannot exceed capacity of jug B." << endl;
		return 1;
	}
	if (ar[5] > ar[2]){
		cout << "Error: Goal cannot exceed capacity of jug C." << endl;
		return 1;
	}
	if (ar[3] + ar[4] + ar[5] != ar[2]){ //check if goal capacity equals capacity of jug c
		cout << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
		return 1;
	}
	cout << waterjugSolution(ar[0],ar[1],ar[2],ar[3],ar[4],ar[5]) << endl;
	return 0;
}


