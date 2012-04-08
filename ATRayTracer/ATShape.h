//
//  ATShape.h
//  ATRayTracer
//
//  Created by Andrew Taeoalii on 4/7/12.
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#ifndef ATRayTracer_ATShape_h
#define ATRayTracer_ATShape_h

#include "ATRay.h"
#include "ATColor.h"
#include <iostream>

class ATShape
{
public:
    virtual void intersect(ATRay ray, float* intersectPt1, float* intersectPt2) const = 0;
    virtual ATVector3D pointNormal(ATVector3D point) const = 0;
    virtual ATColor getColor() const = 0;
    
    
};
#endif
