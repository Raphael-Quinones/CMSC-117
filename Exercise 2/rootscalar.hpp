#ifndef ROOTSCALAR_HPP_INCLUDE
#define ROOTSCALAR_HPP_INCLUDE

//standard library includes
#include <iostream>
#include <iomanip>
#include <climits>
#include <cmath>

//local include
#include "timer.hpp"

namespace root { namespace scalar{
    //type for a function with input and output having the type double
    using UniVarFunction = double(double);

    //struct for parameters in scalar-root finding algorithms
    struct param{
        double tol = std::numeric_limits<double>::epsilon();
        int maxit = 1000;
    };

    //struct for solution to scalar-root finding problems
    struct RootScalarResult{
        int numit;
        int maxit;
        double x;
        double funval;
        double error;
        double tol;
        double elapsed_time;
        std::string method_name;
        std::string termination_flag;

        //default constructor
        RootScalarResult(){}

        //user-defined constructor
        RootScalarResult(const int &numit, const int &maxit, const double &x, const double &funval, const double &error, const double &tol, const double &elapsed_time, const std::string &method_name, const std::string &termination_flag){
            this->numit = numit;
            this->maxit = maxit;
            this->x = x;
            this->funval = funval;
            this->error = error;
            this->tol = tol;
            this->elapsed_time = elapsed_time;
            this->method_name = method_name;
            this->termination_flag = termination_flag;
        }

        void print(){
            std::cout << "ROOT FINDER:                      "
                << method_name << std::endl;
            std::cout << std::setprecision(16);
            std::cout << std::fixed;
            std::cout << "APPROXIMATE ROOT / LAST ITERATE:  "
                << x << std::endl;
            std::cout << "TERMINATION:                      "
                << termination_flag << std::endl;
            std::cout << std::scientific;
            std::cout << "FUNCTION VALUE:                   "
                << funval << std::endl;
            std::cout << "ERROR:                            "
                << error << std::endl;
            std::cout << "TOLERANCE:                        "
                << tol << std::endl;
            std::cout << "NUM ITERATIONS:                   "
                << numit << std::endl;
            std::cout << "ELAPSED TIME:                     "
                << elapsed_time
                << " seconds" << std::endl;
            std::cout << std::defaultfloat;
        }
    };

    //bisection method for approximating a solutino of scalar equation f(x) = 0.
    RootScalarResult bisection(UniVarFunction &f, double a, double b, param &parameter){
        timer stopwatch;
        stopwatch.start();
        std::string term_flag = "Success";
        double err = b - a;
        double fa = f(a);
        double fb = f(b);
        int k = 0;
        double c;
        if (fa == 0){
            c = a;
            err = 0;
        }

        if (fb == 0){
            c = b;
            err = 0;
        }

        if (fa*fb > 0){
            std::cerr << "Method Fails!" << std::endl;
            return RootScalarResult();
        }

        //main loop
        double fc;
        while ((err > parameter.tol) && (k < parameter.maxit)){
            c = (a + b)/2.0;
            fc = f(c);
            if (fc*fa > 0){
                a = c;
                fa = fc;
            }
            else{
                b = c;
            }
            err = std:: abs(b-a);
            k++;
        }
        if ((err > parameter.tol) && (k == parameter.maxit)){
            term_flag = "Fail";
        }
        stopwatch.stop();
        return RootScalarResult(k, parameter.maxit, c, fc, err, parameter.tol, stopwatch.get_elapsed_time(), "BISECITON METHOD", term_flag);
    }
}
} // end of namespace root::scalar

#endif