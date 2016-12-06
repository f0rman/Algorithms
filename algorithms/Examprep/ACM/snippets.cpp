#include <vector>
#include <iostream>
#include <math.h>
#include <map>
#include <limits.h>
#include <algorithm>

using namespace std;

const long maximum=LONG_MAX;
int shortestSet;

int main(){

ios_base::sync_with_stdio(false);

int numTests;
cin >> numTests;
vector<int> outputs;

//map and list iterators are bidirectional so they only support ++ and --. Then you use advance to increment the iterator several steps.

for (int i=0; i<numTests; i++){

	int numWords;
	int numOccur;
	cin >> numWords;
	vector<int> numOccurences(numWords); //shows how many times this word occurs.

	for (int j=0; j<numWords; j++){ //fill numOccurences
		cin >> numOccur;
		numOccurences.at(j)=numOccur;
	}

	long int startPos=maximum;
	long int endPos=0;
	int lengthOfArray=0; //keeps track of how long the array containing all words in the document will be.
	vector<pair<long int, int> > docArray;

	for (int w=0; w<numWords; w++){

		for (int j=0; j<numOccurences.at(w); j++){
			long pos;
			cin >> pos;
			if (pos>endPos) endPos=pos;
			if (pos<startPos) startPos=pos;
			docArray.push_back(make_pair(pos, w));
			lengthOfArray++;
		}

	}

	sort(docArray.begin(), docArray.end());

	//we now have all the entire document in order. Time to find smallest subset..
	
	long int sizeOfSet=endPos-startPos;
	vector<int> inSet(numWords); //shows which words and how many are in a set
	int left=0;
	int right=-1;
	int numWordsCovered=0;
	bool finished=false;

	while (finished==false){

		int word;
		while (true){
			if (numWordsCovered!=numWords){  //if not everything is covered...

				if (right<lengthOfArray-1){

					right++; //increment right
					word=docArray.at(right).second;

					if (inSet.at(word)==0){
						numWordsCovered++;
					}
					inSet.at(word)++;
				}
				else break; //we're at the last index but we still don't cover everything. Nothing can be done.
			}

			else{ //if all words covered now, stop

				endPos=docArray.at(right).first;
				startPos=docArray.at(left).first;
				if (endPos-startPos+1<sizeOfSet)
					sizeOfSet=endPos-startPos+1;

				break;
			}
		}

		if (numWordsCovered!=numWords && right==lengthOfArray-1)
			break;

		//remove leftmost word
		word=docArray.at(left).second;

		if (inSet.at(word)==1){
			numWordsCovered--;
		}
		inSet.at(word)--;

		left++;
		if (numWordsCovered!=numWords && right==lengthOfArray-1)
			finished=true;
	}

  	outputs.push_back(sizeOfSet);

  }

for (int k=0; k<numTests; k++){
	cout << outputs.at(k) << endl;
}

return 0;

}
