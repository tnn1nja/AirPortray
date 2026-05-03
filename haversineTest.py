from math import sin, cos

def distance(pi1, lambda1, pi2, lambda2):
    earthRadius = 6378000
    deltaPi = pi2 - pi1
    deltaLambda = lambda2 - lambda1
    theta = (1 - cos(deltaPi) + cos(pi1)*cos(pi2)*(1 - cos(deltaLambda)))/2
    return theta * earthRadius

