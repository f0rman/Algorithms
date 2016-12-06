#include <iostream>
#include <vector>

using namespace std;

//Count even subarrays in array of n numbers (same as Even Pairs)
int count_even(int numbers[], int n) {
  vector<int> s;
  int sum = 0;
  for (int i = 0; i < n; i++) {
    sum += numbers[i];
    s.push_back(sum);
  }

  int even_counter = 0;
  int even = 1;
  int odd = 0;
  for (int i = 0; i < n; i++) {
    if (s[i] % 2 == 0) {
      even_counter += even;
      even++;
    } else {
      even_counter += odd;
      odd++;
    }
  }

  return even_counter;
}

void testcase() {
  int n; cin >> n;

  //Input matrix
  int M[n][n];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int x; cin >> x;
      M[i][j] = x;
    }
  }

  //Matrix of sums
  int S[n][n + 1];
  for (int i = 0; i < n; i++) {
    for (int j = 1; j < n + 1; j++) {
      //Build sum for i-th element using i-1st element
      S[i][j] = S[i][j-1] + M[i][j-1];
    }
  }

  int even_sums[n];
  int total_even = 0;
  //For each two indices j1 and j2 create an array depending on parity of the difference of sums
  for (int j1 = 1; j1 < n + 1; j1++) {
    for (int j2 = j1; j2 < n + 1; j2++) {
      for (int i = 0; i < n; i++) {
	if ((S[i][j2] - S[i][j1] + M[i][j1 - 1]) % 2 == 0) {
	  even_sums[i] = 0;
	} else {
	  even_sums[i] = 1;
	}
      }
      //Compute the number of even pairs in the array for current indices
      total_even += count_even(even_sums, n);
    }
  }
  
  cout << total_even << endl;
}

int main() {
  ios::sync_with_stdio(false);
  int t; cin >> t;
  
  for (int i = 0; i < t; i++) {
    testcase();
  }
  
  return 0;
}
