#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;

const long long MAX=5000000000;

typedef struct resultNode{ //an object representing a result
	int a;
	int b;
	int emptyspace;
} resultNode;

bool sortByResult(const resultNode &node1, const resultNode &node2){ //these functions aren't used.
	return node1.emptyspace < node2.emptyspace;
}

bool sortbyB(const resultNode &node1, const resultNode &node2){
	return node1.b > node2.b;
}

int main()
{

	int numberOfTestCases;
	cin >> numberOfTestCases;
	int l, m, n; //length of wall, length of shorter shelf, length of longer shelf.
	
	resultNode optimum;

	for (int i = 0; i < numberOfTestCases; i++){

		cin >> l >> m >> n;

		optimum.a = MAX; //stores a, how many short shelves you use
		optimum.b = MAX; //stores b, number of how many long shelves used
		optimum.emptyspace = MAX;

		int aUpLim;
		int bUpLim;

		if (n <= sqrt((double)(l+0.01))){
			aUpLim = n; //put a as outer loop and go through all b until l-am-bn<0, then continue.

			for (int a = 0; a <aUpLim; a++){
					
				int b = (int)((double)(l - a*m+0.0001) / n);
				int result = l - a*m - b*n;
					
				if (result < 0 || b<0)
					continue;

				if (result < optimum.emptyspace){  //store best result.
					optimum.emptyspace = result;
					optimum.b = b;
					optimum.a = a;
					continue;
				}
				if (result == optimum.emptyspace){

					if (b > optimum.b){
						optimum.b = b;
						optimum.a = a;
					}
				}
			}
		}

		else {
			
			bUpLim = (int) l/n;  //put b as outer loop and go through all a until l-am-bn<0

			for (int b = 0; b <= bUpLim; b++){

				int a = (int)((double)(l - b*n) / m);
				int result = l - a*m - b*n;

					if (result < 0 || a<0)
						continue;

					else if (result < optimum.emptyspace){  //store best result.
						optimum.emptyspace = result;
						optimum.b = b;
						optimum.a = a;
						continue;
			
					}
					else if (result == optimum.emptyspace){
						
						if (b > optimum.b){
							optimum.b = b;
							optimum.a = a;
						}
					}
				}
		}

		cout << optimum.a << " " << optimum.b << " " << optimum.emptyspace << endl;

	}

	return 0;
}
