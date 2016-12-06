#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <functional> // greater
#include <cmath>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	int T;  cin >> T;
	while (T--) {
		int n; cin >> n;
		vector<int> parasols; vector<int> best_locations;
		for (int i = 0; i < n; i++) {
			int loc;  cin >> loc; parasols.push_back(loc);
		}
		std::sort(parasols.begin(), parasols.end());
		queue<int> Q; 
		int maxParasols = 0; int bestMaxLength = 200;
		for (int i = 0; i < parasols.size(); i++) {
			int right_parasol = parasols[i];
			Q.push(right_parasol);
			while (Q.front() < right_parasol - 200) { //basically you want your left parasol to be greater than this, to avoid desert
				Q.pop();
			}
			int left_parasol = Q.front();
			int covered = Q.size();
			
			int length = right_parasol - left_parasol;
			int max_length = ceil(double(length) / 2.0); // you would always put the bar in the midPoint of 2 extremes.
			int pos = (length) / 2 + left_parasol; //you put your bar at the floor of the midpoint. (could be ceil, doesn't matter)
			if (covered > maxParasols || ((covered == maxParasols) && (max_length < bestMaxLength))) {
				bestMaxLength = max_length;
				maxParasols = covered;

				best_locations.clear(); best_locations.push_back(pos);
				if (length % 2 == 1) best_locations.push_back(pos + 1); // since in an odd length interval, there are two 												    positions for bar
			} else if (covered == maxParasols && max_length == bestMaxLength) {
				best_locations.push_back(pos);
				if (length % 2 == 1) best_locations.push_back(pos + 1);
			}
		}
		cout << maxParasols << " " << bestMaxLength << endl;
		std::unique(best_locations.begin(), best_locations.end()); //it could happen that you have two consecutive same points optimal
		std::sort(best_locations.begin(), best_locations.end());    // (think about two optimal odd length intervals for example and 											flooring ceiling) 
		for (int i = 0; i < best_locations.size(); i++) {	   
			if (i < best_locations.size() - 1) {
				cout << best_locations[i] << " ";
			} else {
				cout << best_locations[i];
			}
		}
		cout << endl;
	}
	return 0;
}
