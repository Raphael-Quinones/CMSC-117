#include "rootscalar.hpp"

double f(double x){
    return x * exp(-std::pow(x, 2)) - std::cos(x);
}

double fprime(double x){
    double h = std::sqrt(std::exp(1));
    return (f(x + h) - f(x-h))/2*h;
}

int main(){
    //print filename
    std::cout << "File: " << __FILE__ <<std::endl;
    //parameter object
    root::scalar::param parameter;
    parameter.tol = 1e-15;
    parameter.maxit = 100;
    //approximate a root by inexactNewtonCentered method
    freopen("inexactNewtonCentered.txt","w+",stdout);
    root::scalar::RootScalarResult  
        result = newton(f, fprime, 1., parameter);
    result.print();
    return 0;
}

