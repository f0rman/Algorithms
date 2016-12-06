#include <iostream>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <vector>
#include <boost/math/special_functions/binomial.hpp>
#include <algorithm>
#include <cmath>

#include <CGAL/Gmpz.h>
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<ET> Program; //numbers are huuuuge!!! ----> use gmpz
typedef CGAL::Quadratic_program_solution<ET> Solution;
CGAL::Quadratic_program_options options;
using namespace std;

typedef struct Point{
	int x;
	int y;
	int z;
} Point;

void preCalcPowers(vector< vector<ET> > &xPowH, vector< vector<ET> > &yPowH, vector< vector<ET> > &zPowH, vector< vector<ET> > &xPowT, vector< vector<ET> > &yPowT, vector< vector<ET> > &zPowT, vector<Point> &healthyPts, vector<Point> &tumorPts, int degree){
	
	xPowH.resize(healthyPts.size());
	yPowH.resize(healthyPts.size());
	zPowH.resize(healthyPts.size());
	xPowT.resize(tumorPts.size());
	yPowT.resize(tumorPts.size());
	zPowT.resize(tumorPts.size());

	//initializing the constants
	for (size_t i=0; i<healthyPts.size(); i++){
		xPowH[i].push_back(1);
		yPowH[i].push_back(1);
		zPowH[i].push_back(1);
	}

	for (size_t i=0; i<tumorPts.size(); i++){
		xPowT[i].push_back(1);
		yPowT[i].push_back(1);
		zPowT[i].push_back(1);
	}

	for (int deg=1; deg<=degree; deg++){

		for(size_t i=0; i<healthyPts.size(); i++){
			xPowH[i].push_back(xPowH[i][deg-1]*healthyPts.at(i).x);
			yPowH[i].push_back(yPowH[i][deg-1]*healthyPts.at(i).y);
			zPowH[i].push_back(zPowH[i][deg-1]*healthyPts.at(i).z);
		}

		for(size_t i=0; i<tumorPts.size(); i++){
			xPowT[i].push_back(xPowT[i][deg-1]*tumorPts.at(i).x);
			yPowT[i].push_back(yPowT[i][deg-1]*tumorPts.at(i).y);
			zPowT[i].push_back(zPowT[i][deg-1]*tumorPts.at(i).z);
		}
	}

return;
}

//function for setting coefficients in qp
void setCoeff(Program &qp, vector< vector<ET> > &xPowH, vector< vector<ET> > &yPowH, vector< vector<ET> > &zPowH, vector< vector<ET> > &xPowT, vector< vector<ET> > &yPowT, vector< vector<ET> > &zPowT, int numHealthy, int numTumors, int degree){

	for (int i=0; i<numHealthy; i++){ //each point gives a constraint

		int var=0;
		for (int pDeg=0; pDeg<=degree; pDeg++){ //polynomial degree

			for (int zDeg=0; zDeg<=pDeg; zDeg++){
				int remDeg=pDeg-zDeg;
				for (int yDeg=0; yDeg<=remDeg; yDeg++){
					int xDeg=remDeg-yDeg;
					qp.set_a(var,i,xPowH[i][xDeg]*yPowH[i][yDeg]*zPowH[i][zDeg]);
					var++;
				}
			}
		}
		qp.set_b(i, -1);
	 }

	for (int i=0; i<numTumors; i++){ //each point gives a constraint

		int var=0;
		for (int pDeg=0; pDeg<=degree; pDeg++){ //polynomial degree

			for (int zDeg=0; zDeg<=pDeg; zDeg++){
				int remDeg=pDeg-zDeg;
				for (int yDeg=0; yDeg<=remDeg; yDeg++){
					int xDeg=remDeg-yDeg;
					qp.set_a(var,i+numHealthy,-1*xPowT[i][xDeg]*yPowT[i][yDeg]*zPowT[i][zDeg]);
					var++;
				}
			}
		}
		qp.set_b(i+numHealthy, -1);
	 }

	return;
}

//Lessons learned: 1. USE BLAND'S RULE.
//2. USE CORRECT NUMBER TYPE TO SUPPORT HUGE NUMBERS. GMPZ.
//3. PRECOMPUTE POWERS IN A GOOD WAY. AVOID UNNECESSARY WORK AS MUCH AS YOU CAN.
//4. MAKE SURE YOUR BOUNDS TO THE PROGRAM ARE CORRECT. IF NO VARIABLE BOUNDS, USE FALSE IN PROGRAM DEFINITION.
//5. STRICT INEQUALITIES CAN BE MODELLED BY HAVING A SMALL EPSILON ON THE RIGHT HAND SIDE. IF IT'S A SEPARATION PROBLEM
//AND SCALES DON'T MATTER, THIS EPSILON CAN BE SET TO ONE.

