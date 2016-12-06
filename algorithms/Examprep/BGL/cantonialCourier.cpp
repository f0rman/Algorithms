#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/tuple/tuple.hpp>
#include <vector>
#include <queue>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
property<edge_capacity_t, long, property<edge_residual_capacity_t, long,
property<edge_reverse_t, Traits::edge_descriptor> > > > Graph;
typedef property_map<Graph, edge_capacity_t>::type EdgeCapacityMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type ReverseEdgeMap;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
const long maximum=LONG_MAX;

void addEdge(int from, int to, long c, EdgeCapacityMap &capacity, ReverseEdgeMap &rev_edge, Graph &G) {
	Edge e, reverseE;
	tie(e, tuples::ignore) = add_edge(from, to, G);
	tie(reverseE, tuples::ignore) = add_edge(to, from, G);
	capacity[e] = c;
	capacity[reverseE]= 0;
	rev_edge[e] = reverseE;
	rev_edge[reverseE] = e;
}

int main(){

	ios_base::sync_with_stdio(false);
	int numTests;
	cin >> numTests;

	for (int i=0; i<numTests; i++){
		
		int numZones, numJobs;
		cin >> numZones >> numJobs; 
		Graph g(numZones+numJobs+2);
		EdgeCapacityMap capacity = get(edge_capacity, g);
		ReverseEdgeMap rev_edge = get(edge_reverse, g);
		ResidualCapacityMap res_capacity = get(edge_residual_capacity, g);
		int s=numZones+numJobs;
		int sink=numZones+numJobs+1;
		int totRew=0;

		int cost;
		for (int j=0; j<numZones; j++){
			cin >> cost;		
			addEdge(numJobs+j, sink, cost, capacity, rev_edge, g);
		}
		int rew;
		for (int j=0; j<numJobs; j++){
			cin >> rew;
			totRew+=rew;		
			addEdge(s, j, rew, capacity, rev_edge, g);
		}

		//connect jobs and zones
		int zoneNeeded, numZonesNeed;
		for (int j=0; j<numJobs; j++){
			cin >> numZonesNeed;
			for (int z=0; z<numZonesNeed; z++){	
				cin >> zoneNeeded;
				zoneNeeded--;	
				addEdge(j, zoneNeeded+numJobs, maximum, capacity, rev_edge, g);
			}
		}

		long MC = push_relabel_max_flow(g, s, sink);
		cout << totRew-MC << endl;
	}

return 0;
}
