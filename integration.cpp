#include <iostream>
#include <cmath>
#include <time.h>
#include <cstdlib>
#include <omp.h>
#include <random>

#include "integration.hpp"

using namespace std;

double IntegrateRectangle(function<double(double)> f, double a, double b, size_t N){
    double result = 0;

    double h = (b-a)/double(N);

    for (size_t i = 0; i<N;i++){
        double x = a + i*h;
        result += f(x);
    }
    
    return result*h;
}

double IntegrateMonteCarlo(function<double(double)> f, double a, double b, size_t N, default_random_engine& engine){

    uniform_real_distribution<double> distribution(a, b);
	
    double sum = 0;
    for (size_t i = 0; i<N;i++){
        double x = distribution(engine);
        sum += f(x);
    }
    double avg = sum/N;
    double result = (b-a)*avg;
    return result;
}

double RelativeError(double approx, double exact){
    double error = abs(approx-exact)/exact;
    return error;
}




