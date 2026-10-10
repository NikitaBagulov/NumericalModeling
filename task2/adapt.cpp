#include <iostream>
#include <fstream>
#include <cmath>
#include <unordered_map>

#include "adapt.hpp"

using namespace std;

double f(double x) {
    return pow(x, 2)*sin(x); 
}

double adapt_int(double a, double b, double eps, double Int_old, unordered_map<double, double>& points) {
    double mid = (a + b) / 2.0;
    double h = (b - a) / 2.0;

    double x11 = a + h / 2.0;
    double x12 = mid + h / 2.0;

    double Int_left = f(x11) * h;
    double Int_right = f(x12) * h;
    double Int_new = Int_left + Int_right;

    if ((Int_old - Int_new) < eps) {
        points[x11] = h;
        points[x12] = h;
        return Int_new;
    } else {
        return adapt_int(a, mid, eps / 2.0, Int_left, points) + 
               adapt_int(mid, b, eps / 2.0, Int_right, points);
    }
}