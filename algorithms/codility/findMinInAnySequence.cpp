// you can use includes, for example:
// #include <algorithm>
#include <vector>
using namespace std;

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

vector<int> solution(string &S, vector<int> &P, vector<int> &Q) {
    
    int N=S.length();
    vector< vector<int> > cs(N+1, vector<int>(4));
    vector<int> sInt(N);
    
    for (int i=0; i<N; i++){
       char c = S.at(i);
       cs.at(i+1).at(0)=cs.at(i).at(0);
       cs.at(i+1).at(1)=cs.at(i).at(1);
       cs.at(i+1).at(2)=cs.at(i).at(2);
       cs.at(i+1).at(3)=cs.at(i).at(3);
       
       switch ( c ) {
         case 'A':
            cs.at(i+1).at(0)++;
            sInt.at(i)=1;
            break;
         case 'C' :
            cs.at(i+1).at(1)++;
            sInt.at(i)=2;
            break;
         case 'G' :
            cs.at(i+1).at(2)++;
            sInt.at(i)=3;
            break;
         case 'T' :
            cs.at(i+1).at(3)++;
            sInt.at(i)=4;
            break;
       }
    }
    
    int M=Q.size();
    vector<int> results(M);
    for (int i=0; i<M; i++){
        int start=P.at(i);
        int end=Q.at(i);
        if (start==end){
            results.at(i)=sInt.at(start);
            continue;
        }
        end++;
        for (int j=0; j<4; j++){
            if ((cs.at(end).at(j)-cs.at(start).at(j))>0){
               results.at(i)=j+1;
               break;
            }
        }
    }
    return results;
}
