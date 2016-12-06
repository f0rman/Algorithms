#include <vector>
#include <iostream>
#include <stdexcept>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <queue>
#include <map>
#include <CGAL/Object.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Face_iterator Face_iterator;
typedef Triangulation::Face_handle FaceHandle;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;
typedef K::Line_2 L;
using namespace std;

int main(){

	ios::sync_with_stdio(false);
	long int n, m;
	double x,y,d;
	cin >> n;

	while (n!=0){

		vector<K::Point_2> pts;
  		pts.reserve(n);
	
		for (int j=0; j<n; j++){
			cin >> x >> y;
			K::Point_2 p(x,y);
			pts.push_back(p);
		}

		// construct triangulation
  		Triangulation t;
  		t.insert(pts.begin(), pts.end());

		cin >> m;
		for (int i=0; i<m; ++i){

			cin >> x >> y >> d;
			K::Point_2 queryPt(x,y);

			if (CGAL::squared_distance(t.nearest_vertex(queryPt)->point(),queryPt)<d){ 
				cout << "n";            //make a simple check if your starting point is feasible.
				continue;
			}			

			//which face in the delaunay triangulation are we in??
			Triangulation::Face_handle start=t.locate(queryPt);
			if (t.is_infinite(start)){
				cout << "y";
				continue;
			}
			else { //we're in a finite face

				queue<Triangulation::Face_handle> q;
				map<Triangulation::Face_handle, bool> visited; //which faces have been visited
				q.push(start); //push the face onto the queue.
				visited[start]=true;
				bool escapePossible=false;

				while (!q.empty()){

					//K::Point_2 voronoiPt=q.front();
					Triangulation::Face_handle f=q.front();
					q.pop();
					//f=faceMap[voronoiPt]; //get which face you're in.
					
					for (int i=0; i<3; ++i){ //for all neighbours of this face
						
						Triangulation::Edge e=make_pair(f,i);
						if (t.segment(e).squared_length()*0.25 >= d){ //can you go through the edge in the triangle?
							
							//Get the neighbouring face
							FaceHandle neighbour = f->neighbor(i);
							if (t.is_infinite(neighbour)) {
								cout << "y";
								escapePossible=true;
	    							break;
							}
							else if (visited[neighbour]==false){
								q.push(neighbour);
								visited[neighbour]=true;
							}
						}
					} //end of for all edges of this face
				if (escapePossible){break;}
				} //end of while

				if (!escapePossible){cout << "n";};
			
			} //end of else finite face
		} //end of for m
		cout << endl;
		cin >> n;
	} //end of while n!=0
			
	return 0;
}
