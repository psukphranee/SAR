#include <iostream>
#include <cmath>
#include <complex>
#include "vector_functions.h"
#include "utility_functions.h"
#include "scalar_functions.h"

using namespace std;

int main(){

    vector<double> test = linspace(0,300,299);
    vector<double> test2 = transform(test.begin(), test.end(), test2.begin(), modulus<double>);
    outputVector(test);

    return 0;
}