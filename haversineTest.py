from math import sin, cos, asin, sqrt, pi
earthRadius = 6371000

def distance(phi1, lambda1, phi2, lambda2):
    phi1 = phi1 * pi/180
    lambda1 = lambda1 * pi/180
    phi2 = phi2 * pi/180
    lambda2 = lambda2 * pi/180

    deltaphi = phi2 - phi1
    deltaLambda = lambda2 - lambda1
    haversineTheta = (1 - cos(deltaphi) + cos(phi1)*cos(phi2)*(1 - cos(deltaLambda)))/2
    theta = 2*asin(sqrt(haversineTheta))
    print(theta * earthRadius)

distance(50, -100, 30, -90)

