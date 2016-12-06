#include <iostream>	
#include <vector>	
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/strong_components.hpp>
#include <boost/tuple/tuple.hpp>
#include <map>

using namespace std;
using namespace boost;
const int maximum=INT_MAX;

typedef adjacency_list<vecS, vecS, directedS,
	no_property, no_property > Graph;			// directed Graph
typedef graph_traits<Graph>::edge_descriptor Edge;

int main() {

	int numTests, numVertices, numEdges, cost;
	cin >> numTests;

	for (int i=0; i<numTests; i++){

		cin >> numVertices >> numEdges;
		Graph g(numVertices);

		int from, to;
		for (int j=0; j<numEdges; j++){
			cin >> from >> to;
			from--;
			to--;
			add_edge(from, to, g);
		}

		vector<int> costs(numVertices);

		for (int k=0; k<numVertices; k++){
			cin >> cost;
			costs.at(k)=cost;
		}

		vector<int> scc(numVertices);
		int nscc = strong_components(g, make_iterator_property_map(scc.begin(), get(vertex_index, g)));
		vector<int> costOfComps(nscc, maximum);
		vector<bool> stored(nscc, false);
		
  		for (int i = 0; i < numVertices; ++i){
			
  			int component=scc[i]; //get the component of the vertex
			if (stored.at(component)==false){ //if we haven't put a cost for this component in the map yet...
				if (costs.at(i)<costOfComps[component]){
					costOfComps[component]=costs.at(i);
				}
			}
		}

		//iterate over all edges, and find the ones connecting 2 strongly connected components.
		Graph::edge_iterator edgeIt, edgeEnd; tie(edgeIt, edgeEnd) = edges(g);

     		for (; edgeIt!= edgeEnd; ++edgeIt) { 
			
			if(scc[source(*edgeIt, g)]!=scc[target(*edgeIt, g)]){ //if this edge connects two different connected comps..
				costOfComps.at(scc[target(*edgeIt, g)])=0; //the head has 0 cost.			
			}
    		} 

		int sum=0;
		for (int j=0; j<nscc; j++){
			sum+=costOfComps[j];
		}

		cout << sum << endl;
		g.clear();	
	}
	
return 0;
}


