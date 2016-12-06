#include <boost/config.hpp>
#include <iostream>
#include <fstream>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/property_map.hpp>

using namespace boost;
using namespace std;
long int maximum=1100000000;

int main()
{
  ios_base::sync_with_stdio(false);
  typedef adjacency_list < listS, vecS, directedS,
    no_property, property < edge_weight_t, int > > graph_t;
  typedef graph_traits < graph_t >::vertex_descriptor vertex_descriptor;
  typedef std::pair<int, int> Edge;

  int numTest;
  cin >> numTest;
  int numVertices, numEdges;
  int source, target;
  int edgeStart, edgeEnd, weight;

  for (int i=0; i<numTest; i++){

	cin >> numVertices >> numEdges;
	graph_t g(4*numVertices);
	cin >> source >> target;
	for (int j=0; j<numEdges; j++){
		cin >> edgeStart >> edgeEnd >> weight;
		if (weight%2==0){ //if weight is even...
		add_edge(edgeStart, edgeEnd+2*numVertices, weight, g);
		add_edge(edgeStart+numVertices, edgeEnd+3*numVertices, weight, g);
		add_edge(edgeStart+2*numVertices, edgeEnd, weight, g);
		add_edge(edgeStart+3*numVertices, edgeEnd+numVertices, weight, g);
		}
		else { //if weight is odd
		add_edge(edgeStart, edgeEnd+3*numVertices, weight, g);
		add_edge(edgeStart+numVertices, edgeEnd+2*numVertices, weight, g);
		add_edge(edgeStart+2*numVertices, edgeEnd+numVertices, weight, g);
		add_edge(edgeStart+3*numVertices, edgeEnd, weight, g);
		}
	}

  property_map<graph_t, edge_weight_t>::type weightmap = get(edge_weight, g);
  std::vector<vertex_descriptor> p(num_vertices(g));
  std::vector<int> d(num_vertices(g));

  dijkstra_shortest_paths(g, source,
			  predecessor_map(boost::make_iterator_property_map(p.begin(), get(boost::vertex_index, g))).
                          distance_map(boost::make_iterator_property_map(d.begin(), get(boost::vertex_index, g))));

  if (d[target+3*numVertices]>maximum){
	cout << "no" << endl;
  }
  else {
  std::cout << d[target+3*numVertices] << endl;
  }
	
  }
  
  return 0;
}
