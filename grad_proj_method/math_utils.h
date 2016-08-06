#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <cstdio>
#include <vector>
#include <cmath>
#include <cassert>
#include <iostream>
#include<fstream>

/*** Vector Operations ***/

std::vector<double> operator+(const std::vector<double>& x, const std::vector<double>& y)
{
    assert(x.size()==y.size());
    std::vector<double> z(x.size());
    for(int i=0;i<x.size();i++)
    {
        z.at(i)=x.at(i)+y.at(i);
    }
    
    return z;
}

std::vector<double> operator-(const std::vector<double>& x, const std::vector<double>& y)
{
    assert(x.size()==y.size());
    std::vector<double> z(x.size());
    for(int i=0;i<x.size();i++)
    {
        z.at(i)=x.at(i)-y.at(i);
    }
    
    return z;
}

std::vector<double> operator*(const double& c, const std::vector<double>& x)
{
    std::vector<double> z(x.size());
    for(int i=0;i<x.size();i++)
    {
        z.at(i)=c*x.at(i);
    }
    
    return z;
}

void disp(std::vector<double>& x)
{
    printf("vector:\n");
    for(int i=0;i<x.size();i++)
    {
        printf("%f\n",x.at(i));
    }
}

//inner product
double dot(const std::vector<double>& x,const std::vector<double>& y)
{
    double z=0;
    for(int i=0;i<x.size();i++)
    {
        z += x.at(i)*y.at(i);
    }
    return z;
}

double operator*(const std::vector<double>& x, const std::vector<double>&y)
{
    double z=0;
    for(int i=0;i<x.size();i++)
    {
        z += x.at(i)*y.at(i);
    }
    return z;
}
//multiply a vector by a scalar
std::vector<double> scalarMult(const double c,const std::vector<double>& x)
{ 
    std::vector<double> y=x;
    for(int i=0;i<x.size();i++)
    {
        y.at(i)*=c;
    }
    
    return y;
}

double sqr(const double& x)
{
    return x*x;
}

/*** Vector Operations ***/
double norm2(const std::vector<double>& x)
{
    double norm=0;
    for(int i=0; i<x.size(); i++)
    {
        norm=norm+sqr(x.at(i));
    }
    return std::sqrt(norm);
}

double norm_sqr(const std::vector<double>& x)
{
    double norm=0;
    for(int i=0; i<x.size(); i++)
    {
        norm=norm+sqr(x.at(i));
    }
    return norm;
}

void normalize(std::vector<double>& x)
{
    double r=norm2(x);
    
    for(int i=0;i<x.size();i++)
    {
        x[i] = x[i]/r;
        
    }
    return;
}

void printVector(const std::vector<double>& x)
{
    std::cout << "Vector: " << std::endl;
    for(int i=0;i<x.size();i++)
    {
        std::cout << x[i] << std::endl ;
    }
}

//Fortran style reshape
std::vector < std::vector<double> > reshape(int n, int N, std::vector<double> x)
{
    std::vector < std::vector<double> > y(N);
    for(int j=0;j<N;j++)
    {
        for(int i=0;i<n;i++)
        {
            y[j].push_back(x[n*j+i]);
        }
    }
    return y;    
}

void vec_to_csv(std::vector<double>& x)
{
    std::ofstream file;
    file.open ("points.csv");
    //Point j of N points
    for(int j=0;j<x.size()-1;j++)
    {   
        
            file << x[j] << ","; 
        
    }
    file << x.back();
    file.close();
}

void array_to_csv(std::vector< std::vector<double> > y)
{
    int numPoints=y.size();
    int spaceDim=y[0].size();
    std::ofstream file;
    file.open("array.csv");
    for(int j=0;j<numPoints;j++)
    {
     
        for(int i=0;i<spaceDim-1;i++)
        {
            file << y[j][i] << ",";
        }
        file << y[j][spaceDim-1] << std::endl;
    }
        file.close();
}


#endif



