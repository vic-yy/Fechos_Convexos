#include <iostream>
#include <cmath>
#include "vector"

using namespace std;

// Scan of graham algorithm

double teta (double x, double y){
    double teta = atan(y/x);
    return teta;
}

double r (double x, double y){
    double r = sqrt(pow(x,2) + pow(y,2)); 
    return r;
}


bool comparePoints (const points &p1, const points &p2){
    if (p1.y != p2.y){
        return p1.y < p2.y;
    }
    return p1.x < p2.x;
}
// x = r cos(teta)
// y = r sen(teta)
// teta = atan(y/x);


struct points{
    double x;
    double y;
};



int main (){
    double a,b;
    vector <double> x, y;
    vector <double> teta;
    vector<double> r;


    while(cin >> a >> b){
        x.push_back(a);
        y.push_back(b);

    }

    for  (int i = 0; i < x.size(); i++){
        teta.push_back(atan(y[i]/x[i]));
        r.push_back(sqrt(pow(x[i],2) + pow(y[i],2)));
    }

    return 0;
}