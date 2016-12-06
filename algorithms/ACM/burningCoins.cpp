// BurningCoins

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<vector<int>> storedResults; //rows correspond to sub-solution number (i.e. "the number of coins you have in this subproblem"), columns 					     to which of these sub-solutions.
vector<int> coins; //keeps the value of each coin

void storeResults(vector<int> coins){

	vector<int> cumsumVec;
	cumsumVec.push_back(0);  //start by building cumsumVec.
	int cumSum = 0;

	for (size_t i = 0; i < coins.size(); i++){
		cumSum = cumSum + coins.at(i);
		cumsumVec.push_back(cumSum);
	}

	storedResults.at(0) = coins;  //first row of storedResults containing subsolutions is just the coins-array

	for (size_t i = 1; i < coins.size(); i++){  //for all other bigger subsolutions...

		for (size_t j = 0; j < coins.size() - i; j++){

			int result = cumsumVec.at(j + i + 1) - cumsumVec.at(j) - min(storedResults.at(i - 1).at(j), storedResults.at(i - 1).at(j + 1));
			storedResults.at(i).push_back(result);

		}

	}

}


int main()
{
	int numberOfTestCases;
	cin >> numberOfTestCases;
	int numberOfCoins;
	int value;

	for (int testCase = 0; testCase < numberOfTestCases; testCase++){

		storedResults.clear();
		coins.clear();

		cin >> numberOfCoins;

		for (int coin = 0; coin < numberOfCoins; coin++){
			cin >> value;
			coins.push_back(value);
		}

		storedResults.resize(numberOfCoins);
		storeResults(coins);

		cout << storedResults.at(numberOfCoins - 1).at(0)<<endl;

	}

	return 0;
}
