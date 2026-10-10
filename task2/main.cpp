#include <iostream>
#include <fstream>
#include <cmath>
#include <unordered_map>

#include "adapt.hpp"

using namespace std;


int main() {
    double a = 0.0, b = M_PI;
    double epsilon = 0.001;

	unordered_map<double, double> points;
	
    double x0 = (a + b) / 2.0;
    double Int0 = f(x0) * (b - a);

    double total_sum = adapt_int(a, b, epsilon, Int0, points);

    ofstream file("results.csv"); 
    
    file << "x,length,value\n";
        
    for (const auto& pair : points) {
        double x = pair.first;
        double delta_x = pair.second;
        double fx = f(x);
            
        file << x << "," << delta_x << "," << fx << "\n"; 
    }
	
    file.close();

    cout << "Total sum: " << total_sum << "\n"; 
    
    return 0;
}
