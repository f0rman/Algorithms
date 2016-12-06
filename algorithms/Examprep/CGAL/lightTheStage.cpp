#include <vector>
#include <iostream>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
using namespace std;

int main(){

int numTests;
cin >> numTests;

for (int i=0; i<numTests; i++){

	int numPlayers;
	int numLamps;
	cin >> numPlayers >> numLamps;

	vector< pair<K::Point_2, double> > playerVec(numPlayers);

	double x, y, r;

	for (int j=0; j<numPlayers; j++){

		cin >> x >> y >> r;
		K::Point_2 point=K::Point_2(x,y);
		playerVec.at(j).first=point;
		playerVec.at(j).second=r;

	}

	double lampRad;
	cin >> lampRad;
	vector< K::Point_2 > lampVec(numLamps);

	for (int k=0; k< numLamps; k++){
		cin >> x >> y;
		K::Point_2 lamp=K::Point_2(x,y);
		lampVec.at(k)=lamp;
	}

	// construct triangulation
	Triangulation t;
	t.insert(lampVec.begin(), lampVec.end());
	vector<bool> dead(numPlayers);
	int numDead=0;

	for (int m=0; m<numPlayers; m++){
	K::FT dist=CGAL::squared_distance(playerVec.at(m).first,t.nearest_vertex(playerVec.at(m).first)->point());
		if(dist<((playerVec.at(m).second+lampRad)*(playerVec.at(m).second+lampRad))){
			dead.at(m)=true;
			numDead++;
		}
	} 

	if (numDead!=numPlayers){
		for (size_t p=0; p<playerVec.size(); p++){
			if (dead.at(p)==false)
			cout << p << " ";
		}
		cout << endl;
		continue;
	}

	else { 

		vector< vector<int> > lampKillMatrix(numLamps);

		for (int m=0; m<numPlayers; m++){
			for (int lamp=0; lamp<numLamps; lamp++){
				K::FT dist=CGAL::squared_distance(playerVec.at(m).first,lampVec.at(lamp));
				if(dist<((playerVec.at(m).second+lampRad)*(playerVec.at(m).second+lampRad))){
					lampKillMatrix.at(lamp).push_back(m);
					break;
				}
			}
		} 

		int deadCount=0;
		vector<bool> survivors(numPlayers, true);
		vector<bool> prevSurvivors=survivors;

		for (int lamp=0; lamp<numLamps; lamp++){
			prevSurvivors=survivors;
			vector<int> killedByLamp=lampKillMatrix.at(lamp);
			for (size_t k=0; k<killedByLamp.size(); k++){
				deadCount++;
				survivors.at(killedByLamp.at(k))=false;
			}
			if (deadCount==numPlayers){ //If everyone dead now, this was the last round.
				break;
			}
		}

		for (int s=0; s<prevSurvivors.size(); s++){
			if (prevSurvivors.at(s)==true)
				cout << s << " ";
		}
		cout << endl;
	}
}

return 0;
}
