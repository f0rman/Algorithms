#include <vector>
#include <stack>
#include <cstdio>
#include <iostream>

using namespace std;

vector<vector<int>> G;
vector<bool> visited;

pair < int, int > DFS(int A){  //A is index of any vertex. We always choose 0 in the code.
	stack < int > S;
	S.push(A);
	visited.at(A) = true;
	bool flag;
	int max_height = 0;
	int ans_vertex = A;
	int x;
	while (!S.empty()){
		x = S.top();
		flag = false;
		for (size_t i = 0; i<G.at(x).size(); i++){
			if (!visited[G.at(x).at(i)]){ //we'll only put max one item onto the stack at a time, because of the break.
				flag = true;
				S.push(G[x][i]);
				visited[G[x][i]] = true;
				break;
			}
		}
		if (S.size()>max_height){
			max_height = S.size();
			ans_vertex = S.top();
		}
		if (!flag)  //If your vertex is a leaf, pop it.
			S.pop();
	}
	/* the distance of the farthest node will be maximum height of the stack-1.*/
	pair<int,int> answer=make_pair(ans_vertex, max_height);
	return answer;
}

int main(){

	int numberOfTestcases;
	cin >> numberOfTestcases;

	int numberOfVertices;
	int edgeStart, edgeEnd;

	for (int i = 0; i < numberOfTestcases; i++){

		G.clear();
		visited.clear();
		cin >> numberOfVertices;
		G.resize(numberOfVertices);
		visited=vector<bool>(numberOfVertices, false);

		for (int j = 0; j < numberOfVertices - 1; j++){  //all edges

			cin >> edgeStart >> edgeEnd;

			G.at(edgeStart).push_back(edgeEnd);
			G.at(edgeEnd).push_back(edgeStart);
		}

		pair<int, int> B, C;
		B = DFS(0);
		visited.clear();
		visited = vector<bool>(numberOfVertices, false);
		C = DFS(B.first);
		cout << C.second << endl;

	}

	return 0;
}
