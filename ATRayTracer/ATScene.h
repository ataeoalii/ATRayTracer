//
//  ATScene.h
//  ATRayTracer
//
//  Created by Andrew Taeoalii on 4/6/12.
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#ifndef ATRayTracer_ATScene_h
#define ATRayTracer_ATScene_h
#include <string>
#include <vector>
#include "ATLight.h"
#include "ATShape.h"
using namespace std;

class ATScene
{
private:
    vector<ATLight> lights;
    vector<ATShape> shapes;
    
public:
    ATScene();
    ~ATScene();
    void readInScene(string filename);
};
#endif
