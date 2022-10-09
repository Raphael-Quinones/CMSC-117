#include "rootscalar.hpp"

double f(double x){
    return x * exp(-std::pow(x, 2)) - std::cos(x);
}

int main(){
    //print filename
    std::cout << "File: " << __FILE__ <<std::endl;
    //parameter object
    root::scalar::param parameter;
    parameter.tol = 1e-15;
    parameter.maxit = 50;
    //approximate a root by regulafalsi method
    freopen("regulafalsi.txt","w+",stdout);
    root::scalar::RootScalarResult  
        result = regulafalsi(f, 2., 1., parameter);
    result.print();
    return 0;
}

