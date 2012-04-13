//
//  ATScene.cpp
//  ATRayTracer
//
//  Created by Andrew Taeoalii on 4/6/12.
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#include "ATScene.h"

// default constructor
ATScene::ATScene()
{
    
}

// destructor
ATScene::~ATScene()
{
    
}

// reads in a scene file
void ATScene::readInScene(string filename)
{
    FILE *file;
    file = fopen(filename.c_str(), "r");
    
    if((filename.substr(filename.length()-3))!="xml")
    {
        printf("Warning: Incompatible Filetype - %s\n", filename.c_str());
    }
    
    printf("reading in file %s\n", filename.c_str());
    
    char magNum[3];
    float eyeX, eyeY, eyeZ;
    float spotX, spotY, spotZ;
    float upX, upY, upZ;
    float ambientRed, ambientGreen, ambientBlue;
    
    fscanf(file, "%s", &magNum);
    fscanf(file, "%d %d", &width, &height);
    
    fscanf(file, "%f %f %f", &eyeX, &eyeY, &eyeZ);
    eyePt = ATVector3D(eyeX, eyeY, eyeZ);
    
    fscanf(file, "%f %f %f", &spotX, &spotY, &spotZ);
    spotPt = ATVector3D(spotX, spotY, spotZ);
    
    fscanf(file, "%f %f %f", &upX, &upY, &upZ);
    upVector = ATVector3D(upX, upY, upZ);
    
    fscanf(file, "%f %f", &fovy, &aspectRatio);
    
    fscanf(file, "%f %f %f", &ambientRed, &ambientGreen, &ambientBlue);
    ambientColor = ATColor(ambientRed, ambientGreen, ambientBlue);
    
    printf("%s\n", magNum);
    printf("width:%d height:%d\n", width, height);
    printf("eyeX:%f eyeY:%f eyeZ:%f\n", eyePt.x, eyePt.y, eyePt.z);
    printf("spotX:%f spotY:%f spotZ:%f\n", spotPt.x, spotPt.y, spotPt.z);
    printf("upX:%f upY:%f upZ:%f\n", upVector.x, upVector.y, upVector.z);
    printf("fovy:%f, aspectRatio:%f\n", fovy, aspectRatio);
    printf("Color: r:%f g:%f b:%f a:%f\n", ambientColor.getredF(), ambientColor.getgreenF(), ambientColor.getblueF(), ambientColor.getalphaF());
    
    char nextPiece;
    while(fscanf(file, "%c", &nextPiece)!=EOF)
    {
        // l x y z r g b - Identiﬁes a point light source
        if(nextPiece=='l')
        {
            float x, y, z;
            float r, g, b;
            fscanf(file, "%f %f %f %f %f %f", &x, &y, &z, &r, &g, &b);
            
            ATLight light(ATVector3D(x,y,z), ATColor(r,g,b));
            
            lights.push_back(light);
            
            printf("Created light - \nposition: %f %f %f\ncolor: %f %f %f %f\n", light.position.x, light.position.y, light.position.z, light.color.getredF(), light.color.getgreenF(), light.color.getblueF(), light.color.getalphaF());
        }
        // s x y z radius r g b - Identiﬁes a sphere with a center point (x,y,z) and a radius
        else if(nextPiece=='s')
        {
            float x, y, z;
            float rad, r, g, b;
            fscanf(file, "%f %f %f %f %f %f %f", &x, &y, &z, &rad, &r, &g, &b);
            
            ATSphere* sphere = new ATSphere(rad, ATVector3D(x, y, z), ATColor(r,g,b));
            
            shapes.push_back(sphere);
            
            printf("Created sphere - radius: %f\norigin: %f %f %f\ncolor: %f %f %f %f\n", sphere->radius, sphere->origin.x, sphere->origin.y, sphere->origin.z, sphere->color.getredF(), sphere->color.getgreenF(), sphere->color.getblueF(), sphere->color.getalphaF());
        }
        // p x y z nx ny nz r g b - Identiﬁes a plane deﬁned by a point on the plane (x,y,z) and a normal to the plane (nx, ny, nz).
        else if(nextPiece=='p')
        {
            float x, y, z, nx, ny, nz;
            float r, g, b;
            fscanf(file, "%f %f %f %f %f %f %f %f %f", &x, &y, &z, &nx, &ny, &nz, &r, &g, &b);
            
            ATPlane* plane = new ATPlane(ATVector3D(x, y, z), ATVector3D(nx, ny, nz), ATColor(r,g,b));
            
            shapes.push_back(plane);
            
            
            printf("Created plane - \norigin: %f %f %f \nnormal: %f %f %f\ncolor: %f %f %f %f\n", plane->origin.x, plane->origin.y, plane->origin.z, plane->normal.x, plane->normal.y, plane->normal.z, plane->color.getredF(), plane->color.getgreenF(), plane->color.getblueF(), plane->color.getalphaF());
            
        }
        // t x1 y1 z1 x2 y2 z2 x3 y3 z3 r g b - Identiﬁes a triangle deﬁned by three points in space, (x1,y1,z1), (x2,y2,z2), (x3,y3,z3).
        else if(nextPiece=='t')
        {
            float x1, y1, z1, x2, y2, z2, x3, y3, z3;
            float r, g, b;
            fscanf(file, "%f %f %f %f %f %f %f %f %f %f %f %f", &x1, &y1, &z1, &x2, &y2, &z2, &x3, &y3, &z3, &r, &g, &b);
            
            ATTriangle* triangle = new ATTriangle(ATVector3D(x1, y1, z1), ATVector3D(x2, y2, z2), ATVector3D(x3, y3, z3), ATColor(r, g, b));
            
            shapes.push_back(triangle);
            
            
            printf("Created triangle - \nVertexA: %f %f %f\nVertexB: %f %f %f\nVertexC: %f %f %f\ncolor: %f %f %f %f\n", triangle->vertA.x, triangle->vertA.y, triangle->vertA.z, triangle->vertB.x, triangle->vertB.y, triangle->vertB.z, triangle->vertC.x, triangle->vertC.y, triangle->vertC.z, triangle->color.getredF(), triangle->color.getgreenF(), triangle->color.getblueF(), triangle->color.getalphaF());
            
            
        }
        // ignore
        else 
        {
            printf("skipping line, bad char received: %c\n", nextPiece);
        }
    }
    
}

