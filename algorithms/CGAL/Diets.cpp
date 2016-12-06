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

int numFoods, numNutrients;
cin >> numNutrients >> numFoods;

while (numNutrients!=0 && numFoods!=0){

	// by default, we have a nonnegative LP with Ax <= b
	Program qp (CGAL::SMALLER,true,0,false,0);

	long int minIntake, maxIntake, price;
	for (int i=0; i<numNutrients; i++){
		cin >> minIntake >> maxIntake;
		qp.set_b(i,minIntake*-1);
		qp.set_b(i+numNutrients,maxIntake);
	}

	long int nutrientVal;
	for (int i=0; i<numFoods; i++){
		cin >> price;
		qp.set_c(i,price);
		for (int j=0; j<numNutrients; j++){
			cin >> nutrientVal;
			qp.set_a(i,j,nutrientVal*-1);
			qp.set_a(i,j+numNutrients,nutrientVal);
		}
	}		
		
	// solve the program, using ET as the exact type
  	Solution s = CGAL::solve_linear_program(qp, ET());
  	assert (s.solves_linear_program(qp));

	  // output
	  if (s.status() == CGAL::QP_INFEASIBLE) {
	  	std::cout << "No such diet.\n";
	  }
	  else {
		  assert (s.status() == CGAL::QP_OPTIMAL);
		  std::cout << (int)(floor_to_double(s.objective_value())) << "\n";
	  }

	cin >> numNutrients >> numFoods;
}
  return 0;
}
