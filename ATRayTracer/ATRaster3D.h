#ifndef _ATRaster3D_H_
#define _ATRaster3D_H_
#include "ATColor.h"
#include "ATVector3D.h"
#include "ATLight.h"
#include "ATScene.h"
#include <stdint.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <math.h>
#include <float.h>

using namespace std;

class ATTriangleGroup;
class ATScene;


class ATRaster3D
{

public:
    int width, height, size;
	ATColor* rasterPixels;
	float* depths;
	ATRaster3D();
	ATRaster3D(const ATRaster3D &copy);
	~ATRaster3D();
	ATRaster3D(int _width, int _height);

	
	float getDepth(unsigned int index);
	
	void setDepth(unsigned int index, float value);

	void setPixel(int index, ATColor color);
	ATColor getPixel(int index);

	void blendPixel(int index, ATColor color, float alpha);

	static void GetBarycentricCoordinates(ATVector3D vect, ATVector3D atv1, ATVector3D atv2, ATVector3D atv3, float* lambda1, float* lambda2, float* lambda3);

	static void saveToPPM(ATColor pixels[], int width, int height, char* path);

	static void saveToBMP(ATColor pixels[], int width, int height, char* path);

};
#endif