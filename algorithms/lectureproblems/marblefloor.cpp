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
	int numOnes=0;
	for (int i=0; i<h; i++){

		for (int j=0; j<w; j++){
			cin >> value;
			matrix.at(i).push_back(value);
			if (value==1){
				numOnes++;
			}
		}
	}

	if(numOnes%2){
		cout << "no" << endl;
		continue;
	}

	Graph g;

	//go through matrix and connect adjacent 1`s
	for (int i=0; i<h; i++){

		for (int j=0; j<w; j++){
			if (matrix.at(i).at(j)==1){
				if (i>0 && matrix.at(i-1).at(j)==1){
					add_edge(i*w+j,(i-1)*w+j, g);
				}
				if (i<h-1 && matrix.at(i+1).at(j)==1){
					add_edge(i*w+j,(i+1)*w+j, g);
				}
				if (j>0 && matrix.at(i).at(j-1)==1){
					add_edge(i*w+j,i*w+j-1, g);
				}
				if (j<w-1 && matrix.at(i).at(j+1)==1){
					add_edge(i*w+j,i*w+j+1, g);
				}
			}
		}
	}

	std::vector<graph_traits<Graph>::vertex_descriptor> mate(num_vertices(g));

	bool success=checked_edmonds_maximum_cardinality_matching(g, &mate[0]);
	assert(success);

	if(matching_size(g, &mate[0])== numOnes/2) {cout << "yes" << endl; }
	else {cout << "no" << endl;}	

}



return 0;
}
