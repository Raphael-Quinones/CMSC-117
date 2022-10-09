#include "rootscalar.hpp"

double f(double x){
    return x * exp(-std::pow(x, 2)) - std::cos(x);
}

double fprime(double x){
    return std::sin(x) - (2*std::pow(x,2) * std::exp(-std::pow(x,2))) + exp(-std::pow(x, 2));
}

double fprimecenter(double x){
    double h = std::sqrt(std::exp(1));
    return (f(x + h) - f(x-h))/2*h;
}

double fprimeforward(double x){
    double h = std::sqrt(std::exp(1));
    return (f(x+h) - f(x))/h;
}

double fprimebackward(double x){
    double h = std::sqrt(std::exp(1));
    return (f(x) - f(x-h))/h;
}


int main(){
    //print filename
    std::cout << "File: " << __FILE__ <<std::endl;
    //parameter object
    root::scalar::param parameter;
    parameter.tol = 1e-15;
    parameter.maxit = 100;
    //approximate by all methods
    freopen("rootfinder.txt","w+",stdout);
    std::cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
    std:: cout << "METHOD\t\t\t\t\tAPPROXIMATE ROOT\t\t\t\t\t\tFUNCTION VALUE\t\t\t\t\t\t\tERROR\t\t\t\t\t\t\t\t\tNITERS" << std::endl;
    std::cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
    
    root::scalar::RootScalarResult  
        regulafalsiactivity = regulafalsi(f, 2., 1., parameter, "Regula Falsi             ");
    root::scalar::RootScalarResult  
        secantactivity = secant(f, 1., 2., parameter, "Secant                   ");
    root::scalar::RootScalarResult  
        newtonactivity = newton(f, fprime, 1., parameter, "Newton                   ");
    root::scalar::RootScalarResult  
        inexactnewtonactivity = newton(f, fprimecenter, 1., parameter, "Inexact Newton           ");
    root::scalar::RootScalarResult  
        steffensenactivity = steffensen(f, 2., parameter, "Steffensen               ");
    regulafalsiactivity.printActivity();
    secantactivity.printActivity();
    newtonactivity.printActivity();
    inexactnewtonactivity.printActivity();
    steffensenactivity.printActivity();

    std::cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
    std:: cout << "METHOD\t\t\t\t\tAPPROXIMATE ROOT\t\t\t\t\t\tFUNCTION VALUE\t\t\t\t\t\t\tERROR\t\t\t\t\t\t\t\t\tNITERS" << std::endl;
    std::cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
    root::scalar::RootScalarResult  
        inexactnewtoncenter = newton(f, fprimecenter, 1., parameter, "Center                   ");
    root::scalar::RootScalarResult  
        inexactnewtonforward = newton(f, fprimeforward, 1., parameter, "Forward                  ");
    root::scalar::RootScalarResult  
        inexactnewtonbackward = newton(f, fprimebackward, 1., parameter, "Backward                 ");
    inexactnewtoncenter.printActivity();
    inexactnewtonforward.printActivity();
    inexactnewtonbackward.printActivity();


    return 0;
}

