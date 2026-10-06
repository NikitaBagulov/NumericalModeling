#include <functional>
#include <random>

using namespace std;

double IntegrateRectangle(function<double(double)> f, double a, double b, size_t N, int num_thr);
double IntegrateMonteCarlo(function<double(double)> f, double a, double b, size_t N, unsigned int base_seed, int num_thr);
double RelativeError(double approx, double exact);