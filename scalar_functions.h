#ifndef scalar_functions
#define scalar_functions

#include <cmath>
#include <vector>
#include <complex>

using namespace std;

static inline double computeSquare (double x) { return x*x; }

complex<double> returnComplex(double angle){
    complex<double> result(cos(angle), sin(angle));
    return result;
}

double returnRealOfComplex(double angle){
    double temp = real(returnComplex(angle));
    return temp;
}



#endif