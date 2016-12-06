#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int MAX = 32000;

inline void minimumChange(const vector<int> &coinVals, const vector<int> &retVals){ 

	//Check maximum value in retVals.
	int maximum=*max_element(retVals.begin(), retVals.end());
	vector<int> sums(maximum + 1, MAX);
	sums[0] = 0; //solution of number of coins summing up to 0 is 0.

	//coins are sorted!

	for (int sum = 1; sum <= maximum; sum++){     //Just go the maximum and store only up the maxretValue.
		for (size_t j = 0; j < coinVals.size(); j++){
	 		if (coinVals[j] > sum){ break;}
				if (sums[sum - coinVals[j]] + 1 < sums[sum]){
					sums[sum] = sums[sum - coinVals[j]] + 1;
				}				
		}
	}

	for (size_t k = 0; k < retVals.size(); k++){

		if (sums[retVals[k]] >= MAX){
			cout << "not possible" << endl;
		}

		else cout << sums.at(retVals[k]) << endl;

	}
	return;
}


int main()
{
	ios_base::sync_with_stdio(false);
	int numberOfTestCases;
	int numberOfDiffCoinVals;
	int numberOfSampleRetVals;
	int coinValue;
	int change;
	vector<int> coinVals;
	vector<int> retVals;
	cin >> numberOfTestCases;

	for (int i = 0; i < numberOfTestCases; ++i){
		coinVals.clear();
		retVals.clear();
		cin >> numberOfDiffCoinVals >> numberOfSampleRetVals;

		for (int j = 0; j < numberOfDiffCoinVals; ++j){
			cin >> coinValue;
			coinVals.push_back(coinValue);
		}

		for (int k = 0; k < numberOfSampleRetVals; ++k){
			cin >> change;
			retVals.push_back(change);
		}

		minimumChange(coinVals, retVals);

	}

	return 0;
}
