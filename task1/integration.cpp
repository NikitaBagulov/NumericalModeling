#include <iostream>
#include <cmath>
#include <time.h>
#include <cstdlib>
#include <omp.h>
#include <random>

#include "integration.hpp"

using namespace std;

double IntegrateRectangle(function<double(double)> f, double a, double b, size_t N, int num_thr){
    double result = 0;

    double h = (b-a)/double(N);
	#pragma omp parallel for reduction(+:result) num_threads(num_thr)
    for (size_t i = 0; i<N;i++){
        double x = a + i*h;
        result += f(x);
    }
    
    return result*h;
}

double IntegrateMonteCarlo(function<double(double)> f, double a, double b, size_t N, unsigned int base_seed, int num_thr) {
    double sum = 0;
	
    #pragma omp parallel reduction(+:sum) num_threads(num_thr)
    {
        int thread_id = omp_get_thread_num();
        default_random_engine engine(base_seed + thread_id);
        uniform_real_distribution<double> distribution(a, b);

        #pragma omp for
        for (size_t i = 0; i < N; i++) {
            double x = distribution(engine);
            sum += f(x);
        }
    }

    double avg = sum / N;
    double result = (b - a) * avg;
    return result;
}

double RelativeError(double approx, double exact){
    double error = abs(approx-exact)/exact;
    return error;
}




