#ifndef GRADIENT_DESCENT_H
#define GRADIENT_DESCENT_H

#include <string.h>
#include <limits>
#include <ctime>
#include <cassert>
#include "optim_utils.h"

class grad_proj_method
{
    //cost function pointer supplied by user
    cost_function* f;
    //feasible set object provides nonexpansive projection operator
    feasible_set* S;
    //current and last state of the algorithm. x_bar is a value used in the armijo step
    std::vector<double> x,x_last,x_bar;
    //current and last value of the objective function
    double f_val,f_val_last;
    //current gradient of the objective function
    std::vector<double> df;
    //Constructor
    unsigned int n;
    //initial step size at each iteration
    double s0;
    //decreasing step size during armijo step
    double s;
    //coefficient for decreasing step size in armijo step
    double beta;
    //step size for central difference calculation in gradient. f_tol is the termination criteria.
    double grad_tol,f_tol,sigma;
    //counting iterations
    int max_iter,iter_count;
    
public:
    grad_proj_method(cost_function* _f,
                     feasible_set* _S,
                     decisionVar _x0,
                     double _beta,
                     double _s0,
                     double _sigma,
                     double _grad_tol,
                     double _f_tol,
                     int _max_iter)
    {
        f=_f;
        S=_S;
        x=_x0;
        x_last=99999*_x0;
        f_val=f->cost(x);
        f_val_last=f_val;
        beta=_beta;
        s0=_s0;
        s=s0;
        f_tol=_f_tol;
        sigma=_sigma;
        max_iter=_max_iter;
        grad_tol=_grad_tol;
    }
    
    //Uses the gradient (df) and state (x) to determine the step size to take
    void diminishing_step()
    {
        f_val_last = f_val;
        x_last = x;
        
        iter_count++;
        s=s/(iter_count);
        
        df = f->gradient(x,grad_tol);
        x = x_last-(s*(df));
        S->projection(x);
        f_val = f->cost(x);
        
        return;
    }
    
    //Armijo step for gradient projection
    void armijo_step()
    {
        s=s0;//Has to be reset to something at every iter
        iter_count++;
        f_val_last = f_val;
        x_last = x;
        
        
        df = f->gradient(x_last,grad_tol);
        x = S->projection(x_last-(s*(df)));
        while( f_val_last - f->cost(x) < sigma*dot(df,x_last-x) )
        {
            s *= beta;
            x = S->projection(x_last-s*df);
        }
        f_val = f->cost(x);
        
        return;
    }
    
    decisionVar optimize()
    {
        iter_count = 0;
        do{
            armijo_step();
//                         printf("Iteration: %6d, Objective: %17.14f\n", (int) iter_count, (double) f_val);
        }while( iter_count<max_iter and fabs(f_val-f_val_last)>f_tol);
        
        print_sol(f_val,iter_count);
        return x;
    }
    
};
#endif