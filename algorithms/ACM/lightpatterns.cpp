#include <vector>
#include <iostream>
#include <algorithm>
#include <limits.h>

using namespace std;
const int maximum=INT_MAX;

void findCost1(int index, bool flipped, int cost, vector<int> &bitArray, vector<int> &optimalCosts){

	if (index < 0){
		return;
	}

	else {

		cost+=flipped^bitArray.at(index);

		if (cost < optimalCosts.at(index)){ //fill in cost if smallest found so far. only recurse here
		
			optimalCosts.at(index) = cost;  

			if (flipped^bitArray.at(index) == 0){    //If added cost is zero...
			
				if (index>0){
					findCost1(index-1, flipped, cost, bitArray, optimalCosts);	
				}
			}

			else  { //proceed recursively on flipped or non-flipped part.

				if (index>0){

					if (flipped^bitArray.at(index-1)==1){
						findCost1(index-1, !flipped, cost, bitArray, optimalCosts);
					}
					else findCost1(index-1, flipped, cost, bitArray, optimalCosts);
				}
			}

		}

	}

	return;
}

void findCost2(int index, bool flipped, int k, int cost, vector<int> &numWrong, vector<int> &optimalCosts){

	if (index < 0){
		return;
	}

	else {

		int cost1, cost2; //the two possible costs you can incur depending on your choice
		int costOfNext1, costOfNext2;
		int totCost1, totCost2;

		if (flipped==false){
			cost1=numWrong.at(index);
			cost2=1+k-numWrong.at(index);
			if (index>0){
				costOfNext1=min(numWrong.at(index-1),1+k-numWrong.at(index-1)); //worth flipping or not?? costOfNext1 is no 													flip
				costOfNext2=min(k-numWrong.at(index-1), 1+numWrong.at(index-1));
				totCost1=cost1+costOfNext1;
				totCost2=cost2+costOfNext2;
				if (totCost1<totCost2){
					cost+=cost1;
					optimalCosts.at(index)=cost;
					findCost2(index-1, flipped, k, cost, numWrong, optimalCosts);
				}
				else {
					cost+=cost2;
					optimalCosts.at(index)=cost;
					findCost2(index-1, !flipped, k, cost, numWrong, optimalCosts);
				}
			}
			else { 
				cost+=min(cost1,cost2);
				optimalCosts.at(index)=cost;
			}
		}
	
		else {

			cost1=k-numWrong.at(index);
			cost2=1+numWrong.at(index);

			if (index>0){
				costOfNext1=min(k-numWrong.at(index-1),1+numWrong.at(index-1)); //worth flipping or not?? costOfNext1 is no 													flip
				costOfNext2=min(numWrong.at(index-1), 1+k-numWrong.at(index-1));
				totCost1=cost1+costOfNext1;
				totCost2=cost2+costOfNext2;
				if (totCost1<totCost2){
					cost+=cost1;
					optimalCosts.at(index)=cost;
					findCost2(index-1, flipped, k, cost, numWrong, optimalCosts);
				}
				else {
					cost+=cost2;
					optimalCosts.at(index)=cost;
					findCost2(index-1, !flipped, k, cost, numWrong, optimalCosts);
				}
			}
			else {  cost+=min(cost1,cost2);
				optimalCosts.at(index)=cost;
			}
		}	
	}

	return;
}

int main() {

	ios_base::sync_with_stdio(false);
	int numTests, numBulbs, k, x, bit;
	cin >> numTests;

	for (int i=0; i<numTests; i++){

		cin >> numBulbs >> k >> x;
		
		if (k==1){

			vector<int> bitArray(numBulbs);
			vector<int> optimalCosts(numBulbs);

			for (int j=0; j<numBulbs; j++){
				cin >> bit;
				bitArray.at(j)=bit;
				optimalCosts.at(j)=maximum;
			}

			findCost1(numBulbs-1, false, 0, bitArray, optimalCosts);
			cout << optimalCosts.at(0) << endl;		
		}

		else {

			vector<int> bitArray(numBulbs);
			vector<int> optimalCosts(numBulbs/k);

			for (int j=0; j<numBulbs; j++){
				cin >> bit;
				bitArray.at(j)=bit;
				if ((j%k)==0){
					optimalCosts.at(j/k)=maximum;
				}
			}

			vector<int> xInBinary(k); //get the pattern in binary notation
			for (int i = 0; i < k; ++i) {
			    xInBinary[k-i-1] = x & (1 << i) ? 1 : 0;
			}

			vector<int> numWrong;
			for (int j=0; j<numBulbs; j+=k){
				int sum=0;
				int count=0;
				for (int p=j; p<j+k; p++){
					sum+=xInBinary[count]^bitArray[p];
					count++;
				}
				numWrong.push_back(sum);
			}
			findCost2(numWrong.size()-1, false, k, 0, numWrong, optimalCosts);
			cout << optimalCosts.at(0) << endl;
		}
	}

return 0;

}
