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
            std::cout << "MAX ITERATIONS:                   "
                << maxit << std::endl;
            std::cout << "ELAPSED TIME:                     "
                << elapsed_time
                << " seconds" << std::endl;
            std::cout << std::defaultfloat;
        }

        void printActivity(){
            std::cout << method_name;
            std::cout << std::setprecision(16);
            std::cout << std::fixed;
            //approximate root
            std::cout << x << "\t\t\t\t\t\t" ;
            //function value
            std::cout << funval << "\t\t\t\t\t\t";
            //error
            std::cout << error << "\t\t\t\t\t\t";
            //niters
            std::cout << numit << "\t\t\t\t\t\t" << std::endl;
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

    RootScalarResult fixpoint(UniVarFunction &g, double x, param &parameter){
        timer stopwatch;
        stopwatch.start();
        std::string term_flag = "Success";
        double err = parameter.tol + 1.;
        int k = 0;
        double x_old;
        double gx;
        double c;


        while ((err > parameter.tol) && (k < parameter.maxit)){
            gx = g(x);
            x_old = x;
            x = g(x);
            err = std::abs(x - x_old);
            k++;
        }

        if ((err > parameter.tol) && (k == parameter.maxit)){
            term_flag = "Fail";
        }
        stopwatch.stop();
        return RootScalarResult(k, parameter.maxit, x, gx, err, parameter.tol, stopwatch.get_elapsed_time(), "FIXPOINT METHOD", term_flag);
    }

    RootScalarResult secant(UniVarFunction &f, double x0, double x1, param &parameter, std::string method_name){
        timer stopwatch;
        stopwatch.start();
        std::string term_flag = "Success";
        double err = parameter.tol + 1.;
        double f0 = f(x0);
        double f1 = f(x1);
        int k = 1;
        double q, x_temp;


        while ((err > parameter.tol) && (k < parameter.maxit)){
            q = (f1 - f0)/(x1-x0);
            x_temp = x1;
            x1 = x1 - (f1/q);
            x0 = x_temp;
            f0 = f1;
            f1 = f(x1);
            err = std::abs(x1 - x0) + std::abs(f1);
            k++;
        }

        if ((err > parameter.tol) && (k == parameter.maxit)){
            term_flag = "Fail";
        }
        stopwatch.stop();
        return RootScalarResult(k, parameter.maxit, x1, f1, err, parameter.tol, stopwatch.get_elapsed_time(), method_name, term_flag);
    }

    RootScalarResult regulafalsi(UniVarFunction &f, double x0, double x1, param &parameter,std::string method_name){
        timer stopwatch;
        stopwatch.start();
        std::string term_flag = "Success";
        double err = parameter.tol + 1.;
        double xarray[50];
        double farray[50];

        xarray[0] = x0;
        xarray[1] = x1;

        farray[0] = f(x0);
        farray[1] = f(x1);

        int k = 1;

        //extras
        double xc, fc, x_tild, f_tild, q, x;
        int k_tild;


        while ((err > parameter.tol) && (k < parameter.maxit)){
            xc = xarray[k];
            fc = farray[k];
            k_tild = k - 1;

            x_tild = xarray[k_tild];
            f_tild = farray[k_tild];

            while(((f_tild * fc) >= 0) && (k_tild > 1)){
                k_tild = k_tild - 1;
                x_tild = xarray[k_tild];
                f_tild = farray[k_tild];
            }
            q = (fc - f_tild)/(xc- x_tild);
            x = xc - (fc/q);
            xarray[k+1] = x;
            farray[k+1] = f(x);

            err = std::abs(x- xc) + std::abs(farray[k+1]);
            k++;
        }


        if ((err > parameter.tol) && (k == parameter.maxit)){
            term_flag = "Fail";
        }
        stopwatch.stop();
        return RootScalarResult(k, parameter.maxit, x, f(x), err, parameter.tol, stopwatch.get_elapsed_time(), method_name, term_flag);
    }

    RootScalarResult newton(UniVarFunction &f, UniVarFunction &fprime, double x, param &parameter, std::string method_name){
        timer stopwatch;
        stopwatch.start();
        std::string term_flag = "Success";
        double err = parameter.tol + 1.;
        double fx = f(x);
        int k = 0;
        double xold;


        while ((err > parameter.tol) && (k < parameter.maxit)){
            xold = x;
            x = x - (fx/fprime(x));
            fx = f(x);
            err = std::abs(x - xold) + std::abs(fx);
            k++;
        }

        if ((err > parameter.tol) && (k == parameter.maxit)){
            term_flag = "Fail";
        }
        stopwatch.stop();
        return RootScalarResult(k, parameter.maxit, x, fx, err, parameter.tol, stopwatch.get_elapsed_time(), method_name, term_flag);
    }
    
    RootScalarResult steffensen(UniVarFunction &f, double x, param &parameter, std::string method_name){
        timer stopwatch;
        stopwatch.start();
        std::string term_flag = "Success";
        double err = parameter.tol + 1.;
        double fx = f(x);
        int k = 0;
        double xold, q;


        while ((err > parameter.tol) && (k < parameter.maxit)){
            xold = x;
            q = (f(x + fx) - fx)/fx;
            x = x - (fx/q);
            fx = f(x);
            err = std::abs(x - xold) + std::abs(fx);
            k++;
        }

        if ((err > parameter.tol) && (k == parameter.maxit)){
            term_flag = "Fail";
        }
        stopwatch.stop();
        return RootScalarResult(k, parameter.maxit, x, fx, err, parameter.tol, stopwatch.get_elapsed_time(), method_name, term_flag);
    }
}
} // end of namespace root::scalar

#endif