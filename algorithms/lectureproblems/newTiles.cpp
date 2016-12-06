#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <cassert>
#include <boost/graph/max_cardinality_matching.hpp>
#include <boost/tuple/tuple.hpp>
#include <vector>
#include <algorithm>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS> Graph;

int main(){

ios_base::sync_with_stdio(false);
int numTests;
cin >> numTests;

for (int k=0; k<numTests; k++){

	int w, h;

	cin >> w >> h;

	vector< vector<int> > matrix(h);

	int value;
	for (int i=0; i<h; i++){

		for (int j=0; j<w; j++){
			cin >> value;
			matrix.at(i).push_back(value);
		}
	}

	//transformed matrix where we can see where we can actually put tiles
	vector< vector<int> > tMatrix(h-1);

	int numOnes=0;
	//look around top left corner
	for (int i=0; i<h-1; i++){

		tMatrix.at(i).resize(w-1, 0);
		for (int j=0; j<w-1; j++){

			if (matrix.at(i).at(j)==0){
				continue;
			}
			else { //check 3 adjacent entries here.
				
				if (matrix.at(i).at(j+1)==1 && matrix.at(i+1).at(j+1)==1 && matrix.at(i+1).at(j)==1){
					tMatrix.at(i).at(j)=1;
					numOnes++;
				}
			}
		}
	}

	for (size_t i=0; i<tMatrix.size(); i++){
		for (size_t j=0; j<tMatrix[0].size(); j++){
			cout << tMatrix[i][j];
		}
		cout << endl;
	}

	Graph g;

	//go through tMatrix and connect adjacent 1`s
	for (int i=0; i<h-1; i++){

		//checking 8 neighbours
		for (int j=0; j<w-1; j++){
			if (tMatrix.at(i).at(j)==1){
				if (i>0 && j>0){
					if(tMatrix.at(i-1).at(j-1)==1){ //top row
						add_edge(i*w+j,(i-1)*w+j-1, g);
					}
				}
				if (i>0){
					if(tMatrix.at(i-1).at(j)==1){
						add_edge(i*w+j,(i-1)*w+j, g);
					}
				}
				if (i>0 && j<w-2){
					if(tMatrix.at(i-1).at(j+1)==1){
						add_edge(i*w+j,(i-1)*w+j+1, g);
					}
				}
				if (j>0 && tMatrix.at(i).at(j-1)==1){  //middle row
					add_edge(i*w+j,i*w+j-1, g);
				}
				if (j<w-2 && tMatrix.at(i).at(j+1)==1){
					add_edge(i*w+j,i*w+j+1, g);
				}

				if (i<h-2 && j>0 && tMatrix.at(i+1).at(j-1)==1){ //bottom row
					add_edge(i*w+j,(i+1)*w+j-1, g);
				}
				if (i<h-2 && tMatrix.at(i+1).at(j)==1){ 
					add_edge(i*w+j,(i+1)*w+j, g);
				}
				if (i<h-2 && j<w-2 && tMatrix.at(i+1).at(j+1)==1){ 
					add_edge(i*w+j,(i+1)*w+j+1, g);
				}
			}
		}
	}

	cout << "numOnes is " << numOnes << endl;

	std::vector<graph_traits<Graph>::vertex_descriptor> mate(num_vertices(g));

	bool success=checked_edmonds_maximum_cardinality_matching(g, &mate[0]);
	assert(success);
	cout << numOnes-matching_size(g, &mate[0]) << endl;

}

return 0;
}
