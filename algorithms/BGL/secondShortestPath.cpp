#include <vector>
#include <queue>
#include <iostream>
#include <climits>
#include <algorithm>    // std::reverse

using namespace std;

int findShortest(const vector< vector<int> > &adjacencyList, int start, int target, int numVertices, vector<int> &pred){ //function finds 																shortest path by BFS
	queue<int> Q;
	vector<bool> visited(numVertices);
	visited.at(start)=true;
	Q.push(start);

	if (start==target){
		return 0;
	}

	bool foundTarget=false;
	while (!Q.empty()){

		int currentVertex=Q.front();
		Q.pop();
	
		vector<int> adjacentVertices=adjacencyList.at(currentVertex);

		for(size_t j=0; j<adjacentVertices.size(); j++){

			int adjvert=adjacentVertices.at(j);
			if (adjvert==target){
				visited.at(adjvert)=true;
				pred.at(adjvert)=currentVertex;
				foundTarget=true;
				break;
			}
			else if (!visited.at(adjvert)){
				Q.push(adjvert);
				visited.at(adjvert)=true;
				pred.at(adjvert)=currentVertex;
			}
		}
		if (foundTarget) break;
	}

	if (!foundTarget) {return -1;}
	else{ 
		int length=0;
		int parent=pred[target];
		while(parent!=-1){
			parent=pred[parent];
			length++;
		}
 	return length;
	}
}

void findSecondShortest(const vector< vector<int> > &adjacencyList, int start, int target, int numVertices){

	vector<int> pred(numVertices, -1);
	int lengthOfShortestPath=findShortest(adjacencyList, start, target, numVertices, pred);

	if (lengthOfShortestPath==-1) {
		cout << "no" << endl;
		return;
	}

	//backtrack through pred and store shortest path in vector;

	vector<int> shortestPath;
	shortestPath.push_back(target);
	int parent=pred[target];
	
	while(parent!=-1){
		shortestPath.push_back(parent);
		parent=pred[parent];
	}

	std::reverse(shortestPath.begin(),shortestPath.end());

	//we now know exactly which nodes were used in the shortest path. Time to exit path and find shortest path again.

	int shortestSecond=INT_MAX;

	for (size_t k=0; k<shortestPath.size(); k++){

		int currentVert=shortestPath[k];
		vector<int> adjVerts=adjacencyList.at(currentVert);
		for (size_t a=0; a<adjVerts.size(); a++){
			int adjVert=adjVerts.at(a);

			if ((k==shortestPath.size()-1) || (shortestPath[k+1]!=adjVert)){ // if the adjacent vertex exits the path
				vector<int> pred2(numVertices, -1);
				int myLength=findShortest(adjacencyList, adjVert, target, numVertices, pred2);
				if (myLength==-1){continue;} //if there was no path, continue.
				if (myLength+k+1<shortestSecond)
					shortestSecond=myLength+k+1;
			}
		}
	}

	if (shortestSecond==INT_MAX) cout << "no" << endl;
	else cout << shortestSecond << endl;

return;
}

int main(){

int T;
cin >> T;

while (T--){

	int numVertices;
	int numEdges;
	int start, target;

	cin >> numVertices >> numEdges;
	cin >> start >> target;
	start--;
	target--;

	vector <vector <int> > adjacencyList(numVertices);

	int s, t;
	for (int e=0; e<numEdges; e++){

		cin >> s >> t;
		s--;
		t--;
		adjacencyList.at(s).push_back(t);

	}

	findSecondShortest(adjacencyList, start, target, numVertices);

}

return 0;

}
