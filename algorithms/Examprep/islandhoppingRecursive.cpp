#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

//recursive thing.
long int findOptimum(int pos, int radius, vector<long int> &dArray, vector<long int> &SArray, vector<bool> &called){

	if (pos==0){
		return SArray[0];
	}

	else {
		int numConnected;
		int firstIndex;
		if (pos-radius>=0){
			numConnected=pos-radius;
			firstIndex=pos-radius;
		}
		else {
			numConnected=pos;
			firstIndex=0;
		}
		vector<int> connected(numConnected); //costs at the connected nodes
		for (int j=firstIndex; j<firstIndex+numConnected; j++){
			if (called[j]==false){ //call recursively, if not called yet
				called[j]=true;
				connected.at(j)=findOptimum(j, radius, dArray, SArray);
			}
			connected.at(j)==SArray[j];
		}

		long int maximum=negative; //maximum denotes connected node with maximum troops remaining
		for (int j=0; j<numConnected; j++){
			if (connected.at(j)>maximum){
				maximum=connected.at(j);
			}
		}
		SArray[pos]=maximum-dArray[pos];
	}

return SArray[pos];

}

int main(){

int numTests;
cin >> numTests;

for (int i=0; i<numTests; i++){

	int k, r, e;
	cin >> k >> r >> e;

	vector<long int> dArray(k-1);
	int d;

	for (int j=1; j<k; j++){
		cin >> d;
		dArray.at(j)=d;
	}

	vector<long int> SArray(k)
	SArray[0]=e;

	int firstTarget=k-r;

	//find an optimal path to last target (index k-1)
	vector<bool> called(k, false);
	findOptimum(k-1, r, dArray, SArray, called);

	//check if all targets are filled, if not, call the function again.
	
return 0;
}
