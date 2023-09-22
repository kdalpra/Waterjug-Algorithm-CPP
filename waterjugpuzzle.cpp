
#include <iostream>
#include <cctype>
#include <sstream>
#include <iomanip>
#include <limits>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;


struct State { // struct to keep track of gallons in each jug and a pointer to how it got there
    int a, b, c;
    string directions;
    State *parent;

    State(int _a, int _b, int _c, string _directions) :
        a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} { }
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss  << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};
void printStepsDirs(vector<vector<int>> nums){
// due to an error with the directions variable in the struct, I decided to find the directions string after finding the solution and not during

	for(string::size_type i = 0; i <nums.size()-1; i++){

		if(i == 0){
			int aPrev = nums[i][0];
			int bPrev = nums[i][1];
			int cPrev = nums[i][2];
			cout<< "Initial state. " << "(" << aPrev << ", " << bPrev << ", " << cPrev << ")" <<endl;
			}
			int aPrev = nums[i][0];
			int bPrev = nums[i][1];
			int cPrev = nums[i][2];
			int aAf = nums[i+1][0];
			int bAf = nums[i+1][1];
			int cAf = nums[i+1][2];
			if(aAf > aPrev){ // TO A
				if(bAf < bPrev){ //from b
					int amnt = bPrev - bAf;
					string gal = " gallons ";
					if(amnt ==1){
						gal = " gallon ";
					}
					cout<< "Pour " <<  amnt << gal << "from B to A. "<< "(" << aAf << ", " << bAf << ", " << cAf << ")"<<endl;
				}
				else{ //from c
					int amnt = cPrev - cAf;
						string gal = " gallons ";
						if(amnt ==1){
							gal = " gallon ";
						}
						cout<< "Pour " <<  amnt << gal << "from C to A. "<< "(" << aAf << ", " << bAf << ", " << cAf << ")"<<endl;
					}
				}
			if(bAf > bPrev){ // TO B
				if(aAf < aPrev){ //from a
					int amnt = aPrev - aAf;
					string gal = " gallons ";
					if(amnt ==1){
						gal = " gallon ";
					}
					cout<< "Pour " <<  amnt << gal << "from A to B. "<< "(" << aAf << ", " << bAf << ", " << cAf << ")"<<endl;
				}
				else{ //from c
					int amnt = cPrev - cAf;
						string gal = " gallons ";
						if(amnt ==1){
							gal = " gallon ";
						}
						cout<< "Pour " <<  amnt << gal << "from C to B. "<< "(" << aAf << ", " << bAf << ", " << cAf << ")"<<endl;
					}
			}
			if(cAf > cPrev){ //TO C
				if(aAf < aPrev){ //from a
				int amnt = aPrev - aAf;
				string gal = " gallons ";
				if(amnt ==1){
					gal = " gallon ";
				}
				cout<< "Pour " <<  amnt << gal << "from A to C. "<< "(" << aAf << ", " << bAf << ", " << cAf << ")"<<endl;
			}
				else{ //from b
					int amnt = bPrev - bAf;
						string gal = " gallons ";
						if(amnt ==1){
							gal = " gallon ";
						}
						cout<< "Pour " <<  amnt << gal << "from B to C. "<< "(" << aAf << ", " << bAf << ", " << cAf << ")"<<endl;
					}
			}
		}
}

// runs through the solution state and its pointers, and creates a vector of a b and c for each state. The vector of vectors is then sent to get the directions string

void printSteps(State x){
	vector<vector<int>> dirs;
	vector<int> temp;
	temp.push_back(x.a);
	temp.push_back(x.b);
	temp.push_back(x.c);
	dirs.insert(dirs.begin(),temp);
	while(x.parent != nullptr){
		vector<int> temp2;
		temp2.push_back(x.parent->a);
		temp2.push_back(x.parent->b);
		temp2.push_back(x.parent->c);
		dirs.insert(dirs.begin(),temp2);
		x.parent = x.parent->parent;
	}
	printStepsDirs(dirs);

}
//In the specific order, each instruction is performed to the current state (front of queue)
// Each new state is added to the queue if it hasnt been seen yet
// Calls the function to print the solution if the state contains the goal capacities
// The direction string is also calculated here, but they kept getting corrupted in the print steps function, so they are not actually used

