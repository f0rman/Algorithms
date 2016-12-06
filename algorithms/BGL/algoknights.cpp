#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <cassert>
#include <boost/graph/max_cardinality_matching.hpp>
#include <boost/tuple/tuple.hpp>
#include <vector>
#include <algorithm>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS> Graph;

int main(){

	ios_base::sync_with_stdio(false);
	int numTests;
	cin >> numTests;

	for (int i=0; i<numTests; i++){

		int length;
		cin >> length;
		vector<vector <int> > board(length);

		int value;
		int numNonZero=0;

		for (int i=0; i<length; i++){
			board.at(i).resize(length);
			for (int j=0; j<length; j++){
				cin >> value;
				if (value==1) numNonZero++;
				board.at(i).at(j)=value;
			}
		}
		Graph g;

		for (int i=0; i<length; i++){
			for (int j=0; j<length; j++){
				if (board.at(i).at(j)==1){
					if (i-1>=0){
						if (j-2>=0 && board.at(i-1).at(j-2)==1)
							add_edge(i*length+j, (i-1)*length+(j-2), g);

						if (j+2<=(length-1) && board.at(i-1).at(j+2)==1)
							add_edge(i*length+j, (i-1)*length+(j+2), g);
					}
					if (i-2>=0){
						if (j-1>=0 && board.at(i-2).at(j-1)==1)
							add_edge(i*length+j, (i-2)*length+(j-1), g);

						if (j+1<=(length-1) && board.at(i-2).at(j+1)==1)
							add_edge(i*length+j, (i-2)*length+(j+1), g);
					}
					if (i+1<=(length-1)){
						if (j+2<=(length-1) && board.at(i+1).at(j+2)==1)
							add_edge(i*length+j, (i+1)*length+(j+2), g);

						if (j-2>=0 && board.at(i+1).at(j-2)==1)
							add_edge(i*length+j, (i+1)*length+(j-2), g);
					}
					if (i+2<=(length-1)){
						if (j-1>=0 && board.at(i+2).at(j-1)==1)
							add_edge(i*length+j, (i+2)*length+(j-1), g);

						if (j+1<=(length-1) && board.at(i+2).at(j+1)==1)
							add_edge(i*length+j, (i+2)*length+(j+1), g);
					}
				}
			}
		}
		
	  std::vector<graph_traits<Graph>::vertex_descriptor> mate(num_vertices(g));

	  bool success = checked_edmonds_maximum_cardinality_matching(g, &mate[0]);
	  assert(success);

	  std::cout << numNonZero-matching_size(g, &mate[0]) << std::endl;
		
	  }

return 0;

}
