// Exercise 3
#include <iostream>
#include <math.h>
#include <complex>
using namespace std;
int main()

{
    float a,b,c, d;
    complex<double> sol1(1,1),sol2(1,1);
    cout <<"Enter a:";
    cin>>a;
    cout <<"Enter b:";
    cin>>b;
    cout <<"Enter c:";
    cin>>c;
    d=b*b-4*a*c;
    sol1=(-1*b+sqrt(d))/(2*a);
    sol2=(-1*b-sqrt(d))/(2*a);
    cout << "first solution is"
    << sol1<< "\n";
    cout << "second solution is"
    << sol2<< "\n";
    return 0;
}
