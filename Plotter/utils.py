import numpy as np

#yeah, linear search
def dist_nearest(X):
    #X=np.transpose(X)
    s=np.shape(X)
    N=s[0]
    n=s[1]
    d = 8888*np.ones((N,N))
    for j in xrange(0,N,1):
        for i in xrange(0,N,1):
            d[i][j] = np.linalg.norm(X[i]-X[j])
            
    d=d+99999*np.eye(N);
    np.savetxt("data.txt", d)
    dmin=np.amin(d, axis=0)
    return dmin

def filt(X,c):
    x=list()
    s=np.shape(X)
    N=s[0]
    for i in xrange(0,N):
        if c[0]*X[i][0]+c[1]*X[i][1]+c[2]*X[i][2]<=.05:
            x.append([X[i][0],X[i][1],X[i][2]])
    return x