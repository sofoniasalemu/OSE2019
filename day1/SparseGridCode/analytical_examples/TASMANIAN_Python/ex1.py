import TasmanianSG
import numpy as np

# imports specifically needed by the examples
import math
from random import uniform
from datetime import datetime

print("TasmanianSG version: {0:s}".format(TasmanianSG.__version__))
print("TasmanianSG license: {0:s}".format(TasmanianSG.__license__))

grid  = TasmanianSG.TasmanianSparseGrid()
grid1 = TasmanianSG.TasmanianSparseGrid()
grid2 = TasmanianSG.TasmanianSparseGrid()



#############################################################################

# Oscillatory function
print("\n-------------------------------------------------------------------------------------------------")
print("\n-------------------------------------------------------------------------------------------------")
print("Interpolation of oscillatory function")
print("       the error is estimated as the maximum from 1000 random points\n")



print("\n-------------------------------------------------------------------------------------------------")
print("       using fixed sparse grid with depth {0:1d}".format(iDepth))
# 1000 2-dimensional sample points
no_pts=1000
no_dim=4
c=np.ones(no_dim)
w=np.ones(no_dim)
aPnts = np.empty([no_pts, no_dim])
for iI in range(no_pts):
    for iJ in range(no_dim):
        aPnts[iI][iJ] = uniform(-1.0, 1.0)

# Result
aTres = np.empty([no_pts,])
for iI in range(no_pts):
    aTres[iI] = math.cos(2*math.pi*w[0]+c@aPnts[iI,:])


# Sparse Grid with dimension 2 and 1 output and refinement level 5
iDim = no_dim
iOut = 1
iDepth = 5
which_basis = 1 #1= linear basis functions -> Check the manual for other options



# construct sparse grid
grid.makeLocalPolynomialGrid(iDim, iOut, iDepth, which_basis, "localp")
aPoints = grid.getPoints()
#iNumP1 = aPoints.shape[0]
aVals = np.empty([aPoints.shape[0], 1])
for iI in range(aPoints.shape[0]):
    aVals[iI] = math.cos(2*math.pi*w[0]+c@aPoints[iI,:])
grid.loadNeededPoints(aVals)

# compute the error
aRes = grid.evaluateBatch(aPnts)
fError1 = max(np.fabs(aRes[:,0] - aTres))
print(" For localp    Number of points: {0:1d}   Max. Error: {1:1.16e}".format(iNumP1, fError1))

f=open("fix_sparse_grid.txt", 'a')
np.savetxt(f, aPoints, fmt='% 2.16f')
f.close()


print("\n-------------------------------------------------------------------------------------------------")
print("   tolerance is set at 1.E-5 and piecewise linear basis functions are used\n")
print("               Classic refinement ")
print(" refinement level         points     error   ")


iDim = no_dim
iOut = 1
iDepth = 5
which_basis = 1 #1= linear basis functions -> Check the manual for other options
refinement_level = 5

grid1.makeLocalPolynomialGrid(iDim, iOut, iDepth, which_basis, "localp")
aPoints = grid1.getPoints()
aVals = np.empty([aPoints.shape[0], 1])
for iI in range(aPoints.shape[0]):
    aVals[iI] = math.cos(2*math.pi*w[0]+c@aPoints[iI,:])
grid1.loadNeededPoints(aVals)

#refinement level
for iK in range(refinement_level):
    grid1.setSurplusRefinement(fTol, 1, "fds")   #also use fds, or other rules
    aPoints = grid1.getNeededPoints()
    aVals = np.empty([aPoints.shape[0], 1])
    for iI in range(aPoints.shape[0]):
        aVals[iI] = math.cos(2*math.pi*w[0]+c@aPoints[iI,:])
    grid1.loadNeededPoints(aVals)

    aRes = grid1.evaluateBatch(aPnts)
    fError1 = max(np.fabs(aRes[:,0] - aTres))
    print(" {0:9d} {1:9d}  {2:1.2e}".format(iK+1, grid1.getNumPoints(), fError1))

# write coordinates of grid to a text file
f2=open("Adaptive_sparse_grid.txt", 'a')
np.savetxt(f2, aPoints, fmt='% 2.16f')
f2.close()

grid2 = TasmanianSG.TasmanianSparseGrid()
grid2.makeLocalPolynomialGrid(iDim, iOut, refinement_level+iDepth, which_basis, "localp")
a = grid2.getNumPoints()

print("\n-------------------------------------------------------------------------------------------------")
print( "   a fix sparse grid of level ", refinement_level+iDepth, " would consist of " ,a, " points")
print("\n-------------------------------------------------------------------------------------------------\n")