int doIns(queue<State> x, int** tracker, int aCap, int bCap, int cCap){

	for(int i = 0; i < 6; i++){
//C TO A
		if(i == 0 && x.front().c != 0 && x.front().a != aCap){ // #1: C is not 0, A can hold more
			int dif = aCap - x.front().a;
			if(x.front().c >= dif){ //dif = how much a can hold    if A cant hold all of C
				string gals = "gallons ";
				if(dif == 1){
					gals = "gallon ";
				}
				if(tracker[aCap][x.front().b] != 1){
					struct State temp = State(aCap,x.front().b,x.front().c - dif,"Pour " + to_string(dif) + " " + gals + "from C to A. ");
					temp.parent = &x.front();
					if(tracker[aCap][x.front().b] == 2){
						printSteps(temp);
						return 0;
					}
					tracker[aCap][x.front().b] = 1;
					x.push(temp);
				}
			}
				else{ //if destination can hold all of origin
					string gals = "gallons ";
					if(x.front().c == 1){
						gals = "gallon ";
					}
					if(tracker[x.front().a + x.front().c][x.front().b] != 1){
						struct State temp = State(x.front().a + x.front().c,x.front().b,0,"Pour " + to_string(x.front().c) + " " + gals + "from C to A. ");
						temp.parent = &x.front();
						if(tracker[x.front().a + x.front().c][x.front().b] == 2){
							printSteps(temp);
							return 0;
						}
						tracker[x.front().a + x.front().c][x.front().b] = 1;
						x.push(temp);
					}
				}
			}
//B TO A
		if(i == 1 && x.front().b != 0 && x.front().a != aCap){
			int dif = aCap - x.front().a;
			if(x.front().b >= dif){ //dif = how much dest can hold    if A cant hold all of B
				string gals = "gallons ";
				if(dif == 1){
					gals = "gallon ";
				}
				if(tracker[aCap][x.front().b - dif] != 1){
					struct State temp = State(aCap,x.front().b - dif,x.front().c,"Pour " + to_string(dif) + " " + gals + "from B to A. ");
					temp.parent = &x.front();
					if(tracker[aCap][x.front().b - dif] == 2){
						printSteps(temp);
						return 0;
					}
					tracker[aCap][x.front().b - dif] = 1;
					x.push(temp);
				}
			}
				else{ //if destination can hold all of origin
					string tempS;
					string gals = "gallons ";
					if(x.front().b == 1){  //origin
						gals = "gallon ";
					}
					if(tracker[x.front().a + x.front().b][0] != 1){
						struct State temp = State(x.front().a + x.front().b,0,x.front().c,"Pour " + to_string(x.front().b) + " " + gals + "from B to A. ");
						temp.parent = &x.front();
						if(tracker[x.front().a + x.front().b][0] == 2){
							printSteps(temp);
							return 0;
						}
						tracker[x.front().a + x.front().b][0] = 1;
						x.push(temp);
					}
				}
		}
		//C TO B
		if(i == 2 && x.front().c != 0 && x.front().b != bCap){
					int dif = bCap - x.front().b;
					if(x.front().c >= dif){ //dif = how much a can hold    if A cant hold all of C
						string gals = "gallons ";
						if(dif == 1){
							gals = "gallon ";
						}
						if(tracker[x.front().a][bCap] != 1){
							struct State temp = State(x.front().a,bCap,x.front().c - dif,"Pour " + to_string(dif) + " " + gals + "from C to B. ");
							temp.parent = &x.front();
							if(tracker[x.front().a][bCap] == 2){
								printSteps(temp);
								return 0;
							}
							tracker[x.front().a][bCap] = 1;
							x.push(temp);
						}
					}
						else{ //if destination can hold all of origin
							string gals = "gallons ";
							if(x.front().c == 1){
								gals = "gallon ";
							}
							if(tracker[x.front().a ][x.front().b + x.front().c] != 1){
								struct State temp = State(x.front().a ,x.front().b + x.front().c,0,"Pour " + to_string(x.front().c) + " " + gals + "from C to B. ");
								temp.parent = &x.front();
								if(tracker[x.front().a][x.front().b + x.front().c] == 2){
									printSteps(temp);
									return 0;
								}
								tracker[x.front().a ][x.front().b + x.front().c] = 1;
								x.push(temp);
							}

						}
					}
		//A TO B
		if(i == 3 && x.front().a != 0 && x.front().b != bCap){
					int dif = bCap - x.front().b;
					if(x.front().a >= dif){ //dif = how much dest can hold    if A cant hold all of B
						string gals = "gallons ";
						if(dif == 1){
							gals = "gallon ";
						}
						if(tracker[x.front().a - dif][bCap] != 1){
							struct State temp = State(x.front().a - dif,bCap,x.front().c,"Pour " + to_string(dif) + " " + gals + "from A to B. ");
							temp.parent = &x.front();
							if(tracker[x.front().a - dif][bCap] == 2){
								printSteps(temp);
								return 0;
							}
							tracker[x.front().a - dif][bCap] = 1;
							x.push(temp);
						}
					}
						else{ //if destination can hold all of origin
							string gals = "gallons ";
							if(x.front().a == 1){  //origin
								gals = "gallon ";
							}

							if(tracker[0][x.front().b + x.front().a] != 1){
								struct State temp = State(0,x.front().a + x.front().b,x.front().c,"Pour " + to_string(x.front().a) + " " + gals + "from A to B. ");
								temp.parent = &x.front();
								if(tracker[0][x.front().a + x.front().b] == 2){
									printSteps(temp);
									return 0;
								}

								tracker[0][x.front().a + x.front().b] = 1;
								x.push(temp);
							}
						}
				}
// B TO C
		if(i == 4 && x.front().b != 0 && x.front().c != cCap){ // #1: C is not 0, A can hold more
					int dif = cCap - x.front().c;
					if(x.front().b >= dif){ //dif = how much a can hold    if C cant hold all of B
						string gals = "gallons ";
						if(dif == 1){
							gals = "gallon ";
						}
						if(tracker[x.front().a][x.front().b - dif] != 1){
							struct State temp = State(x.front().a,x.front().b - dif,cCap,"Pour " + to_string(dif) + " " + gals + "from B to C. ");
							temp.parent = &x.front();
							if(tracker[x.front().a][x.front().b - dif] == 2){
								printSteps(temp);
								return 0;
							}
							tracker[x.front().a][x.front().b - dif] = 1;
							x.push(temp);
						}
					}
					else{ //if destination can hold all of origin
						string gals = "gallons ";
						if(x.front().c == 1){
							gals = "gallon ";
						}
						if(tracker[x.front().a][0] != 1){
							struct State temp = State(x.front().a,0,x.front().c + x.front().b,"Pour " + to_string(x.front().b) + " " + gals + "from B to C. ");
							temp.parent = &x.front();
							if(tracker[x.front().a][0] == 2){
								printSteps(temp);
								return 0;
							}
							tracker[x.front().a][0] = 1;
							x.push(temp);
						}
					}
		}
		//from A to C
		if(i == 5 && x.front().a != 0 && x.front().c != cCap){ // #1: C is not 0, A can hold more
			int dif = cCap - x.front().c;
			if(x.front().a >= dif){ //dif = how much a can hold    if C cant hold all of B
				string gals = "gallons ";
				if(dif == 1){
					gals = "gallon ";
				}
				if(tracker[x.front().a - dif][x.front().b] != 1){
					struct State temp = State(x.front().a - dif,x.front().b,cCap,"Pour " + to_string(dif) + " " + gals + "from A to C. ");
					temp.parent = &x.front();
					if(tracker[x.front().a - dif][x.front().b] == 2){
						printSteps(temp);
						return 0;
					}
					tracker[x.front().a - dif][x.front().b] = 1;
					x.push(temp);
				}
			}

				else{ //if destination can hold all of origin
					string gals = "gallons ";
					if(x.front().c == 1){
						gals = "gallon ";
					}
					if(tracker[0][x.front().b] != 1){
						struct State temp = State(0,x.front().b,x.front().c + x.front().a,"Pour " + to_string(x.front().a) + " " + gals + "from A to C. ");
						temp.parent = &x.front();
						if(tracker[0][x.front().b] == 2){

							printSteps(temp);
							return 0;
						}
						tracker[0][x.front().b] = 1;
						x.push(temp);
					}
								}
							}

	}
	//after for loop
	//run doIns again, but pop the queue

	// Does instructions for the next state in the queue
	x.pop();
	if(!x.empty()){
		return doIns(x, tracker, aCap, bCap, cCap);
	}
	// if the queue is empty and the solution has not been found, then no solution is printed
	else{
		cout<< "No solution." << endl;
		return 0;
	}
}


