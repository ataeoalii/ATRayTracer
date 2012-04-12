//
//  ATPlane.h
//  ATRayTracer
//
//  Created by Andrew Taeoalii on 4/7/12.
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#ifndef ATRayTracer_ATPlane_h
#define ATRayTracer_ATPlane_h
#include "ATShape.h"
#include "ATVector3D.h"
#include "ATColor.h"
#include "ATRay.h"
#include <math.h>

class ATPlane : public ATShape
{
public:
    ATVector3D origin;
    ATVector3D normal;
    ATColor color;
    
    ATPlane();
    ATPlane(ATVector3D o, ATVector3D n, ATColor c);
    ATPlane(const ATPlane& copy);
    ~ATPlane();
    
    virtual void intersect(ATRay ray, float* intersectPt1, float* intersectPt2) const;
    
    virtual ATVector3D pointNormal(ATVector3D point) const;
    
    virtual ATColor getColor() const;
};


#endif
