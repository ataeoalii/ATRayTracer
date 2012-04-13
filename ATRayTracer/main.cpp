//
//  main.cpp
//  ATRayTracer
//
//  Created by Andrew Taeoalii on 4/6/12.
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#include <iostream>
#include "ATScene.h"
#include "ATRaster3D.h"

void raytraceScene(ATScene&, ATRaster3D&);

int main(int argc, const char * argv[])
{
    ATScene ats;
    ats.readInScene("test.txt");
    
    ATRaster3D raster(ats.width, ats.height);
    
    raytraceScene(ats, raster);

    ATRaster3D::saveToBMP(raster.rasterPixels, raster.width, raster.height, (char*)"boto.bmp");
    ATRaster3D::saveToPPM(raster.rasterPixels, raster.width, raster.height, (char*)"boto.ppm");
    return 0;
}

// traces rays across the scene and saves them in the raster
void raytraceScene(ATScene& scene, ATRaster3D& raster)
{
    ATVector3D rayOrigin = scene.eyePt;    
    ATVector3D screenCenter = scene.spotPt;
    
    ATVector3D lookAt = ATVector3D::subtractTwoVectors(screenCenter, rayOrigin);
    ATVector3D screenV = ATVector3D::normalize(ATVector3D::crossProduct(lookAt, scene.upVector));
    ATVector3D screenU = ATVector3D::normalize(ATVector3D::crossProduct(lookAt, screenV));
    for(int y = 0; y < raster.height; y++)
    {
        for(int x = 0; x < raster.width; x++)
        {
                
            ATVector3D u = screenU;
            u.scaleVector((float)x / (float)raster.width * 2.0f - 1.0f);
            
            ATVector3D v = screenV;
            v.scaleVector((float)y / (float)raster.height * 2.0f - 1.0f);
                
            ATVector3D rayDirection = ATVector3D::addTwoVectors(screenCenter, ATVector3D::addTwoVectors(u, v));
                
            ATRay ray(rayOrigin, rayDirection);
            
            float int1 = NAN;
            ATShape* nearestShape = scene.sceneIntersect(ray, NULL, &int1);
                
            if(!isnan(int1) && nearestShape!=NULL)
            {
                ATLight light = scene.getLights()[0];
                ATColor color = ATColor::multiply(nearestShape->getColor(), scene.ambientColor);
                ATVector3D intersectPt = ray.calculatePoint(int1);
                ATVector3D normal = nearestShape->pointNormal(intersectPt);
                ATVector3D lightVector = ATVector3D::normalize(ATVector3D::subtractTwoVectors(light.position, intersectPt));
                    
                    
                float contribution = ATVector3D::dot(lightVector, normal);
                if (contribution < 0.0f)
                    contribution = 0.0f;
                    
                // get point on object to cast ray to light
                ATVector3D lightOrigin = ray.direction;
                lightOrigin.scaleVector(int1);
                lightOrigin = ATVector3D::addTwoVectors(ray.origin, lightOrigin);
                    
                // get direction pointing towards the light
                ATVector3D lightDirection = ATVector3D::subtractTwoVectors(light.position, lightOrigin);
                ATRay lightRay(lightOrigin, lightDirection);
                    
                float shadowPt = NAN;
                ATShape *obstructShape = scene.sceneIntersect(lightRay, nearestShape, &shadowPt);
                    
                if(isnan(shadowPt) || obstructShape==NULL)
                {
                    ATColor diffuseColor = ATColor::multiply(nearestShape->getColor(), light.color);
                    diffuseColor.scaleColor(contribution);
                    diffuseColor.clampColor();
                    color = ATColor::addTwoColors(color, diffuseColor);
                }
                    
                color.clampColor();
                    
                raster.setPixel(y*raster.width + x, color);
                   
            }
        }
    }
}