int main() {

ios_base::sync_with_stdio(false);
options.set_pricing_strategy(CGAL::QP_BLAND); //VERY IMPORTANT TO AVOID CYCLYING!!

int numTests;
cin >> numTests;

while (numTests--){

	int numHealthy, numTumors;
	cin >> numHealthy >> numTumors;

	vector<Point> healthyPts(numHealthy);
	vector<Point> tumorPts(numTumors);

	int x, y, z;
	for (int i=0; i<numHealthy; i++){
		cin >> x >> y >> z;
		Point point;
		point.x=x;
		point.y=y;
		point.z=z;
		healthyPts.at(i)=point;
	}

	for (int i=0; i<numTumors; i++){
		cin >> x >> y >> z;
		Point point;
		point.x=x;
		point.y=y;
		point.z=z;
		tumorPts.at(i)=point;
	}
		
	//we're gonna start doing an exponential search, then we do a binary search.

	//check if lower bound 0 is feasible(0 tumor points or 0 healthy points), you are done.
	if (numHealthy==0 || numTumors==0){
		cout << 0 << endl;
		continue;
	}

	int lower_bound=0; //first value not working
	int upper_bound=1; //lowest value that might be working

	//precalculate all powers that might be needed
	vector< vector<ET> > xPowH;
	vector< vector<ET> > yPowH;
	vector< vector<ET> > zPowH;
	vector< vector<ET> > xPowT;
	vector< vector<ET> > yPowT;
	vector< vector<ET> > zPowT;

	preCalcPowers(xPowH, yPowH, zPowH, xPowT, yPowT, zPowT, healthyPts, tumorPts, 30);

	bool works=false;
	while (works==false && upper_bound<30) {

		  // by default, we have a nonnegative LP with Ax <= b
		  //VERY IMPORTANT TO SET THIS CORRECTLY. ARE THERE LOWER/UPPER BOUNDS? IF NO, SET FALSE
		  Program qp (CGAL::SMALLER,false,0,false,0);

		  setCoeff(qp, xPowH, yPowH, zPowH, xPowT, yPowT, zPowT, numHealthy, numTumors, upper_bound);		  
		  Solution s = CGAL::solve_linear_program(qp, ET(), options);
		  assert (s.solves_linear_program(qp));

		  if (s.status() == CGAL::QP_INFEASIBLE){ //double upper and lower bound if infeasible
			lower_bound=upper_bound;
			upper_bound=upper_bound*2;
		  }

		  else { //feasible!!
			works=true;
			break;
		  }
	}

	if (upper_bound>=30){ //check if 30 works, otherwise, nothing would.
 
		  upper_bound=30;
		  Program qp (CGAL::SMALLER,false,0,false,0);

		  setCoeff(qp, xPowH, yPowH, zPowH, xPowT, yPowT, zPowT, numHealthy, numTumors, upper_bound);		  
		  Solution s = CGAL::solve_linear_program(qp, ET(), options);
		  assert (s.solves_linear_program(qp));

		  if (s.status() == CGAL::QP_INFEASIBLE){
			cout << "Impossible!" << endl;
			continue;
		  }
	}

	// now we need to do the binary search and find smallest upper_bound so that it works.
	int midPoint=(upper_bound-lower_bound)/2+lower_bound;

	while (true){

		  if (upper_bound-lower_bound<=1){
			break;
		  }

		  Program qp (CGAL::SMALLER,false,0,false,0);
		  setCoeff(qp, xPowH, yPowH, zPowH, xPowT, yPowT, zPowT, numHealthy, numTumors, midPoint);		  
		  Solution s = CGAL::solve_linear_program(qp, ET(), options);
		  assert (s.solves_linear_program(qp));

		  if (s.status() == CGAL::QP_INFEASIBLE){ //midPoint becomes new lower bound
			lower_bound=midPoint;
			midPoint=(upper_bound-lower_bound)/2+lower_bound;
		  }

		  else { //feasible. midPoint becomes new upper bound
			upper_bound=midPoint;
			midPoint=(upper_bound-lower_bound)/2+lower_bound;
		  }
	}
	cout << upper_bound << endl;
}	
  return 0;
}
