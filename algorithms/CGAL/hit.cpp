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

int main()
{
  ios_base::sync_with_stdio (false);
  int numberOfSegments;
  double startX, startY, anPointX, anPointY, r, s, t, u;
  cin>>numberOfSegments;

  while (numberOfSegments!=0){
  cin>>startX>>startY>>anPointX>>anPointY;
  P start(startX, startY), anPoint(anPointX,anPointY);
  R l(start,anPoint); //the ray
  bool flag=false;
  for (int i=0; i<numberOfSegments; i++){

  cin>>r>>s>>t>>u;
  P startOfSegment(r,s);
  P endOfSegment(t, u);
  S segment(startOfSegment, endOfSegment);
  
  if (flag==false && CGAL::do_intersect(l,segment)) {
	flag=true;
      } 
  }

  cin>>numberOfSegments;

  if (flag==true){
  cout << "yes" <<endl;
  }

  else {
  cout << "no" << endl;
  }
  
  }
return 0;
}
