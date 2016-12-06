
#include <boost/graph/adjacency_list.hpp>
#include <vector>
#include <iostream>
#include <boost/graph/max_cardinality_matching.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS> Graph;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::out_edge_iterator OutEdgeIt;
const Vertex NULL_VERTEX = graph_traits<Graph>::null_vertex();

void DFS(int u, Graph &G, vector<bool> &visited, vector<Vertex> &mate) {
	OutEdgeIt ebeg, eend;
	visited[u] = true;
	for (tie(ebeg, eend) = out_edges(u, G); ebeg != eend; ++ebeg) {
		const int v = target(*ebeg, G);
		//  v not vis.  && left to right with Non-Matching edges
		//  		   right to left with Matching edges
		if (!visited[v] && (((v == mate[u]) != (u < v)))) {  //if v is not visited, the following must be true: (v is the mate of u and u is greater than v: i.e. we're going from right to left)
			DFS(v, G, visited, mate);                        //or if v is not the mate of u, u must be smaller than v (going left to right). In either of this cases, do DFS from the thing you found.
		}
	}
}

int main()
{
	int numTestCases;
	int numGround;
	int numSats;
	int numLinks;
	int ground;
	int sat;
	Graph g;
	cin >> numTestCases;
	for (int i = 0; i < numTestCases; i++){

		g.clear();
		cin >> numGround >> numSats >> numLinks;

		if (numSats == 0 || numGround == 0 || numLinks == 0){ //if one of these entities are zero, there is no link.
			cout << 0 << " " << 0;
			cout << endl;
			continue;
		}

		else if (numSats == 1){
			cout << 0 << " " << 1 <<endl;
			cout << 0;
			cout << endl;
			continue;
		}

		else if (numGround == 1){
			cout << 1 << " " << 0 <<endl;
			cout << 0;
			cout << endl;
			continue;
		}
		
		for (int j = 0; j < numLinks; j++){   
			cin >> ground >> sat;
			sat = sat + numGround; //Make sure the satellites start the index after the ground stations. we take care of this later.
			add_edge(ground, sat, g);
		}

		vector<graph_traits<Graph>::vertex_descriptor> mate(numGround + numSats);

		bool success = checked_edmonds_maximum_cardinality_matching(g, &mate[0]);
		assert(success);

		// starting points for VC
		vector<int> startpoints;
		for (int i = 0; i < numGround+numSats; ++i) { //for all vertices..
			if (mate[i] == NULL_VERTEX && i < numGround) { //if unmatched, push back into DFS startpoints.
				startpoints.push_back(i);
			}
		}

		// run depth first visit
		vector<bool> visited(numGround + numSats);
		for (int i = 0; i < startpoints.size(); ++i) {
			DFS(startpoints[i], g, visited, mate);
		}

		vector<int> groundIndexSet;
		vector<int> satIndexSet;
		for (int i = 0; i < numGround+numSats; ++i) {
			if (visited[i] == false && i < numGround) {
				groundIndexSet.push_back(i);
			}
			else if (visited[i] == true && i >= numGround){
				satIndexSet.push_back(i - numGround);
			}
		}

		cout << groundIndexSet.size() << " " << satIndexSet.size()<<endl;

		for (size_t k = 0; k < groundIndexSet.size(); k++){
			cout << groundIndexSet.at(k) << " ";
		}
		for (size_t k = 0; k < satIndexSet.size(); k++){
			cout << satIndexSet.at(k) << " ";
		}
		cout << endl;
	}

	return 0;
}
