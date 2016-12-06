#include <vector>
#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
typedef pair<int, int> ii; 
int numberOfTestCases;
int numWizards;
int pos;
int length;
vector<ii> posAndLengthVec;

bool sortByPosition(const ii &posAndLength1, const ii &posAndLength2);
int finishTime(int occupied, int ringPos, int length);

bool sortByPosition(const ii &posAndLength1, const ii &posAndLength2){
	return posAndLength1.second < posAndLength2.second;
}

int finishTime(int occupied, int ringPos, int length) {

	if (ringPos - occupied > length) {
		return ringPos;
	}
	else { return occupied + length; }
}

//We can in every step either improve our solution or not. two variables, minOccupy and maxnum keep changing.
//start by adding first two boats
//And assume this is optimal. then for each boat after, check if there is overlap or not.
//if yes, and that boat would result in better occupy, only update "occupied". if no better occupy, ignore.
//if no overlap, update both maxnum and occupied.

int countMaxNumOfBoats(vector<ii> sortedPosAndLengthVec){

	//If you only have 1 or 2 wizards...
	if (sortedPosAndLengthVec.size()<=2)
		return sortedPosAndLengthVec.size();

	//otherwise immediately add the leftmost boat and its neighbour. These values are our initial optimum solution.
	int maxnum = 2;
	int minOccupy = finishTime(sortedPosAndLengthVec.at(0).second, sortedPosAndLengthVec.at(1).second, sortedPosAndLengthVec.at(1).first); //theoretical min Occupy

	int occupied = sortedPosAndLengthVec.at(0).second; //what is actually occupied in terms of what length we have absolutely chosen.

	//start looking at third boat all the way to the end.

	for (size_t i = 2; i < sortedPosAndLengthVec.size(); i++){

		//if no overlap, increment maxnum, put minOccupy as that boats occupy.
		if (sortedPosAndLengthVec.at(i).second>=minOccupy){
			maxnum++;
			occupied = minOccupy;
			minOccupy = finishTime(occupied, sortedPosAndLengthVec.at(i).second, sortedPosAndLengthVec.at(i).first);
		}

		else{ //this boat overlaps with the previous. Can we improve our solution?

			int myOccupy = finishTime(occupied, sortedPosAndLengthVec.at(i).second, sortedPosAndLengthVec.at(i).first);

			if (myOccupy < minOccupy){
				minOccupy = myOccupy;
			}

		}

	}

	return maxnum;
}


int main()
{
	cin >> numberOfTestCases;

	for (int i = 0; i < numberOfTestCases; ++i){

		posAndLengthVec.clear();
		cin >> numWizards;

		for (int j = 0; j < numWizards; j++){

			cin >> length >> pos;

			ii posAndLength;
			posAndLength.first = length;
			posAndLength.second = pos;

			posAndLengthVec.push_back(posAndLength);

		}

		//quicksort posAndLengthVec on position
		sort(posAndLengthVec.begin(), posAndLengthVec.end(), sortByPosition);
		int max=countMaxNumOfBoats(posAndLengthVec);
		cout << max<<endl;
	}

	return 0;
}
