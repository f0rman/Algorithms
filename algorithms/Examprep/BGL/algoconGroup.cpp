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
	int numSculpts, numVertices, numEdges, from, to, cap;
	cin >> numSculpts;

	for (int i=0; i<numSculpts; i++){
		
		cin >> numVertices >> numEdges; 
		Graph g(numVertices);
		EdgeCapacityMap capacity = get(edge_capacity, g);
		ReverseEdgeMap rev_edge = get(edge_reverse, g);
		ResidualCapacityMap res_capacity = get(edge_residual_capacity, g);

		for (int j=0; j<numEdges; j++){

			cin >> from >> to >> cap;			
			addEdge(from, to, cap, capacity, rev_edge, g);
		}

		//let's take vertex 0 as source, run flow from there to all possible sinks and back.
		int source=0;
		int minSource, minSink;
		long minFlow=maximum;

		for (int j=1; j<numVertices; j++){
			int sink=j;
			long flow = push_relabel_max_flow(g, source, sink);
			if (flow<minFlow){
				minFlow=flow;
				minSink=sink;
				minSource=source;
			}
			flow = push_relabel_max_flow(g, sink, source);
			if (flow<minFlow){
				minFlow=flow;
				minSource=sink;
				minSink=source;
			}
		}

        	long flow = push_relabel_max_flow(g, minSource, minSink); //do another push_relabel_max_flow using the found minSink so your 									rescap-map becomes correct
        	vector<bool> visited(numVertices, false);
        	std::queue<int> q;
        	q.push(minSource);
        	visited[minSource] = true;
        	graph_traits<Graph>::out_edge_iterator  eBeg, eEnd;
 	        int count = 1;
 
       		while(!q.empty()){ //do a BFS from source. if the res_capacity of an edge (capacity minus flow) is 0, that means the flow
				   //of that edge is maximal, meaning it is part of the minCut and we cannot cross it. if it is greater
				   //than 0, the connected vertex is still before the min-cut.
		        int u = q.front();
		        q.pop();
	 
		        for(tie(eBeg, eEnd)=out_edges(u, g); eBeg != eEnd; ++eBeg)
		        {
		                int v = target(*eBeg, g); // how to get the target of an edge
		                if(res_capacity[*eBeg] > 0 && !visited[v])
		                {
		                        visited[v]=true;
		                        q.push(v);
		                        count++;
		                }
		        }
        	}
 
		cout << minFlow  << "\n" << count << " ";
	       
		for(int i=0; i <numVertices; ++i)
		{
		        if(visited[i] == true)
		                cout << i << " ";
		}
		cout << endl;
	}

return 0;
}
