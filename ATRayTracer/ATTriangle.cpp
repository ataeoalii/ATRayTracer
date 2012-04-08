#include "ATTriangle.h"

// Constructor without color given.
ATTriangle::ATTriangle(ATVector3D v1, ATVector3D v2, ATVector3D v3)
{
	vertA = v1;
	vertB = v2;
	vertC = v3;
    
    color = ATColor(1.0f, 1.0f, 0.0f, 1.0f);
}

// Constructor with color
ATTriangle::ATTriangle(ATVector3D v1, ATVector3D v2, ATVector3D v3, ATColor col)
{
	vertA = v1;
	vertB = v2;
	vertC = v3;

	color = col;
}

// Copy constructor
ATTriangle::ATTriangle(const ATTriangle &copy)
{
	vertA = copy.vertA;
	vertB = copy.vertB;
	vertC = copy.vertC;
    
	color = copy.color;
}


// Default constructor.
ATTriangle::ATTriangle()
{
	vertA = ATVector3D();
	vertB = ATVector3D();
	vertC = ATVector3D();
    
    color = ATColor(1.0f, 1.0f, 0.0f, 1.0f);
}

// destructor
ATTriangle::~ATTriangle()
{
    
}

// determines where a ray intersects a triangle
void ATTriangle::intersect(ATRay ray, float *intersectPt1, float *intersectPt2) const
{
    // TODO: implement this   
}

// determines the normal for a point in a triangle
ATVector3D ATTriangle::pointNormal(ATVector3D point) const
{ 
    return ATVector3D::normalize(ATVector3D::crossProduct(vertA, vertB));
}

ATColor ATTriangle::getColor() const
{
    return color;
}