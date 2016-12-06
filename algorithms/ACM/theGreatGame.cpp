#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;
const int maximum=32000;

int findOptimum(bool minimize, map<int, int> &maximizedRes, map<int, int> &minimizedRes, vector<vector <int> > &adjacencyList, int target, int start){

	if (start==target){
		maximizedRes[start]=0;
		minimizedRes[start]=0;
		return 0;
	}

	int result;

	//if you're at a minimizing step, you would want the next maximization step to give as small solution as possible.
	//so we just find which of these possible next maximization solutions is minimum, take it and add 1.
	if (minimize) {
		int minDist=maximum;
		int subRes;
		for (size_t i=0; i<adjacencyList.at(start).size(); i++){ //go through all connected nodes...
			if (maximizedRes.count(adjacencyList.at(start).at(i))){ //if there is an entry on maximizedRes here...
				subRes=maximizedRes[adjacencyList.at(start).at(i)]+1;
			}
			else subRes=findOptimum(!minimize, maximizedRes, minimizedRes, adjacencyList, target, adjacencyList.at(start).at(i))+1;
			
			minDist=min(minDist, subRes);
		}
		minimizedRes[start]=minDist;
		result=minDist;
	}

	else {
		int maxDist=0;
		int subRes;
		for (size_t i=0; i<adjacencyList.at(start).size(); i++){
			if (minimizedRes.count(adjacencyList.at(start).at(i))){
			subRes=minimizedRes[adjacencyList.at(start).at(i)]+1;
			}
			else subRes=findOptimum(!minimize, maximizedRes, minimizedRes, adjacencyList, target, adjacencyList.at(start).at(i))+1;
			
			maxDist=max(maxDist, subRes);
		}
		maximizedRes[start]=maxDist;
		result=maxDist;
	}

return result;
}

int main() {

	ios_base::sync_with_stdio(false);
	int numTest, numPos, numTrans, redStart, blackStart; //remember 1-indexed redStart blackStart
	cin >> numTest;

	for (int i=0; i<numTest; i++){
	
		vector< vector<int> > adjacencyList;
		cin >> numPos >> numTrans;
		cin >> redStart >> blackStart;
		redStart=redStart-1; blackStart=blackStart-1;
		int transStart, transEnd;
		adjacencyList.resize(numPos);

		for (int i=0; i<numTrans; i++){

			cin >> transStart >> transEnd;
			transStart--; transEnd--;
			adjacencyList.at(transStart).push_back(transEnd);

		}

		map<int, int> minimizedRes;
		map<int, int> maximizedRes;
		
		int start=0;
		int target=numPos-1;
		findOptimum(true, maximizedRes, minimizedRes, adjacencyList, target, start);

		if (!minimizedRes.count(redStart)){
			findOptimum(true, maximizedRes, minimizedRes, adjacencyList, target, redStart);
		}

		if (!minimizedRes.count(blackStart)){
			findOptimum(true, maximizedRes, minimizedRes, adjacencyList, target, blackStart);
		}

		if (minimizedRes[redStart]==minimizedRes[blackStart]){ //if same and even no. of steps, player 0 wins.
			cout << !((minimizedRes[redStart])%2) << endl;
		}

		else cout << !(minimizedRes[redStart]<minimizedRes[blackStart]) << endl;

	}

return 0;
}
