#include <iostream>
#include <map>
#include <vector>
#include <boost/math/special_functions/binomial.hpp>
#include <algorithm>
#include <math.h>

using namespace std;
using namespace boost;

const double divisor=100003;

int main(){

	ios_base::sync_with_stdio(false);
	int numTests;
	cin >> numTests;

	for (int i=0; i<numTests; i++){
		
		int k, n;
		cin >> k >> n;

		if (n==1){ //all 1-length words are tight
			cout << k+1 << endl;
			continue;
		}

		if (k==0){  //word using one character is tight.
			cout << 1 << endl;
			continue;
		}

		if (k==1){ //words using two characters are tight
			 cout << fmod(pow(2,n),divisor) << endl;
			 continue;
		} 

		//we have at least 3 characters.

		//declaration and initialization
		vector <vector<double> > SMatrix(k+1);
		for (int j=0; j<k+1; j++){
			SMatrix.at(j).resize(n);
			SMatrix.at(j).at(0)=1;
		}

		for (int j=1; j<n; j++){ //For every column

			SMatrix.at(0).at(j)=fmod(SMatrix.at(0).at(j-1)+SMatrix.at(1).at(j-1),divisor); //"border indices" build on 2
			SMatrix.at(k).at(j)=fmod(SMatrix.at(k-1).at(j-1)+SMatrix.at(k).at(j-1),divisor);	

			for (int c=1; c<k; c++){ //"middle indices" build on 3
				SMatrix.at(c).at(j)=fmod(SMatrix.at(c-1).at(j-1)+SMatrix.at(c).at(j-1)+SMatrix.at(c+1).at(j-1),divisor);
			}
		}

		double sum=0;
		
		//linearly traverse down last filled column
		for (int row=0; row<=k; row++){
			sum+=SMatrix.at(row).at(n-1);
		}
		cout << (fmod(sum,divisor)) << endl;
		continue;
	}

return 0;
}
