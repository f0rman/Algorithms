// Maximize It
#include <iostream>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>

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

int p, a, b;
cin >> p;

while (p!=0){

	cin >> a >> b;

	// by default, we have a nonnegative LP with Ax <= b
	Program qp (CGAL::SMALLER,true,0,false,0);

	if (p==1){

		// now set the non-default entries
		const int X= 0;
		const int Y= 1;
		qp.set_a(X,0,1); qp.set_a(Y,0,1); qp.set_b(0,4); // x + y <= 4
		qp.set_a(X, 1, 4); qp.set_a(Y,1,2); qp.set_b(1, a*b); 
		qp.set_a(X, 2, -1); qp.set_a(Y,2,1); qp.set_b(2, 1); // -x+y <= 1
		qp.set_c(Y, -b); // -by
		qp.set_d(X, X, 2*a); // ax^2
	}

	else {
		// now set the non-default entries
		const int X= 0;
		const int Y= 1;
		const int Z= 2; //note Z=Z^2
		qp.set_a(X,0,1); qp.set_a(Y,0,1); qp.set_b(0,4); // x + y <= 4
		qp.set_a(X, 1, 4); qp.set_a(Y,1,2); qp.set_a(Z,1,-1); qp.set_b(1, a*b); 
		qp.set_a(X, 2, -1); qp.set_a(Y,2,1); qp.set_b(2, 1); // -x+y <= 1
		qp.set_c(Y, -b); // -by
		qp.set_d(X, X, 2*a); // ax^2
		qp.set_d(Y, Y, 0);
		qp.set_d(Z, Z, 2);

	}

	// solve the program, using ET as the exact type
	  Solution s = CGAL::solve_nonnegative_quadratic_program(qp, ET());
	  assert (s.solves_quadratic_program(qp));

	  // output
	  if (s.status() == CGAL::QP_INFEASIBLE) {
	  	std::cout << "no\n";
	  }
	  else if (s.status() == CGAL::QP_UNBOUNDED){
	  	std::cout << "unbounded\n";
	  }
	  else {
		  assert (s.status() == CGAL::QP_OPTIMAL);

		  if (p==1){
		    	std::cout << (int)(floor_to_double(s.objective_value()*-1)) << "\n";
		  }
		  else {
			std::cout << (int)ceil_to_double(s.objective_value()) << "\n";
		  }	
	  }

	cin >> p;
}
  return 0;
}
