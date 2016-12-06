#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <iostream>
#include <functional>   // std::greater
#include <algorithm>
#include <vector>

// typedefs
typedef  CGAL::Exact_predicates_exact_constructions_kernel K;
typedef  CGAL::Min_circle_2_traits_2<K>  Traits;
typedef  CGAL::Min_circle_2<Traits>      Min_circle;
using namespace std;
using namespace CGAL;
const double maximum=DBL_MAX;

double ceil_to_double(const K::FT& x){
	double a = ceil(CGAL::to_double(x));
	while(a > x) a -=1;
	while(a < x) a +=1;
	return a;
}

int main()
{
  ios_base::sync_with_stdio (false);
  int numTests;
  long int n;
  double x, y;
  cin>>numTests;

  vector<long long int> outputs; 
  for (int i=0; i<numTests; i++){

	cin >> n;
	cin >> x >> y;
	K::Point_2 firstAnt = K::Point_2(x, y);
 	vector<K::Point_2> P(n-1);
	vector< pair<K::FT, int> > distances(n-1);

	for (int j=0; j<n-1; ++j){  //scan all pts after first one.
	    cin >> x >> y;
	    P[j] = K::Point_2(x, y);
	    distances.at(j)=make_pair(CGAL::squared_distance(firstAnt,P[j]), j);
	}

	if (n<3){cout << 0 << endl; continue;}

	std::sort(distances.rbegin(), distances.rend()); //sort distances in descending order.
  
	vector<K::Point_2> pointsInCircle;
	K::FT distToFarthest=distances.front().first; //distances to farthest away point.
	pointsInCircle.push_back(P[distances.front().second]); //push back farthest away point
	Min_circle mc(pointsInCircle.begin(), pointsInCircle.end(), true);
	Traits::Circle c = mc.circle();
	int count=1;
	K::FT prevMinRadius=0;
	
	//c.squared_radius()=0 in the beginning
	while (distToFarthest>c.squared_radius() && count<n){ //biggest enclosing circle has n-1 pts.
	
		prevMinRadius=c.squared_radius();
		distToFarthest=distances.at(count).first;
		K::Point_2 ptToInsert=P[distances.at(count).second];
		pointsInCircle.push_back(ptToInsert);
		mc.insert(ptToInsert);
		c = mc.circle();
		count++;
	  
  	}

  if (prevMinRadius>distToFarthest){
	cout << ((long long int)ceil_to_double(prevMinRadius)) << endl;
 
  }

  else cout << ((long long int)ceil_to_double(distToFarthest)) << endl;

  }

  return 0;
}
