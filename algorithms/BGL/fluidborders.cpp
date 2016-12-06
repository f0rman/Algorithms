// FluidBorders.cpp : Defines the entry point for the console application.
//

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/boyer_myrvold_planar_test.hpp>
#include <iostream>
#include <vector>
using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, property<vertex_index_t, int>> Graph;
typedef graph_traits<Graph>::vertex_descriptor Vertex;

int main()
{
	int numTestCases;
	int numMetaBlobs;
	int prefNeigh;
	
	cin >> numTestCases;
	vector<vector<int>> electionResults;
	Graph g;

	for (int i = 0; i < numTestCases; i++){
		
		electionResults.clear();
		g.clear();
		cin >> numMetaBlobs;
		electionResults.resize(numMetaBlobs);  	//initialize g to just contain the vertices
		for (int m = 0; m < numMetaBlobs; m++){
			add_vertex(g);
			for (int t = 0; t < numMetaBlobs-1; t++){ 
				cin >> prefNeigh;
				electionResults.at(m).push_back(prefNeigh);
			}
		}

		bool planar=true;
		int neighInd = 0; //number of neighbours that we try starts as one... we use index here cause the matrix just contains neigbhours.s
		
		while (planar==true && neighInd<numMetaBlobs-1){  //as long as the graph is planar, keep adding edges to it.
			for (int m = 0; m < numMetaBlobs; m++){
				add_edge(m, electionResults.at(m).at(neighInd), g); //try adding all preferred neighbours in this column
			}
			if (boyer_myrvold_planarity_test(g)){ //if planar, increase neighInd.
				planar = true;
				neighInd++;
			}
			else planar = false;
		}

		cout << neighInd << endl;

	}

	return 0;
}
