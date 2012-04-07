//
//  ATShape.h
//  ATRayTracer
//
//  Created by Andrew Taeoalii on 4/7/12.
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#ifndef ATRayTracer_ATShape_h
#define ATRayTracer_ATShape_h
class ATShape
{
private:
    // 0 - sphere, 1 - plane, 2 - triangle
    int shapeNum;
    
public:
    ATShape();
    ~ATShape();
    
};
#endif
