#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

const long int infinity=LONG_MAX;

int main(){

int numTests;
cin >> numTests;
vector< pair<long int, long int> > outputs(numTests);

for (int i=0; i<numTests; i++){

	int k, r, e;
	cin >> k >> r >> e;

	vector<long int> dArray(k);
	int d;

	dArray.at(0)=0;
	for (int j=1; j<k; j++){
		cin >> d;
		dArray.at(j)=d;
	}

	vector<long int> SArrayDist(k); //this array stores costs, which we want to minimize.
	vector<long int> SArrayNumEdges(k); //this array stores numEdges, which we want to minimize.
	SArrayDist[0]=0;
	SArrayNumEdges[0]=0;

	for (int j=1; j<k; j++){
		SArrayDist[j]=infinity;
		SArrayNumEdges[j]=infinity;
	}
	 
	//find an optimal path to last target (index k-1). we know our vertex in the outer loop has an optimal distance when examining it.
	
	if (k-r<=0){ //jump from the start to the capital
		outputs.at(i).first=0;
		outputs.at(i).second=e;
		continue;
	}

	for (int u=0; u<k-1; u++){
		for (int v=u+1; v<=u+r; v++){
		
			if (v==k){ //you shouldn't go to the capital
				break;
			}
			if (SArrayDist[v]>SArrayDist[u]+dArray[v]){
				SArrayDist[v]=SArrayDist[u]+dArray[v];
				SArrayNumEdges[v]=SArrayNumEdges[u]+1;
			}
			else if (SArrayDist[v]==SArrayDist[u]+dArray[v]){
				if (SArrayNumEdges[v]>SArrayNumEdges[u]+1){
					SArrayNumEdges[v]=SArrayNumEdges[u]+1;
				}
			}
		}
	}

	long int shortestLength=LONG_MAX;
	long int minNumEdges=LONG_MAX;

	int firstTarget=k-r;
	int lastTarget=k-1;

	for (int j=firstTarget; j<=lastTarget; j++){
		
		if (SArrayDist[j]<shortestLength){
			shortestLength=SArrayDist[j];
			minNumEdges=SArrayNumEdges[j];
		}
		else if (SArrayDist[j]==shortestLength){
			if (minNumEdges>SArrayNumEdges[j]){
				minNumEdges=SArrayNumEdges[j];
			}
		}
	}

	if ((e-shortestLength)<=0){
		outputs.at(i).first=LONG_MIN;
		outputs.at(i).second=LONG_MIN;
	}
	
	else {
		outputs.at(i).first=minNumEdges;
		outputs.at(i).second=e-shortestLength;
	}
}

for (int i=0; i<numTests; i++){
	if (outputs.at(i).first!=LONG_MIN){
		cout << outputs.at(i).first << " " << outputs.at(i).second << endl;
	}
	else cout << "safe" << endl;
}
	
return 0;
}
