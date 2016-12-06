#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/tuple/tuple.hpp>
#include <map>
#include <vector>
#include <queue>
#include <boost/graph/connected_components.hpp>

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
typedef adjacency_list <vecS, vecS, undirectedS> UndirectedGraph;

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
		
		int numVertices, numEdges, numSweepers; //rooms, corridors, sweepers (doors)
		cin >> numVertices >> numEdges >> numSweepers;

		int loc;

		if (numEdges==0){ 

			vector<int> sweeperLocs(numVertices,0);
			vector<int> doorLocs(numVertices,0);

			for (int j=0; j<numSweepers; j++){
				cin >> loc;
				sweeperLocs[loc]++;
			}

			for (int j=0; j<numSweepers; j++){
				cin >> loc;
				doorLocs[loc]++;
			}

			int starts, ends;
			for (int e=0; e<numEdges; e++){
				cin >> starts >> ends;
			}

			bool works=true;
			for (int k=0; k<numVertices; k++){
				if (sweeperLocs[k]!=doorLocs[k]){
					works=false;
					break;
				}
			}
			
			if (works) cout << "yes" << endl;
			else cout << "no" << endl;

			continue;
		}

		if (numSweepers==0){ //else there are some edges, but no sweepers.

			for (int j=0; j<numSweepers; j++){
				cin >> loc;
			}

			for (int j=0; j<numSweepers; j++){
				cin >> loc;
			}

			int starts, ends;
			for (int e=0; e<numEdges; e++){
				cin >> starts >> ends;
			}

			cout << "no" << endl;

			continue;
		}
		
		vector<int> sweeperLocs(numVertices,0); //we have some edges, we have some rooms and we have some sweepers.
		vector<int> doorLocs(numVertices,0);

		for (int j=0; j<numSweepers; j++){
			cin >> loc;
			sweeperLocs[loc]++;
		}

		for (int j=0; j<numSweepers; j++){
			cin >> loc;
			doorLocs[loc]++;
		}

		Graph g(numVertices+2);
		UndirectedGraph unG(numVertices);
		EdgeCapacityMap capacity = get(edge_capacity, g);
		ReverseEdgeMap rev_edge = get(edge_reverse, g);
		ResidualCapacityMap res_capacity = get(edge_residual_capacity, g);

		int starts, ends;
		for (int e=0; e<numEdges; e++){
			cin >> starts >> ends;
			add_edge(starts, ends, unG); //undirected graph
			addEdge(starts,ends, 1, capacity, rev_edge, g);
			addEdge(ends,starts, 1, capacity, rev_edge, g); 
		}
		
		int source=numVertices;
		int sink=numVertices+1;

		long int minFlowVal=0;
		//connect source to sweepers and sink to doors. check degree
		for (size_t k=0; k<numVertices; k++){
			
			if (sweeperLocs.at(k)!=0){
				addEdge(source, k, sweeperLocs.at(k), capacity, rev_edge, g);
				minFlowVal+=sweeperLocs.at(k);
			}

			if (doorLocs.at(k)!=0){
				addEdge(k, sink, doorLocs.at(k), capacity, rev_edge, g);
			}
		}

		long flow = push_relabel_max_flow(g, source, sink);

		if (flow<minFlowVal)
			cout << "no" << endl;

		else {
		
			//check if all components that have more than one vertex, have at least one sweeper.
			std::vector<int> component(num_vertices(unG));
			int num = connected_components(unG, &component[0]);

			map<int, vector<int> > compVertexMap;
			for (size_t k = 0; k<component.size(); ++k){
			    compVertexMap[component.at(k)].push_back(k);
  			}

			map<int, vector<int> >::iterator it;

			bool componentWorks=true;
			for (it=compVertexMap.begin(); it!=compVertexMap.end(); it++){ //for each component
				vector<int> verticesInComp=it->second;
				if (verticesInComp.size()==1){
					continue;
				}
				bool connected=false;
				bool cycle=true; 
				for (size_t j=0; j<verticesInComp.size(); j++){ //the component must have a sweeper.
					if(sweeperLocs[verticesInComp.at(j)]){
						connected=true;
					}
					int value=degree(verticesInComp.at(j), unG)-abs(sweeperLocs.at(verticesInComp.at(j))-doorLocs.at(verticesInComp.at(j)));
					if (value%2 || value<0){ //if odd
						cycle=false;
						break;
					}
				}
				if (connected==false || cycle==false){
					componentWorks=false; 
					break;
				}
			}

			if (!componentWorks){
				cout << "no" << endl;
			}

			else {
				cout << "yes" << endl;
			}
		}
	}

return 0;
}
