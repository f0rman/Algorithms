#include <vector>
#include <queue>
#include <iostream>
#include <fstream>

using namespace std;

typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int, int> ii;   //a pair ii. This data structure is used for velocities and grid positions.

typedef struct Vertex {

	ii position;
	ii velocity;
	int distance;

}Vertex;

vvi grid;  //Let's represent our grid by a matrix, where 1 means occupied, 0 means empty.
int x, y;  //width and height of grid.
int x_start, y_start, x_end, y_end;  //Start and finish positions for hopper
int p; //Number of obstacles
int obsXstart, obsYstart, obsXend, obsYend;

//Edges can be deduced by the description of a vertex so no need to store the entire graph explicitly.

//Two vertices of the graph are connected if reaching the point p1 with velocity v1 enables us to
//hop vertex with point p2 with velocity v2. Degree of a vertex is at most 9, so a vertex can maximally have 9 edges

//The algorithm should terminate as soon as we find a vertex with our desired grid position
//When we find the target vertex, we need to traverse back to the start and count how many edges we needed.
//Each visited vertex needs to have a pointer to the previous vertex.

//Visitedvertices can be stored in a cubic matrix

void findShortestPath(Vertex startingVertex){

	int shortestNumberOfEdges = 0;

	if (startingVertex.position.first == x_end && startingVertex.position.second == y_end){  //If the starting vertex has the desired finish pos, return.
		cout << "Optimal solution takes " << shortestNumberOfEdges << " hops." << endl;
		return;
	}

	queue<Vertex> q;   //Make a set Q (queue), containing vertices. This is a set of unvisited vertices.
	q.push(startingVertex);   //Into your set Q, insert the startingVertex

	//find all the vertices that you can jump to by doing bfs. we keep track of visited vertexes by
	//putting them in an array

	vector< vector< vector < vector <bool> > > > visited(x, vector< vector< vector<bool> > >(y, vector< vector<bool> >(7, vector<bool>(7, false))));

	while (!q.empty())   //as long as there are unvisited nodes...
	{
		
		Vertex top = q.front();    
		q.pop();   //put vertex into the set of visited ones and take it away from the set of unvisited ones
		
		//find all the vertices that it's connected to, put 'em in the queue

		for (int xvel = -1; xvel <= 1; ++xvel)  //for all velocities... 
		{

			for (int yvel=-1; yvel <= 1; ++yvel){

				//calculate new position given this position. if this newpos means we reach our target vertex, return
				int nvx = top.velocity.first + xvel;
				int nvy = top.velocity.second + yvel;
				int newxpos = top.position.first+nvx-3;
				int newypos = top.position.second+nvy-3;

				if (nvx >= 0 && nvy >= 0 && nvx < 7 && nvy < 7 && newxpos >= 0 && newxpos < x && newypos >= 0 && newypos < y && grid.at(newxpos).at(newypos)!= 1 && !visited[newxpos][newypos][nvx][nvy])  //if this grid position is not occupied or out of scope
				{
					visited.at(newxpos).at(newypos).at(nvx).at(nvy) = true;

					if (newxpos == x_end && newypos == y_end){  //if we reach the target vertex from this vertex, just return.
						shortestNumberOfEdges = top.distance + 1;
						cout << "Optimal solution takes " << shortestNumberOfEdges << " hops." << endl;
						return;
					}

					else {  //this vertex is okay, put it onto the queue. 

						int distance = top.distance+1;
						Vertex connectedvertex;
						connectedvertex.position.first = newxpos;
						connectedvertex.position.second = newypos;
						connectedvertex.velocity.first = nvx;
						connectedvertex.velocity.second = nvy;
						connectedvertex.distance = distance;
						q.push(connectedvertex);
					}
				}

			}
		}
	}

	cout<< "No solution."<< endl;
}


	int main() {

		int n; //Number of test cases

		cin>>n;

		for (int i = 0; i < n; i++){ //For each test case...

			cin >> x >> y;  //Scan size of grid

			grid.clear();
			//x represents rows, y represents columns.
			
			grid.resize(x);
			for (int j = 0; j < x; j++){
				grid[j].resize(y);
			}

			cin >> x_start >> y_start >> x_end >> y_end;
			cin >> p;

			for (int i = 0; i < p; i++){  //For every obstacle, fill in 1's in the appropriate places in the grid

				cin >> obsXstart >> obsYstart >> obsXend >> obsYend;

				for (int m = obsXstart; m <= obsXend; m++){
					for (int j = obsYstart; j <= obsYend; j++){
						grid.at(m).at(j) = 1;
					}
				}
			}

			Vertex start;
			start.position.first = x_start;
			start.position.second = y_start;
			start.velocity.first = 3;   //velocity (0,0) is equal to 3
			start.velocity.second = 3;
			start.distance = 0;
			
			findShortestPath(start);

		}

		return 0;
	}
