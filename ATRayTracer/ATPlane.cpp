//
//  ATPlane.cpp
//  ATRayTracer
//
//  Created by Andrew Taeoalii on 4/7/12.
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#include "ATPlane.h"

// default constructor
ATPlane::ATPlane()
{
    
}

// constructor specifies origin, normal, color
ATPlane::ATPlane(ATVector3D o, ATVector3D n, ATColor c)
{
    origin = o;
    normal = n;
    color  = c;
}

// copy constructor
ATPlane::ATPlane(const ATPlane& copy)
{
    origin = copy.origin;
    normal = copy.normal;
    color  = copy.color;
}

// destructor
ATPlane::~ATPlane()
{
    
}

// determines if a point intersects the plane
void ATPlane::intersect(ATRay ray, float* intersectPt1, float* intersectPt2) const
{
    *intersectPt2 = NAN;
    float denom = ATVector3D::dot(ray.direction, normal);
    if (fabsf(denom) < 0.00001f)
    {
        *intersectPt1 = NAN;
        return;
    }
    
    float numerator = ATVector3D::dot(ATVector3D::subtractTwoVectors(origin, ray.origin), normal);
    
    float intersection = numerator / denom;
    
    if(intersection < 0.0f)
        *intersectPt1 = NAN;
    else 
        *intersectPt1 = intersection;
}

// determines the normal for a point in a plane
ATVector3D ATPlane::pointNormal(ATVector3D point) const
{ 
    return ATVector3D::normalize(normal);
}

// returns the color of the plane
ATColor ATPlane::getColor() const
{
    return color;
}