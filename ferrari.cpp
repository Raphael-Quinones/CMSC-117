/* Sample implementation of Ferrari's formula */
#include <iomanip>
#include <cstdio>
#include "ferrari.hpp"

int main(){
    //coefficients
    double a = 2, b = 0, c = -2, d = -4, e = -16;
    //pre-allocate array of solutions
    complex_d_t x[4];
    //apply Ferrari's formula
    ferrari(a, b, c, d, e, x);
    freopen("ferrari.txt","w+",stdout);
    std::cout << "The solutions of the quartic equation f(x) = " 
        << a << "x^4 + " << b << "x^3 + " << c << "x^2 + " << d << " x " << e << " = 0 "
        << "are:" << std::endl;
    //print solutions and function values
    std::cout << std::scientific <<std::setprecision(8);
    for (int k = 0; k < 4; k++){
        std::cout << "x = " << x[k] << "\t";
        std::cout << "f(x) = " << evalQuarticPoly(a, b, c, d, e, x[k]) << std::endl;
    } 
    return 0;
}