import TasmanianSG
import numpy as np

# imports specifically needed by the examples
import math
from random import uniform
from datetime import datetime
from matplotlib import pyplot as plt


print("\n-------------------------------------------------------------------------------------------------")
print("\n-------------------------------------------------------------------------------------------------")
print("Interpolation of oscillatory function")

print("\n-------------------------------------------------------------------------------------------------")
print("\n-------------------------------------------------------------------------------------------------\n")


no_pts=1000
no_dim=1
c=np.ones(no_dim)
w=np.ones(no_dim)
aPnts = np.empty([no_pts, no_dim])
for iI in range(no_pts):
    for iJ in range(no_dim):
        aPnts[iI][iJ] = uniform(-1.0, 1.0)
        
# Result
aTres = np.empty([no_pts,])
for iI in range(no_pts):
    aTres[iI] = math.cos(2*math.pi*w[0]+np.matmul(c,aPnts[iI,:]))
    

#############################  FIXED GRID ###############################
print("\n-------------------------------------------------------------------------------------------------")
print("FIXED SPARSE GRID")
print("\n-------------------------------------------------------------------------------------------------")


grid  = TasmanianSG.TasmanianSparseGrid()   
    
# Sparse Grid with dimension 2 and 1 output and refinement level 5
iDim = no_dim
iOut = 1
iDepth = 10
which_basis = 1 #1= linear basis functions -> Check the manual for other options

fError_fixed=np.empty([iDepth,])
iNumP1_fixed=np.empty([iDepth,])
# construct sparse grid
for iK in range(iDepth):
    grid.makeLocalPolynomialGrid(iDim, iOut, iK, which_basis, "localp")
    aPoints = grid.getPoints()
    iNumP1_fixed[iK] = grid.getNumPoints()
    aVals = np.empty([aPoints.shape[0], 1])
    for iI in range(aPoints.shape[0]):
        aVals[iI] = math.cos(2*math.pi*w[0]+np.matmul(c,aPoints[iI,:]))
    grid.loadNeededPoints(aVals)
    # compute the error
    aRes = grid.evaluateBatch(aPnts)
    fError_fixed[iK] = max(np.fabs(aRes[:,0] - aTres))
    print(" No:{0:9d} No Pts: {1:9e}  Max Err: {2:1.2e}".format(iK+1,iNumP1_fixed[iK], fError_fixed[iK]))

#plt.figure(1)
#plt.plot(range(iDepth),fError_fixed)
#plt.xlabel("Depth")
#plt.ylabel("Error")
#plt.title("Fixed grid")
#plt.show()   

f1=open("fix_sparse_grid_err.txt", 'a')
np.savetxt(f1, fError_fixed)
f1.close()

f11=open("fix_sparse_grid_noPts.txt", 'a')
np.savetxt(f11, iNumP1_fixed)
f11.close()


############################# ADAPTIVE GRID  ######################################

print("\n-------------------------------------------------------------------------------------------------")
print("ADAPTIVE SPARSE GRID")
print("\n-------------------------------------------------------------------------------------------------")

iDim = no_dim
iOut = 1
iDepth = 1
which_basis = 1 #1= linear basis functions -> Check the manual for other options
refinement_level = 9
fTol = 1.E-5

grid1 = TasmanianSG.TasmanianSparseGrid()

grid1.makeLocalPolynomialGrid(iDim, iOut, iDepth, which_basis, "localp")
aPoints = grid1.getPoints()
aVals = np.empty([aPoints.shape[0], 1])
for iI in range(aPoints.shape[0]):
    aVals[iI] = math.cos(2*math.pi*w[0]+np.matmul(c,aPoints[iI,:]))
grid1.loadNeededPoints(aVals)
aRes = grid1.evaluateBatch(aPnts)

    
fError_adaptive=np.empty([refinement_level+1,])
iNumP1_adaptive=np.empty([refinement_level+1,])
iNumP1_adaptive[0] = grid1.getNumPoints()
fError_adaptive[0] = max(np.fabs(aRes[:,0] - aTres))


for iK in range(refinement_level):
    grid1.setSurplusRefinement(fTol, 1, "fds")   #also use fds, or other rules
    aPoints = grid1.getNeededPoints()
    aVals = np.empty([aPoints.shape[0], 1])
    for iI in range(aPoints.shape[0]):
        aVals[iI] = math.cos(2*math.pi*w[0]+np.matmul(c,aPoints[iI,:]))
    grid1.loadNeededPoints(aVals)
    iNumP1_adaptive[iK+1] = grid1.getNumPoints()
    aRes = grid1.evaluateBatch(aPnts)
    fError_adaptive[iK+1] = max(np.fabs(aRes[:,0] - aTres))
    print(" No:{0:9d} No Pts: {1:9e}  Max Err: {2:1.2e}".format(iK+1, iNumP1_adaptive[iK+1], fError_adaptive[iK+1]))
    
#plt.figure(2)
#plt.plot(range(refinement_level),fError_adaptive)
#plt.xlabel("refinement")
#plt.ylabel("Error")
#plt.title("Adaptive grid")
#plt.show()


f2=open("Adaptive_sparse_err.txt", 'a')
np.savetxt(f2, fError_adaptive, fmt='% 2.16f')
f2.close()

f22=open("Adaptive_sparse_npPts.txt", 'a')
np.savetxt(f22, fError_adaptive)
f22.close()

