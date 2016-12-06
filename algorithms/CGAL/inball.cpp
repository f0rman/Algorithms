// Inball
#include <iostream>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <math.h>

// choose exact integral type
#ifdef CGAL_USE_GMP
#include <CGAL/Gmpz.h>
typedef CGAL::Gmpz ET;
#else
#include <CGAL/MP_Float.h>
typedef CGAL::MP_Float ET;
#endif

// program and solution types
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
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

main() {

ios_base::sync_with_stdio(false);

int numPlanes, numDims, coeff, b;
cin >> numPlanes;

while (numPlanes!=0){

	cin >> numDims;

	// by default, we have a nonnegative LP with Ax <= b
	Program qp (CGAL::SMALLER,true,0,false,0);

	for (int i=0; i<numPlanes; i++){
		double sqdistsum=0;
		for (int j=0; j<numDims; j++){
			cin >> coeff;
			sqdistsum+=coeff*coeff;
			qp.set_a(j,i,coeff*-1);
			qp.set_a(j+numDims,i, coeff);
		}
		qp.set_a(2*numDims, i, (int)sqrt(sqdistsum));
		cin >> b;
		qp.set_b(i,b);
	}

	qp.set_c(2*numDims, -1); //r has the coefficient place numDims.

	// solve the program, using ET as the exact type
  	Solution s = CGAL::solve_linear_program(qp, ET());
  	assert (s.solves_linear_program(qp));

	  // output
	  if (s.status() == CGAL::QP_INFEASIBLE) {
	  	std::cout << "none\n";
	  }
	  else if (s.status() == CGAL::QP_UNBOUNDED){
	  	std::cout << "inf\n";
	  }
	  else {
		  assert (s.status() == CGAL::QP_OPTIMAL);
		  std::cout << (long int)(floor_to_double(s.objective_value()*-1)) << "\n";
	  }

	cin >> numPlanes;
}
  return 0;
}
