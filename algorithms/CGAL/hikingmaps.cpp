#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <vector>
#include <iostream>
#include <math.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
const int maximum=INT_MAX;
int shortestSet;
std::map<std::pair<int,int>, bool> stored;

using namespace std;

int main()
{

  ios_base::sync_with_stdio(false);

  int numTests;

  cin >> numTests;

  int numVertices, numTriangles;
  double x, y, q0, q1, q2, q3, q4, q5, q6, q7, q8, q9, q10, q11;

  vector<int> outputs;
  for (int i=0; i<numTests; i++){

	cin >> numVertices >> numTriangles;

	vector<K::Point_2> points;
	points.reserve(numVertices);

	for (int j=0; j<numVertices; j++){
		cin >> x >> y;
		points.push_back(K::Point_2(x, y));
	}

	//vector denoting which part of the trail a triangle contains.
	vector< vector<int> > contains(numTriangles);

	for (int k=0; k<numTriangles; k++){

		cin >> q0 >> q1 >> q2 >> q3 >> q4 >> q5 >> q6 >> q7 >> q8 >> q9 >> q10 >> q11;

		vector<K::Point_2> triSides; //triangle is defined by 6 points on its sides
		
		//we need to make sure that the points on the triangle are in correct order so that the triangle is correctly oriented.
		K::Point_2 fsfp(q0, q1);
		K::Point_2 fssp(q2, q3);
		K::Point_2 ssfp(q4, q5);
		K::Point_2 sssp(q6, q7);
		K::Point_2 tsfp(q8, q9);
		K::Point_2 tssp(q10, q11);

		if (CGAL::right_turn(fsfp, fssp, ssfp)){
			K::Point_2 temp=fsfp;
			fsfp=fssp;
			fssp=temp;
		} 	

		if (CGAL::right_turn(ssfp, sssp, tsfp)){
			K::Point_2 temp=ssfp;
			ssfp=sssp;
			sssp=temp;
		} 	
	
		if (CGAL::right_turn(tsfp, tssp, fsfp)){
			K::Point_2 temp=tsfp;
			tsfp=tssp;
			tssp=temp;
		} 	

		triSides.push_back(fsfp); //do not combine initialization vector(numVertices) with push_back!!! reserve is okay.
		triSides.push_back(fssp);
		triSides.push_back(ssfp);
		triSides.push_back(sssp);
		triSides.push_back(tsfp);
		triSides.push_back(tssp);
		
		for (int p=0; p<numVertices-1; p++){ //go through legs. See which legs this triangle contains
			
			K::Point_2 startOfSeg=points.at(p);
			K::Point_2 endOfSeg=points.at(p+1);

			bool contain=true;
			for (int k=0; k<6; k+=2){
				
				K::Point_2 sp1=triSides.at(k);
				K::Point_2 sp2=triSides.at(k+1);
				if (CGAL::right_turn(sp1, sp2, startOfSeg) 
				    || CGAL::right_turn(sp1, sp2, endOfSeg)){ //triangle does not contain segment pt.
					contain=false;
					break;
				}
			}

			if (contain==true){
				contains.at(k).push_back(p);
			}
		}			
	}

	//we now have all our triangles and what they contain. time to decide which to buy.
	
	int sizeOfSet=numTriangles;
	vector<int> inSet(numVertices-1); //shows which legs and how many are in a set
	int left=0;
	int right=-1;
	int numLegsCovered=0;
	bool finished=false;

	while (finished==false){

		vector<int> legsContained;

		while (true){
			if (numLegsCovered!=numVertices-1){  //if not everything is covered...

				if (right<numTriangles-1){

					right++; //increment right
					legsContained=contains.at(right);
	
					for (size_t l=0; l<legsContained.size(); l++){
						int legNo=legsContained.at(l);
						if (inSet.at(legNo)==0){
							numLegsCovered++;
						}
						inSet.at(legNo)++;
					}
				}
				else break; //we're at the last index but we still don't cover everything. Nothing can be done.
			}

			else{ //if all legs covered now, stop

				if (right-left+1<sizeOfSet){
					sizeOfSet=right-left+1;
				}
				break;
			}
			
		}

		if (numLegsCovered!=numVertices-1 && right==numTriangles-1)
			break;

		//remove left triangle.
		legsContained=contains.at(left);

		for (size_t l=0; l<legsContained.size(); l++){
			int legNo=legsContained.at(l);
			if (inSet.at(legNo)==1){
				numLegsCovered--;
			}
			inSet.at(legNo)--;
		}

		left++;
		if (numLegsCovered!=numVertices-1 && right==numTriangles-1)
			finished=true;
	}

  outputs.push_back(sizeOfSet);

  }

for (int i=0; i<numTests; i++){
	cout << outputs.at(i) << endl;
}

return 0;
}
