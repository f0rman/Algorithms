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

int numAssets, numPeople;
cin >> numAssets >> numPeople;

while (numAssets!=0 && numPeople!=0){

	// by default, we have a nonnegative LP with Ax <= b
	Program qp (CGAL::SMALLER,true,0,false,0);

	long int cost, expret;
	for (int i=0; i<numAssets; i++){
		cin >> cost >> expret;
		qp.set_a(i,0,cost);
		qp.set_a(i,1,expret*-1);
	}

	long int var;
	for (int i=0; i<numAssets; i++){
		for (int j=0; j<numAssets; j++){
			// we need to specify the entries of 2D, on and below the diagonal
			cin >> var;
			qp.set_d(i, j, 2*var); 
		}
	}

	long int C, R, V;

	for (int i=0; i<numPeople; i++){
		cin >> C >> R >> V;
		qp.set_b(0, C);
		qp.set_b(1, R*-1);
		// solve the program, using ET as the exact type
  		Solution s = CGAL::solve_nonnegative_quadratic_program(qp, ET());
  		assert (s.solves_quadratic_program(qp));
		// output
  		if (s.status() == CGAL::QP_INFEASIBLE || CGAL::to_double(s.objective_value())>V) {
   			 std::cout << "No.\n";
  		} else {
			std::cout << "Yes.\n";
		}
	}		

	cin >> numAssets >> numPeople;
}
  return 0;
}
