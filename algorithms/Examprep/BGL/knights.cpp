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
		
		int numCols, numRows, numKnights;
		cin >> numCols >> numRows >> numKnights; 
		Graph g(numRows*numCols*2+2);
		EdgeCapacityMap capacity = get(edge_capacity, g);
		ReverseEdgeMap rev_edge = get(edge_reverse, g);
		ResidualCapacityMap res_capacity = get(edge_residual_capacity, g);

		int outDisplacement=numRows*numCols;

		//connect every intersection to itself with capacity 1
		for (int j=0; j<numRows*numCols; j++){
			addEdge(j, j+outDisplacement, 1, capacity, rev_edge, g);
		}

		//connect appropriate intersections according to grid structure. Remember undirected
		for (int row=0; row<numRows; row++){
			for (int col=0; col<numCols; col++){
				int index=row*numCols+col;
				int connectedIndex;
				if (row!=0){
					connectedIndex=(row-1)*numCols+col;
					addEdge(index+outDisplacement,connectedIndex, 1, capacity, rev_edge, g);
					addEdge(connectedIndex+outDisplacement,index, 1, capacity, rev_edge, g);
				}
				if (row!=numRows-1){
					connectedIndex=(row+1)*numCols+col;
					addEdge(index+outDisplacement,connectedIndex, 1, capacity, rev_edge, g);
					addEdge(connectedIndex+outDisplacement,index, 1, capacity, rev_edge, g);
				}
				if (col!=0){
					connectedIndex=row*numCols+col-1;
					addEdge(index+outDisplacement,connectedIndex, 1, capacity, rev_edge, g);
					addEdge(connectedIndex+outDisplacement,index, 1, capacity, rev_edge, g);
				}
				if (col!=numCols-1){
					connectedIndex=row*numCols+col+1;
					addEdge(index+outDisplacement,connectedIndex, 1, capacity,rev_edge, g);
					addEdge(connectedIndex+outDisplacement,index, 1, capacity,rev_edge, g);
				}
			}
		}

		int source=2*numRows*numCols;
		int sink=2*numRows*numCols+1;

		//connect source
		int colpos, rowpos;
		for (int k=0; k<numKnights; k++){
			cin >> colpos >> rowpos;
			int index=rowpos*numCols+colpos;
			addEdge(source, index, 1, capacity, rev_edge, g);
		}

		//connect sink
		for (int col=0; col<numCols; col++){
			addEdge(col+outDisplacement, sink, 1, capacity, rev_edge, g);
			addEdge((numRows-1)*numCols+col+outDisplacement, sink, 1, capacity, rev_edge, g);
		}

		for (int row=0; row<numRows; row++){
			addEdge(row*numCols+outDisplacement, sink, 1, capacity, rev_edge, g);
			addEdge(row*numCols+numCols-1+outDisplacement, sink, 1, capacity, rev_edge, g);
		}

		long flow = push_relabel_max_flow(g, source, sink);
		cout << flow << endl;
	}

return 0;
}