// returns all lights in the scene in a vector
vector<ATLight> ATScene::getLights() const
{
    return lights;
}

// returns all shapes in the scene in a vector
vector<ATShape*> ATScene::getShapes() const
{
    return shapes;
}

// adds a light to the end of the vector of lights
void ATScene::addLight(ATLight light)
{
    
}

// adds a shape to the end of the vector of shapes
void ATScene::addShape(ATShape shape)
{
    shapes.push_back(&shape);
}

// clears all the lights from the scene
void ATScene::clearLights()
{
    lights.clear();
}

// clears all the shapes from the scene
void ATScene::clearShapes()
{
    shapes.clear();
}

// iterates through all objects in the scene and finds where the nearest intersection point is on the ray and
// returns the nearest shape for that pixel/ray combination.
ATShape* ATScene::sceneIntersect(ATRay ray, ATShape* startingShape, float* intersectionPt)
{
    if(shapes.size() == 0)
        return NULL;
    ATShape *currentShape = shapes.at(0);
    float temp2 = NAN;
    
    currentShape->intersect(ray, intersectionPt, &temp2);
    float tempIntersectPt = NAN;
    
    for(unsigned int i=1; i < shapes.size(); i++)
    {
        (shapes.at(i))->intersect(ray, &tempIntersectPt, &temp2);
        if (!isnan(tempIntersectPt) && tempIntersectPt > 0.0f)
        {
            if(isnan(*intersectionPt))
            {
                *intersectionPt = tempIntersectPt;
                currentShape = shapes.at(i);
            }
            else if(tempIntersectPt < *intersectionPt)
            {
                *intersectionPt = tempIntersectPt;
                currentShape = shapes.at(i); 
            }
        }
    }
    
    if (currentShape==startingShape)
        return NULL;
    return currentShape;
    
}