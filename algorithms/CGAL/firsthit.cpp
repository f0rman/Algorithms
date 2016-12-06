#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <iostream>
#include <stdexcept>
#include <vector>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;
using namespace std;
using namespace CGAL;
const double maximum=DBL_MAX;

double floor_to_double(const K::FT& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

int main()
{
  ios_base::sync_with_stdio (false);
  int numberOfSegments;
  double startX, startY, anPointX, anPointY, r, s, t, u;
  cin>>numberOfSegments;

  while (numberOfSegments!=0){
	  P closestPoint(maximum, maximum); //initialize closest point to something that's really far away.
	  cin>>startX>>startY>>anPointX>>anPointY;
	  P start(startX, startY), anPoint(anPointX,anPointY);
	  R l(start,anPoint); //the ray
	  bool flag=false;

	  for (int i=0; i<numberOfSegments; ++i){

	  cin>>r>>s>>t>>u;
	  P startOfSegment(r,s);
	  P endOfSegment(t, u);
	  S segment(startOfSegment, endOfSegment); //read segment and create it.
  
		 if (CGAL::do_intersect(l,segment)) {  //if ray intersects with segment...
			auto o = CGAL::intersection(l, segment);
			if (const P* op = boost::get<P>(&*o)){  //if they intersect in a point, compare distance.
	    			if(has_smaller_distance_to_point (start, *op, closestPoint)){
				   closestPoint=*op;
		                }
			}
			else if (const S* os = boost::get<S>(&*o)) {
				if(has_smaller_distance_to_point (start, os->source(), closestPoint)){
					closestPoint=os->source();
		       		}
				if(has_smaller_distance_to_point (start, os->target(), closestPoint)){
					closestPoint=os->target();
		        	}
			}
			else {    // how could this be? -> error
				throw std::runtime_error("strange segment intersection");
			}
			flag=true;
		}
  	}

  cin>>numberOfSegments;

  if (flag==true){
  cout << (long long)(floor_to_double(closestPoint.x())) << " "<< (long long)(floor_to_double(closestPoint.y())) << endl;
  }

  else {
  cout << "no" << endl;
  }
  
  }
return 0;
}
