#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <vector>
#include <iostream>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
const double maximum=DBL_MAX;

using namespace std;

double ceil_to_double(const K::FT& x){

	double a = ceil(CGAL::to_double(x));
	while(a > x) a -=1;	
	while(a < x) a +=1;
	return a;
}

int main()
{

  ios_base::sync_with_stdio(false);

  long int numRests, numPossLocs;
  double x, y;
  cin >> numRests;

  while (numRests!=0){

  	vector<K::Point_2> pts;
  	pts.reserve(numRests);
	
	for (int j=0; j<numRests; j++){
		cin >> x >> y;
		K::Point_2 p(x,y);
		pts.push_back(p);
	}

  	// construct triangulation
  	Triangulation t;
  	t.insert(pts.begin(), pts.end());

	cin >> numPossLocs;

	for (int i=0; i<numPossLocs; i++){ //find where we are in the delaunay triangulation
		
		cin >> x >> y;
		K::Point_2 p(x,y);
		Triangulation::Vertex_handle v1=t.nearest_vertex(p, t.finite_faces_begin());
		K::FT d = CGAL::squared_distance(v1->point(),p);
  		std::cout << (long long) d << std::endl;
	}

	cin >> numRests;
	
  }
 
return 0;
}