void klayton (int a, int b, int c, int ag, int bg, int cg){
	//2d array of ints from 0 to a capacity for the rows, and 0 to b capacity for the cols
	int rows = a+1;
	int cols = b+1;
	int **tracker = new int*[rows]; // 2d array to keep track of states seen+not seen
	for(int i=0; i < rows; i++){
		tracker[i] = new int[cols];
	}
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){ //fills 2d array with 0 / not seen
			tracker[i][j] = 0;
		}
	}
	tracker[ag][bg] = 2; //this is the goal state
	if(c == cg && bg == 0 && ag == 0){ // if initial state is goal state
		cout<< "Initial state. " << "(" << ag << ", " << bg << ", " << cg << ")";
	}
	else{
		//start doing instructions for the initial state, 0 0 c
		queue<State> sQ;
		struct State initial = State(0,0,c,"Initial state. ");
		sQ.push(initial);
		doIns(sQ, tracker, a, b, c);
	}
	for(int i = 0; i < rows; i++) { //cleans up 2d array for valgrind
		delete[] tracker[i];
	}
	delete[] tracker;
}


int main(int argc, char * const argv[]){

	int a,b,c,ag,bg,cg;
	const char *vars[7] = { " ","A", "B", "C", "A", "B", "C" }; //array for displaying accurate errors
	istringstream inp;
	if(argc != 7){ //command line needs 7 arguments. 6 nums + the program
		cerr << "Usage: " <<argv[0] << " <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" <<endl;
		return 1;
	}
	for(int i = 1; i < 7; i++){
		inp.clear();
		inp.str(argv[i]);
		if(!(inp >> a) || a < 0){ //if the input is not a number, or negative
			if(i < 4){ //capacities
				cerr<< "Error: Invalid capacity \'" << argv[i] <<  "\' for jug " << vars[i] << "." <<endl;
				return 1;
			}
			else{ //goals
				cerr<< "Error: Invalid goal \'" << argv[i] <<  "\' for jug " << vars[i] << "." <<endl;
				return 1;
			}
		}
		else if(i == 3 && a == 0){ // jug c cant be zero because that decides the amount of water in the puzzle
			cerr << "Error: Invalid capacity '0' for jug C." <<endl;
			return 1;
		}
	}

		inp.clear(); // puts arguments into corresponding variables
		inp.str(argv[1]);
		inp >> a; //cap a
		inp.clear();
		inp.str(argv[2]);
		inp >> b;
		inp.clear();
		inp.str(argv[3]);
		inp >> c;
		inp.clear();
		inp.str(argv[4]);
		inp >> ag; //goal a
		inp.clear();
		inp.str(argv[5]);
		inp >> bg;
		inp.clear();
		inp.str(argv[6]);
		inp >> cg;

		//if goals are bigger than capacities
		if(ag > a){
			cerr << "Error: Goal cannot exceed capacity of jug A." <<endl;
			return 1;
		}
		if(bg > b){
			cerr << "Error: Goal cannot exceed capacity of jug B." <<endl;
			return 1;
		}
		if(cg > c){
			cerr << "Error: Goal cannot exceed capacity of jug C." <<endl;
			return 1;
		}
		//if the goals do not add up to the amount of water in the puzzle (jug c initial)
		if(c != ag + bg + cg){
			cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
			return 1;
		}
	//I made a new function at this point to do some testing and to make sure that the variables got correctly assigned, and ended up keeping it
	klayton(a,b,c,ag,bg,cg);
	return 0;
}


