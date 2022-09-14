#ifndef FERRARI_HPP_INCLUDE
#define FERRARI_HPP_INCLUDE

#include "complex.hpp"
#include "cardanoForFerrari.hpp"

//Evaluates az^4 + bz^3 + cz^2 +dz + e using nested multiplication.
complex_d_t evalQuarticPoly(double a, double b, double c, double d, double e, complex_d_t &z) {
    complex_d_t val;
    val = a*z + b;
    val = val*z + c;
    val = val*z + d;
    val = val*z + e;
    return val;
}

// Implementation of Ferrari's method for the solutions of the quartic
// equation az^4 + bz^3 + cz^2 +dz + e = 0

void ferrari(double a, double b, double c, double d, double e, complex_d_t x[]) {
    //parameters in Ferrari's formula
    complex_d_t p = (c/a) - ((3*b*b)/(8*a*a));
    complex_d_t q = (d/a) - (b*c/2*a*a) + ((b*b*b)/(8*a*a*a));
    complex_d_t r = (e/a) - ((b*d)/(4*a*a)) + ((b*b*c)/(16*a*a*a)) - ((3*b*b*b*b)/(256*a*a*a*a));

    //when p = 0
    if (p == 0.0){
        x[0] = std::sqrt((0.5)*(-p+std::sqrt((p*p)-(4.0*r)))) - (b/(4*a));
        x[1] = - std::sqrt((0.5)*(-p+std::sqrt((p*p)-(4.0*r)))) - (b/(4*a));
        x[2] = std::sqrt((0.5)*(-p-std::sqrt((p*p)-(4.0*r)))) - (b/(4*a));
        x[3] = - std::sqrt((0.5)*(-p-std::sqrt((p*p)-(4.0*r)))) - (b/(4*a));
    }
    else{
        //use cardano to find beta
        complex_d_t b_cardano[3];
        cardano(1.0, (2.0*p), ((p*p) - (4.0*r)), (-q*q), b_cardano);

        complex_d_t beta = b_cardano[1];

        x[0] = (0.5)*(-std::sqrt(beta) + std::sqrt(beta - (2.0*(p + beta + (q/(std::sqrt(beta))))))) - (b/(4*a));
        x[1] = (0.5)*(-std::sqrt(beta) - std::sqrt(beta - (2.0*(p + beta + (q/(std::sqrt(beta))))))) - (b/(4*a));
        x[2] = (0.5)*(std::sqrt(beta) + std::sqrt(beta - (2.0*(p + beta + (q/(std::sqrt(beta))))))) - (b/(4*a));
        x[3] = (0.5)*(std::sqrt(beta) - std::sqrt(beta - (2.0*(p + beta + (q/(std::sqrt(beta))))))) - (b/(4*a));
    }
    return;    
}

#endif