// BGLFirstSteps.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <vector>
#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/depth_first_search.hpp>
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
	int numberOfTestCases;
	int numberOfVertices;
	int numberOfEdges;
	int startOfEdge;
	int endOfEdge;
	int edgeWeight;
	cin >> numberOfTestCases;
	Graph g;
	for (int i = 0; i < numberOfTestCases; i++){
		g.clear();
		cin >> numberOfVertices >> numberOfEdges;
		for (int j = 0; j < numberOfEdges; j++){  //start point, ending point, weight.
			cin >> startOfEdge >> endOfEdge >> edgeWeight;
			add_edge(startOfEdge, endOfEdge, edgeWeight, g);  //add edges to your graph.
		}
		property_map < Graph, edge_weight_t >::type weight = get(edge_weight, g); //we have specified that our graph has edge_weight_t as a propery, therefore we can get it from the graph and store the result in a property map. The property map can be used to read the value of the weight for a certain edge.
		property_map<Graph, vertex_distance_t>::type distanceMap = get(vertex_distance, g);
		property_map<Graph, vertex_index_t>::type index = get(vertex_index, g);
		vector<Edge> spanning_tree; //this is the container where my edges will be stored.
		kruskal_minimum_spanning_tree(g, back_inserter(spanning_tree));
		int weightSum = 0;
		for (vector< Edge >::iterator ei = spanning_tree.begin(); ei != spanning_tree.end(); ++ei)
		{
			weightSum += weight[*ei]; //*ei gives you an edge. weight[edge] gives the weight of that edge.
		}
		cout << weightSum << " ";

		Graph::vertex_iterator vertexIt, vertexEnd;
		tie(vertexIt, vertexEnd) = vertices(g);

		// vector for storing distance property
		std::vector<int> d(num_vertices(g));

		// get the first vertex
		Vertex s = *(vertices(g).first);
		// invoke variant 2 of Dijkstra's algorithm

		dijkstra_shortest_paths(g, s, distance_map(&d[0]));
		sort(d.begin(), d.begin() + numberOfVertices);
		cout << d[numberOfVertices-1] << endl;
	}

	return 0;
}
