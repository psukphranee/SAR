#ifndef vector_functions
#define vector_functions

#include <cmath>
#include <vector>
#include "scalar_functions.h"

using namespace std;

//linspace implementations
vector<double> linspace(double min, double max, int n)
{
	vector<double> result;
	// vector iterator
	int iterator = 0;

	for (int i = 0; i <= n-2; i++)	
	{
		double temp = min + i*(max-min)/(floor((double)n) - 1);
		result.insert(result.begin() + iterator, temp);
		iterator += 1;
	}

	//iterator += 1;

	result.insert(result.begin() + iterator, max);
	return result;
}

//examples of vector functions
//std::transform(result.begin(), result.end(), result_temp.begin(), result.begin(), std::plus<double>());
//std::transform(Array2.begin(), Array2.end(), Array2.begin(), computeSquare);
//transform(v.begin(), v.end(), v.begin(), [k](int &c){ return c*k; });
//std::transform(test1.begin(), test1.end(), test2.begin(), test3.begin(), std::plus<double>()); test3=test1+test2

vector<double> const_times_vector(vector<double> &input, double constant){
    
    vector<double> temp;

    for (auto i : input){
        temp.push_back(constant * i);
    }

    return temp;
}

#endif