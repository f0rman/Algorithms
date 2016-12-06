#include <iostream>
#include <vector>
#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <algorithm>

using namespace std;
using namespace boost;
typedef property<edge_weight_t, int> EdgeWeightProperty;
typedef property<vertex_distance_t, int> VertexDistanceProperty;
typedef adjacency_list<vecS, vecS, undirectedS, VertexDistanceProperty,  //vecS corresponds to std::vector
	EdgeWeightProperty > Graph;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_descriptor Edge;

int main()
{

	int numberOfTestcases;
	int numVertices;
	int numEdges;
	int numSpecies;
	int startNode;
	int finishNode;
	int startOfEdge;
	int endOfEdge;
	int edgeWeight;
	int hive;

	cin >> numberOfTestcases;

	Graph finalGraph;
	for (int i = 0; i < numberOfTestcases; i++){ 
		cin >> numVertices >> numEdges >> numSpecies >> startNode >> finishNode;

		vector<Graph> speciesGraphs(numSpecies);
		vector<Graph> minSpanTrees(numSpecies);
		finalGraph.clear();

		if (numVertices == 1 || startNode == finishNode){

			for (int sp = 0; sp < numSpecies; sp++){ //cin the hive but don't care about it.
				cin >> hive;
			}

			cout << 0 << endl;
			continue;
		}

		for (int j = 0; j < numEdges; j++){  //add edges to the tree
			cin >> startOfEdge >> endOfEdge;

			for (int sp = 0; sp < numSpecies; sp++){
				cin >> edgeWeight;
				add_edge(startOfEdge, endOfEdge, edgeWeight, speciesGraphs[sp]);  //add edges to the correct graph
			}
		}

		for (int sp = 0; sp < numSpecies; sp++){ //cin the hive but don't care about it.
			cin >> hive;
		}

		//do kruskal on all graphs, add resulting edges to final Graph

		for (int k = 0; k < numSpecies; k++){

			property_map< Graph, edge_weight_t >::type weightMap = get(edge_weight, speciesGraphs[k]); //we have specified that our graph has edge_weight_t as a propery, therefore we can get it from the graph and store the result in a property map. The property map can be used to read the value of the weight for a certain edge.
			vector<Edge> spanning_tree; //this is the container where my edges will be stored.
			kruskal_minimum_spanning_tree(speciesGraphs[k], back_inserter(spanning_tree));

			//DON'T CLEAR g, that destroys the weightMAP!

			for (vector< Edge >::iterator ei = spanning_tree.begin(); ei != spanning_tree.end(); ++ei)
			{
				int start = source(*ei, speciesGraphs[k]);
				int targ = target(*ei, speciesGraphs[k]);
				add_edge(start, targ, weightMap[*ei], finalGraph);
			}

			spanning_tree.clear();

		}

		// vector for storing distance property
		std::vector<int> d(numVertices);

		// get the first vertex
		// invoke variant 2 of Dijkstra's algorithm
		dijkstra_shortest_paths(finalGraph, startNode, distance_map(&d[0]));

		cout << d[finishNode]<<endl;
		d.clear();
	}

	return 0;
}
