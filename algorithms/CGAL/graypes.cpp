#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <vector>
#include <iostream>
#include <math.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator Edge_iterator;
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

  long int numGraypes;
  double x, y;
  cin >> numGraypes;

  while (numGraypes!=0){

  	vector<K::Point_2> pts;
  	pts.reserve(numGraypes);
	
	for (int j=0; j<numGraypes; j++){
		cin >> x >> y;
		K::Point_2 p(x,y);
		pts.push_back(p);
	}

  	// construct triangulation
  	Triangulation t;
  	t.insert(pts.begin(), pts.end());
	
	K::FT minDist=maximum;
  	for (Edge_iterator e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e){ //find edge with shortest length.
  		if (t.segment(e).squared_length()<minDist){
			minDist=t.segment(e).squared_length();
		}
  	}

	cout << (long long) ceil_to_double(sqrt(minDist*0.25)*100) << endl;
	cin >> numGraypes;
	
  }
 
return 0;
}
