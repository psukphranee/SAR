#include <cmath>
#include <vector>

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

//callback function for squaring array
static inline double computeSquare (double x) { return x*x; }
//std::transform(Array2.begin(), Array2.end(), Array2.begin(), computeSquare);

vector<double> const_times_vector(vector<double> &input, double constant){
    
    vector<double> temp;

    for (auto i : input){
        temp.push_back(constant * i);
    }

    return temp;
}