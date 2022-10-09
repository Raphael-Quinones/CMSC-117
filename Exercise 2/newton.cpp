#include "rootscalar.hpp"

double f(double x){
    return x * exp(-std::pow(x, 2)) - std::cos(x);
}

double fprime(double x){
    return std::sin(x) - (2*std::pow(x,2) * std::exp(-std::pow(x,2))) + exp(-std::pow(x, 2));
}

int main(){
    //print filename
    std::cout << "File: " << __FILE__ <<std::endl;
    //parameter object
    root::scalar::param parameter;
    parameter.tol = 1e-15;
    parameter.maxit = 50;
    //approximate a root by newton method
    freopen("newton.txt","w+",stdout);
    root::scalar::RootScalarResult  
        result = newton(f, fprime, 1., parameter);
    result.print();
    return 0;
}

