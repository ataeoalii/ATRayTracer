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
    
    return 0;
}

// traces rays across the scene and saves them in the raster
void raytraceScene(ATScene& scene, ATRaster3D& raster)
{
    ATVector3D rayOrigin = scene.eyePt;    
    ATVector3D screenCenter = scene.spotPt;
    ATVector3D screenU = ATVector3D(1.0f, 0.0f, 0.0f);
    ATVector3D screenV = ATVector3D(0.0f, 1.0f, 0.0f);
    
    for(unsigned int shapeNum = 0; shapeNum < scene.getShapes().size(); shapeNum++)
    {
        ATColor col = scene.getShapes()[shapeNum]->getColor();
        ATLight light = scene.getLights()[0];
    
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
                float int2 = NAN;
            
                scene.getShapes()[shapeNum]->intersect(ray, &int1, &int2);
                
            
                if(!isnan(int1) || !isnan(int2))
                {
                    ATColor color = ATColor::multiply(scene.getShapes()[shapeNum]->getColor(), scene.ambientColor);
                    ATVector3D intersectPt = ray.calculatePoint(int1);
                    ATVector3D normal = scene.getShapes()[shapeNum]->pointNormal(intersectPt);
                    ATVector3D lightVector = ATVector3D::normalize(ATVector3D::subtractTwoVectors(light.position, intersectPt));
                    
                    
                    float contribution = ATVector3D::dot(lightVector, normal);
                    if (contribution < 0.0f)
                        contribution = 0.0f;
                    ATColor diffuseColor = ATColor::multiply(col, light.color);
                    diffuseColor.scaleColor(contribution);
                    diffuseColor.clampColor();
                    color = ATColor::addTwoColors(color, diffuseColor);
                    
                    raster.setPixel(y*raster.width + x, color);
                }

            }
        }
    }
    
}

