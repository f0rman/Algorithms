// Bridges.cpp

#include <iostream>
#include <cstdio>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/biconnected_components.hpp>
#include <vector>
#include <algorithm>

using namespace boost;
using namespace std;

//An edge can only be in ONE biconnected component as opposed to vertices, which can be in several. Therefore,
//If a biconnected component has only one edge, it's a bridge.

namespace boost
{
	struct edge_component_t
	{
		enum
		{
			num = 555
		};
		typedef edge_property_tag kind;
	}
	edge_component;
}

bool compare_pairs(pair<int, int> p1, pair<int, int> p2){
	if (p1.first < p2.first){
		return true;
	}
	else if (p1.first == p2.first){
		return p1.second <= p2.second;
	}
	else {
		return false;
	}
}

typedef adjacency_list<vecS, vecS, undirectedS, property<vertex_index_t, int>, property < edge_component_t, size_t > > Graph;
typedef graph_traits <Graph>::vertex_descriptor Vertex;
typedef graph_traits <Graph>::edge_descriptor Edge;

int main()
{
	int numTestCases, numVertices, numEdges, startOfEdge, endOfEdge;
	Graph g;
	cin >> numTestCases;
	for (int i = 0; i < numTestCases; i++){

		g.clear();
		cin >> numVertices >> numEdges;

		for (int j = 0; j < numEdges; j++){
			cin >> startOfEdge >> endOfEdge;
			add_edge(startOfEdge, endOfEdge, g);
		}

		property_map < Graph, edge_component_t >::type component = get(edge_component, g);
		property_map<Graph, vertex_index_t>::type indexMap = get(vertex_index, g);
		vector<Vertex> artPoints;

		biconnected_components(g, component);

		//In component map we have edges as key and int (which component an edge belongs to) as value.
		
		//flip map
		map<int, vector<Edge> > other_map;

		//fill flipped map
		graph_traits<Graph>::edge_iterator ei, ei_end;
		for (tie(ei, ei_end) = edges(g); ei != ei_end; ++ei){
			other_map[component[*ei]].push_back(*ei);
		}

		//iterate through all keys of the map, look at biconnected component size.
		int numBridges=0;
		vector<pair<int,int>> bridges;
		for (map<int, vector<Edge> >::iterator comp_edge = other_map.begin(); comp_edge != other_map.end(); ++comp_edge){
			if (comp_edge->second.size() == 1){
				numBridges++;
				Edge myEdge = comp_edge->second.at(0);
				if (source(myEdge, g) < target(myEdge, g)){
					bridges.push_back(pair<int, int>(source(myEdge, g), target(myEdge, g)));
				}
				else { bridges.push_back(pair<int, int>(target(myEdge, g), source(myEdge, g))); }
			}
		}

		cout << numBridges << endl;
		sort(bridges.begin(), bridges.end());

		for (size_t i = 0; i < bridges.size(); i++){
			cout << bridges.at(i).first << " " << bridges.at(i).second << endl;
		}
	}
	return 0;
}
