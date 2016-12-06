#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

int main() {

	int n;
	cin >> n;
	vector<int> x; x.push_back(0);
	for (int i = 0; i < n; i++) {
		int bit; cin >> bit;
		x.push_back(bit);
	}

	vector<int> S;
	S.push_back(0);
	for (int i = 1; i <= n; i++) {
		S.push_back(S[i - 1] + x[i]);
	}

	int even_counter = 0;
	int even = 1; int odd = 0;
	for (int j = 1; j <= n; j++) {
		if (S[j] % 2 == 0) {
			// how many values S[i-1] are even ... for i = 1 ... j 
			even_counter = even_counter + even;
			even++;
		}
		else {
			// how many values S[i-1] are odd ... for i = 1... j
			even_counter = even_counter + odd;
			odd++;
		}
	}
	cout << even_counter << endl;
	return 0;
}
