#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <iostream>

// typedefs
typedef  CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
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
  long int n;
  double x, y;
  cin>>n;

  while (n!=0){
 	vector<K::Point_2> P(n);
	for (int i=0; i<n; ++i){  //scan all pts.
	    cin >> x >> y;
	    P.at(i) = K::Point_2(x, y);
	}
  
  Min_circle mc(P.begin(), P.begin()+n, true);
  CGAL::Min_circle_2< Traits >::Support_point_iterator supp=mc.support_points_begin();
  K::FT minradius=maximum;
  
  while (supp!=mc.support_points_end()){
  
	  vector<K::Point_2> copyP=P;
	  K::Point_2 removept=*supp;
	  std::vector<K::Point_2>::iterator it;
	  it=std::find(copyP.begin(),copyP.end(), removept); //use find, and remove pt. from vector.
	  copyP.erase(it);
	   
	  Min_circle mc2(copyP.begin(), copyP.end(), true); //make new circle.
	  Traits::Circle c = mc2.circle();
          K::FT d = c.squared_radius();
          if (d<minradius){minradius=d;}
	  supp++;
  }
 	cin >> n;
	long long radius = (long long)(ceil_to_double(sqrt(minradius)));
	std::cout << radius << std::endl;
  }

  return 0;
}
