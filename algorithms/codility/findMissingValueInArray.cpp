//find un-paired value in array.

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

int solution(vector<int> &A) {
    
    if (A.empty()){
        return 1;
    }
    
    int N=A.size();
    int xor1=A.at(0);
    int xor2=1;
    if (N>=2){
        for (int i=1; i<N; i++){
            xor1=xor1^A.at(i);
            xor2=xor2^(i+1);
        }
    }
    xor2=xor2^(N+1);
    return xor1^xor2;
}
