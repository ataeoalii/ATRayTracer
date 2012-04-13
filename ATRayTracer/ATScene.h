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
#include "ATTriangle.h"
#include "ATPlane.h"
#include "ATSphere.h"
#include "ATRay.h"
#include "ATVector3D.h"
#include "ATColor.h"

using namespace std;

class ATScene
{
private:
    vector<ATLight> lights;
    vector<ATShape*> shapes;
    
public:
    int width, height;
    ATVector3D eyePt;
    ATVector3D spotPt;
    ATVector3D upVector;
    float fovy, aspectRatio;
    ATColor ambientColor;
    
    
    ATScene();
    ~ATScene();
    void readInScene(string filename);
    vector<ATLight> getLights() const;
    vector<ATShape*> getShapes() const;
    
    void addLight(ATLight light);
    void addShape(ATShape shape);
    
    void clearLights();
    void clearShapes();
    
    ATShape* sceneIntersect(ATRay ray, ATShape* startingShape, float* intersectionPt);
};
#endif
