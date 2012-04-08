//
//  ATSphere.h
//  ATRayTracer
//
//  Created by Andrew Taeoalii on 4/7/12.
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#ifndef ATRayTracer_ATSphere_h
#define ATRayTracer_ATSphere_h
#include "ATShape.h"
#include "ATVector3D.h"
#include "ATColor.h"
#include <math.h>

class ATSphere : public ATShape
{
    
public:
    float radius;
    ATVector3D origin;
    ATColor color;
    
    ATSphere();
    ATSphere(float rad, ATVector3D o, ATColor col);
    ATSphere(const ATSphere& copy);
    ~ATSphere();
    
    virtual void intersect(ATRay ray, float* intersectPt1, float* intersectPt2) const;
    
    virtual ATVector3D pointNormal(ATVector3D point) const;
    
    virtual ATColor getColor() const;
};

#endif
