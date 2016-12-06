#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <vector>
#include <boost/graph/edmonds_karp_max_flow.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/tuple/tuple.hpp>

using namespace boost;
using namespace std;

typedef	adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
	property<edge_capacity_t, int,
		property<edge_residual_capacity_t, int,
			property<edge_reverse_t, Traits::edge_descriptor> > > >	Graph;
typedef	property_map<Graph, edge_capacity_t>::type		EdgeCapacityMap;
typedef	property_map<Graph, edge_residual_capacity_t>::type	ResidualCapacityMap;
typedef	property_map<Graph, edge_reverse_t>::type		ReverseEdgeMap;
typedef	graph_traits<Graph>::vertex_descriptor			Vertex;
typedef	graph_traits<Graph>::edge_descriptor			Edge;
typedef graph_traits<Graph>::out_edge_iterator			OutEdgeIterator;

// Custom add_edge, also creates reverse edges with corresponding capacities.
Edge addEdge(int u, int v, int c, EdgeCapacityMap &capacity, ReverseEdgeMap &rev_edge, Graph &G) {
	Edge e, reverseE;
	tie(e, tuples::ignore) = add_edge(u, v, G);
	tie(reverseE, tuples::ignore) = add_edge(v, u, G);
	capacity[e] = c;
	capacity[reverseE] = 0;
	rev_edge[e] = reverseE;
	rev_edge[reverseE] = e;
	return e;
}

int main(){
	ios_base::sync_with_stdio(false);
	int num_testcases; cin >> num_testcases;
	for(int t = 0; t < num_testcases; ++t){
		int num_locations, num_paths;
		cin >> num_locations >> num_paths;
		vector<int> soldiers_at_location(num_locations);

		for(int l = 0; l < num_locations; ++l){
			int g, d;
			cin >> g >> d;
			soldiers_at_location[l] = g - d; //soldiers left at each location, can be a negative amount.
		}

		Graph kingdom(num_locations + 2);
		EdgeCapacityMap capacity = get(edge_capacity, kingdom);
		ReverseEdgeMap rev_edge = get(edge_reverse, kingdom);
		int source = num_vertices(kingdom) - 2;
		int sink = num_vertices(kingdom) - 1;

		for(int p = 0; p < num_paths; ++p){
			int s, t, least, most;
			cin >> s >> t >> least >> most;
			soldiers_at_location[s] -= least; //decrease soldiers at start of edge, increase them at the end of the edge
			soldiers_at_location[t] += least;
			addEdge(s, t, most - least, capacity, rev_edge, kingdom); //add an edge with capacity left.
		}

		vector<Edge> critical_edges;

		for(int l = 0; l < num_locations; ++l){
			int soldiers = soldiers_at_location[l];
			if(soldiers > 0){
				addEdge(source, l, soldiers, capacity, rev_edge, kingdom); //add an edge from source to location if there is
			} else if(soldiers < 0){                                           //a positive amount of soldiers there.
				Edge e = addEdge(l, sink, -soldiers, capacity, rev_edge, kingdom); //otherwise add an edge to the sink
				critical_edges.push_back(e);                                      //because these cities need to get flow
			}
		}

		ResidualCapacityMap res_capacity = get(edge_residual_capacity, kingdom); //run flow
		int flow = push_relabel_max_flow(kingdom, source, sink);

		bool possible = true; //make sure there is flow equal to missing soldiers on the critical edges where you missed soldiers
		for(vector<Edge>::iterator ei = critical_edges.begin(); ei != critical_edges.end(); ++ei){
			if(res_capacity[*ei] != 0){
				possible = false;
				break;
			}
		}

		if(possible){
			cout << "yes" << endl;
		} else {
			cout << "no" << endl;
		}
	}
}
