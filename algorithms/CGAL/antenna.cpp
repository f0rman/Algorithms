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
 	K::Point_2 P[n];
	for (int i=0; i<n; ++i){  //scan all pts.
	    cin >> x >> y;
	    P[i] = K::Point_2(x, y);
	}
  
  Min_circle mc(P, P+n, true);
  Traits::Circle c = mc.circle();
  long radius = ceil_to_double(sqrt(c.squared_radius()));  //do not use the intermediate field type to throw into ceil_to_double unless you 								   //have to. Cout longs if possible.
  cin >> n;
  std::cout << radius << std::endl;

  }
 
  return 0;
}
