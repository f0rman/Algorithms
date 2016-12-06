#include <iostream>
#include <vector>

using namespace std;

int lpd(int n) {  //function for finding biggest proper divisor of a number
	int spd = 1;  //smallest proper divisor.
	do {
		spd++;
		if (n / spd < spd) return 1; //If the number is prime, this will happen.
	} while (n % spd); //while the modulus of n divided by spd is not 0, increase spd.
	return n / spd; //you will return the biggest proper divisor with this method
}

int find_shortest(int v1, int v2) {
	if (v1 == v2) return 0;
	else {
		v2 = lpd(v2); //v2 is biggest proper divisor of v2.
		if (v2 > v1) return 1 + find_shortest(v1, v2);
		else return 1 + find_shortest(v2, v1);
	}
}

int div() {
	int n, c, v1, v2; //numbers in graph, number of pairs we want to know distance between. Number 1, number 2.
	cin >> n >> c;
	
	for (int ci = 0; ci < c; ci++) {
		cin >> v1 >> v2;
		if (v2 < v1) {
			int tmp = v2;
			v2 = v1;
			v1 = tmp;
		}
		cout << find_shortest(v1, v2) << endl;
	}

	return 0;
}

int main() {
	ios_base::sync_with_stdio(false);
	int tt;
	cin >> tt;

	for (int ti = 0; ti < tt; ti++) {
		div();
	}

	return 0;
}
