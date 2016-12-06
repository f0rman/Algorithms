#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/nearest_neighbor_delaunay_2.h>
#include <vector>
#include <iostream>
#include <math.h>
#include <map>
#include <algorithm>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator Edge_iterator;
typedef Triangulation::Vertex_iterator Vertex_iterator;
typedef K::Segment_2 S;
typedef K::Point_2 P;
typedef Triangulation::Edge Edge;
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

  long int numBacteria;
  double startXDish, endXDish, startYDish, endYDish;
  double x, y;
  cin >> numBacteria;

  while (numBacteria!=0){

	cin >> startXDish >> startYDish >> endXDish >> endYDish;

	//create the ends of the dish as segments.
	P p1(startXDish,startYDish);
	P p2(endXDish, startYDish);
	P p3(startXDish,endYDish);
	P p4(endXDish,endYDish);
	S seg1=S(p1, p2);
	S seg2=S(p1, p3);
	S seg3=S(p3, p4);
	S seg4=S(p2, p4);
			
  	vector<K::Point_2> pts;
  	pts.reserve(numBacteria);
	
	for (int j=0; j<numBacteria; j++){
		cin >> x >> y;
		K::Point_2 p(x,y);
		pts.push_back(p);
	}

  	// construct triangulation
  	Triangulation t;
  	t.insert(pts.begin(), pts.end());

	//for 50 % you need to find edges counting from the shortest one and up such that more than 50 % of the vertices
	//are covered. The answer would involve the length of the longest edge in this subsets.

	vector<K::FT> distances;

	if (numBacteria==1){

		Vertex_iterator v = t.finite_vertices_begin();
		K::FT minD=CGAL::squared_distance(v->point(),seg1); //find closest neighbour, tray or bacteria.
		if (CGAL::squared_distance(v->point(),seg2)<minD){minD=CGAL::squared_distance(v->point(),seg2);}
		if (CGAL::squared_distance(v->point(),seg3)<minD){minD=CGAL::squared_distance(v->point(),seg3);}
		if (CGAL::squared_distance(v->point(),seg4)<minD){minD=CGAL::squared_distance(v->point(),seg4);}

		if (minD>0.25){
		cout << (long long) ceil_to_double(sqrt(sqrt(minD)-0.5)) << " ";
		cout << (long long) ceil_to_double(sqrt(sqrt(minD)-0.5)) << " ";
		cout << (long long) ceil_to_double(sqrt(sqrt(minD)-0.5)) << endl;
		}
		else cout << 0 << " "<< 0 << " "<< 0 << endl;

	}

	else{
		for(Vertex_iterator v = t.finite_vertices_begin(); v != t.finite_vertices_end(); ++v){ //for all vertices...

			Triangulation::Vertex_handle w=CGAL::nearest_neighbor(t,v); //get nearest neighbor, find distance to him
			S theSegment=S(w->point(), v->point());	//and distance to nearest tray edge. minimum of these quantities will kill him.

			K::FT minD=CGAL::squared_distance(v->point(),seg1); //find closest neighbour, tray or bacteria.
			if (CGAL::squared_distance(v->point(),seg2)<minD){minD=CGAL::squared_distance(v->point(),seg2);}
			if (CGAL::squared_distance(v->point(),seg3)<minD){minD=CGAL::squared_distance(v->point(),seg3);}
			if (CGAL::squared_distance(v->point(),seg4)<minD){minD=CGAL::squared_distance(v->point(),seg4);}
			if (theSegment.squared_length()*0.25 < minD) {minD=theSegment.squared_length()*0.25;}
			if (minD>0.25){distances.push_back(minD);}
			else distances.push_back(0); //we put 0 if the bacteria is dead immediately.			    
		}

		sort(distances.begin(), distances.end());

		if (distances.front()!=0){
			cout << (long long) ceil_to_double(sqrt(sqrt(distances.front())-0.5)) << " ";
		}
		else cout << 0 << " ";

		int median=numBacteria/2;
		if (distances.at(median)!=0){
			cout << (long long) ceil_to_double(sqrt(sqrt(distances.at(median))-0.5)) << " ";
		}
		else cout << 0 << " ";

		if (distances.at(numBacteria-1)!=0){
			cout << (long long) ceil_to_double(sqrt(sqrt(distances.at(numBacteria-1))-0.5)) << endl;
		}
		else cout << 0 << endl;

	}
 
	cin >> numBacteria;
	
  }
 
return 0;
}
