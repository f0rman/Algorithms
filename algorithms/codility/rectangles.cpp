#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

using namespace std;

int main(){

   double xlb, ylb, xlu, ylu, xru, yru, xrb, yrb, xlb2, ylb2, xlu2, ylu2, xru2, yru2, xrb2, yrb2;
   cin >> xlb >> ylb >> xlu >> ylu >> xru >> yru >> xrb >> yrb;
   cin >> xlb2 >> ylb2 >> xlu2 >> ylu2 >> xru2 >> yru2 >> xrb2 >> yrb2;

   double A1=(xrb-xlb)*(ylu-ylb);
   double A2=(xrb2-xlb2)*(ylu2-ylb2);
   double C;

   if (xlb2 < xrb && xrb2 > xlb){  //intersect
	if (ylb2 < ylu && ylu2 > ylu){
		C=(min(xrb,xrb2)-max(xlb,xlb2))*(min(ylu,ylu2)-max(ylb,ylb2));
	}
      cout << A1+A2-C;
   }

   else cout << A1+A2;
   return 0;
}
