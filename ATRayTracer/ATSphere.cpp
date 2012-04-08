//
//  ATSphere.cpp
//  ATRayTracer
//
//  Created by Andrew Taeoalii on 4/7/12.
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#include "ATSphere.h"
#include <iostream>

// default constructor
ATSphere::ATSphere()
{
    origin = ATVector3D(0.0f, 0.0f, -1.0f);
    radius = 1.0f;
    color  = ATColor(1.0f, 1.0f, 1.0f, 0.0f);
}

// constructor specifies radius and origin
ATSphere::ATSphere(float rad, ATVector3D o, ATColor col)
{
    radius = rad;
    origin = o;
    color  = col;
}

// copy constructor
ATSphere::ATSphere(const ATSphere& copy)
{
    radius = copy.radius;
    origin = copy.origin;
}

// destructor
ATSphere::~ATSphere()
{
    
}

// intersection point
void  ATSphere::intersect(ATRay ray, float* intersectPt1, float* intersectPt2) const
{
    ATVector3D v = ATVector3D::subtractTwoVectors(ray.origin, origin);
    
    float a = ATVector3D::dot(ray.direction, ray.direction);
    float b = 2.0f * ATVector3D::dot(ray.direction, v);
    float c = ATVector3D::dot(v, v) - radius * radius;
    
    float determinant = b*b - 4.0f*a*c;
    
    if (determinant < 0.0f)
    {
        *intersectPt2 = NAN;
        *intersectPt1 = NAN;
        return;
    }
    
    float sqrtdet = sqrtf(determinant);
    float nearPt = (-b - sqrtdet) / (2.0f*a);
    float farPt = (-b + sqrtdet) / (2.0f*a);
    
    if (farPt < 0.0f)
    {
        *intersectPt2 = NAN;
        *intersectPt1 = NAN;
        return;
    }
    *intersectPt1 = farPt;
    
    // inside sphere
    if ( nearPt < 0.0f)
    {
        *intersectPt1 = NAN;
    }
    *intersectPt2 = nearPt;
    
}

// determines the normal for a point in a triangle
ATVector3D ATSphere::pointNormal(ATVector3D point) const
{
    ATVector3D normal = ATVector3D::normalize(ATVector3D::subtractTwoVectors(point, origin));
    return normal;
}

// gets the color of the sphere
ATColor ATSphere::getColor() const
{
    return color;
}