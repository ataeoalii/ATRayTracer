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

	int getHeight();
	int getWidth();
	ATColor* getPixels();
	
	float* getDepths();
	
	float getDepth(unsigned int index);
	
	void setDepth(unsigned int index, float value);

	void setPixel(int index, ATColor color);
	ATColor getPixel(int index);

	void blendPixel(int index, ATColor color, float alpha);



	static void GetBarycentricCoordinates(ATVector3D vect, ATVector3D atv1, ATVector3D atv2, ATVector3D atv3, float* lambda1, float* lambda2, float* lambda3);


	static void ATSaveToPPM(ATColor pixels[], int width, int height, char* path);

	static void ATSaveToBMP(ATColor pixels[], int width, int height, char* path);

	static ATColor calculateColor(ATColor ambientColor, ATColor materialColor, ATColor specularColor, const vector<ATLight> &lights,
								ATVector3D normal, ATVector3D point, float shininess);

	static void PhongInterpolateTriangle(ATRaster3D* raster, ATColor ambientColor, ATColor materialColor, ATColor specularColor, const vector<ATLight> &lights, int minX, int maxX, int minY, int maxY, float alpha, float shininess);

	static void PhongInterpolateScene(ATRaster3D* raster, ATScene &scene, ATColor ambientColor);


};
#endif