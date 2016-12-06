#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/nearest_neighbor_delaunay_2.h>
#include <vector>
#include <iostream>
#include <math.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator Edge_iterator;
typedef Triangulation::Vertex_iterator Vertex_iterator;
typedef K::Segment_2 S;
typedef K::Point_2 P;
typedef Triangulation::Edge Edge;
const double maximum=DBL_MAX;

using namespace std;

int main()
{

  ios_base::sync_with_stdio(false);

  int numTests;
  long int numPlanes, distance; //planes refer to airplanes
  int x, y;
  cin >> numTests;

  for (int i=0; i<numTests; i++){

	cin >> numPlanes;
	cin >> distance;
  	vector<K::Point_2> pts;
  	pts.reserve(numPlanes);
	
	for (int j=0; j<numPlanes; j++){
		cin >> x >> y;
		K::Point_2 p(x,y);
		pts.push_back(p);
	}

  	// construct triangulation
  	Triangulation t;
  	t.insert(pts.begin(), pts.end());
	int numDanger=0;

  	for(Vertex_iterator v = t.finite_vertices_begin(); v != t.finite_vertices_end(); ++v){ //for all vertices...

			Triangulation::Vertex_handle w=CGAL::nearest_neighbor(t,v); //get nearest neighbor, find distance to him
			S theSegment=S(w->point(), v->point());	
			if(theSegment.squared_length()<distance*distance){
				numDanger++;			
				continue;
			}
	}

	cout << numDanger << endl;

  }
 
return 0;
}
