//Stamps
#include <iostream>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <vector>
#include <iostream>
#include <math.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
const double maximum=DBL_MAX;

// choose exact integral type   //DO NOT USE Gmpz here. only CGAL/MP_Float works if you're working with doubles!!!!!
//#ifdef CGAL_USE_GMP
//#include <CGAL/Gmpz.h>
//typedef CGAL::Gmpz ET;
//#else
#include <CGAL/MP_Float.h>
typedef CGAL::MP_Float ET;
//#endif

// program and solution types
typedef CGAL::Quadratic_program<double> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef K::Segment_2 S;
using namespace std;

double floor_to_double(const CGAL::Quotient<ET> &x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

double ceil_to_double(const CGAL::Quotient<ET> &x){

	double a = ceil(CGAL::to_double(x));
	while(a > x) a -=1;	
	while(a < x) a +=1;
	return a;
}

const double pUpLim=4096;
const double pLowLim=1;


int main() {

	ios_base::sync_with_stdio(false);

	int numTests, numLamps, numStamps, numWalls;
	cin >> numTests;

	for (int i=0; i<numTests; i++){

		cin >> numLamps >> numStamps >> numWalls;

		double x, y;
		double intensity;
		double startX, startY, endX, endY;

		vector<K::Point_2> lampPos;
		vector<K::Point_2> stampPos;
		vector<K::FT> maxIntensity(numStamps); 
	  	lampPos.reserve(numLamps);
		stampPos.reserve(numStamps);
		
		// by default, we have a nonnegative LP with Ax <= b
		Program qp (CGAL::SMALLER,true,0,false,0);
	
		for (int j=0; j<numLamps; j++){
			cin >> x >> y;
			K::Point_2 p(x,y);
			lampPos.push_back(p);
			qp.set_u(j, true, 4096); //these upper and lower bound constraints means you should use linear solver not nonnegative
			qp.set_l(j, true, 1);
		}

		for (int j=0; j<numStamps; j++){
			cin >> x >> y >> intensity;
			K::Point_2 p(x,y);
			maxIntensity.at(j)=intensity;
			stampPos.push_back(p);
		}

		vector<S> walls(numWalls);
		for (int j=0; j<numWalls; j++){
			cin >> startX >> startY >> endX >> endY;
			K::Point_2 p1(startX,startY);
			K::Point_2 p2(endX, endY);
			S segment(p1,p2);
			walls.at(j)=segment;
		}
	
		for (int j=0; j<numStamps; j++){

			K::Point_2 theStamp=stampPos.at(j);		
			
			for (int k=0; k<numLamps; k++){
				K::Point_2 theLamp=lampPos.at(k);
				S lampStampSeg(theStamp, theLamp);

				bool intersect = false;

				for (int w=0; w<numWalls; w++) {
				
					if (CGAL::do_intersect(lampStampSeg, walls.at(w))) {
						intersect = true;
						break;
					}
				}

				if (intersect==false) {
					K::FT sqRadius=CGAL::squared_distance (theStamp, theLamp); 
					qp.set_a(k,j*2, 1.0/CGAL::to_double(sqRadius));
					qp.set_a(k, j*2+1, 1.0/CGAL::to_double(sqRadius*-1));
				}	
			}

			qp.set_b(2*j,maxIntensity.at(j));
			qp.set_b(2*j+1,-1.0);
		}	

		/*for (int j=0; j<numLamps; j++){   //DON'T DO THIS. IF YOUR GONNA SET VARIABLE CONSTRAINTS, DO IT WITH SET_U
			qp.set_a(j,2*numStamps+j,1.0);
			qp.set_b(2*numStamps+j,pUpLim);
			qp.set_a(j,numLamps+2*numStamps+j,-1.0);
			qp.set_b(numLamps+2*numStamps+j,pLowLim*-1);
		}*/
		
		// solve the program, using ET as the exact type
		  Solution s = CGAL::solve_linear_program(qp, ET());
		  assert (s.solves_linear_program(qp));

		  // output
		  if (s.status() == CGAL::QP_INFEASIBLE) {
		  	std::cout << "no\n";
		  }
		  else {
		  	std::cout << "yes\n";
		  }

	}
  return 0;

}
