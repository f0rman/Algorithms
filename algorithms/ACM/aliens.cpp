#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

using namespace std;

bool comparator(const pair<int, int> &firstPair, const pair<int, int> &secondPair){ 

	if (firstPair.first < secondPair.first)				
		return true;						
	
	if (secondPair.first<firstPair.first)
		return false;
	
	return (secondPair.second < firstPair.second);

}


int main()
{
	ios_base::sync_with_stdio(false);
	int numTestCases, numAliens, numHumans; //indices starting at 1. 
	pair<int, int> interval;
	int left, right;
	cin >> numTestCases;

	for (int i = 0; i < numTestCases; i++){

		cin >> numAliens >> numHumans;
		vector<pair < int, int > > intervalVec;

		for (int j = 0; j<numAliens; j++){ //read intervals. Ignore zero,zero pairs.
			cin >> left >> right;
			if (left == 0 && right == 0){ continue; }
			interval = make_pair(left, right);
			intervalVec.push_back(interval);
		}

		//sort pairs. (lexicographical ordering)
		sort(intervalVec.begin(), intervalVec.end());
		
		int rightmost = 0;
		bool flag=false;
		for (size_t i = 0; i<intervalVec.size(); i++){  //check superHuman
			if (intervalVec.at(i).first>rightmost + 1){ 
				flag = true;
				break;
			}
			else {
				rightmost = max(rightmost, intervalVec.at(i).second);
			}
		}

		if (intervalVec.empty()){ flag = true; };  //case when no aliens have wounded any human.
		if (rightmost < numHumans) { flag = true; };

		if (flag == true){ cout << 0 << endl; continue; }

		//if there is just one alien, and no superhuman...
		if (numAliens == 1){
			cout << 1 << endl; 
			continue;
		}

		else { //look at how many overlapping intervals you have. 

			//sort correct way.
			sort(intervalVec.begin(), intervalVec.end(), comparator);
			map<pair<int, int>, bool> identicals;

			int numSuperior = 0;
			int maxRight = 0;
			vector<bool> bragAliens(numAliens);
			for (size_t i = 0; i < intervalVec.size(); i++){

				if (intervalVec.at(i).second>maxRight){ //this will always happen for the first alien, so no problem with second if.
					numSuperior++; maxRight = intervalVec.at(i).second;
					bragAliens.at(i)=true;
					continue;
				}

				if (intervalVec.at(i).second == maxRight && intervalVec.at(i).first == intervalVec.at(i - 1).first && 					    bragAliens.at(i-1)==true){
					identicals[intervalVec.at(i)] = true;
					bragAliens.at(i-1)=false; bragAliens.at(i)=false;
				    }
				else bragAliens.at(i)=false;
			}

			numSuperior = numSuperior - identicals.size();
			cout << numSuperior << endl;
		}

	}

	return 0;
}
