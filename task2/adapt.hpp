#include <iostream>
#include <fstream>
#include <cmath>
#include <unordered_map>

using namespace std;

double f(double x);
double adapt_int(double a, double b, double eps, double Int_old, unordered_map<double, double>& points);