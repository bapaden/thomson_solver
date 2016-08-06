#ifndef OPTIM_UTILS_H
#define OPTIM_UTILS_H

#include <cstdio>
#include <vector>
#include <cassert>
#include <cmath>
#include <float.h>
#include "math_utils.h"

typedef std::vector<double> decisionVar;


class feasible_set
{
public:
   virtual decisionVar projection(const decisionVar& x)=0; 
};

class cost_function
{
    std::vector<double> grad;
    std::vector<double> forward;
    std::vector<double> backward;
public:
  cost_function()
  {
      return;
  }
  virtual double cost(decisionVar& x)=0; 
  
  
  
  std::vector<double> gradient(const std::vector<double>& x, double tol)
  {
      grad.resize(x.size());
      forward = x;
      backward = x;
      
      double delta=tol;
      double grad_approx;
      int count;
      
      for(int i=0;i<x.size();i++)
      {
          forward = x;
          backward = x;
          
          forward.at(i)+=delta;
          backward.at(i)-=delta;
          grad_approx=(cost(forward)-cost(backward))/(2.0*delta);
          grad.at(i)=grad_approx;
      }
      return grad;
  }
  
};

void print_sol(double fval ,int iters)
{
    printf("Solution found in %d iterations\n",iters);
    printf("Minimum cost: %f\n",fval);
    
    return;
}

void read_params(int& spaceDim, 
                 int& numPoints, 
                 double& alpha,
                 int& max_iter, 
                 double& f_tol, 
                 double& grad_tol,
                 double& s0,
                 double& sigma,
                 double& beta
)

{
    std::string s;
    std::ifstream config_file;
    config_file.open("../parameters.config");
    
    config_file >> s;
    config_file >> s;
    config_file >> s;
    
    spaceDim = std::stoi(s);
    
    config_file >> s;
    config_file >> s;
    numPoints = std::stoi(s);
    
    config_file >> s;
    config_file >> s;
    alpha = std::stod(s);
    
    config_file >> s;
    config_file >> s;
    config_file >> s;
    config_file >> s;
    max_iter = std::stoi(s);
    
    config_file >> s;
    config_file >> s;
    f_tol = std::stod(s);
    
    config_file >> s;
    config_file >> s;
    grad_tol = std::stod(s);
    
    config_file >> s;
    config_file >> s;
    config_file >> s;
    sigma = std::stod(s);
    
    config_file >> s;
    config_file >> s;
    beta = std::stod(s);
    
    config_file >> s;
    config_file >> s;
    s0 = std::stod(s);
    
    return;
}



#endif