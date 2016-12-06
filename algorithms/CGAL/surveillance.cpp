#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <vector>
#include <boost/graph/edmonds_karp_max_flow.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/tuple/tuple.hpp>
#include <map>
#include <queue>

using namespace boost;
using namespace std;
const int maximum=INT_MAX;

typedef	adjacency_list_traits<vecS, vecS, directedS> Traits; 
typedef adjacency_list<vecS, vecS, directedS, property<vertex_index_t, int>, property<edge_capacity_t, int, property<edge_residual_capacity_t, int, property<edge_reverse_t, Traits::edge_descriptor> > > >	Graph;
typedef	property_map<Graph, edge_capacity_t>::type		EdgeCapacityMap;
typedef	property_map<Graph, edge_residual_capacity_t>::type	ResidualCapacityMap;
typedef	property_map<Graph, edge_reverse_t>::type		ReverseEdgeMap;
typedef	graph_traits<Graph>::vertex_descriptor			Vertex;
typedef	graph_traits<Graph>::edge_descriptor			Edge;
typedef graph_traits<Graph>::out_edge_iterator			OutEdgeIterator;

// Custom add_edge, also adds capacities.
Edge addEdge(int u, int v, int c, EdgeCapacityMap &capacity, ReverseEdgeMap &rev_edge, Graph &G) {
	Edge e, reverseE;
	tie(e, tuples::ignore) = add_edge(u, v, G);   //we're not interested in the boolean value only the edge that we add, hence ignore.
	tie(reverseE, tuples::ignore) = add_edge(v, u, G);
	capacity[e] = c; //when we add our edge, our capacity on the edgecapacitymap at this place should be c, the argument of edge-capcity.
	capacity[reverseE] = 0;
	rev_edge[e] = reverseE; //add reverse edges to reverse edge property map.
	rev_edge[reverseE] = e;
	return e;
}

void bfs(int startVertex, map<int,int> &photoPos, Graph &g, Graph &subGraph, EdgeCapacityMap &capacity, ReverseEdgeMap &rev_edge, int numIntersections){

	std::queue<int> q;
	map<int, bool> visited;
	q.push(startVertex); 
	visited[startVertex]=true;
	OutEdgeIterator e, e_end;

	if (photoPos.count(startVertex)){ //if there is a photo where you start your search...
		addEdge(startVertex+numIntersections, startVertex+2*numIntersections, maximum, capacity, rev_edge, g);
	}

	while (!q.empty()){

		int top=q.front();
		q.pop();
					
		for (tie(e, e_end) = out_edges(vertex(top, subGraph), subGraph); e != e_end; ++e){
		
			if (visited[target(*e, subGraph)]==false){
				q.push(target(*e, subGraph));
				if (photoPos.count(target(*e, subGraph))){ //if key exists in photoMap...
					addEdge(startVertex+numIntersections, target(*e, subGraph)+2*numIntersections, maximum, capacity, rev_edge, g);
				}
				visited[target(*e, subGraph)]=true;
			}
		}
			
	}  //end of while
return;
}

int main(){
	ios_base::sync_with_stdio(false);
	int num_testcases, numStations, numPhotos, numIntersections, numEdges, position, startOfEdge, endOfEdge;
	cin >> num_testcases;
	for(int t = 0; t < num_testcases; ++t){
		
		cin >> numIntersections >> numEdges >> numStations >> numPhotos;
		Graph g; 
		map<int, int> policePos; //maps vertex index to number of polices
		map<int, int> photoPos;  //maps vertex index to number of photos
		
		for (int i=0; i<numStations; i++){
			cin >> position;
			policePos[position]++;
			add_vertex(position+numIntersections, g); //for policeman
			add_vertex(position+numIntersections*3, g); //For police stations
		}

		for (int j=0; j<numPhotos; j++){ //for photos
			cin >> position;
			photoPos[position]++;
			add_vertex(position+numIntersections*2, g);
		}

		EdgeCapacityMap	capacity = get(edge_capacity, g);  //make a capacity-map, reverse edge-map and residualcapacitymap.
		ReverseEdgeMap rev_edge = get(edge_reverse, g);
		ResidualCapacityMap res_capacity = get(edge_residual_capacity, g);

		Graph subGraph;
		for (int k=0; k<numEdges; k++){ //For the graph itself
			cin >> startOfEdge >> endOfEdge;
			addEdge(startOfEdge, endOfEdge, 1, capacity, rev_edge, g);
			add_edge(startOfEdge, endOfEdge, subGraph);
		}

		int source=numIntersections*4;  //source and sink indices.
		int sink=numIntersections*4+1;

		for (map<int,int>::iterator it=policePos.begin(); it!=policePos.end(); ++it){ //connect source to policemen and sink to station
			addEdge(source, it->first+numIntersections, it->second, capacity, rev_edge, g);
			addEdge(it->first+numIntersections*3, sink, it->second, capacity, rev_edge, g);
		}

		for (map<int,int>::iterator it=photoPos.begin(); it!=photoPos.end(); ++it){ //connect photos to the graph
			addEdge(it->first+numIntersections*2, it->first, it->second, capacity, rev_edge, g);
		}

		for (map<int,int>::iterator it=policePos.begin(); it!=policePos.end(); ++it){ //connect graph to stations
			addEdge(it->first, it->first+numIntersections*3, it->second, capacity, rev_edge, g);
		}	

		Graph::edge_iterator edgeIt, edgeEnd; tie(edgeIt, edgeEnd) = edges(g);		
		//make BFS from police stations to see which photos are reachable.
		for (map<int,int>::iterator it=policePos.begin(); it!=policePos.end(); ++it){ 
			bfs(it->first, photoPos, g, subGraph, capacity, rev_edge, numIntersections);
		}

		int flow = push_relabel_max_flow(g, source, sink);
		cout << flow << endl;

	}

return 0;
}
