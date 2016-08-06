import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import matplotlib.pyplot as plt
from utils import *
from numpy import genfromtxt
from mpl_toolkits.mplot3d import Axes3D
from mpl_toolkits.mplot3d.art3d import Poly3DCollection
from matplotlib.colors import LightSource
from matplotlib import cm
import mpl_toolkits

#Load point cloud
X = genfromtxt('array.csv', delimiter=',')
#X = genfromtxt('pts7875_045401.csv', delimiter=',')

#Find nearest neighbor of every point
d=dist_nearest(X)
dmax=np.max(d)

#Plot points
#X=filt(X,[0,1,0]) #Remove half of the points to make visualization clearer 
X = np.asarray(X)
X=np.transpose(X)
fig1 = plt.figure(figsize=(12,12))

#Figure out dimensions
s=np.shape(X)
spaceDim = s[0]
numPoints = s[1]
#print numPoints

ax1 = fig1.gca(projection='3d')

#Plot edges for fun
X=np.transpose(X)
for i in xrange(0,numPoints,1):
 for j in xrange(0,i,1):
     if(np.linalg.norm(X[i]-X[j])<=1.3*d[i]):
        ax1.plot([ X[i][0],X[j][0] ], [ X[i][1],X[j][1] ], [ X[i][2],X[j][2] ],linewidth=3,alpha=0.7,color='black')

X=np.transpose(X)
ax1.scatter(X[0], X[1], X[2], s=600, marker='.',color='b')
ax1.axis('off')
#Make sphere
r = 1.00
pi = np.pi
cos = np.cos
sin = np.sin
phi, theta = np.mgrid[0.0:pi:100j, 0.0:2.0*pi:100j]
x = r*sin(phi)*cos(theta)
y = r*sin(phi)*sin(theta)
z = r*cos(phi)

white = np.ones((z.shape[0], z.shape[1], 3))
red = white * np.array([0.1,.1,.1])
green = white * np.array([0,1,0])
blue = white * np.array([0,0,1])
light = LightSource(60, 45)
illuminated_surface = light.shade_rgb(red, z)
ax1.plot_surface(x, y, z,  rstride=1, cstride=1, antialiased=False, color='white', alpha=0.2, linewidth=0)

#Show nearest neighbor distances
#print("average dist: {}".format(np.average(d)))

plt.show()

