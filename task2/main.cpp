#include <iostream>
#include <fstream>
#include <cmath>
#include <unordered_map>
#include <chrono>
#include <iomanip>

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

    double exact = M_PI * M_PI - 4.0;

    cout << "Analytical res: " << exact << "\n";
    cout << "Error: " << abs(total_sum - exact) << "\n";


    ofstream file_eps("eps_vs_speed.csv");
    file_eps << "eps,steps,time_ms,res,error\n";

    for (double eps = 0.1; eps >= 1e-6; eps /= 2.0) {
        points.clear();

        x0 = (a + b) / 2.0;
        Int0 = f(x0) * (b - a);

        auto start = chrono::high_resolution_clock::now();

        double res = adapt_int(a, b, eps, Int0, points);

        auto finish = chrono::high_resolution_clock::now();

        double time_ms = chrono::duration<double, milli>(finish - start).count();

        size_t steps = points.size();
        double err = abs(res - exact);

        file_eps << setprecision(16) << eps << "," << steps << "," << time_ms << "," << res << "," << err << "\n";
    }

    file_eps.close();

    ofstream file_parts("parts.csv");
    file_parts << "parts,res,error,steps,time_ms\n";

    for (int N = 1; N <= 100; ++N) {
        points.clear();

        double h = (b - a) / N;
        double sum = 0.0;

        auto start = chrono::high_resolution_clock::now();

        for (int i = 0; i < N; ++i) {
            double left = a + i * h;
            double right = left + h;

            double mid = (left + right) / 2.0;
            double Int_part = f(mid) * (right - left);

            sum += adapt_int(left, right, epsilon, Int_part, points);
        }

        auto finish = chrono::high_resolution_clock::now();

        double time_ms = chrono::duration<double, milli>(finish - start).count();

        size_t steps = points.size();
        double err = abs(sum - exact);

        file_parts << setprecision(16) << N << "," << sum << "," << err << "," << steps << "," << time_ms << "\n";
    }

    file_parts.close();

    return 0;
}