#include <iostream>
#include <cmath>
#include <numeric>
#include <complex>
#include "vector_functions.h"
#include "utility_functions.h"
#include "scalar_functions.h"

using namespace std;

int main(){

    //#define parameters
    double f_s = 1e6; //#sampling rate; data points per second 
    double PRF = 10e1;// #10kHz
    double D = .4; //#duty time

    double PRT = 1/PRF;
    double f_m = f_s/2;
    double tau = D*PRT;

    double A = 1;// #pulse height
    double k = 10; //#chirp rate
    double f_c = 10e1; //#carrier freq

    //Generate time vector. Then take its modulus to be periodic
    double t_end = PRT*4; // #multiple of pulse repittion period
    vector<double> t = linspace(-1*PRT, t_end, int(f_s*t_end));
    vector<double> t_mod = vector_modulus_const(t, PRT);
    //generate pulse
    vector<double> pulse = generate_LFM_Pulse(t_mod, tau, 1, k, f_c);

    //Ground reflection - Convolution Matrix
    double ds = 1/f_s;
    double d_tau = ds;

    //#number of ground segments
    double n_g = 10000;
    vector<double> g = linspace(0, n_g-1, n_g);
    g = const_times_vector(g, d_tau);

    vector<double> g_index = const_times_vector(g,1/ds);

    //#define an identity matrix of size n_g (the number of ground elements)
    vector<double> I_ng(n_g); I_ng[0] = 1;
    //#The identity matrix will be shifted, summed and stored in the following matrix
    vector<double> Convolution_Matrix(n_g); 

    //--------
    vector<double> &t_index_delay = g_index; //#rename; alias; copied from previous scratch work

    for(size_t i=0; i < n_g; ++i){
        vector<double> I_ng_copy = I_ng;
        int curr_delay_index = static_cast<int>(t_index_delay[i]);

        curr_delay_index = curr_delay_index < n_g ? curr_delay_index : 0;// #limit shifting to convolution window limit. otherwise we can get redundant or unwanted values
        rotate(I_ng_copy.begin(), I_ng_copy.begin() + curr_delay_index, I_ng_copy.end());

        std::transform(Convolution_Matrix.begin(), Convolution_Matrix.end(), I_ng_copy.begin(), Convolution_Matrix.begin(), std::plus<double>());

    }
    
    // //pad and perform matrix mult
    vector<double> padding(n_g);
    // //pad pulse vector
    for(size_t i =0; i < n_g; ++i){
        pulse.insert(pulse.begin(), 0);
    }
    for(size_t i =0; i < n_g; ++i){
        pulse.push_back(0);
    }

    // #convolution matrix flip
    reverse(Convolution_Matrix.begin(), Convolution_Matrix.end());

    // #
    vector<double> reflection(pulse.size());

    // for i in range(pulse_padded.shape[1]-n_g):
    for(size_t i = 0; i < n_g; ++i){
        vector<double> temp(n_g);
        transform(pulse.begin() + i, pulse.begin() + (i + n_g), Convolution_Matrix.begin(), temp.begin(), std::multiplies<double>());
        reflection[i] = accumulate(temp.begin() + 1, temp.end(), 0);
    }

    outputVector(reflection);

    return 0;
}