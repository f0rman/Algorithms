#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/tuple/tuple.hpp>
#include <vector>
#include <algorithm>

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

using namespace std;

int main(){

	ios_base::sync_with_stdio(false);
	int numTests;
	cin >> numTests;

	for (int i=0; i<numTests; i++){

		int width, numBricks;
		cin >> width >> numBricks;
		
		long height=0;
		int start, end;
		
		if (width==0 || numBricks==0){

			for (int j=0; j<numBricks; j++){
				cin >> start >> end;
			}

			cout << 0 << endl;
			continue;
		}

		else if (width==1){

			for (int j=0; j<numBricks; j++){

				cin >> start >> end;
				if (start==end){
				continue;
				}
				else height++;

			}
			cout << height << endl;
			continue;
		}

		Graph g((width-1)*2+2);

		EdgeCapacityMap capacity = get(edge_capacity, g);
		ReverseEdgeMap rev_edge = get(edge_reverse, g);
		ResidualCapacityMap res_capacity = get(edge_residual_capacity, g);

		for (int j=1; j<width; j++){
			addEdge(j, j+width-1, 1, capacity, rev_edge, g);
		}

		for (int j=0; j<numBricks; j++){

			cin >> start >> end;

			if (end<start){
				int tempstart=start; 
				start=end;
				end=tempstart;
			}

			if (end-start==width){
				height++;
				continue;
			}

			else if (start==end){
				continue;
			}

			else {
				if (start==0){
					addEdge(start, end, 1, capacity, rev_edge, g);
				}
				else if (end==width){
					addEdge(start+width-1, end+width-1, 1, capacity, rev_edge, g);
					}
				else {
					addEdge(start+width-1, end, 1, capacity, rev_edge, g);
				} 				
			}
		}

		Vertex source = add_vertex(g);
   		Vertex sink = add_vertex(g);
    		addEdge(source, 0, 20000000, capacity, rev_edge, g); 
		addEdge(width+width-1, sink, 20000000, capacity, rev_edge, g); 

		Graph::vertex_iterator vertexIt, vertexEnd;
 		Graph::adjacency_iterator neighbourIt, neighbourEnd;
		tie(vertexIt, vertexEnd) = vertices(g);
		long flow = push_relabel_max_flow(g, source, sink);
		cout << height+flow << endl;

	}

return 0;

}
