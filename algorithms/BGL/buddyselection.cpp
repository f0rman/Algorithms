// BuddySelection.cpp

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace boost;
using namespace std;

typedef adjacency_list<vecS, vecS, undirectedS, no_property, no_property> Graph;

bool in_array(const string &value, const std::vector<string> &array)
{
	return std::find(array.begin(), array.end(), value) != array.end();
}

int main()
{

	int numTestCases;
	int numVertices;
	int numProperties;
	int f; //minimum as supposed by Dr.
	string property;
	vector<vector<string>> propertyArray;

	cin >> numTestCases;
	for (int i = 0; i < numTestCases; i++){

		cin >> numVertices >> numProperties >> f;
		Graph g(numVertices);
		propertyArray.clear();
		propertyArray.resize(numVertices);

		for (int j = 0; j < numVertices; j++){  //read and store student characteristics.
			for (int p = 0; p < numProperties; p++){
				cin >> property;
				propertyArray.at(j).push_back(property);
			}
		}

		//go through students, if numMatchings are more than f, make an edge. Start at second student.
		int numMatches;
		for (int i = 1; i < numVertices; i++){ //for every student...

			for (int j = 0; j < i; j++){  //for every student before in the list...
				numMatches = 0;
				for (int propno = 0; propno < numProperties; propno++){ //get the property, see if it exists in student j.
					property = propertyArray.at(i).at(propno);
					if (in_array(property, propertyArray.at(j))) numMatches++;
					if (numMatches>f) { //if numMatches now greater than f, draw an edge between student i and j and break.
						add_edge(i, j, g);
						break;
					}
				}
			}
		}

		std::vector<graph_traits<Graph>::vertex_descriptor> mate(numVertices);

		//do edmonds, check size of matching
		bool success = checked_edmonds_maximum_cardinality_matching(g, &mate[0]);
		assert(success);
		
		if (matching_size(g, &mate[0]) == numVertices / 2){ //if all people are matched. (All are pairs)
			cout << "not optimal" << endl;
		}
		else cout <<"optimal" << endl;

	}

	return 0;
}
