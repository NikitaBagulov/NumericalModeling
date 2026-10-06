#include <iostream>
#include <fstream>
#include <functional>
#include <cmath>
#include <chrono>
#include <vector>
#include <omp.h>
#include <random>
#include <algorithm>

#include "integration.hpp"

using namespace std;

double custom_f(double x){
    return pow((10-x), 2);
}

struct IterationResult {
    size_t N;
    double rectangle_time;
    double r_error;
    double montecarlo_time;
    double mc_error;
};

int main(){

	//first experiment
    chrono::steady_clock::time_point begin;
    chrono::steady_clock::time_point end;
    
    double exact = 1000.0 / 3.0;
    
    size_t Ns = 1000000;
    size_t step = 100;
    size_t total_steps = Ns / step; 

    size_t num_repeats = 11;
    
    function<double(double)> f = custom_f;

    vector<IterationResult> results(total_steps);
    
    begin = chrono::steady_clock::now();

    int max_threads = omp_get_max_threads();
    cout << "Max threads: " << max_threads << '\n';

    random_device r;
    unsigned int base_seed = r();

    for (size_t i = 1; i <= total_steps; i++) {
        size_t current_N = i * step;

        double rect_times[num_repeats];
        double rect_errors[num_repeats];
        double mc_times[num_repeats];
        double mc_errors[num_repeats];
        
        for (size_t rep = 0; rep < num_repeats; ++rep) {

            auto r_begin = omp_get_wtime();
            double result = IntegrateRectangle(f, 0., 10., current_N, max_threads);
            auto r_end = omp_get_wtime();
            
            rect_times[rep] = (r_end - r_begin) * 1000000.0;
            rect_errors[rep] = RelativeError(result, exact);

            auto mc_begin = omp_get_wtime();
            double result2 = IntegrateMonteCarlo(f, 0., 10., current_N, base_seed, max_threads);
            auto mc_end = omp_get_wtime();
            
            mc_times[rep] = (mc_end - mc_begin) * 1000000.0;
            mc_errors[rep] = RelativeError(result2, exact);
        }
        
        std::sort(rect_times, rect_times + num_repeats);
        std::sort(rect_errors, rect_errors + num_repeats);
        
        std::sort(mc_times, mc_times + num_repeats);
        std::sort(mc_errors, mc_errors + num_repeats);

        results[i - 1] = { 
            current_N, 
            rect_times[1], 
            rect_errors[1], 
            mc_times[1], 
            mc_errors[1] 
        };
    }
    
    ofstream file("results.csv");
    file << "N,rectangle_time,rectangle_error,montecarlo_time,montecarlo_error\n";
    for (const auto& res : results) {
        file << res.N << "," << res.rectangle_time << "," << res.r_error << "," 
             << res.montecarlo_time << "," << res.mc_error << "\n";
    }
    file.close();
    
    end = chrono::steady_clock::now();


	//second experiment
	size_t fixed_N = 10000000;

	ofstream threads_file("threads.csv");
	threads_file << "threads,rectangle_time,montecarlo_time\n";
	
	for (int t = 1; t <= max_threads; ++t) {
	
	    vector<double> rect_times(num_repeats);
	    vector<double> mc_times(num_repeats);
	
	    for (size_t rep = 0; rep < num_repeats; ++rep) {
			
	        double r_begin = omp_get_wtime();
	        IntegrateRectangle(f, 0.0, 10.0, fixed_N, t);
	        double r_end = omp_get_wtime();

	        rect_times[rep] = (r_end - r_begin) * 1000000.0;
	
	        double mc_begin = omp_get_wtime();
	        IntegrateMonteCarlo(f, 0.0, 10.0, fixed_N, base_seed, t);
	        double mc_end = omp_get_wtime();
	
	        mc_times[rep] = (mc_end - mc_begin) * 1000000.0;
		}
		
	    sort(rect_times.begin(), rect_times.end());
	    sort(mc_times.begin(), mc_times.end());
	
	    double rect_median = rect_times[1];
	    double mc_median = mc_times[1];
	
	    threads_file << t << "," << rect_median << "," << mc_median << "\n";
	
	    cout << "Threads: " << t << " Rectangle: " << rect_median << " MonteCarlo: " << mc_median << " mc";
	}
	
	threads_file.close();

    return 0;
}
