//
//  ATRay.h
//  ATRayTracer
//
//  Created by Andrew Taeoalii on 4/7/12.
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#ifndef ATRayTracer_ATRay_h
#define ATRayTracer_ATRay_h
#include "ATVector3D.h"

class ATRay
{
public:
    ATVector3D origin;
    ATVector3D direction;
    
    ATRay();
    ATRay(ATVector3D o, ATVector3D d);
    ATRay(const ATRay& copy);
    ~ATRay();
    
    ATVector3D calculatePoint(float t);
};

#endif
