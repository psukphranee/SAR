#include <iostream>
#include "math_functions.h"
#include "utility_functions.h"

using namespace std;

int main(){

    vector<double> test = linspace(0,9,10);
    test = const_times_vector(test, 2);
    
    outputVector(test);

    return 0;
}