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
    
    char magNum[10];
    int width, height;
    float eyeX, eyeY, eyeZ;
    float spotX, spotY, spotZ;
    float upX, upY, upZ;
    float fovy, aspectRatio;
    float ambientRed, ambientGreen, ambientBlue;
    
    fscanf(file, "%s", &magNum);
    fscanf(file, "%d %d", &width, &height);
    fscanf(file, "%f %f %f", &eyeX, &eyeY, &eyeZ);
    fscanf(file, "%f %f %f", &spotX, &spotY, &spotZ);
    fscanf(file, "%f %f %f", &upX, &upY, &upZ);
    fscanf(file, "%f %f", &fovy, &aspectRatio);
    fscanf(file, "%f %f %f", &ambientRed, &ambientGreen, &ambientBlue);
    
    printf("%s\n", magNum);
    printf("width:%d height:%d\n", width, height);
    printf("eyeX:%f eyeY:%f eyeZ:%f\n", eyeX, eyeY, eyeZ);
    printf("spotX:%f spotY:%f spotZ:%f\n", spotX, spotY, spotZ);
    printf("upX:%f upY:%f upZ:%f\n", upX, upY, upZ);
    printf("fovy:%f, aspectRatio:%f\n", fovy, aspectRatio);
    printf("Color: %f %f %f", ambientRed, ambientGreen, ambientBlue);
    
    char nextPiece;
    while(fscanf(file, "%c", &nextPiece)!=EOF)
    {
        // l x y z r g b - Identiﬁes a point light source
        if(nextPiece=='l')
        {
            float x, y, z;
            float r, g, b;
            fscanf(file, "%f %f %f %f %f %f", &x, &y, &z, &r, &g, &b);
            
            lights.push_back(ATLight(ATVector3D(x,y,z), ATColor(r,g,b,1.0f)));
        }
        // s x y z radius r g b - Identiﬁes a sphere with a center point (x,y,z) and a radius
        else if(nextPiece=='s')
        {
            
        }
        // p x y z nx ny nz r g b - Identiﬁes a plane deﬁned by a point on the plane (x,y,z) and a normal to the plane (nx, ny, nz).
        else if(nextPiece=='p')
        {
            
        }
        // t x1 y1 z1 x2 y2 z2 x3 y3 z3 r g b - Identiﬁes a triangle deﬁned by three points in space, (x1,y1,z1), (x2,y2,z2), (x3,y3,z3).
        else if(nextPiece=='t')
        {
            float x1, y1, z1, x2, y2, z2, x3, y3, z3;
            float r, g, b;
            fscanf(file, "%f %f %f %f %f %f %f %f %f %f %f %f", &x1, &y1, &z1, &x2, &y2, &z2, &x3, &y3, &z3, &r, &g, &b);
            
            // shapes.push_back(ATTriangle(ATVector3D(x1, y1, z1), ATVector3D(x1, y1, z1), ATVector3D(x1, y1, z1), ATColor(1.0f, r, g, b)));
            
            
        }
        // ignore
        else 
        {
            printf("skipping line, bad char received: %c", nextPiece);
        }
    }
    
}