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
	tie(e, tuples::ignore) = add_edge(u, v, G);   //we're not interested in the boolean, value only the edge that we add, hence ignore.
	tie(reverseE, tuples::ignore) = add_edge(v, u, G);
	capacity[e] = c; //when we add our edge, our capacity on the edgecapacitymap at this place should be c, the argument of edge-capcity.
	capacity[reverseE] = 0;
	rev_edge[e] = reverseE; //add reverse edges to reverse edge property map.
	rev_edge[reverseE] = e;
	return e;
}

int main(){
	ios_base::sync_with_stdio(false);
	int num_testcases; cin >> num_testcases;
	for(int t = 0; t < num_testcases; ++t){
		int num_players, num_rounds;
		cin >> num_players >> num_rounds;

		vector<int> wins_needed(num_players, 0);
		vector< pair<int,int> > uncertain_rounds;

		for(int r = 0; r < num_rounds; ++r){ //decrement wins_needed of each player for every round he has won. Into uncertain_rounds
			int p1, p2, outcome;         //push back those rounds(pairs) which are uncertain.
			cin >> p1 >> p2 >> outcome;
			if(outcome == 1){
				--wins_needed[p1];
			} else if(outcome == 2){
				--wins_needed[p2];
			} else if(outcome == 0){
				uncertain_rounds.push_back(make_pair(p1,p2));
			}
		}

		bool not_possible = false;
		for(int p = 0; p < num_players; ++p){  //read the scoreboard. Increment wins_needed for each score that you've recorded.
			int wins; cin >> wins;         //this makes sure you track the case when you've assigned to few points to someone.
			wins_needed[p] += wins;
			if(wins_needed[p] < 0){
				not_possible = true;
			}
		}
		if(not_possible){
			cout << "no" << endl;
		} else {
			int num_of_vertices = num_players+uncertain_rounds.size()+2; //make a graph with all players, uncertain rounds 
			int source = num_of_vertices - 1;                            //and 2 verices for sink and source.
			int sink = num_of_vertices - 2;

			Graph graph(num_of_vertices);
			EdgeCapacityMap	capacity = get(edge_capacity, graph);  //make a capacity-map, reverse edge-map and residualcapacitymap.
			ReverseEdgeMap	rev_edge = get(edge_reverse, graph);
			ResidualCapacityMap	res_capacity = get(edge_residual_capacity, graph);
			
			vector<Edge> source_edges; //this stores all the source edges (edges from source to unknown rounds)
			for(int ur = 0; ur < uncertain_rounds.size(); ++ur){ //for every unknown round...
				int ur_index = ur + num_players;             //the unknown round is a vertex, so add it to the graph and 									     	     //connect.
				addEdge(ur_index, uncertain_rounds[ur].first, 1, capacity, rev_edge, graph);
				addEdge(ur_index, uncertain_rounds[ur].second, 1, capacity, rev_edge, graph);
				source_edges.push_back(addEdge(source, ur_index, 1, capacity, rev_edge, graph));
			}

			vector<Edge> max_score_edges;
			for(int p = 0; p < num_players; ++p){ //wins needed is like the capacity of that edge. How much flow can/should go in 								      //this edge. Each player has one of these edges going to the sink.
				Edge e;
				e = addEdge(p, sink, wins_needed[p], capacity, rev_edge, graph);
				max_score_edges.push_back(e);
			}
			
			vector<int> color_map(num_of_vertices);
			vector<Edge> pred_map(num_of_vertices);
			int flow = push_relabel_max_flow(graph, source, sink); //calculates max flow and flow values for all edges.
			bool fulfilled = true;
			for(vector<Edge>::iterator ei = source_edges.begin(); ei != source_edges.end(); ++ei){ //for all source edges
				if(res_capacity[*ei] != 0){ //if there is capcaity left, i.e the flow is not maximal, fulfilled=false.
					fulfilled = false;
					break;
				}
			}
			if(fulfilled){
				for(vector<Edge>::iterator ei = max_score_edges.begin(); ei != max_score_edges.end(); ++ei){
					if(res_capacity[*ei] != 0){ //if there is any edge, that has capacity left it equates to max flow not 							                    //being fulfilled.
						fulfilled = false;
						break;
					}
				}
			}
			if(fulfilled){
				cout << "yes" << endl;
			} else {
				cout << "no" << endl;
			}
		}

	}
}
