//
//  ATRay.cpp
//  ATRayTracer
//
//  Created by Andrew Taeoalii on 4/7/12.
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#include "ATRay.h"

// default constructor
ATRay::ATRay()
{
    origin = ATVector3D(0.0f, 0.0f, 0.0f);
    direction = ATVector3D(0.0f, 0.0f, 1.0f);
}

// gen. purpose constructor
ATRay::ATRay(ATVector3D o, ATVector3D d)
{
    origin = o;
    direction = d;
}

// Copy constructor
ATRay::ATRay(const ATRay& copy)
{
    origin = copy.origin;
    direction = copy.direction;
}

// destructor
ATRay::~ATRay()
{
    
}

// calculates where on the ray a point is
ATVector3D ATRay::calculatePoint(float t)
{
    ATVector3D dir = direction;
    dir.scaleVector(t);
    return ATVector3D::addTwoVectors(origin, dir);
}