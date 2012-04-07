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