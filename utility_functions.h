#ifndef utility_functions
#define utility_functions

#include <iostream>
#include "vector_functions.h"

using namespace std;

void outputVector(vector<double> &vect){
    for(auto i : vect){
        cout << i << ' ';
    }
    cout << endl;
}

vector<double> generate_pulse_envelope(vector<double> &time_array, double pulse_width, double pulse_height){
  //this function returns pulse envelopes of tau width wide. the left edge of the envelope is located at any zeros of the time array.
    vector<double> chi(time_array.size());

    vector<double> &t = time_array;
    double A = pulse_height;
    double tau = pulse_width; 
    double tau_half = tau/2;

    for(size_t i = 0; i < time_array.size(); ++i){
        chi[i] = A * (abs((t[i]-tau_half)/tau_half) <= 1);
    }

    return chi;
}

vector<double> generate_pulse_wave(vector<double> &time_array, double chirp_rate, double carrier_frequency){
    //time ---------------
    vector<double> &t = time_array; 
    vector<double> t_squared(time_array.size());

    //LFM  ---------------
    double k = chirp_rate;
    double f_c = carrier_frequency;

    //argument to be passed to exponenetial
    transform( t.begin(), t.end(), t_squared.begin(), computeSquare);

    //Python code translation
    // exp_arg = 2j*np.pi*(f_c*t + .5*k*(t_squared));
    vector<double> arg1 = const_times_vector(t_squared, 5*k);
    vector<double> arg2 = const_times_vector(t, f_c);
    //add and store into arg1
    std::transform(arg1.begin(), arg1.end(), arg2.begin(), arg1.begin(), std::plus<double>());
    //multiply arg1 by 2pi
    arg1 = const_times_vector(arg1, 2*M_PI);
    //return the real part
    transform(arg1.begin(), arg1.end(), arg1.begin(), cosf);

    //create alias to be consistent with python code
    vector<double> &LFM = arg1;
    return LFM;
}

vector<double> generate_LFM_Pulse(vector<double> &time_array, double pulse_width, double pulse_height, double chirp_rate, double carrier_frequency){
  
    //time ---------------
    vector<double> &t = time_array; //#expected time vector should be preprocessed before passed to this function. pulse and envelope start their sequences at times values of zeros.

    //#pulse envelope  ---------------
    vector<double> chi = generate_pulse_envelope(t, pulse_height, pulse_width);

    //#LFM  ---------------
    double k = chirp_rate;
    double f_c = carrier_frequency;

    vector<double> LFM = generate_pulse_wave(t, k, f_c);

    //pulse = chi * LFM;

    transform( chi.begin(), chi.end(), LFM.begin(), LFM.begin(),  multiplies<int>() );
    
    return LFM;
}
#endif