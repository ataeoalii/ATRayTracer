#include "ATVector3D.h"
#include <math.h>

// default constructor
ATVector3D::ATVector3D()
{
	x = 0;
	y = 0;
	z = 1;
}

// gen purpose constructor
ATVector3D::ATVector3D(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

// copy constructor
ATVector3D::ATVector3D(const ATVector3D &copy)
{
	x = copy.x;
	y = copy.y;
	z = copy.z;
}

// destructor
ATVector3D::~ATVector3D()
{
    
}

// adds a vector to this vector
void ATVector3D::addVector(ATVector3D atv)
{
	x+=atv.x;
	y+=atv.y;
    z+=atv.z;
}

// Multiplies the given vector by a scalar
void ATVector3D::scaleVector(float scalar)
{
	x*=scalar;
	y*=scalar;
	z*=scalar;
}


// Returns the addition of two vectors
ATVector3D ATVector3D::addTwoVectors(ATVector3D atv1, ATVector3D atv2)
{
	ATVector3D vec(atv1.x + atv2.x, atv1.y + atv2.y, atv1.z + atv2.z);
	return vec;
}

// Returns the subtraction of two vectors
 ATVector3D ATVector3D::subtractTwoVectors(ATVector3D atv1, ATVector3D atv2)
 {
	 float xa = atv1.x - atv2.x;
	 float ya = atv1.y - atv2.y;
	 float za = atv1.z - atv2.z;

	 ATVector3D atv(xa, ya, za);
	 return atv;
 }

// Returns the cross product vector of two vectors
ATVector3D ATVector3D::crossProduct(ATVector3D atv1, ATVector3D atv2)
{
	float xa = atv1.y*atv2.z - atv1.z*atv2.y;
	float ya = atv1.z*atv2.x - atv1.x*atv2.z;
	float za = atv1.x*atv2.y - atv1.y*atv2.x;
	ATVector3D atv(xa, ya, za);

	return atv;
}

// Returns the normalized version of the vector
ATVector3D ATVector3D::normalize(ATVector3D atv)
{
	float magnitude = sqrtf((atv.x*atv.x) + (atv.y*atv.y) + (atv.z*atv.z));
	ATVector3D atvA(atv.x/magnitude, atv.y/magnitude, atv.z/magnitude);
	return atvA;
}

float ATVector3D::dot(ATVector3D atv1, ATVector3D atv2)
{
    float fl = atv1.x * atv2.x + atv1.y * atv2.y + atv1.z * atv2.z ;
    return fl;
}
