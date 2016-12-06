#include <iostream>     // std::cout
#include <algorithm>    // std::unique, std::distance
#include <vector>       // std::vector
#include <map>

//find all pairs in an array giving a certain sum

using namespace std;

void func(vector<int> A, int k){

  sort(A.begin(), A.end());
  int N=A.size();
  map<int, int> howManyOfEach;
  for (int i = 0; i < A.size(); i++)
  {
    howManyOfEach[A[i]] += 1;
  }

  int count=0;
  std::vector<int>::iterator it;
  it = std::unique (A.begin(), A.end());
  A.resize( std::distance(A.begin(),it) );
  
  for (int i = 0; i < A.size(); i++)
  {
    int needed=k-A.at(i);
    if(howManyOfEach.count(needed)){
	count++;
    }
  }
  cout << count;
}

int main () {
  int k=2;
  int myints[] = { 0, -1, 3, 2, -5, 7 };
  std::vector<int> A (myints, myints + sizeof(myints) / sizeof(int) );
  func(A,k); 
  return 0;
}
