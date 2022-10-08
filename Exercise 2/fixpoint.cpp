#include "rootscalar.hpp"

double g(double x){
    return (std::cos(x))/std::exp(x);
}

int main(){
    //print filename
    std::cout << "File: " << __FILE__ <<std::endl;
    //parameter object
    root::scalar::param parameter;
    parameter.tol = 1e-15;
    parameter.maxit = 500;
    //approximate a root by fixpoint method
    freopen("fixpoint.txt","w+",stdout);
    root::scalar::RootScalarResult  
        result = fixpoint(g, 0.5, parameter);
    result.print();
    return 0;
}

