#include <functional>
#include <random>

using namespace std;

double IntegrateRectangle(function<double(double)> f, double a, double b, size_t N);
double IntegrateMonteCarlo(function<double(double)> f, double a, double b, size_t N, default_random_engine& engine);
double RelativeError(double approx, double exact);