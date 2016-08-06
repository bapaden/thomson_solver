# Solver for the generalized Thomson problem
This code solves for local extrema to the generalized Thomson problem in arbitrary dimensions, and for any power law defining the objective. There are no dependancies. However, a python visualization is included which requires some basic python packages like matplotlib and numpy.   

# Solver details  
The gradient projection method is used with an Armijo-like step rule  described in Dimitri Bertsekas' text on nonlinear programming (pg. 218).  

#Compiling Instructions  
Compile using CMAKE. For linux there is a bash script setup.sh that will create a build directory and compile the source. From the terminal:  

./setup.sh

#Usage
The problem and solver parameters can be specified by modifying the values in the parameters.config file.  

After compiling, there will be an executable generalized_thomson_problem. To run the solver and plot the results (asuming they are 3d) execute the run.sh script. From the terminal:  

./run.sh  

Plotting the results requires python and the python packages matplotlib and numpy
