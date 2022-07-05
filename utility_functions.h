#include <iostream>
using namespace std;

void outputVector(vector<double> &vect){
    for(auto i : vect){
        cout << i << ' ';
    }
    cout << endl;
}