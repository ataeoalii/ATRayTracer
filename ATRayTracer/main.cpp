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
    char *path=NULL;
    size_t size = 0;
    path=getcwd(path,size);
    cout<<"\n current Path"<<path << endl;
    
    ATScene ats;
    ats.readInScene("scene.urt");
    
    ATRaster3D raster(ats.width, ats.height);
    
    raytraceScene(ats, raster);

    ATRaster3D::saveToBMP(raster.rasterPixels, raster.width, raster.height, (char*)"scene.bmp");
    ATRaster3D::saveToPPM(raster.rasterPixels, raster.width, raster.height, (char*)"scene.ppm");
    return 0;
}


float planeEquationGetZ(ATVector3D normal, ATVector3D point, float x, float y)
{
    
   return point.z - ((normal.x *(x - point.x) + normal.y*(y - point.y)) / normal.z) ;
    
}

// traces rays across the scene and saves them in the raster
void raytraceScene(ATScene& scene, ATRaster3D& raster)
{
    ATVector3D rayOrigin = scene.eyePt;    
    ATVector3D screenCenter = scene.spotPt;
    
    ATVector3D lookAt = ATVector3D::subtractTwoVectors(screenCenter, rayOrigin);
    
    ATVector3D screenU = ATVector3D::normalize(ATVector3D::crossProduct(scene.upVector, lookAt));
    
    ATVector3D screenV = ATVector3D::normalize(ATVector3D::crossProduct(screenU, lookAt));
    
    screenV.scaleVector(ATVector3D::magnitude(lookAt) * tanf(scene.fovy*0.5f));
    
    screenU.scaleVector(-1.0f * scene.aspectRatio * ATVector3D::magnitude(screenV));
    
    printf("lookat: %f %f %f\nscreenU: %f %f %f\nscreenV: %f %f %f\n", lookAt.x, lookAt.y, lookAt.z, screenU.x, screenU.y, screenU.z, screenV.x, screenV.y, screenV.z);
    
    
    for(int y = 0; y < raster.height; y++)
    {
        for(int x = 0; x < raster.width; x++)
        {
                
            ATVector3D u = screenU;
            u.scaleVector((float)x / (float)raster.width * 2.0f - 1.0f);
            
            ATVector3D v = screenV;
            v.scaleVector((float)y / (float)raster.height * 2.0f - 1.0f);
                
            ATVector3D rayDirection = ATVector3D::addTwoVectors(lookAt, ATVector3D::addTwoVectors(u, v));
                
            ATRay ray(rayOrigin, rayDirection);
            
            float int1 = NAN;
            ATShape* nearestShape = scene.sceneIntersect(ray, NULL, &int1);
                
            if(!isnan(int1) && nearestShape!=NULL)
            {
                
                ATColor color = ATColor::multiply(nearestShape->getColor(), scene.ambientColor);
                ATVector3D intersectPt = ray.calculatePoint(int1);
                ATVector3D normal = nearestShape->pointNormal(intersectPt);
                
                
                ATColor diffuseColor(1.0f, 0.0f, 0.0f);
                
                for(unsigned long lightIdx=0; lightIdx<scene.getLights().size(); lightIdx++)
                {
                    ATLight light = scene.getLights()[lightIdx];
                    ATVector3D lightVector = ATVector3D::normalize(ATVector3D::subtractTwoVectors(light.position, intersectPt));
                    
                    /*****SHADOWING******/
                    ATVector3D lightOrigin = intersectPt;
                    
                    // get direction pointing towards the light
                    ATVector3D lightDirection = ATVector3D::normalize(ATVector3D::subtractTwoVectors(light.position, lightOrigin));
                    ATRay lightRay(lightOrigin, lightDirection);
                        
                    float shadowPt = NAN;
                    ATShape *obstructShape = scene.sceneIntersect(lightRay, nearestShape, &shadowPt);
                    
                    if(obstructShape==NULL)
                    {
                        float contribution = ATVector3D::dot(lightVector, normal);
                        if (contribution < 0.0f)
                            contribution = 0.0f;
                        diffuseColor = ATColor::multiply(nearestShape->getColor(), light.color);
                        diffuseColor.scaleColor(contribution);
                        diffuseColor.clampColor();
                        color = ATColor::addTwoColors(color, diffuseColor);
                        color.clampColor();
                    }
                }
                    
                color.clampColor();
                    
                raster.setPixel(y*raster.width + x, color);
                   
            }
        }
    }
}

