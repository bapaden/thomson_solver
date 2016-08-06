#include <memory>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>
//Gradient_projection method with Bertsekas' armijo-like step size
#include "grad_proj_method/gradient_projection_method.h"

//This funtion is used to generate a random initial configuration of points on the n-sphere
std::vector< double > uniformSamplesSn(const int spaceDim, const int numPoints)
{
    //Generate random seed
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::normal_distribution<double> distribution(0.0,1.0);
    std::vector<double> points(0);
    double normal_rv,nearest;
    std::vector< double > point(0);
    for(int j=0;j<numPoints;j++)
    {
        //get standard normal rv on R^m
        for(int i=0;i<spaceDim;i++)
        {
            normal_rv = (double) distribution(generator);
            point.push_back(normal_rv);
        }
        //normalize to get uniform dist on S^m
        normalize(point);
        points.insert( points.end(), point.begin(), point.end() );
        point.clear();
    }
    
    return points;
}

//Feasible set and projection for gradient-projection method    
class unit_sphere: public feasible_set
{
    int numPoints;
    int spaceDim;
public:
    unit_sphere(int _spaceDim, int _numPoints)
    {
        numPoints=_numPoints;
        spaceDim=_spaceDim;
    }
    
    //Takes numPoints vectorized points in R^spaceDim and normalizes them with ||.||_2
    decisionVar projection(const decisionVar& x)
    {
        double r=0;
        std::vector<double> y=x;
        for(int j=0;j<numPoints;j++)
        {
            r=0;
            for(int i=0;i<spaceDim;i++)
            {
                r+=sqr(y[spaceDim*j+i]);
            }
            r=sqrt(r);
            if(r>=1.0)
            {
                for(int i=0;i<spaceDim;i++)
                {
                    y[spaceDim*j+i] = y[spaceDim*j+i]/r;
                }
            }
        }
        return y;
    }
};

//Objective for generalized Thomson problem
class generalized_energy: public cost_function
{
    
public:
    int spaceDim;
    int numPoints;
    double alpha;
    generalized_energy(int _spaceDim, int _numPoints, double _alpha)
    {
        spaceDim=_spaceDim;
        numPoints=_numPoints;
        alpha=_alpha;
        return;
    }
    double cost(decisionVar& x)
    {
        double c=0;
        double d=0;
        //Distances squared
        for(int k=0;k<numPoints;k++)
        {
            //point j compared to point k
            for(int j=0;j<k;j++)
            {
                d=0;
                for(int i=0;i<spaceDim;i++)
                {
                    d+= sqr(x[spaceDim*j+i]-x[spaceDim*k+i]);
                }
                
                if(alpha>0)
                    c-=pow(sqrt(d),alpha);
                else if(alpha<0)
                    c+=pow(sqrt(d),alpha);
                else
                    c+=log(1.0/d);
            }
        }
        return c;
    }
};

int main(int argc, char **argv) {
    
    
    int spaceDim;
    int numPoints; 
    double alpha;
    int  max_iter; 
    double  f_tol;
    double  grad_tol;
    double  s0;
    double  sigma;
    double  beta;
    
	//Function to read these values from parameters.config
    read_params(spaceDim, 
                numPoints, 
                alpha,
                max_iter, 
                f_tol, 
                grad_tol,
                s0,
                sigma,
                beta);
    //Cost function
    generalized_energy myCost(spaceDim,numPoints,alpha);
    //Projection operator
    unit_sphere S(spaceDim,numPoints);
    //Initial condition
    std::vector<double> x0 = uniformSamplesSn(spaceDim,numPoints);
    //Initialize solver
    grad_proj_method gd(&myCost,
                        &S,
                        x0,
                        beta,
                        s0,
                        sigma,
                        grad_tol,
                        f_tol,
                        max_iter);
    
    decisionVar x = gd.optimize();
    
    //Record results to a text file
    std::vector< std::vector<double> > y = reshape(spaceDim,numPoints,x);
    array_to_csv(y);
    
    return 0;
}
