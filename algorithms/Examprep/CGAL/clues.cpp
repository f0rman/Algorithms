#include <vector>
#include <map>
#include <iostream>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/bipartite.hpp>
#include <boost/graph/connected_components.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Finite_faces_iterator Face_iterator;
typedef Triangulation::Finite_edges_iterator Edge_iterator;
typedef Triangulation::Finite_vertices_iterator Vertex_iterator;
typedef K::Segment_2 Segment;
using namespace std;
using namespace boost;
typedef adjacency_list<vecS, vecS, undirectedS> Graph;
typedef graph_traits <Graph> traits;
typename traits::vertex_iterator vertex_iter, vertex_end;
const double maximum=DBL_MAX;

int main(){

ios_base::sync_with_stdio(false);

int T;
cin >> T;

while (T--){

	long int numStations, numClues, r;
	cin >> numStations >> numClues >> r;

	map< K::Point_2, long int> stations;
	map<long int, K::Point_2 > stationPointMap; //flipped map
	vector <K::Point_2> stationsVec(numStations);
	vector< pair<K::Point_2, K::Point_2> > clues(numClues);
	vector<char> answers;

	for (int i=0; i<numStations; i++){
		long int x, y;
		cin >> x >> y;
		K::Point_2 point=K::Point_2(x,y);
		stations[point]=i;
		stationPointMap[i]=point;
		stationsVec.at(i)=point;
	}

	for (int i=0; i<numClues; i++){
		long int x1, y1;
		long int x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		K::Point_2 point1=K::Point_2(x1,y1);
		K::Point_2 point2=K::Point_2(x2,y2);
		clues.at(i)=make_pair(point1, point2);
	}

	// construct triangulation
	Triangulation t;
	t.insert(stationsVec.begin(), stationsVec.end());

	Graph g(numStations);

	//iterate over all edges in Triangulation
	for (Edge_iterator e=t.finite_edges_begin(); e!=t.finite_edges_end(); ++e){
		Segment s=t.segment(e); //** notes below
		if (s.squared_length()<=r*r){
			add_edge(stations[s.source()],stations[s.target()], g);
		}
	}

	if (is_bipartite(g)){ //bipartiteness possible but not necessarily since an edge might be missed by Delaunay

		//there is one more thing to check. Check monochromatic edges!!
		typedef std::vector <default_color_type> partition_t; //a vector holding default colors is of type partition_t
		typedef property_map<Graph, vertex_index_t>::type index_map_t; //index-map for all vertices. Use this kind of index_map
		typedef iterator_property_map <partition_t::iterator, index_map_t> partition_map_t;
		partition_t partition (num_vertices (g)); //partition is a vector holding colors with size num_Vertices
		partition_map_t partition_map (partition.begin (), get (vertex_index, g));
		is_bipartite (g, get (vertex_index, g), partition_map);

		vector<K::Point_2> white_points;
		vector<K::Point_2> black_points;
	        for (boost::tie (vertex_iter, vertex_end) = vertices (g); vertex_iter != vertex_end; ++vertex_iter)
	    	{
		get (partition_map, *vertex_iter) == 
		color_traits <default_color_type>::white () ? white_points.push_back(stationPointMap[*vertex_iter])
		: black_points.push_back(stationPointMap[*vertex_iter]);
	        }

		// construct triangulations
		Triangulation whiteT;
		whiteT.insert(white_points.begin(), white_points.end());
		Triangulation blackT;
		blackT.insert(black_points.begin(), black_points.end());

		//find shortest monochromatic edge
		K::FT minDist=maximum;
		for (Edge_iterator e = whiteT.finite_edges_begin(); e != whiteT.finite_edges_end(); ++e){ 
			if (whiteT.segment(e).squared_length()<minDist){
				minDist=whiteT.segment(e).squared_length();
			}
		}

		for (Edge_iterator e = blackT.finite_edges_begin(); e != blackT.finite_edges_end(); ++e){ 
			if (blackT.segment(e).squared_length()<minDist){
				minDist=blackT.segment(e).squared_length();
			}
		}

		if (minDist<r*r){ //communication impossible in this network! Graph not bipartite!!
			for (int j=0; j<numClues; j++){
			cout << "n";
			}
			cout << endl;
			continue;
		}

		//communication possible. holmes and wattson must now connect to the same component

		std::vector<int> component(numStations);
   		int num = connected_components(g, &component[0]);

		for (int c=0; c<numClues; c++){ //check nearest vertex in Delaunay.

			K::Point_2 holmes=clues.at(c).first;
			K::Point_2 wattson=clues.at(c).second;

			if (CGAL::squared_distance(holmes,wattson)<=r*r){
				answers.push_back('y');
			}

			else if (CGAL::squared_distance(holmes,t.nearest_vertex(holmes)->point())<=r*r && 
				 CGAL::squared_distance(wattson,t.nearest_vertex(wattson)->point())<=r*r
				 && component[stations[t.nearest_vertex(holmes)->point()]]
				 ==component[stations[t.nearest_vertex(wattson)->point()]]){ //if all this is true...

				answers.push_back('y');
			}
			else answers.push_back('n'); // ' ' for char not " "
		}

		for (int j=0; j<numClues; j++){
			cout << answers.at(j);
		}
	}

	else { //communication impossible in this network! not bipartite!
	
		for (int j=0; j<numClues; j++){
			cout << "n";
		}
	}

	cout << endl;
}

return 0;
}s
