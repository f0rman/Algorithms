//the idea is to check outer-planarity. If the graph is outer-planar, all nodes are in a "circle" and every guy can have a toilet.

#include <iostream>
#include <cstdio>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/boyer_myrvold_planar_test.hpp>

int main()
{
	std::ios_base::sync_with_stdio(false);
	using namespace boost;
	using namespace std;
	typedef adjacency_list<vecS, vecS, undirectedS, property<vertex_index_t, int> > Graph;
	typedef graph_traits<Graph>::vertex_descriptor Vertex;
	typedef pair<int, int> Edge;

	int numTestCases, numVertices, numEdges, startOfEdge, endOfEdge;
	cin >> numTestCases;
	for (int i = 0; i < numTestCases; i++){

		cin >> numVertices >> numEdges;
		Graph g(numVertices + 1);

		for (int j = 0; j < numEdges; j++){
			cin >> startOfEdge >> endOfEdge;
			add_edge(startOfEdge, endOfEdge, g);
		}

		//connect infinity node to all other nodes.
		int infIndex = numVertices;
		for (int k = 0; k < numVertices; k++){
			add_edge(k, infIndex, g);
		}

		if (boyer_myrvold_planarity_test(g))
			std::cout << "yes" << std::endl;
		else
			std::cout << "no"<< std::endl;
	}
	
	return 0;
}
